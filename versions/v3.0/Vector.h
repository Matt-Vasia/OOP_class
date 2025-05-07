#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstddef>      // size_t, ptrdiff_t
#include <stdexcept>    // std::out_of_range, std::length_error
#include <iterator>     // std::reverse_iterator, iterator tags
#include <memory>       // std::uninitialized_copy, std::uninitialized_fill_n, std::destroy_n (C++17) / manual loop
#include <utility>      // std::move, std::swap, std::forward
#include <initializer_list>
#include <algorithm>    // std::lexicographical_compare, std::equal, std::max
#include <limits>       // std::numeric_limits
#include <type_traits>  // std::is_nothrow_move_constructible, etc. (for potential optimization)

// Helper function to destroy elements (needed before C++17's std::destroy_n)
template <typename T>
void destroy_range(T* first, T* last) {
    while (first != last) {
        first->~T();
        ++first;
    }
}

template <typename T>
class Vector {
public:
    // --- Member Types ---
    using value_type             = T;
    using pointer                = T*;
    using const_pointer          = const T*;
    using reference              = T&;
    using const_reference        = const T&;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;

    // --- Iterators ---
    // Simple pointer-based iterators
    using iterator               = T*;
    using const_iterator         = const T*;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

// --- Member Variables ---
private:
    pointer data_     = nullptr; // Pointer to the beginning of the allocated buffer
    size_type size_     = 0;     // Number of elements currently stored
    size_type capacity_ = 0;     // Total capacity of the allocated buffer
    static inline int memory_realocated = 0;

    // --- Private Helper Functions ---

    // Reallocates memory, moving existing elements. Strong exception guarantee desirable here.
    // For simplicity, this version offers basic guarantee (vector state might change on exception).
    void reallocate(size_type new_capacity) {
        if (new_capacity <= capacity_) return; // Should generally not happen if called correctly

        // Use plain ::operator new to avoid potential T::operator new overloads interfering
        // Allocate raw memory first
        pointer new_data = static_cast<pointer>(::operator new(new_capacity * sizeof(value_type)));

        // Move elements (or copy if move is not noexcept or not available)
        // Use uninitialized_move for potential performance gains and correctness
        // If move construction can throw, we might prefer copying or need more complex handling.
        // Let's simplify here and use move if possible, copy otherwise (basic guarantee).
        size_type elements_to_move = size_;
        try {
             if constexpr (std::is_nothrow_move_constructible_v<value_type>) {
                 std::uninitialized_move(data_, data_ + size_, new_data);
             } else {
                 std::uninitialized_copy(data_, data_ + size_, new_data); // Fallback to copy
             }
        } catch (...) {
            ::operator delete(new_data); // Clean up allocated memory on exception
            throw; // Re-throw the exception
        }


        // Destroy old elements (if any)
        destroy_range(data_, data_ + size_);

        // Deallocate old memory
        ::operator delete(data_);

        // Update members
        data_ = new_data;
        capacity_ = new_capacity;
        // size_ remains the same
    }

    // Calculates recommended new capacity (common strategy: double or 1.5x)
    size_type calculate_growth(size_type min_capacity) const {
        // Handle initial allocation and avoid overflow
        if (capacity_ > max_size() / 2) {
            return max_size();
        }
        return std::max(min_capacity, capacity_ + capacity_ / 2); // ~1.5x growth, minimum min_capacity
        // Or simpler doubling: return std::max(min_capacity, capacity_ == 0 ? 1 : capacity_ * 2);
    }

    // Destroys elements and deallocates memory
    void clear_and_deallocate() {
        if (data_) {
            destroy_range(data_, data_ + size_); // Destroy elements
            ::operator delete(data_);            // Deallocate buffer
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
        }
    }


public:
    // --- Constructors ---

    // Default constructor
    Vector() noexcept = default; // data_, size_, capacity_ already initialized to 0/nullptr

