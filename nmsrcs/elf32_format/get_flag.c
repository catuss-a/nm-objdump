/*
** get_flag.c for nm in /home/catuss_a//Desktop/nmobjdump
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Thu Mar 10 23:29:39 2011 axel catusse
** Last update Sat Mar 12 16:40:25 2011 axel catusse
*/

#include "nm.h"

static char		c_flag(Elf32_Sym *symtab)
{
  if (ELF32_ST_BIND(symtab->st_info) == STB_GLOBAL)
    {
      if (ELF32_ST_TYPE(symtab->st_info) == STT_OBJECT
	  && symtab->st_shndx == SHN_COMMON)
	return ('C');
    }
  return (NO_TYPE);
}

char			get_flag(Elf32_Sym *symtab,
				 Elf32_Shdr *shdr)
{
  char			type;

  if ((type = c_flag(symtab)) != NO_TYPE)
    return (type);
  if (ELF32_ST_BIND(symtab->st_info) == STB_GNU_UNIQUE)
    return ('U');
  if (symtab->st_shndx != SHN_ABS && symtab->st_shndx != SHN_COMMON)
    {
      if ((type = global_symbol(symtab, shdr)) != NO_TYPE)
	return (type);
      if ((type = local_symbol(symtab, shdr)) != NO_TYPE)
	return (type);
    }
  if ((type = weak_symbol(symtab)) != NO_TYPE)
    return (type);
  if (symtab->st_shndx == SHN_ABS)
    return (ELF32_ST_BIND(symtab->st_info) == STB_LOCAL ? 'a' : 'A');
  return ('?');
}
