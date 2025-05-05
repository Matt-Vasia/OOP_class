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
}