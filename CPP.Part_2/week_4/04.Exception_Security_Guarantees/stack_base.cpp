// Base guarantee
template<class T>
struct Stack
{
    void push(T const& t) {
        data_.push_back(t);
    }

    T pop() {
        T tmp = data_.back();
        data_.pop_back();
        return tmp; // Potential exception.
    }

    std::vector<T> data_;
};

