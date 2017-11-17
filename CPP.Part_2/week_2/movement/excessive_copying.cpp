#include <cstddef>

struct String
{
public:
    String() = default;
    String(String const &s);
    String &operator=(String const &s);
    // ...
private:
    char  *data_ = nullptr;
    std::size_t size_ = 0;
};

String getCurrentDateString()
{
    String date;
    // date fills "21 october 2015"
    return date; // Copy constructor
}

String date = getCurrentDateString(); // Copy constructor
