/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include <string.h>
#include "nm.h"

char get_symtype(Elf64_Shdr *shdr,
		 Elf64_Sym *sym,
		 void *strtab)
{
	char res = '?';
	char *sh_name = shdr ? (char*)strtab + shdr->sh_name : NULL;

	if ((ELF64_ST_BIND(sym->st_info) == STB_WEAK))
	{
		res = ELF64_ST_TYPE(sym->st_info) == STT_OBJECT ? 'v' : 'w';
		res -= sym->st_shndx == SHN_UNDEF ? 0 : 32;
	}
	else if (sym->st_shndx == SHN_UNDEF)
		res = 'U';
	else if (sym->st_shndx == SHN_ABS)
		res = 'A';
	else if (sh_name && !strcmp(sh_name, ".bss"))
		res = 'b';
	else if ((ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE))
		res = 'u';
	else if (sh_name && (!strcmp(sh_name, ".text") ||
			     strstr(sh_name, "init") ||
			     strstr(sh_name, "fini")))
		res = 't';
	else if ((shdr && (shdr->sh_flags == SHF_ALLOC)) ||
		 (sh_name && !strcmp(sh_name, ".rodata")))
		res = 'r';
	else if (shdr && (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT
			  || ELF64_ST_TYPE(sym->st_info) == STT_NOTYPE))
		res = res == 'b' ? res : 'd';
	if (IS_LOWER(res) &&
	    (res != 'u' && res != 'v' && res != 'w'))
		res -=
			(ELF64_ST_BIND(sym->st_info) == STB_GLOBAL) ? 32 : 0;
	if (res == '?' && (ELF64_ST_TYPE(sym->st_info) == STT_COMMON
			   || ELF64_ST_TYPE(sym->st_info) == STT_OBJECT))
		res = 'C';
	return (res);
}

char get_symtype32(Elf32_Shdr *shdr,
		   Elf32_Sym *sym,
		   void *strtab)
{
	char res;
	char *sh_name = (char*)strtab + shdr->sh_name;

	res = '?';
	if ((ELF32_ST_BIND(sym->st_info) == STB_WEAK))
	{
		res = ELF32_ST_TYPE(sym->st_info) == STT_OBJECT ? 'v' : 'w';
		res -= sym->st_shndx == SHN_UNDEF ? 0 : 32;
	}
	else if (sym->st_shndx == SHN_UNDEF)
		res = 'U';
	else if (strstr(sh_name, "bss"))
		res = 'b';
	else if ((ELF32_ST_BIND(sym->st_info) == STB_GNU_UNIQUE))
		res = 'u';
	else if (!strcmp(sh_name, ".text") ||
		 strstr(sh_name, "init") ||
		 strstr(sh_name, "fini"))
		res = 't';
	else if (shdr->sh_flags == (SHF_ALLOC | SHF_WRITE))
		res = 'd';
	else if ((shdr->sh_flags == SHF_ALLOC) ||
		 !strcmp(sh_name, ".rodata"))
		res = 'r';
	if (IS_LOWER(res) &&
	    (res != 'u' && res != 'v' && res != 'w'))
		res -=
			(ELF32_ST_BIND(sym->st_info) == STB_GLOBAL) ? 32 : 0;
	return (res);
}
