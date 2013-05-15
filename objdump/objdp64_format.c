/*
** objdp64_format.c for obj in /home/catuss_a//Desktop/nmobjdump
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun Mar 13 22:02:35 2011 axel catusse
** Last update Sun Mar 13 22:34:44 2011 axel catusse
*/

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "objdump.h"

static int		check_elf_format(Elf64_Ehdr *elf, char *path)
{
  if (elf->e_ident[EI_MAG0] != ELFMAG0
      || elf->e_ident[EI_MAG1] != ELFMAG1
      || elf->e_ident[EI_MAG2] != ELFMAG2
      || elf->e_ident[EI_MAG3] != ELFMAG3
      || (elf->e_type != ET_EXEC && elf->e_type
	  != ET_REL && elf->e_type != ET_DYN))
    {
      fprintf(stderr, "nm: %s: File format not recognized\n", path);
      return (-1);
    }
  return (1);
}

static void		print_ascii(unsigned int j,
				    unsigned int *z,
				    unsigned char *w,
				    char *t)
{
  int			x;

  x = j;
  while (x % 16 != 0)
    {
      if (x % 4 == 0 && x % 16)
	printf(" ");
      printf("  ");
      ++x;
    }
  printf("  ");
  while (*z < j)
    {
      if (isprint(w[*z]))
	printf("%c", t[*z]);
      else
	printf(".");
      (*z)++;
    }
  while ((*z)++ % 16 != 0)
    printf(" ");
  *z = j;
  printf("\n");
}

static void		print_sect(char *strtab,
				   Elf64_Ehdr *elf,
				   Elf64_Shdr *shdr,
				   int i)
{
  unsigned char		*w;
  unsigned int		j;
  int			addr;
  unsigned int		z;

  addr = shdr[i].sh_addr;
  printf("Contents of section %s:\n", &strtab[shdr[i].sh_name]);
  w = (unsigned char*)((char*)elf + shdr[i].sh_offset);
  j = 0;
  z = 0;
  while (j < shdr[i].sh_size)
    {
      if (j % 16 == 0)
	printf(" %04x ", addr);
      printf("%02x", w[j++]);
      if (j % 4 == 0 && j % 16 && j < shdr[i].sh_size)
	printf(" ");
      if (j % 16 == 0)
	addr += 16;
      if (j % 16 == 0 || j >= shdr[i].sh_size)
	print_ascii(j, &z, w, (char*)w);
    }
}

static void		print_section64(char *strtab,
					Elf64_Ehdr *elf,
					Elf64_Shdr *shdr)
{
  int			i;

  i = -1;
  while (++i < elf->e_shnum)
    {
      if (shdr[i].sh_size
	  && strcmp(&strtab[shdr[i].sh_name], ".strtab")
	  && strcmp(&strtab[shdr[i].sh_name], ".symtab")
	  && strcmp(&strtab[shdr[i].sh_name], ".shstrtab")
	  && strcmp(&strtab[shdr[i].sh_name], ".bss"))
      	{
	  print_sect(strtab, elf, shdr, i);
	}
    }
}

void			objdp64_format(void *data, char *filename)
{
  Elf64_Ehdr		*elf;
  Elf64_Shdr		*shdr;
  char			*strtab;

  elf = (Elf64_Ehdr*)data;
  if (check_elf_format(elf, filename) == -1)
    return ;
  shdr = (Elf64_Shdr*)(data + elf->e_shoff);
  strtab = (char*)(data + shdr[elf->e_shstrndx].sh_offset);
  printf("\n%s:%5cfile format\n", filename, ' ');
  printf("architecture: %s, flags 0x%08x:\n\n",
	 elf->e_machine == 3 ? "i386" : "notf", elf->e_flags);
  printf("start address 0x%016x\n\n", (int)elf->e_entry);
  print_section64(strtab, elf, shdr);
}
