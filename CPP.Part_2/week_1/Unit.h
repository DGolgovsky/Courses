#ifndef UNIT_H
#define UNIT_H

#include <iostream>

struct Unit
{
public:
    explicit Unit(size_t id)
        : id_(id)
    {
        print_info();
    }

    explicit Unit(size_t id, size_t hp)
        : id_(id)
        , hp_(hp)
    {
        print_info();
    }

    void print_info() const {
        std::cout << "Unit created. ID: "
                  << id_ << ", HP: "
                  << hp_ <<'\n';
    }

    size_t id() const { return id_; }

private:
    size_t id_;
    size_t hp_;
};

#endif
