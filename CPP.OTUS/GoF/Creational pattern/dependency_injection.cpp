// Внедрение зависимости (Dependency Injection)

#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <array>

class IStorage
{
public:
    virtual void execute_query() = 0;
};

class Report
{
    IStorage* storage;

public:
    Report(IStorage* storage_) : storage(storage_)
    {
    }

    void print()
    {
        storage->execute_query();
        std::cout << "done" << std::endl;
    }
};

class TestStorage : public IStorage
{
    void execute_query() override
    {
        std::cout << "... fetching data" << std::endl;
    }
};

int main(int, char *[])
{
    Report report(new TestStorage);
    report.print();

    return 0;
}
