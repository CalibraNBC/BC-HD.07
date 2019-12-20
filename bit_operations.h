#ifndef _bit_operations_
#define _bit_operations_

#define SetBit(address,bit) (address |= (1<<bit))
#define ClrBit(address,bit) (address &=~ (1<<bit))
#define ChckBit(address,bit) (address & (1<<bit))


#endif
