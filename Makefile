##
## Makefile for Makefile in /home/catuss_a//Desktop/nmobjdump
## 
## Made by axel catusse
## Login   <catuss_a@epitech.net>
## 
## Started on  Wed Mar  9 15:53:57 2011 axel catusse
## Last update Sun Mar 13 22:46:51 2011 axel catusse
##

IFLAG		=	-I./nmsrcs
CFLAGS		+=	-W -Wall $(IFLAG)
RM		=	rm -rf
CC		=	gcc

#####################################################################
# NM
#####################################################################
NM		=	my_nm
DIR_NM		=	./nmsrcs
DIR_32F		=	$(DIR_NM)/elf32_format
DIR_64F		=	$(DIR_NM)/elf64_format
NM_OBJS		=	$(NM_SRCS:.c=.o)

NM_SRCS		=	$(DIR_NM)/nm.c			\
			$(DIR_32F)/global_symbols.c	\
			$(DIR_32F)/weak_symbol.c	\
			$(DIR_32F)/get_flag.c		\
			$(DIR_32F)/elf32_format.c	\
			$(DIR_32F)/sort_by_ascii.c	\
			$(DIR_32F)/print_sym.c		\
			$(DIR_32F)/xfunc.c		\
			$(DIR_32F)/local_symbols.c	\
			$(DIR_64F)/global_symbols64.c	\
			$(DIR_64F)/weak_symbol64.c	\
			$(DIR_64F)/get_flag64.c		\
			$(DIR_64F)/elf64_format.c	\
			$(DIR_64F)/sort_by_ascii64.c	\
			$(DIR_64F)/print_sym64.c	\
			$(DIR_64F)/local_symbols64.c

#####################################################################
# OBJDUMP -f -s
#####################################################################
OBJDUMP		=	my_objdump
DIR_OBJDP	=	./objdump
OBJDP_OBJS	=	$(OBJDUMP_SRCS:.c=.o)

OBJDUMP_SRCS	=	$(DIR_OBJDP)/objdump.c		\
			$(DIR_OBJDP)/xfunc.c		\
			$(DIR_OBJDP)/objdp32_format.c	\
			$(DIR_OBJDP)/objdp64_format.c

#####################################################################
# RULES
#####################################################################

all		:	$(NM) $(OBJDUMP)

$(NM)		:	$(NM_OBJS)
		$(CC) -o $(NM) $(NM_OBJS)

$(OBJDUMP)	:	$(OBJDP_OBJS)
		$(CC) -o $(OBJDUMP) $(OBJDP_OBJS)

clean		:
		$(RM) $(NM_OBJS) $(OBJDP_OBJS)
		@$(RM) *.c~
		@$(RM) *#
		@$(RM) $(DIR_NM)/*#
		@$(RM) $(DIR_NM)/*.c~

fclean		:	clean
		$(RM) $(NM) $(OBJDUMP)

re		:	fclean all

.PHONY		:	all clean fclean re

.SUFFIXES	:	.c .o