#include <stdio.h>

#include "utils.h"

int parseValue(const unsigned char IDproc, const unsigned char message)
{
    return IDproc*256 + message;
}

void findBytes(const int value, unsigned int * IDproc, unsigned int * message)
{
    *IDproc = ((value >> 8)) & 255;
    *message = (value & 255);
}

