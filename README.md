fuu
===

## yet another insult generator.

fuu is composed of three parts :

  * cfuu: c program that generate random text insults
  * genfuu: php script that generates X insults, in text and audio
  * webfuu: a web page which displays a random insult plus its audio

## Features

  * multi-language
  * random insults (size, words, ...)
  * web interface
  * support of french insults

## Dependancies

Following libraries are required to build cfuu:

  - json-c library (0.9.x)

## Todo

  * support more languages :-)

## Examples

# Standart use
$ fuu
Espèce de moche haricot bleu de nazareth de ptit poil de branloman obèse de moche buveur de chnoque néandertalien bleu de buveur de morbak infecte
$

# Insult someone (Unexpected result)
$ fuu | mail xxx@xx.xx

# Need sound?
$ fuu | espeak -v fr -s 150 -p 40 -g 10 -z 

# License
Copyright (c) 2010 Sebastien Rannou <rannou.sebastien@gmail.com>

Permission to use, copy, modify, and distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
