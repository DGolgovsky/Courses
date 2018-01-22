// Прототип (Prototype)

#include <iostream>
#include <map>

class Prototype
{
public:
    virtual void connection() = 0;

    virtual Prototype *clone() = 0;
};

class TcpConnector : public Prototype
{
public:
    void connection() override
    {
        std::cout << "tcp connection" << std::endl;
    }
public:
    TcpConnector *clone() override
    {
        return new TcpConnector{};
    }
};

class UdpConnector : public Prototype
{
public:
    void connection() override
    {
        std::cout << "udp connection" << std::endl;
    }
public:
    UdpConnector *clone() override
    {
        return new UdpConnector{};
    }
};

int main(int, char const **)
{
    Prototype *c = new TcpConnector{};

    //

    std::cout << "primary" << std::endl;
    c->connection();

    auto mirror = c->clone();
    std::cout << "mirror" << std::endl;
    mirror->connection();

    return 0;
}
