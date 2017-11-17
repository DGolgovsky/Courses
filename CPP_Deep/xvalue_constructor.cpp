class T {
public: // function ::acquire/ ::release - imagination
    explicit T(const std::string& _name) :
        handle {::acquire(_name)} {}
    T(T&& rhs) : handle {rhs.handle} {rhs.handle = nullptr;}
    T& operator=(T&& rhs) { // rhs - right hand side . Resourse own rhs
        T copy{std::move(rhs)}; // Resourse own copy
        std::swap(handle, copy.handle); // Resourse own *this
        return *this; // Call copy's T::~T()
    }
    ~T() { ::release(handle); }
private:
    resourse_t handle;
};
