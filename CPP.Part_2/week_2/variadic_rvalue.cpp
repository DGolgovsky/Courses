template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(
            new T(std::forward<Args>(args)...));
}

auto p = make_unique<Array<string>>(10, string("Hello"));
