/*
** fuu.h for fuu in /home/mxs/code/insultator
** 
** Made by sebastien rannou
** Login   <mxs@epitech.net>
** 
** Started on  Tue Apr 20 13:16:54 2010 sebastien rannou
** Last update Wed Apr 21 11:30:35 2010 sebastien rannou
*/

#ifndef _FUU_H_
#define _FUU_H_

#include <json/json.h>

#define PATH_DICTIONNARY	"dictionnary.json"

#define DEFAULT_LANG		"FR"
#define DEFAULT_STRENGTH	"MEDIUM"
#define DEFAULT_GENDER		"MAN"

enum fuustrength {
  STRENGTH_TINY, STRENGTH_MEDIUM, STRENGTH_STRONG, STRENGTH_ULTIMATE };

struct fuu {
	char lang[32];
	char gender[32];
	enum fuustrength strength;
	struct json_object *jo_dictionnary;
};

/*
 * Json related functions
 */

struct json_object *db_get_package(struct json_object *, char *);
struct json_object *db_get_words(struct json_object *, char *);
char *db_get_link(struct json_object *);
char *db_get_prefix(struct json_object *);
char *db_get_name_prefix(struct json_object *);
char *db_get_name_suffix(struct json_object *);
char *db_get_name(struct json_object *);

#endif 
