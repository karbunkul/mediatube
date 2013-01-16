<?php
/**
 * Implements hook_menu().
 */
function mediatube_menu() {
 $items = array();
 
 // http:example.com/mediatube
 $items['mediatube'] = array(
  'title' => variable_get('mediatube_name_in menu','MediaTube'),
  'access callback' => TRUE,
  'page callback' => 'page_main_callback',
  'type' => MENU_NORMAL_ITEM,
  'menu_name' => 'navigation',
 );
 
 $items['mediatube/default'] = array(
  'title' => t('View'),
   'type' => MENU_DEFAULT_LOCAL_TASK,
   'weight' => -10,
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
 
 // administration 
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
 
 $items['admin/config/media/mediatube/playlist/%/edit'] = array(
  'title' => t('Edit playlist'),
  'type' => MENU_VISIBLE_IN_BREADCRUMB,
  'access callback' => TRUE,
  'page callback' => 'drupal_get_form',
  'page arguments' => array('mediatube_edit_playlist_form'),
 );

 
 // node/add integration
 $items['node/add/mediatube'] = array(
  'title' => 'Mediatube',
  'page callback' => 'drupal_get_form',
  'page arguments' => array('mediatube_add_video_form'),
  'access callback' => TRUE,
  'type' => MENU_NORMAL_ITEM,
 );
 
 $items['node/add/mediatube/default'] = array(
  'title' => t('Add'),
   'type' => MENU_DEFAULT_LOCAL_TASK,
   'weight' => -10,
 );
 
 $items['node/add/mediatube/import'] = array(
  'title' => t('Import'),
   'type' => MENU_LOCAL_TASK,
   'access callback' => TRUE,
   'page callback' => 'drupal_get_form',
   'page arguments' => array('mediatube_import_video_form'),
 );
 
 return $items;
}