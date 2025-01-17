/*
** EPITECH PROJECT, 2019
** get_no_endian.c
** File description:
** returns an int with reversed endian
*/

#include "asm.h"

int get_no_endian(int nb, int size)
{
    int bytes[] = {(nb & 0xff) << 24,
                    (nb & 0xff00) << 8,
                    (nb & 0xff0000) >> 8,
                    (nb & 0xff000000) >> 24};

    switch (size) {
        case IND_SIZE:
            return ((nb & 0xff) << 8 | (nb & 0xff00) >> 8);
        case DIR_SIZE:
            return (bytes[3] | bytes[2] | bytes[1] | bytes[0]);
        default: return (nb);
    }
    return (nb);
}
