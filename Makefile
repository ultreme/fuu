NAME 	= fuu
CC	= gcc
RM	= rm -f
CFLAGS	= -W -Wall -pedantic -ansi -Wshadow -Werror -O3

SRCS	= fuu.c
OBJS	= $(SRCS:.c=.o)

# Rules

all: 	$(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
