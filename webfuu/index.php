<?php
error_reporting(E_ALL);
require_once('fuu.php');

if (isset($_GET['play'])) {
    $id = (int) $_GET['play'];
    increase_nb_play($id);
    play_insult($id);
  }

$insult = get_random_insult();
$stats = get_stats();
increase_nb_view($insult['id']);

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="fr" lang="fr">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />    
    <title>Fuu</title>

    <style type="text/css">

      body { 
      background-color: #303030;
      font-family: 'Lucida Grande',sans-serif;
      line-height: 1.5;
      font-size: 0.75em;
      color: #C0C0C0;
      text-align: center;
      }

      #wrapper { 
      width: 500px;
      margin: auto;
      text-align: center;
      }

      h1 { 
      letter-spacing: 0.1em;
      font-size: 2em;
      background-color: #333333;
      }

      a { 
      color: #FFFFFF;
      text-decoration: none;
      }

      #content, #title, #console_bot { 
      background-color: #404040;
      padding: 30px;
      margin-bottom: 30px;
      }

      #player {
      margin: 40px;
      }

      #fuuu {
      margin: 40px;
      }

      #title_colored { 
      color: #0084b4
      }

    </style>

  </head>
  <body>

<div id="wrapper">
  <div id="content">

<h1 id="title_colored">Fuuu!</h1>

<div id="player">
<object data="p.swf" width="160" height="20" name="dewplayer" type="application/x-shockwave-flash">
  <param name="movie" value="dewplayer-bubble.swf" />
  <param name="flashvars" value="mp3=index.php?play=<?php echo $insult['id'] ?>" />
  <param name="wmode" value="transparent" />
</object>
</div>

<h3><?php echo $insult['insult'] ?></h3>

<img src="img/fuuu.png" alt="fuuu" id="fuuu" />

<p>
Powered by aimxhaisse
</p>

  </div>
</div>

  </body>

  <!--
     Number of views: <?php echo $stats['nb_views'] ?>

     Number of plays: <?php echo $stats['nb_plays'] ?>
    -->

</html>