    // Fill constructor (count default-inserted elements)
    explicit Vector(size_type count) : size_(count), capacity_(count) {
        if (count > max_size()) throw std::length_error("Vector(count): count exceeds max_size()");
        if (count == 0) return; // data_ remains nullptr
        data_ = static_cast<pointer>(::operator new(count * sizeof(value_type)));
        try {
            std::uninitialized_value_construct_n(data_, count); // C++17: Default constructs
            // Pre-C++17 manual loop:
            // for(size_type i = 0; i < count; ++i) { ::new (static_cast<void*>(data_ + i)) value_type(); }
        } catch (...) {
            ::operator delete(data_);
            data_ = nullptr;
            capacity_ = 0;
            size_ = 0;
            throw;
        }
    }


    // Fill constructor (count copies of value)
    Vector(size_type count, const_reference value) : size_(count), capacity_(count) {
        if (count > max_size()) throw std::length_error("Vector(count, value): count exceeds max_size()");
         if (count == 0) return;
        data_ = static_cast<pointer>(::operator new(count * sizeof(value_type)));
        try {
            std::uninitialized_fill_n(data_, count, value); // Copies value count times
        } catch (...) {
            ::operator delete(data_);
            data_ = nullptr;
            capacity_ = 0;
            size_ = 0;
            throw;
        }
    }

    // Range constructor
    template <typename InputIt, typename = std::enable_if_t<
        std::is_base_of_v<std::input_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>
    >>
    Vector(InputIt first, InputIt last) {
        // Use reserve and push_back for input iterators
        // For random access iterators, could optimize by calculating distance first
        if constexpr (std::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>) {
           difference_type count = std::distance(first, last);
           if (count < 0) throw std::length_error("Vector range constructor: invalid range");
           size_type initial_size = static_cast<size_type>(count);
           if (initial_size > max_size()) throw std::length_error("Vector range constructor: range too large");
           if (initial_size == 0) return;

           data_ = static_cast<pointer>(::operator new(initial_size * sizeof(value_type)));
           capacity_ = initial_size;
           try {
               std::uninitialized_copy(first, last, data_);
               size_ = initial_size;
           } catch (...) {
                ::operator delete(data_);
                data_ = nullptr;
                capacity_ = 0;
                size_ = 0;
                throw;
           }
        } else {
            // Input iterator path (less efficient, uses push_back)
            for (; first != last; ++first) {
                push_back(*first); // push_back handles allocation
            }
        }
    }


    // Copy constructor
    Vector(const Vector& other) : size_(other.size_), capacity_(other.size_) { // Start with exact capacity
         if (other.size_ == 0) return;
        if (other.size_ > max_size()) throw std::length_error("Vector copy constructor: source size exceeds max_size()");
        data_ = static_cast<pointer>(::operator new(other.size_ * sizeof(value_type)));
        try {
            std::uninitialized_copy(other.data_, other.data_ + other.size_, data_);
        } catch (...) {
            ::operator delete(data_);
            data_ = nullptr;
            capacity_ = 0;
            size_ = 0;
            throw;
        }
    }

