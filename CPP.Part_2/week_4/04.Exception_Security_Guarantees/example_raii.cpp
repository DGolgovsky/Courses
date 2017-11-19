// RAII method
template<class T>
struct Array {
    void resize(size_t n) {
        unique_ptr<T[]> ndata(new T[n]);
        
        for (size_t i = 0; i != n && i != size_; ++i)
                ndata[i] = data_[i]; // ifexception -> ~unique_ptr
        
        data_ = std::move(ndata);
        size_ = n;
    }

    unique_ptr<T[]> data_;
    size_t          size_;
};
