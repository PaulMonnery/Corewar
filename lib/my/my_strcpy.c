/*
** EPITECH PROJECT, 2018
** my_strcpy
** File description:
** Day06 task01 my_strcpy
*/

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}
