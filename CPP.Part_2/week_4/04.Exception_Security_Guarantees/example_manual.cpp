// Manual trying
template<class T>
struct Array {
    void resize(size_t n)
    {
        T * ndata = new T[n];
        try {
            for (size_t i = 0; i != n && i != size_; ++i)
                ndata[i] = data_[i];
        } catch (...) {
            delete [] ndata;
            throw;
        }
        delete [] data_;
        data_ = ndata;
        size_ = n;
    }

    T *    data_;
    size_t size_;
};
