/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include "objdump.h"

uint32_t dump_bfd_flags32(Elf32_Ehdr *ehdr,
						  Elf32_Shdr *shdr,
						  void *p_strtab)
{
		uint32_t	flags;
		int			i;
		const char	*p_str;

		flags ^= flags;
		if (ehdr->e_phnum)
				flags |= D_PAGED;
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
				ehdr->e_type == ET_DYN ? DYNAMIC : 0;
		printf("0x%08x:\n", flags);
		print_flags(flags);
		return (flags);
}
