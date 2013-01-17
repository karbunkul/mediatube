<?php
/**
 * Implements hook_theme().
 */
function mediatube_theme($existing, $type, $theme, $path){
 $themes = array(
  'mediatube_dashboard' => array(
   'template' => 'template/mediatube-dashboard',
   ),
  'mediatube_playlists_block' => array(
   'template' => 'template/mediatube-playlists-block',
  ),
  'mediatube_video' => array(
   'template' => 'template/mediatube-video',
  ),
  'mediatube_playlist' => array(
   'template' => 'template/mediatube-playlist',
  ),
 );
 
 return $themes;
}

/**
 * template_preprocess_hook().
 **/
function template_preprocess_mediatube_dashboard(&$vars) {

 $path = isset($_GET['q']) ? $_GET['q'] : '<front>';
 $link = url($path, array('absolute' => TRUE));

 $vars['url'] = $link;
 $vars['hello'] = 'Hello World!';
}

/**
 * template_preprocess_hook().
 **/
function template_preprocess_mediatube_playlists_block(&$vars) {
 $vars['items']  = Mediatube::get_categories(array('title, alias, cid')); 
}


function template_preprocess_mediatube_video(&$vars){
 $video = Mediatube::video_info(arg(2));
 drupal_add_js(variable_get('mediatube_jwplayer_path') . '/jwplayer.js');
 $vars['movie'] = $video; 
}

function template_preprocess_mediatube_playlist(&$vars){
 $cid = Mediatube::get_category_cid(arg(2));
 
 $res = db_query('SELECT vid,cid,title,alias, description FROM {mediatube_movies} WHERE cid = :cid', array(':cid' => $cid));
 
 $playlist = array();
 while ($item = $res->fetchAssoc()){
  $url = $item['alias'];
  unset($item['alias']);
  
  if ( empty($url) ){
   $url = $item['vid'];
  }
  $item['url'] = url('mediatube/video/' . $url );
  
  $playlist[] = $item;
  unset($url);
 }
 
 $vars['playlist'] = $playlist;
}