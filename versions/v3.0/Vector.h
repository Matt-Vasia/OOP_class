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
}