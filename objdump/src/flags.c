/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include "objdump.h"

void print_flags(uint32_t flags)
{
	size_t i;
	size_t n;
	unsigned char byte;
	int values[8];

	if (!flags)
		return ;
	i = -1;
	n = 0;
	while (++i < sizeof(flags))
	{
		byte = *((unsigned char*)&flags + i);
		values[n++] = (byte & 0x0F) << (i * 8);
		values[n++] = ((byte >> 4) & 0x0F) << (i * 8 + 4);
	}
	i = -1;
	n = 0;
	while (++i < 8)
	{
		if (FLAG_STR(values[i]) != 0)
		{
			printf(n ? ", %s" : "%s", FLAG_STR(values[i]));
			++n;
		}
	}
}

uint32_t dump_bfd_flags(Elf64_Ehdr *ehdr,
			Elf64_Shdr *shdr,
			void *p_strtab)
{
	uint32_t	flags;
	int			i;
	const char	*p_str;

	flags ^= flags;
	flags |= ehdr->e_phnum ? D_PAGED : 0;
	if (p_strtab)
	{
		i = -1;
		while (++i < ehdr->e_shnum)
		{
			p_str = (char*)(p_strtab + shdr[i].sh_name);
			if (!strcmp(p_str, ".symtab") ||
			    !strcmp(p_str, ".dynsym"))
				flags |= HAS_SYMS;
		}
	}
	flags |= ehdr->e_type == ET_EXEC ? EXEC_P :
		ehdr->e_type == ET_DYN ? DYNAMIC :
		ehdr->e_type == ET_REL ? HAS_RELOC : 0;
	printf("0x%08x:\n", flags);
	print_flags(flags);
	return (flags);
}
