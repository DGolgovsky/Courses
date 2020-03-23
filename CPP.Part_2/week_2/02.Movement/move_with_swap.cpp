#include <utility>

struct String
{
    void swap(String &s) {
        std::swap(data_, s.data_);
        std::swap(size_, s.size_);
    }

    String (String &&s) {
    	// can be called default ctor
        swap(s);
    }

    String &operator=(String &&s) {
        // better use clear mem of current object
        swap(s);
        return *this;
    }
private:
	// must be initialized by default values
    char *data_ = nullptr;
    std::size_t size_ = 0;
};

