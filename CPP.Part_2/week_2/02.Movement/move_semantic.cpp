struct String
{
    String (String && s) // && - rvalue reference
        : data_(s.data_)
        , size_(s.size_)
    {
        s.data_ = nullptr;
        s.size_ = 0;
    }

    String &operator=(String &&s)
    {
        delete [] data_;
        data_ = s.data_;
        size_ = s.size_;
        s.data_ = nullptr;
        s.size_ = 0;
        return *this;
    }
};
