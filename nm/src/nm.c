/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include <stdio.h>
#include <string.h>
#include "nm.h"

char *g_input_file;

void nm(void *map)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr*)map;
	Elf64_Shdr *shdr = (Elf64_Shdr*)(map + ehdr->e_shoff);
	Elf64_Shdr *sh_strtab = &shdr[ehdr->e_shstrndx];
	void *p = map + sh_strtab->sh_offset;
	t_sym *list = NULL;  
	int i = -1;
	int j = -1;

	while(++i < (int)ehdr->e_shnum) {
		if (shdr[i].sh_type == SHT_SYMTAB) {
			void *p_strtab = (char*)(map + shdr[shdr[i].sh_link].sh_offset);
			Elf64_Sym *sym = (Elf64_Sym*)(map + shdr[i].sh_offset);
			while (++j < (int)(shdr[i].sh_size / shdr[i].sh_entsize)) {
				if (sym[j].st_info != 0x3 && sym[j].st_info != 0x4) {
					Elf64_Shdr *s = (sym[j].st_shndx < ehdr->e_shnum) ?
						&shdr[sym[j].st_shndx] : NULL;
					if (*(char*)p_strtab + sym[j].st_name) {
						push_sym(&list,
							 sym[j].st_value,
							 get_symtype(s, &sym[j], p),
							 (char*)p_strtab + sym[j].st_name);
					}
				}
			}
		}
	}
	sort_symlist(&list, 0);
	free_symlist(list);
}

void nm32(void *map)
{
	Elf32_Ehdr *ehdr = (Elf32_Ehdr*)map;
	Elf32_Shdr *shdr = (Elf32_Shdr*)(map + ehdr->e_shoff);
	Elf32_Shdr *sh_strtab = &shdr[ehdr->e_shstrndx];
	void *p_strtab;
	void *p = map + sh_strtab->sh_offset;
	t_sym *list = NULL;  
	int i = -1;
	int j = -1;

	while(++i < (int)ehdr->e_shnum) {
		if (shdr[i].sh_type == SHT_SYMTAB) {
			p_strtab = (char*)(map + shdr[shdr[i].sh_link].sh_offset);
			Elf32_Sym *sym = (Elf32_Sym*)(map + shdr[i].sh_offset);
			while (++j < (int)(shdr[i].sh_size / shdr[i].sh_entsize)) {
				if (sym[j].st_info != 0x3 && sym[j].st_info != 0x4) {
					Elf32_Shdr *s = (sym[j].st_shndx < ehdr->e_shnum) ?
						&shdr[sym[j].st_shndx] : NULL;
					if (*(char*)p_strtab + sym[j].st_name) {
						push_sym(&list,
							 sym[j].st_value,
							 get_symtype32(s, &sym[j], p),
							 (char*)p_strtab + sym[j].st_name);
					}
				}
			}
		}
	}
	sort_symlist(&list, 1);
	free_symlist(list);
}

void read_header(const int fd, int fsize)
{
	char *map = mmap(0, fsize, PROT_READ, MAP_PRIVATE, fd, 0);

	if ((void*)map == MAP_FAILED)
	{
		printf("nm: Warning: '%s' is not an ordinary file\n",
		       g_input_file);
		return;
	}
	if (fsize < 4 ||
	    strncmp((char*)map, "\x7f\x45\x4c\x46", 4))
	{
		printf("nm: %s: File format not recognized\n",
		       g_input_file);
		munmap(map, fsize);
		return ;
	}
	if ((unsigned char)map[4] == ELF32)
		nm32(map);
	else if ((unsigned char)map[4] == ELF64)
		nm(map);
	munmap(map, fsize);
}
