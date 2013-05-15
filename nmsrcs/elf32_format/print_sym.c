/*
** print_sym.c for nm in /home/catuss_a//Desktop/nmobjdump
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Fri Mar 11 00:13:08 2011 axel catusse
** Last update Sun Mar 13 22:44:34 2011 axel catusse
*/

#include <stdlib.h>
#include <stdio.h>
#include "nm.h"

static Elf32_Sym	**get_symtab_cpy(Elf32_Sym *symtab,
					 unsigned int size)
{
  Elf32_Sym		**new;
  unsigned int		i;

  new = malloc(sizeof(*new) * (size + 1));
  i = -1;
  while (++i < size)
    new[i] = &symtab[i];
  return (new);
}

static void		print_line_sym(Elf32_Sym **symtab_cpy,
				       char *strsymtab,
				       Elf32_Shdr *shdr,
				       int i)
{
  char			type;

  if (symtab_cpy[i]->st_name != 0
      && symtab_cpy[i]->st_name != 1)
    {
      if (symtab_cpy[i]->st_info != 4)
	{
	  type = get_flag(symtab_cpy[i], shdr);
	  if (type != 'U' && type != 'w')
	    printf("%08x ", symtab_cpy[i]->st_value);
	  else
	    printf("%9c", ' ');
	  printf("%c", type);
	  printf(" %s\n", &strsymtab[symtab_cpy[i]->st_name]);
	}
    }
}

void			print_sym(Elf32_Shdr *symsection,
				  Elf32_Sym *symtab,
				  char *strsymtab,
				  Elf32_Shdr *shdr)
{
  unsigned int		i;
  unsigned int		size;
  Elf32_Sym		**symtab_cpy;

  size = symsection->sh_size / sizeof(*symtab);
  if ((symtab_cpy = get_symtab_cpy(symtab, size)) == NULL)
    {
      fprintf(stderr, "error: malloc: failed.\n");
      return ;
    }
  sort_by_ascii(symtab_cpy, 0, size - 1, strsymtab);
  i = - 1;
  while (++i < size)
    print_line_sym(symtab_cpy, strsymtab, shdr, i);
  free(symtab_cpy);
}
