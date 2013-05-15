/*
** weak_symbol.c for nm in /home/catuss_a//Desktop/nmobjdump
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Thu Mar 10 23:25:55 2011 axel catusse
** Last update Thu Mar 10 23:28:20 2011 axel catusse
*/

#include "nm.h"

char			weak_symbol(Elf32_Sym *symtab)
{
  if (ELF32_ST_BIND(symtab->st_info) == STB_WEAK)
    {
      if (ELF32_ST_TYPE(symtab->st_info) == STT_OBJECT)
	{
	  if (symtab->st_shndx != SHN_UNDEF)
	    return 'V';
	  return 'v';
	}
      if (symtab->st_shndx != SHN_UNDEF)
	return 'W';
      return 'w';
    }
  return (NO_TYPE);
}
