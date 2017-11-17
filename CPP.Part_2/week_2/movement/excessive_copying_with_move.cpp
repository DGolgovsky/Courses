#include <utility>

struct String
{
public:
    String() = default;
    String(String const &s);            // lvalue-reference
    String &operator=(String const &s);
    String(String const &&s);           // rvalue-reference
    String &operator=(String const &&s);
    // ...
private:
    char  *data_ = nullptr;
    std::size_t size_ = 0;
};

String getCurrentDateString()
{
    String date;
    // date fills "21 october 2015"
    return std::move(date);
}

String date = getCurrentDateString();

