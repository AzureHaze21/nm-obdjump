/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#ifndef _OBJDUMP_H_
#define _OBJDUMP_H_

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

#define BFD_NO_FLAGS	0x00
#define HAS_RELOC	0x01
#define EXEC_P		0x02
#define HAS_LINEO	0x04
#define HAS_DEBUG	0x08
#define HAS_SYMS	0x10
#define HAS_LOCALS	0x20
#define DYNAMIC		0x40
#define WP_TEXT		0x80
#define D_PAGED		0x100

#define FLAG_STR(f)	f==ET_REL?"HAS_RELOC":				\
		f==EXEC_P?"EXEC_P":					\
		f==HAS_LINEO?"HAS_LINEO":				\
		f==HAS_DEBUG?"HAS_DEBUG":				\
		f==HAS_SYMS?"HAS_SYMS":					\
		f==HAS_LOCALS?"HAS_LOCALS":				\
		f==DYNAMIC?"DYNAMIC":					\
		f==WP_TEXT?"WP_TEXT":					\
		f==D_PAGED?"D_PAGED":					\
		f==(HAS_SYMS | HAS_LOCALS)?"HAS_SYMS, HAS_LOCALS":	\
		f==(HAS_SYMS | DYNAMIC)?"HAS_SYMS, DYNAMIC":		\
		f==(HAS_SYMS | WP_TEXT)?"HAS_SYMS, WP_TEXT":		\
		f==(DYNAMIC | HAS_LOCALS)?"DYNAMIC, HAS_LOCALS":	\
		f==(DYNAMIC | WP_TEXT)?"DYNAMIC, WP_TEXT":		\
		f==(HAS_LOCALS | WP_TEXT)?("HAS_LOCALS, WP_TEXT"):0

#define USAGE "Usage: objdump <file(s)>"

void	dump_bytes(unsigned char *data,
		   unsigned int *start,
		   unsigned int n);

void   	dump_content(char *p_strtab,
		     Elf64_Ehdr *ehdr,
		     Elf64_Shdr *shdr, int i);

void   	dump_content32(char *p_strtab,
		       Elf32_Ehdr *ehdr,
		       Elf32_Shdr *shdr, int i);

uint32_t dump_bfd_flags(Elf64_Ehdr *ehdr,
			Elf64_Shdr *shdr,
			void *p_strtab);

uint32_t dump_bfd_flags32(Elf32_Ehdr *ehdr,
			  Elf32_Shdr *shdr,
			  void *p_strtab);

void	print_sec6on(char *p_strtab,
		     Elf64_Ehdr *ehdr,
		     Elf64_Shdr *shdr);

void	print_sec6on32(char *p_strtab,
		       Elf32_Ehdr *ehdr,
		       Elf32_Shdr *shdr);

void	dump_bytes(unsigned char *data,
		   unsigned int *start,
		   unsigned int n);

void	dump_content(char *p_strtab,
		     Elf64_Ehdr *ehdr,
		     Elf64_Shdr *shdr,
		     int i);

void dump_elf(void *map);
void dump_elf32(void *map);
void dump_bytes();
void print_flags(uint32_t flags);
int check_hname(char *hname);
int is_elf(Elf64_Ehdr *header);
void read_header(const int fd, int fsize);

extern char *g_input_file;

#endif
