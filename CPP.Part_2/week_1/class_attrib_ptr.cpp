struct Unit
{
    unsigned id;
    unsigned hp;
};

typedef unsigned Unit::*UnitField;

void sort(Unit *p, Unit *q, UnitField f)
{
    for (Unit *m = p; m != q; ++m)
        for (Unit *r = m; r + 1 != q; ++r)
            /* Bubble sort */
            if ( (r->*f) > ((r + 1)->*f) )
                swap(*r, *(r+1));
}

// Usage
sort(p, q, &Unit::id); // Sort by id attribute


struct Unit
{
    explicit Unit(size_t id) : id_(id) {}
    size_t id() const {
        return id_;
    }
private:
    size_t id_;
};

struct Archer : virtual Unit
{
    explicit Archer(size_t id): Unit(id) {}
    Unit const *ptr = this;
    size_t tmp = 5;
};

/*
 * Unit const* Archer::*
 */
