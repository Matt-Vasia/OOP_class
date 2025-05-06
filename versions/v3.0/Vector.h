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
}