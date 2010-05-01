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

#include "compat.h"

#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "fuu.h"

/*
 * This file contains function providing an access to data from the dictionnary.
 */

/*
 * for an unknown reason, this structure is kept private in json-c's library 
 * but some public macros require its definition (foreachC), should report this
 */
struct json_object_iter {
	char *key;
	struct json_object *val;
	struct lh_entry *entry;
};

struct json_object *
db_get_package(struct json_object *dictionnary, char *lang)
{
	struct json_object_iter	iter;

	json_object_object_foreachC(dictionnary, iter) {
		if (strcasecmp(iter.key, lang) == 0) {
			return iter.val;
		}
	}
	return NULL;
}

struct json_object *
db_get_words(struct json_object *package, char *gender)
{
	struct json_object_iter	iter;

	json_object_object_foreachC(package, iter) {
		if (strcasecmp(iter.key, gender) == 0) {
			return iter.val;
		}
	}
	return NULL;
}

const char *
db_get_link(struct json_object * package)
{
	struct json_object *	link_array;
	struct json_object *	link;
	int			len, seed;

	if (json_object_get_type(package) != json_type_object)
		return NULL;
	if ((link_array = json_object_object_get(package, "link")) == NULL)
		return NULL;

	len = json_object_array_length(link_array);
	seed = rand() % len;	

	if ((link = json_object_array_get_idx(link_array, seed)) == NULL)
		return NULL;

	return json_object_get_string(link);
}

const char *
db_get_prefix(struct json_object * package)
{
	struct json_object *	prefix;

	prefix = json_object_object_get(package, "prefix");
	if (prefix != NULL)
		return json_object_get_string(prefix);
	return NULL;
}

const char *
db_get_name_prefix(struct json_object * words)
{
	struct json_object *	prefix_array;
	struct json_object *	prefix;
	int			len, seed;

	if (json_object_get_type(words) != json_type_object)
		return NULL;
	if ((prefix_array = json_object_object_get(words, "prefix")) == NULL)
		return NULL;

	len = json_object_array_length(prefix_array);
	seed = rand() % len;

	if ((prefix = json_object_array_get_idx(prefix_array, seed)) == NULL)
		return NULL;

	return json_object_get_string(prefix);
}

const char *
db_get_name_suffix(struct json_object * words)
{
	struct json_object *	suffix_array;
	struct json_object *	suffix;
	int			len, seed;

	if (json_object_get_type(words) != json_type_object)
		return NULL;
	if ((suffix_array = json_object_object_get(words, "suffix")) == NULL)
		return NULL;

	len = json_object_array_length(suffix_array);
	seed = rand() % len;

	if ((suffix = json_object_array_get_idx(suffix_array, seed)) == NULL)
		return NULL;

	return json_object_get_string(suffix);
}

const char *
db_get_name(struct json_object * words)
{
	struct json_object *	name_array;
	struct json_object *	name;
	int			len, seed;

	if (json_object_get_type(words) != json_type_object)
		return NULL;
	if ((name_array = json_object_object_get(words, "name")) == NULL)
		return NULL;

	len = json_object_array_length(name_array);
	seed = rand() % len;

	if ((name = json_object_array_get_idx(name_array, seed)) == NULL)
		return NULL;

	return json_object_get_string(name);
}
