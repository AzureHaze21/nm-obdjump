/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include "objdump.h"

char *g_input_file;

int	check_hname(char *hname)
{
	if (strcmp(hname, ".bss")
	    && strcmp(hname, ".tbss")
	    && strcmp(hname, ".symtab")
	    && !strstr(hname, "strtab")
	    && strcmp(hname, ".rela.eh_frame"))
	{
		return (1);
	}
	return (0);
}

void print_sec6on(char *p_strtab,
		  Elf64_Ehdr *ehdr,
		  Elf64_Shdr *shdr)
{
	int n = 0;
	int shnum = (int)(ehdr->e_shnum);
	char *name = NULL;

	while (n < shnum)
	{
		name = (char*)(p_strtab + shdr[n].sh_name);
		if (shdr[n].sh_size
		    && shdr[n].sh_type != SHT_NOBITS
		    && shdr[n].sh_type != SHT_SYMTAB
		    && name
		    && check_hname(name))
		{
			dump_content(p_strtab, ehdr, shdr, n);
		}
		n = -~n;
	}
}

void read_header(const int fd, int fsize)
{
	char *map = mmap(0, fsize, PROT_READ, MAP_PRIVATE, fd, 0);

	if ((void*)map == MAP_FAILED)
	{
		printf("objdump: Warning: '%s' is not an ordinary file\n",
		       g_input_file);
		return;
	}
	if (fsize < 4 ||
	    strncmp((char*)map, "\x7f\x45\x4c\x46", 4))
	{
		printf("objdump: %s: File format not recognized\n",
		       g_input_file);
		munmap(map, fsize);
		return ;
	}
	if ((unsigned char)map[4] == ELF32)
		dump_elf32(map);
	else if ((unsigned char)map[4] == ELF64)
		dump_elf(map);
	munmap(map, fsize);
}
