// Строитель (Builder)

#include <cassert>
#include <iostream>
#include <map>
#include <vector>

class Tariff
{
    const std::vector<double> amount;
    const std::vector<int> discount;

public:
    Tariff(const std::vector<double> &amount_, const std::vector<int> &discount_) : amount(amount_), discount(discount_)
    {
        assert(amount.size() == discount.size());
    }

    void apply();
};


class TariffBuilder
{
    std::map<double, int> tariff;

public:
    void add_discount(double subtotal_, int discount_)
    {
        tariff[subtotal_] = discount_;
    }

    Tariff build()
    {
        std::vector<double> amount;
        std::vector<int> discount;
        for (const auto &t : tariff)
        {
            amount.push_back(t.first);
            discount.push_back(t.second);
        }

        return Tariff(amount, discount);
    }
};

void Tariff::apply()
{
    std::cout << "tariff is:" << std::endl;
    for (size_t i = 0; i < amount.size(); ++i)
    {
        std::cout << "after " << amount[i] << " RUB apply " << discount[i] << "%" << std::endl;
    }
}

int main(int, char *[])
{
    auto builder = TariffBuilder();
    builder.add_discount(1000, 10);
    builder.add_discount(20000, 20);
    builder.add_discount(10000, 15);
    auto t = builder.build();

    t.apply();

    return 0;
}
