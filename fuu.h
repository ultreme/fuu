/*
** fuu.h for fuu in /home/mxs/code/insultator
** 
** Made by sebastien rannou
** Login   <mxs@epitech.net>
** 
** Started on  Tue Apr 20 13:16:54 2010 sebastien rannou
** Last update Tue Apr 20 15:15:53 2010 sebastien rannou
*/

#ifndef _FUU_H_
#define _FUU_H_

#include <json/json.h>

#define PATH_DICTIONNARY	"dictionnary.json"

#define DEFAULT_LANG		"FR"
#define DEFAULT_STRENGTH	"MEDIUM"

enum fuustrength { STRENGTH_TINY, STRENGTH_MEDIUM, STRENGTH_STRONG };

struct fuu {
	char lang[32];
	enum fuustrength strength;
	struct json_object *jo_dictionnary;
};

#endif 
