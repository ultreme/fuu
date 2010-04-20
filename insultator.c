/*
** main.c for insultator in /home/mxs/code/insultator
** 
** Made by sebastien rannou
** Login   <mxs@epitech.net>
** 
** Started on  Tue Apr 20 12:53:11 2010 sebastien rannou
** Last update Tue Apr 20 13:14:45 2010 sebastien rannou
*/

#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

extern char *__progname;

void usage(void);

int
main(int argc, char *argv[])
{	
	extern char	*optarg;
	extern int	optind;
	int		ch;
	
	while ((ch = getopt(argc, argv, "l:")) != -1) {
		switch (ch) {
		case 'l':
		       
			break;
		default:
			usage();
			/* NOTREACHED */
		}
		argc -= optind;
		argv += optind;
	}
	
	return 0;
}

void
usage(void)
{
	(void)fprintf(stderr, "usage: %s", __progname);
	exit(1);
}
