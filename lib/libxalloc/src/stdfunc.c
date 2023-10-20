#include "stdhead.h"
#include "stdfunc.h"

bool __xalloc_std_is_litle_endian()
{
    ui8_t swaptest[2] = { 0, 1 };
    return (*(ui16_t*)swaptest);
}

char __xalloc_std_to_hex(const ui8_t _4bits)
{
    const ui8_t bits4 = _4bits & 0x0f;
    if (bits4 >= 0x00 && bits4 <= 0x09) return bits4 + '0';
    else if (bits4 >= 0x0a && bits4 <= 0x0f) return bits4 - 0x0a + 'a';
    else abort();
}
