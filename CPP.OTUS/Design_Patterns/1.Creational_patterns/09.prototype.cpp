// Прототип (Prototype)

#include <iostream>
#include <map>

class Prototype
{
public:
    virtual void connection() = 0;
    virtual Prototype *clone() = 0;
};

class TCPConnector: public Prototype
{
public:
    void connection() override
    {
        std::cout << "TCP connection" << std::endl;
    }
    TCPConnector *clone() override
    {
        return new TCPConnector{};
    }
};

class UDPConnector: public Prototype
{
public:
    void connection() override
    {
        std::cout << "UDP connection" << std::endl;
    }
public:
    UDPConnector *clone() override
    {
        return new UDPConnector{};
    }
};

int main(int, char **)
{
    Prototype *c = new TCPConnector{};

    std::cout << "primary" << std::endl;
    c->connection();

    auto mirror = c->clone();
    std::cout << "mirror" << std::endl;
    mirror->connection();

    return 0;
}
