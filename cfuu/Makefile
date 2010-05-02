# Copyright (c) 2010 Sebastien Rannou <rannou.sebastien@gmail.com>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

NAME 	= fuu
CC	= gcc
RM	= rm -f
CFLAGS	= -W -Wall -pedantic -ansi -Wshadow -Werror -g -I/usr/local/include
LDFLAGS	= -L/usr/local/lib -ljson

SRCS	= fuu.c db.c compat.c
OBJS	= $(SRCS:.c=.o)

all: 	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS) *.core

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
