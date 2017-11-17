#include <utility>

struct String
{
    void swap(String &s) {
        std::swap(data_, s.data_);
        std::swap(size_, s.size_);
    }

    String (String &&s) {
        swap(s);
    }

    String &operator=(String &&s) {
        // better use clear mem of current object
        swap(s);
        return *this;
    }
private:
    char *data_ = nullptr;
    std::size_t size_ = 0;
};

