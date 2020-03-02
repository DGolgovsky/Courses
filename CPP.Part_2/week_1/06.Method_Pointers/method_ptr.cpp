struct Unit
{
    virtual unsigned id() const;
    virtual unsigned hp() const;
}

typedef unsigned (Unit::*UnitMethod)() const;

void sort(Unit *p, Unit *q, UnitMethod mtd)
{
    for (Unit *m = p; m != q; ++m)
        for (Unit *r = m; r + 1 != q; ++r)
            if ( (r->*mtd)() > ((r+1)->*mtd)() )
                swap(*r, *(r+1));
}

// Usage
sort(p, q, &Unit::hp); // Sorting by HP
