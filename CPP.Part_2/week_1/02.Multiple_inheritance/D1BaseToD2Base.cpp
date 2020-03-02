#include "D1BaseToD2Base.h"
/*
 * Вам дана следующая иерархия классов:
 * struct Base {};
 * struct D1 : Base {};
 * struct D2 : Base {};
 * struct D3 : D1, D2 {};
 *
 * Напишите функцию D1BaseToD2Base, которая преобразует указатель
 * типа Base на объект типа D3, который ссылается на экземпляр Base,
 * соответствующий D1, в указатель, ссылающийся на экземпляр Base
 * соответствующий D2.
 */

Base * D1BaseToD2Base(Base const * base)
{
    /* Better way
    const D1* d1 = static_cast<const D1*>(base);
    const D3* d3 = static_cast<const D3*>(d1);
    const D2* d2 = static_cast<const D2*>(d3);
    return const_cast<Base*>(static_cast<const Base*>(d2));
    */

	/* Another solution
	return (Base*)(D2*)(D3*)(D1*) base;
	*/

    /* My solution */
    D3 d3;
    D2 &d2 = d3;
    Base *base_d2 = &d2;

    return base_d2;
}
