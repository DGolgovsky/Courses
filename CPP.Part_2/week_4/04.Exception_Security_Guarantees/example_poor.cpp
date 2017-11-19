// Not even base guarantee
template<class T>
struct Array {
    void resize(size_t n)
    {
        T * ndata = new T[n]; // *new, *T constructor
        for (size_t i = 0; i != n && i != size_; ++i)
            ndata[i] = data_[i]; // if exception -> memory leak
        delete [] data_;
        data_ = ndata;
        size_ = n;
    }

    T *    data_;
    size_t size_;
};
