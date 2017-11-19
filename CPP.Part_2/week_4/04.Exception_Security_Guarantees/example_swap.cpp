template<class T>
struct Array {
    void resize(size_t n) {
        Array t(n);
        for (size_t i = 0; i != n && i != size_; ++i)
            t[i] = data_[i];
        t.swap(*this); // usually noexcept
    }

    T *    data_;
    size_t size_;
};
