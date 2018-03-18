/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include "objdump.h"

void dump_content32(char *p_strtab,
					Elf32_Ehdr *ehdr,
					Elf32_Shdr *shdr,
					int i)
{
		unsigned int	add;
		unsigned char	*data;
		unsigned int	start;
		size_t			n;

		n ^= n;
		start = n;
		add = shdr[i].sh_addr;
		data = (unsigned char*)((char*)ehdr + shdr[i].sh_offset);
		printf("Contents of section %s:\n",
			   &p_strtab[shdr[i].sh_name]);
		while (n < shdr[i].sh_size)
		{
				if (n % 16 == 0)
				{
						printf(" %04x ", add);
						add += 16;
				}
				printf("%02x", data[n]);
				n = -~n;
				if (n % 4 == 0 && n % 16 && n < shdr[i].sh_size)
						printf(" ");
				if (n % 16 == 0 || n >= shdr[i].sh_size)
						dump_bytes(data, &start, n);
		}
}

void print_sec6on32(char *p_strtab,
					Elf32_Ehdr *ehdr,
					Elf32_Shdr *shdr)
{
		int	n;
		int	shnum;

		n ^= n ;
		shnum = (int)(ehdr->e_shnum);
		while (n < shnum)
		{
				if (shdr[n].sh_size
					&& check_hname(p_strtab + shdr[n].sh_name))
				{
						dump_content32(p_strtab, ehdr, shdr, n);
				}
				n = -~n;
		}
}
