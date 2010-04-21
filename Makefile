NAME 	= fuu
CC	= gcc
RM	= rm -f
CFLAGS	= -W -Wall -pedantic -ansi -Wshadow -Werror -g -I/usr/local/include
LDFLAGS	= -L/usr/local/lib -ljson

SRCS	= fuu.c db.c
OBJS	= $(SRCS:.c=.o)

# Rules

all: 	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS) *.core

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
