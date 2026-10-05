#ifndef __W5500_PORT_H__
#define __W5500_PORT_H__

#include "main.h"

void W5500_Select(void);
void W5500_Unselect(void);

void W5500_Reset(void);

uint8_t W5500_ReadByte(void);
void W5500_WriteByte(uint8_t byte);

void W5500_Init(void);

#endif