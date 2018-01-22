// Объектный пул (Object pool)

#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <array>

class PgConnection
{
};


class PgConnectionPool
{
private:
    struct PgConnectionBlock
    {
        PgConnection* connection;
        bool busy;
    };

    std::vector<PgConnectionBlock> m_pool;

public:
    PgConnection* get()
    {
        for (size_t i = 0; i < m_pool.size(); ++i)
        {
            if (!m_pool[i].busy)
            {
                m_pool[i].busy = true;
                return m_pool[i].connection;
            }
        }

        auto block = PgConnectionBlock{new PgConnection, true};
        m_pool.push_back(block);

        return block.connection;
    }

    void put(PgConnection* object)
    {
        for (size_t i = 0; i < m_pool.size(); ++i)
        {
            if (m_pool[i].connection == object)
            {
                m_pool[i].busy = false;
                break;
            }
        }
    }

    ~PgConnectionPool()
    {
        for (const auto &i : m_pool)
        {
            std::cout << i.connection << std::endl;
            delete i.connection;
        }
    }
};


int main(int, char const **)
{
    PgConnectionPool pool;

    auto report_conn = pool.get();
    pool.put(report_conn);

    auto admin_conn = pool.get();
    pool.put(admin_conn);

    return 0;
}
