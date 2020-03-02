/*
 * Diamond inheritance
 *
 *     |Unit|
 *    /      \
 *   Elf    Archer
 *    \      /
 *    ElfArcher
 */

#ifndef ELFARCHER_H
#define ELFARCHER_H

#include "Unit.h"
#include <iostream>

struct Elf: virtual Unit
{
    explicit Elf(size_t);
};

struct Archer: virtual Unit
{
    explicit Archer(size_t);
};

struct ElfArcher: Elf, Archer
{
    explicit ElfArcher(size_t);
};

#endif
