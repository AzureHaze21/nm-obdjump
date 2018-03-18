##
## EPITECH PROJECT, 2018
## 
## File description:
## 
##

NM = ./my_nm

OBJDUMP = ./my_objdump

CC	= gcc

RM	= rm -f

SRC_NM	= ./nm/src/main.c \
	  ./nm/src/nm.c \
	  ./nm/src/symlist.c \
	  ./nm/src/symtype.c \

SRC_OBJDUMP = ./objdump/src/dump.c \
	  ./objdump/src/flags.c \
	  ./objdump/src/flags32.c \
	  ./objdump/src/main.c \
	  ./objdump/src/objdump.c \
	  ./objdump/src/objdump32.c 

OBJS_NM	= $(SRC_NM:.c=.o)

OBJS_OBJDUMP = $(SRC_OBJDUMP:.c=.o)

CFLAGS = -I./nm/inc/ -I./objdump/inc

CFLAGS += -W -Wall -Wextra

all: $(NM) $(OBJDUMP)

nm: $(NM)

objdump: $(OBJDUMP)

$(NM): $(OBJS_NM)
	 $(CC) $(OBJS_NM) -o $(NM) $(LDFLAGS)

$(OBJDUMP): $(OBJS_OBJDUMP)
	 $(CC) $(OBJS_OBJDUMP) -o $(OBJDUMP) $(LDFLAGS)

clean:
	$(RM) $(OBJS_NM)
	$(RM) $(OBJS_OBJDUMP)

fclean: clean
	$(RM) $(NM)
	$(RM) $(OBJDUMP)

re: fclean all

.PHONY: all clean fclean re
