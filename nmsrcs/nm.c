/*
** nm.c for nm in /home/catuss_a//Desktop/nmobjdump
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Mon Mar  7 15:14:32 2011 axel catusse
** Last update Sat Mar 12 16:25:46 2011 axel catusse
*/

#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <errno.h>
#include "nm.h"

static void		my_nm(char *filename, int ac)
{
  void			*data;
  Elf32_Ehdr		*elf;
  int			fd;
  long			size;

  if (xaccess(filename) == -1)
    return ;
  if ((fd = xopen(filename)) == -1)
    return ;
  if ((size = lseek(fd, 0, SEEK_END)) == -1)
    {
      fprintf(stderr, "error: lseek: %s\n", strerror(errno));
      return ;
    }
  if ((data = xmmap(fd, filename, size)) == MAP_FAILED)
    return ;
  elf = (Elf32_Ehdr*)data;
  if (elf->e_ident[EI_CLASS] == ELFCLASS32)
    elf32_format(data, filename, ac);
  else if (elf->e_ident[EI_CLASS] == ELFCLASS64)
    elf64_format((Elf64_Ehdr*)data, filename, ac);
  if (close(fd) == -1)
    fprintf(stderr, "error: munmap: %s\n", strerror(errno));
  if (munmap(data, size) == -1)
    fprintf(stderr, "error: munmap: %s\n", strerror(errno));
}

int			main(int ac, char **av)
{
  int			i;

  i = 0;
  if (ac > 1)
    {
      while (++i < ac)
	my_nm(av[i], ac);
    }
  else
    my_nm("./a.out", ac);
  return (1);
}
