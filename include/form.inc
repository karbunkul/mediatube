<?php

function mediatube_form_alter(&$form, &$form_state, $form_id) {
  //dsm($form_id);  // print form ID to messages
  //dsm($form);  // pretty print array using Krumo to messages
}

/**
* Implements hook_form().
*/

function mediatube_settings_form($form){
 $form['jwplayer_path'] = array(
  '#title' => t('Path to JWplayer'),
  '#type' => 'textfield',
  '#default_value' => variable_get('mediatube_jwplayer_path', 'sites/all/libraries/jw_player'),
  '#description' => t('The location where Jw player plugin is installed. Relative paths are from the Drupal root directory.'),
  '#required' => TRUE,
 );
  
 $form = system_settings_form($form);
 $form['#submit'] = array('mediatube_settings_form_submit');
 
 return $form;
}
/**
* Implements form_validate().
*/
function mediatube_settings_form_validate($form, &$form_state) {
 if (!file_exists($form_state['input']['jwplayer_path'])) {
  form_set_error('jwplayer_path', 'Folder path jw player plugin not exists');
 }
}

/**
* Implements hook_form_submit().
*/
function mediatube_settings_form_submit($form, $form_state) {
 // path to jwplayer
 //$dsm($form_state);
 variable_set('mediatube_jwplayer_path', $form_state['input']['jwplayer_path']);
 
 //drupal_set_message(t('Your configuration has been saved.'));
}

function mediatube_new_playlist_form($form){
 
 
 $form['title'] = array(
  '#type' => 'textfield',
  '#title' => t('Title'),
  '#default_value' => '',
  '#required' => TRUE,
 );
 
  $form['alias'] = array(
  '#type' => 'textfield',
  '#title' => t('Alias'),
  '#default_value' => '',
 );
 
 $form['extra'] = array(
  '#type' => 'fieldset',
  '#title' => t('Advanced'),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
 );
 
 $form['extra']['active'] = array(
  '#type' => 'radios',
  '#title' => t('Active'),
  '#options' => array(1 => t('Enabled'), 0 => t('Disabled')),
  '#default_value' => 1,
 );

 $form['extra']['description'] = array(
  '#type' => 'textarea',
  '#title' => t('Description'),
  '#default_value' => '',
  '#rows' => 2,
 );

 
 $form = system_settings_form($form);
 
 $form['actions']['submit']['#value'] = t('Add playlist');
 $form['#submit'] = array('mediatube_new_playlist_form_submit');
 
 return $form;
}

function mediatube_new_playlist_form_validate($form, &$form_state) {
 $res = db_query('SELECT title,alias FROM {mediatube_categories} WHERE title = :title', array(':title' => $form_state['input']['title']))->fetchAssoc();
 //dsm($res);
 
 if ( $form_state['input']['title'] == $res['title'] ){
  form_set_error('title', t('Title exist'));
 }
 
 if ( $form_state['input']['alias'] == $res['alias'] ){
  form_set_error('alias', t('Alias exist'));
 } 
 
}

function mediatube_new_playlist_form_submit($form, &$form_state) {
 $record = db_insert('mediatube_categories')
  ->fields(array(
   'title' => $form_state['input']['title'],
   'alias' => $form_state['input']['alias'],
   'created' => REQUEST_TIME,
   'changed' => REQUEST_TIME,
   'description'=> $form_state['input']['description'],
   'active'=> $form_state['input']['active'],
   'preview'=> '',
   'weight'=> 10,
  ))
  ->execute();
}

function mediatube_edit_playlist_form($form){
 $row = db_query('SELECT title,alias,active,description FROM {mediatube_categories} WHERE cid = :cid', array(':cid' => arg(5)))->fetchAssoc();
 
 //dsm($row);
 $form['title'] = array(
  '#title' => t('Title'),
  '#type' => 'textfield',
  '#value' => $row['title'],
  '#required' => TRUE,
 );
 
 $form['active'] = array(
  '#type' => 'radios',
  '#title' => t('Active'),
  '#options' => array(1 => t('Enabled'), 0 => t('Disabled')),
  '#default_value' => $row['active'],
  '#required' => TRUE,
 );
 $form['alias'] = array(
  '#type' => 'textfield',
  '#title' => t('Alias'),
  '#value' => $row['alias'],
 );
 
 $form['description'] = array(
  '#type' => 'textarea',
  '#title' => t('Description'),
  '#value' => $row['description'],
  '#rows' => 2,
 );
 
 $form = system_settings_form($form);
 
 $form['actions']['submit']['#value'] = t('Update');
 $form['#submit'] = array('mediatube_edit_playlist_form_submit');
 return $form;
}

