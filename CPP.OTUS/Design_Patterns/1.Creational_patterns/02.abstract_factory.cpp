// Abstract factory

#include <iostream>

enum class Env
{
    cloud, local
};

// Config
class IConfig
{
public:
    virtual void read() = 0;
};

class ConsulConfig: public IConfig
{
public:
    void read() override
    {
        std::cout << "Connect to Consul (cloud)" << std::endl;
    }
};

class LocalConfig: public IConfig
{
public:
    void read() override
    {
        std::cout << "Open local file" << std::endl;
    }
};

// Metric
class IMetric
{
public:
    virtual void send() = 0;
};

class PrometheusMetric: public IMetric
{
public:
    void send() override
    {
        std::cout << "Push to Prometheus (cloud)" << std::endl;
    }
};

class LocalMetric: public IMetric
{
public:
    void send() override
    {
        std::cout << "Write to local log" << std::endl;
    }
};

//
class EnvironmentFactory
{
public:
    virtual IConfig* CreateConfig() = 0;
    virtual IMetric* CreateMetric() = 0;
};

class CloudFactory: public EnvironmentFactory
{
public:
    IConfig* CreateConfig() override
    {
        return new ConsulConfig();
    }
    IMetric* CreateMetric() override
    {
        return new PrometheusMetric();
    }
};

class LocalFactory: public EnvironmentFactory
{
public:
    IConfig* CreateConfig() override
    {
        return new LocalConfig();
    }
    IMetric* CreateMetric() override
    {
        return new LocalMetric();
    }
};

int main(int, char *[])
{
    auto environment = Env::cloud;

    EnvironmentFactory* factory;
    switch (environment) {
        case Env::cloud:
            factory = new CloudFactory();
            break;
        case Env::local:
            factory = new LocalFactory();
            break;
        default:
            return 1;
    }

    auto config = factory->CreateConfig();
    auto metric = factory->CreateMetric();

    config->read();
    metric->send();

    return 0;
}
