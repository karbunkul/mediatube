<?php

/**
 * Playlists page callback.
 **/
function page_playlists_callback() {
 
 $breadcrumb[] = l('Home', '<front>');
 drupal_set_breadcrumb($breadcrumb);
 $query = 'SELECT title,alias,description FROM {mediatube_categories}';
 $res = db_query_range($query, 0,5);
 
 //kpr($res);
 $output = '';
 $rows = array();
 while ( $row = $res->fetchAssoc() ){
  $row['title'] = l($row['title'], 'mediatube/playlist/' . $row['alias']);
  $rows[] = $row;
 }
 if ( count($rows) > 0 ){
 $header = array(t('Title'),t('Alias'),t('Description'));
 $output .= theme('table', array('header'=>$header, 'rows'=>$rows));
 }else{
  $record = db_insert('mediatube_categories')
  ->fields(array(
   'cid' => 1,
   'title' => 'Новости',
   'alias' => 'news',
   'created' => 1357754373,
   'changed' => 1357754373,
   'description'=> 'Новости университета',
   'active'=> 'on',
   'preview'=> '',
   'weight'=> 10,
  ))
  ->execute();
  
 }
 return $output;
}

function page_playlist_callback(){
 return '123';
}

function title_playlist(){
 
 $arg = arg(2);
 
 if ( !empty($arg) ){
  $breadcrumb = array();
  $breadcrumb[] = l('Home', '<front>');
  $breadcrumb[] = l('MediaTube', 'mediatube');
  $breadcrumb[] = l('Playlists', 'mediatube/playlists');
  
  drupal_set_breadcrumb($breadcrumb); 
 }elseif (arg(1) == 'playlists'){
  $breadcrumb = array();
  $breadcrumb[] = l('Home', '<front>');
  $breadcrumb[] = l('MediaTube', 'mediatube');
  
  drupal_set_breadcrumb($breadcrumb);
  
 }
 
 return 'Playlist ' . arg(2);
}

