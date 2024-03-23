#ifndef __STDPORT_H
#define __STDPORT_H

#include "stdint.h"

// Writes value to specified hardware port.
void outPortb(uint16_t _port, uint8_t _data);

// TODO: inPortB (spelling?)

#endif