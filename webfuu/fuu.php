<?php
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

$db = sqlite_open("data/fuu.db");

// Returns an array of a random insult of the following pattern:
// * insult -> string (the insult)
// * id -> integer (id of the insult)
function get_random_insult()
{
  global $db;

  $query = "SELECT id, insult FROM fuu ORDER BY RANDOM() LIMIT 1";
  $res = sqlite_array_query($db, $query, SQLITE_ASSOC);

  if (count($res) > 0) {
    return $res[0];
  }

  header('HTTP/1.1 500 Internal Server Error');
  exit;
}

// Simply increase the number of view of an insult
function increase_nb_view($id)
{
  global $db;

  $id = (int) $id;
  $query = "UPDATE fuu SET nb_view=nb_view + 1 WHERE id='$id'";

  return sqlite_query($db, $query);
}

// Simple increase the number of play of an insult
function increase_nb_play($id)
{
  global $db;

  $id = (int) $id;
  $query = "UPDATE fuu SET nb_play=nb_play + 1 WHERE id='$id'";

  return sqlite_query($db, $query);
}

// Plays an insult, output the insult like a 
function play_insult($id)
{
  global $db;

  $query = "SELECT audio_file FROM fuu WHERE id='$id'";
  $res = sqlite_array_query($db, $query, SQLITE_ASSOC);
  if (count($res) > 0) {
    $insult = $res[0]['audio_file'];
    header("Content-type: audio/mpeg");
    echo file_get_contents($insult);
  }
  else {
    header('HTTP/1.1 500 Internal Server Error');
  }
  exit;
}

// Gather some stats
function get_stats()
{
  global $db;

  $query = "SELECT SUM(nb_view) AS nb_views, SUM(nb_play) AS nb_plays FROM fuu WHERE 1";
  $res = sqlite_array_query($db, $query, SQLITE_ASSOC);
  if (count($res) > 0) {
    return $res[0];
  }
  return array('nb_views' => 0, 'nb_plays' => 0);
}
