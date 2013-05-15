/*
** xfunc.c for nm in /home/catuss_a//Desktop/nmobjdump
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Fri Mar 11 00:14:36 2011 axel catusse
** Last update Fri Mar 11 00:26:15 2011 axel catusse
*/

#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

int			xaccess(char *filename)
{
  if (access(filename, F_OK) == -1)
    {
      printf("nm: '%s': No such file\n", filename);
      return (-1);
    }
  return (0);
}

int			xopen(char *filename)
{
  int			fd;

  if ((fd = open(filename, O_RDONLY, 0)) == -1)
    {
      fprintf(stderr, "nm: %s: File format not recognized\n", filename);
      return (-1);
    }
  return (fd);
}

void			*xmmap(int fd, char * filename, unsigned int size)
{
  void			*data;

  if ((data = mmap(NULL, size,
		   PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
      close(fd);
      fprintf(stderr, "nm: Warning: '%s' is not an ordinary file\n", filename);
      return (MAP_FAILED);
    }
  return (data);
}
