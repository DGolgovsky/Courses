#include "ElfArcher.h"

Elf::Elf(size_t id)
        : Unit(id, 100)
{
}


Archer::Archer(size_t id)
        : Unit(id, 120)
{
}


ElfArcher::ElfArcher(size_t id)
        : Unit(id, 150)
        , Elf(id)
        , Archer(id)
{
}

