/*
** EPITECH PROJECT, 2019
** CPE_corewar_2018
** File description:
** corewar
*/

#include "vm.h"
#include "my.h"
#include "asm.h"

int get_list_len(process_t *head)
{
    int len = 0;

    for (; head != NULL; head = head->next)
        len += 1;
    return (len);
}

static void write_in_arena(unsigned char *arena,
unsigned long address, int fd, int size)
{
    char buffer[size];

    if (read(fd, &buffer, size) < size)
        my_error("Invalid prog_size");
    for (int i = 0; i < size; i += 1)
        arena[address + i] = buffer[i];
    close(fd);
}

static void spawn_champions(environment_t *env)
{
    int division = 0;
    int offset = 0;

    division = (int)(MEM_SIZE / get_list_len(env->processes_head));
    for (process_t *tail = PROC_HEAD(env);
    tail != NULL; tail = tail->next) {
        if (!tail->address)
            tail->address = offset;
        if (tail->address + division <
        tail->address + tail->header.prog_size)
            offset = tail->address + tail->header.prog_size;
        else {
            offset += division;
            offset %= MEM_SIZE;
        }
        write_in_arena(env->arena, tail->address,
        tail->fd, tail->header.prog_size);
    }
}

int load_champions(environment_t *env)
{
    int prog_nb = 0;

    if (!get_list_len(PROC_HEAD(env)))
        return (ERROR);
    for (process_t *tail = PROC_HEAD(env);
    tail != NULL; tail = tail->next) {
        if (read(tail->fd, &tail->header, sizeof(header_t))
        < (ssize_t)sizeof(header_t))
            my_error("Invalid header size");
        tail->header.prog_size = get_no_endian(tail->header.prog_size, 4);
        if (tail->header.prog_size <= 0)
            my_error("Invalid prog_size");
        if (get_no_endian(tail->header.magic, 4) != COREWAR_EXEC_MAGIC)
            my_error("File is not an executable");
        if (!tail->prog_number)
            tail->prog_number = prog_nb++;
        else
            prog_nb += 1;
    }
    spawn_champions(env);
    return (0);
}
