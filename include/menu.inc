<?php
/**
 * Implements hook_menu().
 */
function mediatube_menu() {
 $items = array();
 
 // http:example.com/mediatube
 $items['mediatube'] = array(
  'title' => t('MediaTube'),
  'access callback' => TRUE,
  'page callback' => 'page_main_callback',
  'type' => MENU_NORMAL_ITEM,
  'menu_name' => 'navigation',
 );
 // http:example.com/mediatube/vid-1
 $items['mediatube/%'] = array(
  'title callback' => 'title_video_callback',
  'access callback' => TRUE,
  'page callback' => 'page_video_callback',
  'type' => MENU_NORMAL_ITEM,
 );
 
 // http:example.com/mediatube/playlists
 $items['mediatube/playlists'] = array(
   'title' => t('Playlists'),
   'access callback' => TRUE,
   'page callback' => 'page_playlists_callback',
   'type' => MENU_LOCAL_TASK,
 );
 
 // http:example.com/mediatube/playlists/1
 $items['mediatube/playlist/%'] = array(
   'title callback' => 'title_playlist_callback',
   'access callback' => TRUE,
   'page callback' => 'page_playlist_callback',
   'type' => MENU_NORMAL_ITEM,
 );
 
 $items['mediatube/default'] = array(
  'title' => t('View'),
   'type' => MENU_DEFAULT_LOCAL_TASK,
   'weight' => -10,
 );

 $items['admin/config/media/mediatube'] = array(
  'title' => 'MediaTube',
  'description' => 'MediaTube settings',
  'type' => MENU_NORMAL_ITEM,
  'access callback' => TRUE,
  'page callback' => 'drupal_get_form',
  'page arguments' => array('mediatube_settings_form'),
  );
 
 $items['admin/config/media/mediatube/default'] = array(
  'title' => t('Settings'),
  'type' => MENU_DEFAULT_LOCAL_TASK,
  'weight' => -10,
 );

 $items['admin/config/media/mediatube/playlists'] = array(
  'title' => t('Playlists'),
   'access callback' => TRUE,
   'page callback' => 'page_admin_playlists_callback',
   'type' => MENU_LOCAL_TASK,
 );
 
 return $items;
}