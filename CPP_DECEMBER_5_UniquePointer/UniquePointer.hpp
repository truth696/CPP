
template <typename T>

class unique_ptr{
    T* data;
public:
    unique_ptr(T* t = nullptr) noexcept : data(t) {}
    unique_ptr(const unique_ptr& u) = delete;
    unique_ptr(unique_ptr&& u) noexcept : data(u.data){
        u.data = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& u) noexcept {
        if(this == &u) return *this;
        data = u.data;
        u.data = nullptr;
        return *this;
    }

    T* release() noexcept {
        T* tmp = this->data;
        this->data = nullptr;
        return tmp;
    }

    void reset() noexcept {
        delete data;
        data = nullptr;
    }

    void swap(unique_ptr& u) noexcept {
        std::swap(this->data,u.data);
    }

    T* get() const noexcept {
        return data;
    }

    explicit operator bool() const noexcept {
        if(!this->data) return false;
        return true;
    }

    T& operator* ()const noexcept {return *data;}

    T* operator-> ()const noexcept {return data;}

    ~unique_ptr() { reset(); }
};
