/*
** sort_by_ascii.c for nm in /home/catuss_a//Desktop/nmobjdump
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Fri Mar 11 00:11:33 2011 axel catusse
** Last update Sat Mar 12 17:11:39 2011 axel catusse
*/

#include <string.h>
#include "nm.h"

static void		swapptr(Elf32_Sym **symtab_cpy, int fst, int snd)
{
  Elf32_Sym		*t;

  t = symtab_cpy[fst];
  symtab_cpy[fst] = symtab_cpy[snd];
  symtab_cpy[snd] = t;
}

void			sort_by_ascii(Elf32_Sym **symtab_cpy,
				      int begin,
				      int end,
				      char *strsymtab)
{
  int			left;
  int			right;
  char			*pivot;

  if (begin >= end)
    return ;
  right = end + 1;
  left = begin - 1;
  pivot = &strsymtab[symtab_cpy[begin]->st_name];
  while (42)
    {
      --right;
      while (strcmp(&strsymtab[symtab_cpy[right]->st_name], pivot) > 0)
	--right;
      ++left;
      while (strcmp(&strsymtab[symtab_cpy[left]->st_name], pivot) < 0)
	++left;
      if (left < right)
	swapptr(symtab_cpy, left, right);
      else
	break;
    }
  sort_by_ascii(symtab_cpy, begin, right, strsymtab);
  sort_by_ascii(symtab_cpy, right + 1, end, strsymtab);
}
