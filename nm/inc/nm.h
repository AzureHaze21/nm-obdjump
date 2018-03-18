/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#ifndef _NM_H_
#define _NM_H_

#include <sys/mman.h>
#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

#define ELF32		0x1
#define ELF64		0X2
#define IS_LOWER(c)	((c > 96) && (c <= 122))
#define IS_UPPER(c)	((c > 64 && c < 91) ? 1 : 0)
#define TO_LOWER(c)	(IS_UPPER(c) ? c + 32 : c)
#define IS_SPECIAL(c) (!((c > 64 && c < 91) ||			\
						 (c > 96 && c < 123)) ? 1 : 0)

typedef struct s_sym t_sym;

struct s_sym
{
		unsigned addr;
		unsigned char info;
		char *name;
		char type;
		t_sym *next;
};

void free_symlist(t_sym *head);
void swap_syms(t_sym **head);
void print_symbols(t_sym *, size_t);
void print_symbols32(t_sym *, size_t);
void sort_symlist(t_sym **head, int arch);
void read_header(const int fd, int fsize);
char get_symtype(Elf64_Shdr *shdr, Elf64_Sym *sym, void *strtab);
char get_symtype32(Elf32_Shdr *shdr, Elf32_Sym *sym, void *strtab);
void push_sym(t_sym **head, unsigned addr, unsigned char type, char *name);
void nm(void *map);
void nm32(void *map);

extern char	*g_input_file;

#endif