function mediatube_edit_playlist_form_validate($form, &$form_state){
 $cid = arg(5);
 $title = $form_state['input']['title'];
 
 $res = db_query('SELECT cid,title FROM {mediatube_categories} WHERE title = :title', array(':title' => $title));
 
 while ( $row = $res->fetchAssoc() ){
  
  if ( ($row['title'] == $title) && ($row['cid'] != $cid) ){
   form_set_error('title', format_string('That name %title already exists', array('%title' => $title)));
  }
 }
 
 $alias = $form_state['input']['alias'];
 
 if ( $alias != '' ){
  $res = db_query('SELECT cid,alias FROM {mediatube_categories} WHERE alias = :alias', array(':alias' => $alias));
 
  while ( $row = $res->fetchAssoc() ){
  
  if ( ($row['alias'] == $alias) && ($row['cid'] != $cid) ){
   form_set_error('alias', format_string('Alias %alias already exists', array('%alias' => $alias)));
   }
  }
 }
}


function mediatube_edit_playlist_form_submit($form, $form_state){
 //dsm($form_state);
 $upd = db_update('mediatube_categories')->fields(
  array(
   'title' => $form_state['input']['title'],
   'alias' => $form_state['input']['alias'],
   'active' => $form_state['input']['active'],
   'changed' => REQUEST_TIME,
   'description' => $form_state['input']['description'],
  )
 )->condition('cid', arg(5), '=')->execute();
}


function mediatube_add_video_form($form){
 // New video title
 $form['title'] = array(
  '#title' => t('Title'),
  '#description' => t('Title for added video'),
  '#type' => 'textfield',
  '#default_value' => 'title',
  '#required' => TRUE,
 );
 
 // get all playlists
 $res = db_query('SELECT cid, title FROM {mediatube_categories}');
 $options = array();
 while ( $row = $res->fetchAssoc() ){
  $options[$row['cid']] = $row['title'];
 }
 
 $form['cid'] = array(
  '#type' => 'select',
  '#title' => t('Playlist'),
  '#options' => $options,
  '#required' => TRUE,
  // load last playlist cid
  '#default_value' => variable_get('mediatube_last_playlist'), 
 );
 
 $form['description'] = array(
  '#type' => 'textarea',
  '#title' => t('Description'),
  '#default_value' => '',
  '#rows' => 2,
  //'#weight' => 10,
 );
 
 // Advenced params
 $form['extra'] = array(
  '#type' => 'fieldset',
  '#title' => t('Advanced'),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
 );
 
 $form['extra']['alias'] = array(
  '#type' => 'textfield',
  '#title' => t('Alias'),
  '#default_value' => '',
 );
 
 $form['extra']['active'] = array(
  '#type' => 'radios',
  '#title' => t('Active'),
  '#options' => array(1 => t('Enabled'), 0 => t('Disabled')),
  '#default_value' => 1,
 );
 
 
 
 $form['extra']['provider'] = array(
  '#type' => 'radios',
  '#title' => t('Provider'),
  '#options' => array(0 => 'http', 1 => 'rtmp'),
  '#default_value' => '',
 );
 
 
 
 $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add video'),
  );
 
 $form = system_settings_form($form);
 
 $form['actions']['submit']['#value'] = t('Add');
 $form['#submit'] = array('mediatube_add_video_form_submit');
 //dsm($form);
 
 return $form;
}

function mediatube_add_video_form_submit($form, $form_state){
 variable_set('mediatube_last_playlist', $form_state['input']['cid']);
 drupal_set_message(t('Add new video.'));
}


function mediatube_import_video_form($form){
 $form = array();
 
 // get all playlists
 $res = db_query('SELECT cid, title FROM {mediatube_categories}');
 $options = array();
 while ( $row = $res->fetchAssoc() ){
  $options[$row['cid']] = $row['title'];
 }
 
 $form['cid'] = array(
  '#type' => 'select',
  '#title' => t('Playlist'),
  '#options' => $options,
  '#required' => TRUE,
  // load last playlist cid
  '#default_value' => variable_get('mediatube_last_playlist'), 
 );
 
 $form['upload'] = array(
  '#name' => '',
  '#type' => 'file',
  '#title' => t('Load from file'),
  '#size' => 50,
 );
 
 $form['export'] = array(
  '#type' => 'textarea',
  '#cols' => 5,
  '#title' => t('JSON'),
 );
 
 $form = system_settings_form($form);
 
 $form['actions']['submit']['#value'] = t('Import');
 $form['#submit'] = array('mediatube_add_video_form_submit');
 
 return $form;
}