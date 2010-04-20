/*
** main.c for insultator in /home/mxs/code/insultator
** 
** Made by sebastien rannou
** Login   <mxs@epitech.net>
** 
** Started on  Tue Apr 20 12:53:11 2010 sebastien rannou
** Last update Tue Apr 20 19:48:36 2010 sebastien rannou
*/

#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fuu.h"

extern char *__progname;

void usage(void);
void opt_set_lang(const char *);
void opt_set_strength(const char *);
void opt_set_dictionnary(char *);

static struct fuu fu_main;

void
fuu(void)
{
	printf("%s\n", json_object_to_json_string(fu_main.jo_dictionnary));
}

int
main(int argc, char *argv[])
{	
	extern char	*optarg;
	extern int	optind;
	int		ch, lflag = 0, dflag = 0, sflag = 0;

	memset(&fu_main, 0, sizeof(fu_main));
	while ((ch = getopt(argc, argv, "l:d:s:")) != -1) {
		switch (ch) {
		case 'l':
			lflag = 1;
			strlcpy(fu_main.lang, optarg, sizeof(fu_main.lang));
			break;
		case 'd':
			dflag = 1;
			opt_set_dictionnary(optarg);
			break;
		case 's':
			sflag = 1;
			opt_set_strength(optarg);
			break;
		default:
			usage();
			/* NOTREACHED */
		}
		argc -= optind;
		argv += optind;
	}

	/* Set a default lang */
	if (lflag == 0)
		strlcpy(fu_main.lang, DEFAULT_LANG, sizeof(fu_main.lang));
	/* Set a default dictionnary */
	if (dflag == 0)
		opt_set_dictionnary(PATH_DICTIONNARY);
	/* Set a default strength */
	if (sflag == 0)
		opt_set_strength(DEFAULT_STRENGTH);
	fuu();
	return 0;
}

void
opt_set_strength(const char *strength)
{
	if (strcasecmp(strength, "TINY") == 0)
		fu_main.strength = STRENGTH_TINY;
	else if (strcasecmp(strength, "MEDIUM") == 0)
		fu_main.strength = STRENGTH_MEDIUM;
	else if (strcasecmp(strength, "STRONG") == 0)
		fu_main.strength = STRENGTH_STRONG;
	else
		errx(1, "invalid argument for strength (%s), try"
		     "one of the following: TINY, MEDIUM, STRONG.", strength);
}

void
opt_set_dictionnary(char *dictionnary)
{
	if ((fu_main.jo_dictionnary = json_object_from_file(dictionnary)) == 0)
		errx(1, "unable to load dictionnary %s", dictionnary);
}

void
usage(void)
{
	(void)fprintf(stderr, 
		      "usage: %s [-l language] [-d dictionnary] [-s strength]",
		      __progname);
	exit(1);
}
