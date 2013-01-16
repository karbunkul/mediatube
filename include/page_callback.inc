<?php
/**
 * page_main_callback().
 **/
function page_main_callback() {
 return theme('mediatube_dashboard');
}

/**
 * Playlists page callback.
 **/
function page_playlists_callback() {
 // breadcrumb for adress /mediatube 
 $breadcrumb[] = l('Home', '<front>');
 drupal_set_breadcrumb($breadcrumb);
 
 $output = '';
 
 $fields = array('title', 'alias', 'description');
 $rows = Mediatube::get_categories($fields);
 
 if ( count($rows) > 0 ){
 $header = array(t('Title'),t('Alias'),t('Description'));
 $output .= theme('table', array('header'=>$header, 'rows'=>$rows));
 }
 return $output;
}

function page_playlist_callback(){
 return '123';
}

function title_playlist_callback(){
 
 $arg = arg(2);
 
 if ( !empty($arg) ){
  $breadcrumb = array();
  $breadcrumb[] = l('Home', '<front>');
  $breadcrumb[] = l(variable_get('mediatube_name_in menu','MediaTube'), 'mediatube');
  $breadcrumb[] = l('Playlists', 'mediatube/playlists');
  
  drupal_set_breadcrumb($breadcrumb); 
 }elseif (arg(1) == 'playlists'){
  $breadcrumb = array();
  $breadcrumb[] = l('Home', '<front>');
  $breadcrumb[] = l('MediaTube', 'mediatube');
  
  drupal_set_breadcrumb($breadcrumb);
 }
 $res = Mediatube::get_category_title(arg(2));
 if ( $res ){
  return $res;
 }else{
  return 'Playlist not exists';
 }
 
}

/**
 * Video view page callback.
 **/
function page_video_view_callback($vid) {
 return t('Страница просмотра ролика ') .  $vid;
}

/**
 * Video view title callback.
 **/
function title_video_view_callback($vid) {
 return t('Страница ролика ') .  $vid;
}

function title_video_callback(){
 return 'Video ' . arg(1);
}

/**
 * Implements page_video_callback.
 */
function page_video_callback(){
 return 'Video ' . arg(1);
}

function page_admin_playlists_callback(){
 //return 'vasy';
 
 $out['new_playlist'] = array(
  drupal_get_form('mediatube_new_playlist_form'),
 );
 
 // get categories
 $rows = Mediatube::get_categories(array('title', 'cid', 'alias', 'description'));

 
 $rows_temp = array();
 foreach ($rows AS $row){
  $row['cid'] = l('Edit', 'admin/config/media/mediatube/playlist/' . $row['cid'] . '/edit',  array('query' => array('destination' => 'admin/config/media/mediatube/playlists')));
  $rows_temp[] = $row;
 }
 
 //dsm($rows_temp);
 $rows = $rows_temp;
 
 $header = array('Title', 'Operations', 'Alias', 'Description');

 $out['table'] = array(
  '#type' => 'markup',
  '#markup' => theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'mediatube-admin-playlists'))),
 );
 
 return $out;
}