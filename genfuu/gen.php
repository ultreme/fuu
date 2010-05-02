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

// This script generates a number of insults, as text and as mp3 file
// Insults are stored in a sqlite database, audio files in a directory
// This script is not really friendly, custom it to your need. Actually,
// it generates insults for french man.
//
// It requires the following binaries :
//
// -> lame (mp3 encoder)
// -> espeak (vocal synthetisor)
// -> php5-sqlite

// Forbid execution of this script outside a cli context
if(php_sapi_name() !== 'cli') {
  die("Bleh.");
}

// Customs
define('DB_FILE', 'fuu.db');			// sqlite path to the database to be created
define('DATA_DIR', 'insults');			// directory where to store
define('FUU_PATH', './fuu');			// path to fuu executable
define('INSULT_NUMBER', 1024);			// number of insults to generate

$steps = array('step_1' => "creating database",
	       'step_2' => "checking datadir",
	       'step_3' => "checking binaries",
	       'step_4' => "populating database and datadir with insults");

// Creation of the database
function	step_1()
{
  if (file_exists(DB_FILE) == true) {
    echo DB_FILE . " already exists, deleted\n";
    unlink(DB_FILE);
  }

  $db = new SQLiteDatabase(DB_FILE);

  return $db->query("CREATE TABLE fuu ("
		    . "			 id INTEGER PRIMARY KEY,"
		    . "			 insult TEXT,"
		    . "			 audio_file CHAR(255),"
		    . "			 nb_view INTEGER,"
		    . "			 nb_play INTEGER"
		    . "	   );");
}

// Checking for a valid data_dir
function	step_2()
{
  if (!file_exists(DATA_DIR)) {
    echo DATA_DIR . " doesn't exists, creating...\n";
    if (!mkdir(DATA_DIR)) {
      return false;
    }
  }
  else {
    if (!is_dir(DATA_DIR)) {
      echo DATA_DIR . " already exists, but is not a directory, please remove it...\n";
      return false;
    }
  }

  return true;
}

// Checking binaries
function	step_3()
{
  if (FUU_PATH === false || is_file(FUU_PATH) === false) {
    echo "Please set a correct value for ESPEAK_PATH\n";
    return false;
  }

  return true;
}

// Populating database and datadir with insults
function	step_4()
{
  $fuu = FUU_PATH;
  $db = sqlite_open(DB_FILE);

  if ($db === false) {
    echo "Can't open " . DB_FILE . "\n";
    return false;
  }

  for ($i = 0; $i < INSULT_NUMBER; ++$i) {
    $insult = `$fuu`;
    $output_path = DATA_DIR . '/insult_' . sha1(rand());

    $wav = `espeak -v fr -s 150 -p 40 -g 10 -w $output_path "$insult"`;
    $output_path_mp3 = $output_path . ".mp3";
    `lame -h $output_path $output_path_mp3  --resample 11,025`;
    unlink($output_path);

    $q = "INSERT INTO fuu(insult, audio_file, nb_view, nb_play)"
      . "             VALUES('" . addslashes($insult) . "',"
      . "		     '" . addslashes($output_path_mp3) . "', 0, 0"
      . ");";

    sqlite_exec($db, $q);
    
    echo ".";
  }

  return true;
}

// Bootstrapper
foreach ($steps as $step => $detail)
  {
    echo "-> $detail ...\n";
    if ($step() != true) {
      die("Installation failed\n");
    }
    echo "-> Ok\n";
  }

echo "webfuu is now ready to insult :)\n";
