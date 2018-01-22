// Ленивая инициализация (Lazy initialization)

#include <iostream>

class File
{
    std::string name;
public:
    File(const std::string &name_) : name(name_)
    {
        std::cout << "create " << name << std::endl;
    }
    ~File()
    {
        std::cout << "close " << name << std::endl;
    }
    void write(const std::string &line_)
    {
        std::cout << "write " << line_ << " into " << name << std::endl;
    }
};

class FileOnDemand
{
    std::string name;
    File* file;
public:
    FileOnDemand(const std::string &name_) : name(name_), file(nullptr)
    {
    }
    File* operator->()
    {
        if (!file)
        {
            file = new File(name);
        }
        return file;
    }
};

int main(int, char *[])
{
    FileOnDemand file("test.txt");

    size_t n = 2;
    for (size_t i = 0; i < n; ++i)
    {
        file->write(std::to_string(i));
    }

    return 0;
}
