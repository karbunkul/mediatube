<?php

function mediatube_form_alter(&$form, &$form_state, $form_id) {
  dsm($form_id);  // print form ID to messages
  //dsm($form);  // pretty print array using Krumo to messages
}

/**
* Implements hook_form().
*/

function mediatube_settings_form($form){
 $form['jwplayer_path'] = array(
  '#title' => 'Path to JWplayer',
  '#type' => 'textfield',
  '#value' => variable_get('mediatube_jwplayer_path', 'sites/all/libraries/jw_player'),
  '#description' => t('The location where Jw player plugin is installed. Relative paths are from the Drupal root directory.'),
  '#required' => TRUE,
 );
 $form['actions']['submit'] = array(
  '#type'=>'submit',
  '#value' => t('Save configuration'),
 );
 
 return system_settings_form($form);
}
/**
* Implements form_validate().
*/
function mediatube_settings_form_validate(&$form, &$form_state) {
 if (!file_exists($form_state['values']['jwplayer_path'])) {
   form_set_error('jwplayer_path', 'Folder path jw player plugin not exists');
 }
 return FALSE;
}

/**
* Implements hook_form_submit().
*/
function mediatube_settings_form_submit(&$form, &$form_state) {
 // path to jwplayer
 variable_set('mediatube_jwplayer_path', $form_state['values']['jwplayer_path']);
 
 drupal_set_message(t('Your configuration has been saved.'));
}

function mediatube_new_playlist_form($form){
 $form['fields'] = array(
  '#type' => 'fieldset',
  '#title' => 'Add new playlist',
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
 );
 
 $form['fields']['title'] = array(
  '#type' => 'textfield',
  '#title' => 'Title',
  '#default_value' => 'Лекции',
  '#required' => TRUE,
 );
 
 $form['fields']['active'] = array(
  '#type' => 'radios',
  '#title' => 'Active',
  '#options' => array(1 => 'Enabled', 0 => 'Disabled'),
  '#default_value' => 1,
 );
 $form['fields']['alias'] = array(
  '#type' => 'textfield',
  '#title' => 'Alias',
  '#default_value' => 'lecture',
 );
 
 $form['fields']['description'] = array(
  '#type' => 'textarea',
  '#title' => 'Description',
  '#default_value' => 'Публичные лекции',
  '#rows' => 2,
 );
 
 $form['fields']['actions']['submit'] = array(
  '#type' => 'submit',
  '#value' => t('Add playlist'),
 );
 
 return $form;
}

function mediatube_new_playlist_form_validate(&$form, &$form_state) {
 $res = db_query('SELECT title FROM {mediatube_categories} WHERE title = :title', array(':title' => $form_state['values']['title']))->fetchAssoc();
 dsm($res);
 
 if ($form_state['values']['title'] == $res['title']){
  form_set_error('title', 'Playlist exist');
 }
}

function mediatube_new_playlist_form_submit(&$form, &$form_state) {
 $record = db_insert('mediatube_categories')
  ->fields(array(
   'title' => $form_state['values']['title'],
   'alias' => $form_state['values']['alias'],
   'created' => REQUEST_TIME,
   'changed' => REQUEST_TIME,
   'description'=> $form_state['values']['description'],
   'active'=> $form_state['values']['active'],
   'preview'=> '',
   'weight'=> 10,
  ))
  ->execute();
}

function mediatube_edit_playlist_form($form){
 $row = db_query('SELECT title,alias FROM {mediatube_categories} WHERE cid = :cid', array(':cid' => arg(5)))->fetchAssoc();
 
 dsm($row);
 $form['title'] = array(
  '#title' => 'Title',
  '#type' => 'textfield',
  '#value' => $row['title'],
 );
 
 return system_settings_form($form);
}
