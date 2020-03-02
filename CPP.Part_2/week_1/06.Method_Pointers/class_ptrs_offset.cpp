#include <string>

struct Elf {
    std::string secretName;
};

struct Archer {
    unsigned arrows() { return arrows_; }
    unsigned arrows_;
};

struct ElfArcher : Elf, Archer {};

void foo()
{
    ElfArcher ea;
    unsigned (ElfArcher::*m)() = &Archer::arrows;
    (ea.*m)();
}

struct Unit
{
    unsigned id() const;
    unsigned hp;
};

void bar()
{
    unsigned (Unit::*mtd)() const = &Unit::id;
    unsigned  Unit::*fld          = &Unit::hp;

    Unit u;
    Unit *p = &u;

    (u.*mtd)() == (p->*mtd)();
    (u.*fld)   == (p->*fld);
}
