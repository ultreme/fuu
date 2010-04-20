/*
** main.c for insultator in /home/mxs/code/insultator
** 
** Made by sebastien rannou
** Login   <mxs@epitech.net>
** 
** Started on  Tue Apr 20 12:53:11 2010 sebastien rannou
** Last update Tue Apr 20 23:46:01 2010 sebastien rannou
*/

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
struct json_object * db_get_package(void);
struct json_object * db_get_words(void);
char * db_get_prefix(struct json_object *);
char * db_get_name_prefix(struct json_object *);

static struct fuu fu_main;

/*
 * for an unknown reason, this structure is kept private in json-c's library 
 * but some public macros require its definition (foreachC), should report this
 */
struct json_object_iter {
	char *key;
	struct json_object *val;
	struct lh_entry *entry;
};

int
get_nb_names(void)
{
	int		res;

	switch (fu_main.strength) {
	case STRENGTH_TINY:
		res = rand() % 5;
		break;
	case STRENGTH_MEDIUM:
		res = rand() % 15;
		break;
	default:
		res = rand() % 30;
	}
	return res;
}

int
get_nb_sufix(void)
{
	int		res;

	res = 1 + rand() % 3;
	return res;
}

int
get_nb_prefix(void)
{
	int		res;

	res = 1 + rand() % 3;
	return res;
}

void
fuu(void)
{
	struct json_object *	package;
	struct json_object *	words;
	int			nb_names, nb_prefix, nb_sufix;
	int			i, j;

	if ((package = db_get_package()) == NULL)
		errx(1, "unable to load language package for %s", fu_main.lang);
	if ((words = db_get_words()) == NULL)
		errx(1, "unable to load words");
	fprintf(stdout, "%s", db_get_prefix(package));
	nb_names = get_nb_names();
	for (i = 0; i < nb_names; ++i) {
		nb_prefix = get_nb_prefix();
		for (j = 0; j < nb_prefix; ++j) {
			fprintf(stdout, " %s", db_get_name_prefix(package));
		}
		
		nb_sufix = get_nb_sufix();
		for (j = 0; j < nb_sufix; ++j) {
			
		}
	}
}

struct json_object *
db_get_package(void)
{
	struct json_object_iter	iter;

	json_object_object_foreachC(fu_main.jo_dictionnary, iter) {
		if (strcasecmp(iter.key, fu_main.gender) == 0) {
			return iter.val;
		}
	}
	return NULL;
}

struct json_object *
db_get_words(void)
{
	struct json_object_iter	iter;

	json_object_object_foreachC(fu_main.jo_dictionnary, iter) {
		if (strcasecmp(iter.key, fu_main.lang) == 0) {
			return iter.val;
		}
	}
	return NULL;
}

char *
db_get_prefix(struct json_object * package)
{
	struct json_object *	prefix;

	prefix = json_object_object_get(package, "prefix");
	if (prefix != NULL)
		return json_object_get_string(prefix);
	return NULL;
}

char *
db_get_name_prefix(struct json_object * words)
{
	words = words;
	/* @todo: peek a random name from words */
	return NULL;
}

int
main(int argc, char *argv[])
{	
	extern char	*optarg;
	extern int	optind;
	int		ch, lflag = 0, dflag = 0, sflag = 0, mflag = 0, wflag = 0;

	memset(&fu_main, 0, sizeof(fu_main));
	srand(time(0));
	while ((ch = getopt(argc, argv, "mwl:d:s:")) != -1) {
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
		case 'w':
			if (mflag == 0) {
				strlcpy(fu_main.gender, "WOMAN", sizeof(fu_main.gender));
				wflag = 1;
			}
			break;
		case 'm':
			if (wflag == 0) {
				strlcpy(fu_main.gender, "MAN", sizeof(fu_main.gender));
				mflag = 1;
			}
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
	if (mflag == 0 && wflag == 0)
		usage();
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
		      "usage: %s [-mw] [-l language] [-d dictionnary] [-s strength]",
		      __progname);
	exit(1);
}
