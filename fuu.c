/*
 * Copyright (c) 2010 Sebastien Rannou <rannou.sebastien@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>

#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fuu.h"

extern char *__progname;

void usage(void);
void opt_set_lang(const char *);
void opt_set_strength(const char *);
void opt_set_dictionnary(char *);

static struct fuu fu_main;

int
get_nb_names(void)
{
	int		res;

	res = 1;
	switch (fu_main.strength) {
	case STRENGTH_TINY:
		res += random() % 3;
		break;
	case STRENGTH_MEDIUM:
		res += random() % 5;
		break;
	case STRENGTH_STRONG:
		res += random() % 10;
		break;
	case STRENGTH_ULTIMATE:
		res += random() % 30;
		break;
	default:
		usage();
		/* NOTREACHED */		
	}
	return res;
}

int
get_nb_sufix(void)
{
	int		res;

	res = 1 + random() % 2;
	return res;
}

int
get_nb_prefix(void)
{
	int		res;

	res = 1 + random() % 2;
	return res;
}

/*
 * Construction of an insult is as follow:
 *
 * Prefix + Link + X * (X * Words.Prefix + Words.Name + X * Words.Suffix)
 *
 * Where X is a random number
 * Words is a chapter from the dictionnary related to the language configuration
 * Link,Prefix,Suffix are words
 *
 * (see json file for a concrete example, it follows the same naming convention)
 */
void
fuu(void)
{
	struct json_object *	package;
	struct json_object *	words;
	int			nb_names, nb_prefix, nb_sufix;
	int			i, j;

	if ((package = db_get_package(fu_main.jo_dictionnary, 
				      fu_main.lang)) == NULL) {
		errx(1, "unable to load language package for %s", fu_main.lang);
	}
	if ((words = db_get_words(package, fu_main.gender)) == NULL)
		errx(1, "unable to load words");
	fprintf(stdout, "%s ", db_get_prefix(package));
	nb_names = get_nb_names();
	for (i = 0; i < nb_names; ++i) {
		if (i != 0)
			fprintf(stdout, "%s ", db_get_link(package));
		nb_prefix = get_nb_prefix();
		for (j = 0; j < nb_prefix; ++j) {
			fprintf(stdout, "%s ", db_get_name_prefix(words));
		}
		fprintf(stdout, "%s ", db_get_name(words));
		nb_sufix = get_nb_sufix();
		for (j = 0; j < nb_sufix; ++j) {
			fprintf(stdout, "%s ", db_get_name_suffix(words));
		}
	}
	fprintf(stdout, "\n");
}

int
main(int argc, char *argv[])
{	
	extern char	*optarg;
	extern int	optind;
	int		ch, lflag = 0, dflag = 0, sflag = 0, gflag = 0;

	memset(&fu_main, 0, sizeof(fu_main));
	srandom(time(0) + getpid());
	while ((ch = getopt(argc, argv, "g:l:d:s:")) != -1) {
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
		case 'g':
		        strlcpy(fu_main.gender, optarg, sizeof(fu_main.gender));
			gflag = 1;
			break;
		default:
			usage();
			/* NOTREACHED */
		}
		argc -= optind;
		argv += optind;
	}

	/* Default settings */
	if (lflag == 0)
		strlcpy(fu_main.lang, DEFAULT_LANG, sizeof(fu_main.lang));
	if (dflag == 0)
		opt_set_dictionnary(PATH_DICTIONNARY);
	if (sflag == 0)
		opt_set_strength(DEFAULT_STRENGTH);
	if (gflag == 0)
		strlcpy(fu_main.gender, DEFAULT_GENDER, sizeof(fu_main.gender));
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
	else if (strcasecmp(strength, "ULTIMATE") == 0)
		fu_main.strength = STRENGTH_ULTIMATE;
	else
		errx(1, "invalid argument for strength (%s), try"
		     "one of the following: TINY, MEDIUM, STRONG, ULTIMATE.", 
		     strength);
}

void
opt_set_dictionnary(char *dictionnary)
{
	if ((fu_main.jo_dictionnary = json_object_from_file(dictionnary))
	    == NULL) {
		errx(1, "unable to load dictionnary %s", dictionnary);
	}
}

void
usage(void)
{
	(void)fprintf(stderr, 
		      "usage: %s [-g gender] [-l language] [-d dictionnary] [-s strength]\n",
		      __progname);
	exit(1);
}
