template<class T>
struct shared_ptr_data
{
    void addref() {
        ++counter; // atomic increment
    }

    T * ptr;
    std::atomic<size_t> counter;
};

