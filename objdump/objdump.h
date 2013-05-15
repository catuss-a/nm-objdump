/*
** objdump.h for objdump in /home/catuss_a//Desktop/nmobjdump
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun Mar 13 21:53:28 2011 axel catusse
** Last update Sun Mar 13 22:04:27 2011 axel catusse
*/

#ifndef _OBJDUMP_H_
# define _OBJDUMP_H_

#include <elf.h>

int			xaccess(char *filename);
int			xopen(char *filename);
void			*xmmap(int fd, char * filename, unsigned int size);

void			objdp32_format(void *data, char *filename);
void			objdp64_format(void *data, char *filename);

#endif /* !_OBJDUMP_H_ */
