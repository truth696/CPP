

class ControlBlock{
public: 
    int strong_count = 0;
};

template <typename T>

class shared_ptr{
    T* data;
    ControlBlock* cb;
    public:
    explicit shared_ptr(T* ptr = nullptr) noexcept {
        data = ptr;
        
        if (data) {
            cb = new ControlBlock();
            cb->strong_count = 1;
        } else {
            cb = nullptr;
        }
    }
    
    shared_ptr(const shared_ptr& oth) {
        if (oth.data) ++oth.cb->strong_count; 

        data = oth.data;
        cb = oth.cb;
    }

    shared_ptr(shared_ptr&& oth){
        data = oth.data;
        cb = oth.cb;

        oth.cb = nullptr;
        oth.data = nullptr;
    }

    shared_ptr& operator=(shared_ptr&& oth){
        if (this == &oth) return *this;

        reset();
        data = oth.data;
        cb = oth.cb;

        oth.cb = nullptr;
        oth.data = nullptr;

        return *this;
    }

    shared_ptr& operator=(const shared_ptr& oth){
        if (this == &oth) return *this;

        reset();
        if (oth.data) ++oth.cb->strong_count;

        data = oth.data;
        cb = oth.cb;

        return *this;
    }

    void reset() {
        if (cb) {
            --cb->strong_count;
            if (cb->strong_count == 0){
                delete data;
                delete cb;
            }
        }
            
        cb = nullptr;
        data = nullptr;
    }


    void swap(shared_ptr& oth) noexcept {
        std::swap(this->data,oth.data);
        std::swap(this->cb, oth.cb);
    }

    T* get() const noexcept { return data; }

    T& operator*() const noexcept { return *data; } 

    T* operator->()const noexcept { return data; }

    int use_count() const noexcept { return (cb) ? cb->strong_count : 0; }

    bool unique() const noexcept { return (cb) ? cb->strong_count == 1 : false; }

    explicit operator bool() const noexcept { return data != nullptr; }

    ~shared_ptr(){ reset(); }
   
};
