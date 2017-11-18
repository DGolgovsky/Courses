#include <iostream>
#include <string>
#include <sstream>
#include <exception>

// описание класса исключения bad_from_string
class bad_from_string: public std::exception
{
public:
    /** Constructor (C strings).
     *  @param message C-style string error message.
     *                 The string contents are copied upon construction.
     *                 Hence, responsibility for deleting the char* lies
     *                 with the caller. 
     */
    explicit bad_from_string(const char* message)
		: msg_(message)
	{}

    /** Constructor (C++ STL strings).
     *  @param message The error message.
     */
    explicit bad_from_string(const std::string& message)
		: msg_(message)
	{}

    /** Destructor.
     * Virtual to allow for subclassing.
     */
    virtual ~bad_from_string() throw (){}

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *          is in posession of the Exception object. Callers must
     *          not attempt to free the memory.
     */
    const char* what() const noexcept {
       return msg_.c_str();
    }

protected:
    /** Error message.
     */
    std::string msg_;
};

// функция from_string
template<class T>
T from_string(std::string const& str)
{
    std::istringstream ss(str);
    T num;
    char tmp;
    if (!(ss >> std::noskipws >> num))
        throw bad_from_string("Err while streaming");
    ss >> std::noskipws >> tmp;
    if (!ss.eof())
        throw bad_from_string("Not empty after streaming.");

    return num;
}

int main()
{
    using std::string;
	string s1("123");
	int    a1 = from_string<int>   (s1); // a1 = 123
	std::cout << a1 << '\n';
	double b1 = from_string<double>(s1); // b1 = 123.0
	std::cout << b1 << '\n';
	string c1 = from_string<string>(s1); // c1 = "123"
	std::cout << c1 << '\n';
	string s2("12.3");
	int   a2 = from_string<char>  (s2); // исключение
	std::cout << a2 << '\n';
	double b2 = from_string<double>(s2); // b2 = 12.3
	std::cout << b2 << '\n';
	string c2 = from_string<string>(s2); // c2 = "12.3"
	std::cout << c2 << '\n';
	string s3("abc");
	int    a3 = from_string<int>   (s3); // исключение
	std::cout << a3 << '\n';
	double b3 = from_string<double>(s3); // исключение
	std::cout << b3 << '\n';
	string c3 = from_string<string>(s3); // c3 = "abc"
	std::cout << c3 << '\n';

	return 0;
}
