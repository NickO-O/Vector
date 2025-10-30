#include <stdexcept>
#include <utility>
#include <initializer_list>

template <typename T>
class Vector {
public:
    using value_type = T;

private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    void reallocate(size_t new_cap) {
        if (new_cap == 0) {
            delete[] data_;
            data_ = nullptr;
            capacity_ = 0;
            return;
        }

        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    Vector() = default;

    explicit Vector(size_t count) : size_(count) {
        if (count > 0) {
            data_ = new T[count];
            capacity_ = count;
        }
    }

    Vector(size_t count, const T& value) : size_(count) {
        if (count > 0) {
            data_ = new T[count];
            capacity_ = count;
            for (size_t i = 0; i < count; ++i) {
                data_[i] = value;
            }
        }
    }


    Vector(std::initializer_list<T> init) : size_(init.size()) {
        if (size_ > 0) {
            data_ = new T[size_];
            capacity_ = size_;
            size_t i = 0;
            for (const auto& elem : init) {
                data_[i++] = elem;
            }
        }
    }

    ~Vector() {
        delete[] data_;
    }

    Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
        if (capacity_ > 0) {
            data_ = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            if (capacity_ > 0) {
                data_ = new T[capacity_];
                for (size_t i = 0; i < size_; ++i) {
                    data_[i] = other.data_[i];
                }
            } else {
                data_ = nullptr;
            }
        }
        return *this;
    }

    Vector(Vector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    T& operator[](size_t pos) { return data_[pos]; }
    const T& operator[](size_t pos) const { return data_[pos]; }

    T* begin() noexcept { return data_; }
    const T* begin() const noexcept { return data_; }
    T* end() noexcept { return data_ + size_; }
    const T* end() const noexcept { return data_ + size_; }

    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }

    void resize(size_t new_size) {
        if (new_size <= size_) {
            size_ = new_size;
            return;
        }
        if (new_size > capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            while (new_cap < new_size) new_cap *= 2;
            reallocate(new_cap);
        }
        size_ = new_size;
    }
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        data_[size_] = value;
        ++size_;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        data_[size_] = std::move(value);
        ++size_;
    }

    void pop_back() {
        if (size_ > 0) --size_;
    }

    void clear() noexcept {
        size_ = 0;
    }

    void reserve(size_t new_cap) {
        if (new_cap > capacity_) {
            reallocate(new_cap);
        }
    }

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
};