    // Move constructor
    Vector(Vector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
    {
        // Leave the moved-from object in a valid, empty state
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Initializer list constructor
    Vector(std::initializer_list<T> init) : Vector(init.begin(), init.end()) {} // Delegate to range constructor

    // --- Destructor ---
    ~Vector() {
        clear_and_deallocate();
    }

    // --- Assignment Operators ---

    // Copy assignment operator (Copy-and-swap idiom for strong guarantee)
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other); // Use copy constructor (handles allocation and copy)
            swap(temp);         // Swap internal state with the temporary
        }
        return *this;
    }

    // Move assignment operator
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            clear_and_deallocate(); // Destroy existing resources first

            // Steal resources from other
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            // Leave other in valid empty state
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Initializer list assignment
    Vector& operator=(std::initializer_list<T> ilist) {
        assign(ilist.begin(), ilist.end()); // Use assign method
        return *this;
    }

    // Assign (replace contents) - fill version
    void assign(size_type count, const T& value) {
        clear(); // Destroy existing elements but keep capacity if possible
        if (count > capacity_) {
            // Need to reallocate completely
             clear_and_deallocate(); // Get rid of old buffer
             if (count > max_size()) throw std::length_error("assign count exceeds max_size");
             data_ = static_cast<pointer>(::operator new(count * sizeof(value_type)));
             capacity_ = count;
        }
         // Now fill the (potentially new) buffer
        try {
            std::uninitialized_fill_n(data_, count, value);
            size_ = count;
        } catch (...) {
            // If reallocation happened and fill fails, we need to clean up
             if (capacity_ == count) { // Indicates we just allocated
                 ::operator delete(data_);
                 data_ = nullptr;
                 capacity_ = 0;
             }
             size_ = 0; // Ensure size is 0 even if buffer wasn't deallocated
             throw;
        }
    }


    // Assign (replace contents) - range version
    template <typename InputIt, typename = std::enable_if_t<
        std::is_base_of_v<std::input_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>
    >>
    void assign(InputIt first, InputIt last) {
        clear(); // Destroy existing elements, keep buffer if possible

        // Simple implementation: insert one by one
        // Could be optimized for random access iterators (calculate size, reserve, copy)
        for (; first != last; ++first) {
            push_back(*first); // push_back handles reallocation if needed
        }
    }

    // Assign (replace contents) - initializer list version
    void assign(std::initializer_list<T> ilist) {
        assign(ilist.begin(), ilist.end());
    }

    // --- Element Access ---

    int getMemory_realocated()
    {
        return memory_realocated;
    }

    // Access specified element with bounds checking
    reference at(size_type pos) {
        if (pos >= size_) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return data_[pos];
    }
    const_reference at(size_type pos) const {
        if (pos >= size_) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return data_[pos];
    }

    // Access specified element (no bounds checking)
    reference operator[](size_type pos) {
        // Assert(pos < size_); // Optional assert for debug builds
        return data_[pos];
    }
    const_reference operator[](size_type pos) const {
        // Assert(pos < size_); // Optional assert for debug builds
        return data_[pos];
    }

    // Access the first element
    reference front() {
        // Assert(!empty());
        return data_[0];
    }
    const_reference front() const {
        // Assert(!empty());
        return data_[0];
    }

    // Access the last element
    reference back() {
        // Assert(!empty());
        return data_[size_ - 1];
    }
    const_reference back() const {
        // Assert(!empty());
        return data_[size_ - 1];
    }

    // Direct access to the underlying array
    T* data() noexcept {
        return data_;
    }
    const T* data() const noexcept {
        return data_;
    }

    // --- Iterators ---

    iterator begin() noexcept {
        return data_;
    }
    const_iterator begin() const noexcept {
        return data_;
    }
    const_iterator cbegin() const noexcept {
        return data_;
    }

    iterator end() noexcept {
        return data_ + size_;
    }
    const_iterator end() const noexcept {
        return data_ + size_;
    }
    const_iterator cend() const noexcept {
        return data_ + size_;
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(cend());
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }
    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(cbegin());
    }

    // --- Capacity ---

    // Checks whether the container is empty
    bool empty() const noexcept {
        return size_ == 0;
    }

    // Returns the number of elements
    size_type size() const noexcept {
        return size_;
    }

    // Returns the maximum possible number of elements
    size_type max_size() const noexcept {
        // Theoretical limit based on size_t and pointer difference type
         return std::numeric_limits<difference_type>::max();
        // Practical limit considering memory allocation overhead might be slightly less
        // return std::numeric_limits<size_type>::max() / sizeof(value_type); // Another common approximation
    }


    // Increase the capacity of the vector (the total number of elements that the vector can hold without requiring reallocation)
    void reserve(size_type new_cap) {
        if (new_cap > max_size()) {
             throw std::length_error("Vector::reserve capacity exceeds max_size()");
        }
        if (new_cap > capacity_) {
            reallocate(new_cap);
        }
        // Note: reserve never shrinks capacity in std::vector
    }


    // Returns the number of elements that the container has currently allocated space for
    size_type capacity() const noexcept {
        return capacity_;
    }

    // Requests the removal of unused capacity
    void shrink_to_fit() {
        if (size_ < capacity_) {
            if (size_ == 0) {
                 clear_and_deallocate(); // Special case: become empty
            } else {
                 // Reallocate to exact size (or slightly more if needed)
                 // Note: reallocate requires moving elements, so it's not noexcept
                 Vector temp(std::move(*this)); // Move construct into temp (uses existing buffer)
                 temp.reallocate(size_);        // Reallocate temp to the target size
                 swap(temp);                    // Swap back (this now has the shrunk buffer)
                 // This approach avoids self-move assignment issues within reallocate
                 // A direct reallocate(size_) call is simpler but needs care.
            }
        }
    }

    // --- Modifiers ---

    // Clears the contents (destroys elements, size becomes 0, capacity unchanged)
    void clear() noexcept {
        destroy_range(data_, data_ + size_);
        size_ = 0;
        // Capacity remains unchanged
    }

    // Inserts elements

    // Single element insert (copy)
    iterator insert(const_iterator pos, const T& value) {
        return emplace(pos, value); // Delegate to emplace
    }

     // Single element insert (move)
    iterator insert(const_iterator pos, T&& value) {
        return emplace(pos, std::move(value)); // Delegate to emplace
    }

    // Fill insert
    iterator insert(const_iterator pos, size_type count, const T& value) {
        if (count == 0) return iterator(const_cast<pointer>(pos)); // Non-const conversion needed

        difference_type index = pos - cbegin();
        if (index < 0 || static_cast<size_type>(index) > size_) {
            throw std::out_of_range("Vector::insert iterator out of range");
        }

        size_type current_size = size_; // Save old size
        size_type required_size = size_ + count;
        if (required_size > max_size()) throw std::length_error("Vector::insert count exceeds max_size");

        iterator insert_pos = begin() + index; // Modifiable iterator

        if (required_size > capacity_) {
            // Reallocation needed
            size_type new_cap = calculate_growth(required_size);
            pointer new_data = static_cast<pointer>(::operator new(new_cap * sizeof(value_type)));
            iterator new_insert_pos = new_data + index;
            iterator new_end_pos = new_insert_pos + count;

            // Try to construct the new elements first
            try {
                std::uninitialized_fill_n(new_insert_pos, count, value);
            } catch (...) {
                ::operator delete(new_data);
                throw;
            }

            // Move elements before insertion point
            try {
                // Move construct elements before insertion point
                if constexpr (std::is_nothrow_move_constructible_v<value_type>) {
                    std::uninitialized_move(data_, insert_pos, new_data);
                } else {
                    std::uninitialized_copy(data_, insert_pos, new_data); // Fallback to copy
                }
            } catch (...) {
                destroy_range(new_insert_pos, new_end_pos); // Cleanup constructed new elements
                ::operator delete(new_data);
                throw;
            }

            // Move elements after insertion point
            try {
                // Move construct elements after insertion point
                if constexpr (std::is_nothrow_move_constructible_v<value_type>) {
                    std::uninitialized_move(insert_pos, data_ + current_size, new_end_pos);
                } else {
                    std::uninitialized_copy(insert_pos, data_ + current_size, new_end_pos); // Fallback to copy
                }
            } catch (...) {
                destroy_range(new_data, new_insert_pos); // Cleanup moved elements before insertion point
                destroy_range(new_insert_pos, new_end_pos); // Cleanup constructed new elements
                ::operator delete(new_data);
                throw;
            }


            // Deallocate old data
            destroy_range(data_, data_ + current_size);
            ::operator delete(data_);

            // Update members
            data_ = new_data;
            size_ = required_size;
            capacity_ = new_cap;
            return new_insert_pos;

        } else {
            // No reallocation needed, shift elements within the existing buffer
            iterator old_end = end();
            size_type elements_to_move = old_end - insert_pos; // number of elements from pos to end
            iterator new_end_target = old_end + count;

            if (elements_to_move > 0) {
                // Move construct elements into the newly available space at the end
                std::uninitialized_move(old_end - std::min(count, elements_to_move), old_end, new_end_target - std::min(count, elements_to_move));

                 // Move assign the remaining overlapping elements (or copy if move assign not safe)
                std::move_backward(insert_pos, old_end - std::min(count, elements_to_move), old_end);

                // Destroy the elements that were moved from but not overwritten by insert
                // This happens if count < elements_to_move
                // Note: This destruction part is tricky and often overlooked. A simpler approach might destroy all moved-from elements
                // and then fill, but that's less efficient. Let's assume move ops handle this or accept potential issues in this simplified impl.
            }


            // Insert the new elements by copy constructing/assigning
            std::fill_n(insert_pos, count, value);


            size_ = required_size;
            return insert_pos;
        }
    }

    // Range insert - Omitted for brevity, complex implementation


    // Emplace element (construct in-place)
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        difference_type index = pos - cbegin();
         if (index < 0 || static_cast<size_type>(index) > size_) {
            throw std::out_of_range("Vector::emplace iterator out of range");
        }

        if (size_ == capacity_) {
            // Reallocation required
            size_type new_cap = calculate_growth(size_ + 1);
            pointer new_data = static_cast<pointer>(::operator new(new_cap * sizeof(value_type)));
            iterator insert_pos = new_data + index;

             // Construct the new element first in the new buffer
            try {
                ::new (static_cast<void*>(insert_pos)) value_type(std::forward<Args>(args)...);
            } catch (...) {
                ::operator delete(new_data); // Clean up allocated memory
                throw;
            }

            // Move elements before insertion point
             try {
                 if constexpr (std::is_nothrow_move_constructible_v<value_type>) {
                     std::uninitialized_move(data_, data_ + index, new_data);
                 } else {
                     std::uninitialized_copy(data_, data_ + index, new_data);
                 }
             } catch (...) {
                 insert_pos->~T(); // Destroy the newly constructed element
                 ::operator delete(new_data);
                 throw;
             }

             // Move elements after insertion point
             try {
                 if constexpr (std::is_nothrow_move_constructible_v<value_type>) {
                     std::uninitialized_move(data_ + index, data_ + size_, insert_pos + 1);
                 } else {
                     std::uninitialized_copy(data_ + index, data_ + size_, insert_pos + 1);
                 }
             } catch (...) {
                 destroy_range(new_data, insert_pos); // Destroy elements before insertion point
                 insert_pos->~T(); // Destroy the newly constructed element
                 ::operator delete(new_data);
                 throw;
             }

            // Clean up old data
            destroy_range(data_, data_ + size_);
            ::operator delete(data_);

            // Update members
            data_ = new_data;
            capacity_ = new_cap;
            size_++;
            return insert_pos; // Return iterator to the newly emplaced element

        } else {
            // No reallocation, shift elements within the buffer
            iterator insert_pos = begin() + index; // Modifiable iterator
            if (insert_pos == end()) {
                 // Emplacing at the end is simpler
                 ::new (static_cast<void*>(data_ + size_)) value_type(std::forward<Args>(args)...);
            } else {
                 // Need to shift elements to make space
                 // Move construct the last element into the uninitialized space
                 ::new (static_cast<void*>(data_ + size_)) value_type(std::move(back()));
                 // Move assign elements backwards
                 std::move_backward(insert_pos, end() - 1, end());
                 // Overwrite/assign at the insertion point (or destroy and construct)
                 *insert_pos = value_type(std::forward<Args>(args)...); // Simpler: Assign (requires copy/move assignable)
                 // Alternative: insert_pos->~T(); ::new (static_cast<void*>(insert_pos)) value_type(std::forward<Args>(args)...);
            }
            size_++;
            return insert_pos;
        }
    }

    // Erases elements
    iterator erase(const_iterator pos) {
         difference_type index = pos - cbegin();
         if (index < 0 || static_cast<size_type>(index) >= size_) {
            throw std::out_of_range("Vector::erase iterator out of range");
        }

        iterator erase_pos = begin() + index;

        // Move elements after the erased position one step back
        std::move(erase_pos + 1, end(), erase_pos);

        // Destroy the now-duplicate element at the end
        destroy_range(data_ + size_ - 1, data_ + size_);

        size_--;
        return erase_pos; // Iterator following the last removed element
    }


    // Range erase - Omitted for brevity
    iterator erase(const_iterator first, const_iterator last) {
        difference_type first_idx = first - cbegin();
        difference_type last_idx = last - cbegin();

        if (first_idx < 0 || static_cast<size_type>(first_idx) > size_ ||
            last_idx < first_idx || static_cast<size_type>(last_idx) > size_) {
             throw std::out_of_range("Vector::erase range iterators out of range");
        }

        if (first == last) return iterator(const_cast<pointer>(first)); // Nothing to erase

        iterator erase_first = begin() + first_idx;
        iterator erase_last = begin() + last_idx;

        // Move elements from 'last' to the end, overwritting the erased range
        iterator new_end = std::move(erase_last, end(), erase_first);

        // Destroy the elements that were moved from (now at the end of the used part)
        destroy_range(new_end, end());

        size_ -= (last_idx - first_idx);

        return erase_first; // Iterator to the first element after the erased range
    }

    // Appends the given element value to the end of the container
    void push_back(const T& value) {
         emplace_back(value); // Delegate to emplace_back
    }
    void push_back(T&& value) {
         emplace_back(std::move(value)); // Delegate to emplace_back (move version)
    }

    // Appends a new element to the end of the container (constructed in-place)
    template <typename... Args>
    reference emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            memory_realocated++;
            reserve(calculate_growth(size_ + 1)); // Reserve handles reallocation
        }
        // Construct in place at the end
        ::new (static_cast<void*>(data_ + size_)) value_type(std::forward<Args>(args)...);
        size_++;
        return back(); // Return reference to the newly added element
    }

    // Removes the last element of the container
    void pop_back() {
        if (!empty()) {
            size_--;
            data_[size_].~T(); // Destroy the last element
        }
        // else: Undefined behavior like std::vector? Or just do nothing? Doing nothing is safer.
    }

    // Resizes the container to contain count elements
    void resize(size_type count) {
        if (count < size_) {
             // Shrink: destroy elements from count to size_
             destroy_range(data_ + count, data_ + size_);
             size_ = count;
        } else if (count > size_) {
            // Grow: reserve if needed, then default-construct new elements
            if (count > capacity_) {
                 reserve(calculate_growth(count)); // Use growth strategy
            }
            // Default construct elements from size_ to count
            std::uninitialized_value_construct_n(data_ + size_, count - size_);
            // Pre-C++17 loop:
            // for(size_t i = size_; i < count; ++i) { ::new (static_cast<void*>(data_ + i)) value_type(); }
            size_ = count;
        }
         // if count == size_, do nothing
    }

    // Resizes the container to contain count elements (copying value if growing)
    void resize(size_type count, const value_type& value) {
         if (count < size_) {
             // Shrink: destroy elements from count to size_
             destroy_range(data_ + count, data_ + size_);
             size_ = count;
        } else if (count > size_) {
            // Grow: reserve if needed, then copy-construct new elements
            if (count > capacity_) {
                 reserve(calculate_growth(count)); // Use growth strategy
            }
            // Copy construct elements from size_ to count using 'value'
            std::uninitialized_fill_n(data_ + size_, count - size_, value);
            size_ = count;
        }
         // if count == size_, do nothing
    }

    // Exchanges the contents of the container with those of other
    void swap(Vector& other) noexcept {
        using std::swap; // Enable ADL
        swap(data_, other.data_);
        swap(size_, other.size_);
        swap(capacity_, other.capacity_);
    }

}; // End class Vector


// --- Non-member Function Overloads ---

// Non-member swap
template <typename T>
void swap(Vector<T>& lhs, Vector<T>& rhs) noexcept {
    lhs.swap(rhs);
}

// Comparison operators
template <typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    // Use std::equal with the iterators
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs) {
    // Use std::lexicographical_compare with the iterators
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(rhs < lhs);
}

template <typename T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
    return rhs < lhs;
}

template <typename T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs < rhs);
}


#endif // MY_VECTOR_H