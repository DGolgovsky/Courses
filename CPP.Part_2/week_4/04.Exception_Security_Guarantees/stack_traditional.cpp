template<class T>
struct Stack
{
    void push(T const& t) {
        data_.push_back(t);
    }

    void pop(T & res) {
        res = data_.back();
        data_.pop_back();
    }

    std::vector<T> data_;
};

