// Factory method

#include <iostream>

enum class Storage
{
    mysql, postgres
};

class IStorage
{
public:
    virtual void open() = 0;
    virtual void execute_query() = 0;
    virtual void close() = 0;
};

class MySQLStorage: public IStorage
{
public:
    void open() override
    {
        std::cout << "Connect to MySQL" << std::endl;
    }
    void execute_query() override
    {
        std::cout << "Fetch MySQL result" << std::endl;
    }
    void close() override
    {
        std::cout << "Disconnect from MySQL" << std::endl;
    }
};

class PostgreSQLStorage: public IStorage
{
public:
    void open() override
    {
        std::cout << "Connect to PostgreSQL" << std::endl;
    }
    void execute_query() override
    {
        std::cout << "Fetch PostgreSQL result" << std::endl;

    }
    void close() override
    {
        std::cout << "Disconnect from PostgreSQL" << std::endl;
    }
};

int main(int, char *[])
{
    auto environment = Storage::postgres;

    IStorage* storage;

    switch (environment) {
        case Storage::mysql:
            storage = new MySQLStorage();
            break;

        case Storage::postgres:
            storage = new PostgreSQLStorage();
            break;
        default:
            return 1;
    }

    storage->open();
    storage->execute_query();
    storage->close();

    return 0;
}
