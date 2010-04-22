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
