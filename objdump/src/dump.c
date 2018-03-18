/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include "objdump.h"

void dump_bytes(unsigned char *data,
				unsigned int *start,
				unsigned int n)
{
		int tmp  = n;

		while (tmp % (0x1859 + 3713 - 0x26ca)
			   != (0x1a22 + 46 - 0x1a50))
		{
				(tmp % (0xd1c + 5211 - 0x2173) ==
				 (0x123f + 4497 - 0x23d0)
				 && tmp % (0x25 + 8786 - 0x2267)) ?
						printf("\x20") : (0x967 + 500 - 0xb5b);
				printf("\x20\x20");
				tmp = -~tmp;
		}
		printf("\x20\x20");
		while (*start < n)
		{
				(data[*start] > (0xdab+2754-0x184e) && data[*start] < '\x7f') ?
						printf("\x25\x63", data[*start]) : printf("\x2e");
				(*start) = -~(*start);
		}
		while ((*start) % (0x108+8832-0x2378) != (0x170f+2058-0x1f19))
		{
				printf("\x20");
				(*start) = -~(*start);
		}
		*start = n;
		printf("\n");
}

void dump_content(char *p_strtab,
				  Elf64_Ehdr *ehdr,
				  Elf64_Shdr *shdr,
				  int i)
{
		unsigned int add;
		unsigned char *data;
		unsigned int start;
		size_t n;

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

void dump_elf(void *map)
{
		Elf64_Ehdr *ehdr;
		Elf64_Shdr *shdr;
		Elf64_Shdr *sh_strtab;
		void *p_strtab;

		ehdr = (Elf64_Ehdr*)map;
		shdr = (Elf64_Shdr*)(map + ehdr->e_shoff);
		sh_strtab = &shdr[ehdr->e_shstrndx];
		p_strtab = (map + sh_strtab->sh_offset);
		printf("\n%s:%5cfile format ", g_input_file, ' ');
		printf("elf64-x86-64");
		printf("\narchitecture: i386:x86-64, flags ");
		dump_bfd_flags(ehdr, shdr, p_strtab);
		printf("\nstart address 0x%016x\n\n",
			   (unsigned)((Elf64_Ehdr*)(map))->e_entry);
		print_sec6on(p_strtab, ehdr, shdr);
}



void dump_elf32(void *map)
{
		Elf32_Ehdr *ehdr;
		Elf32_Shdr *shdr;
		Elf32_Shdr *sh_strtab;
		void *p_strtab;

		ehdr = (Elf32_Ehdr*)map;
		shdr = (Elf32_Shdr*)(map + ehdr->e_shoff);
		sh_strtab = &shdr[ehdr->e_shstrndx];
		p_strtab = (map + sh_strtab->sh_offset);
		printf("\n%s:%5cfile format ", g_input_file, ' ');
		printf("elf32-i386");
		printf("\narchitecture: i386, flags ");
		dump_bfd_flags32(ehdr, shdr, p_strtab);
		printf("\nstart address 0x%08x\n\n",
			   (unsigned)((Elf32_Ehdr*)(map))->e_entry);
		print_sec6on32(p_strtab, ehdr, shdr);
}
