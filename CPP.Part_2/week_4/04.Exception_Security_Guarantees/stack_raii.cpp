template<class T>
struct Stack
{
    void push(T const& t) {
        data_.push_back(t);
    }

    unique_ptr<T> pop() { // Bad architecture
        unique_ptr<T> tmp(new T(data_.back()));
        data_.pop_back();
        return std::move(tmp);
    }

    std::vector<T> data_;
};

