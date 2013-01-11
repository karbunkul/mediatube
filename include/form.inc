<?php

/**
 * Implements hook_form().
 */

function mediatube_settings_form($form){
 $form['jwplayer_path'] = array(
  '#title' => 'Path to JWplayer',
  '#type' => 'textfield',
  '#default_value' => variable_get('mediatube_jwplayer_path', 'sites/all/libraries/jw_player'),
  '#description' => t('The location where Jw player plugin is installed. Relative paths are from the Drupal root directory.'),
  '#required' => TRUE,
   );
 $form['submit'] = array(
  '#type'=>'submit',
  '#value' => 'Submit',
 );
  
 return $form;
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
  variable_set('mediatube_jwplayer_path_', $form_state['values']['jwplayer_path']);
  
  drupal_set_message(t('Your configuration has been saved.'));
}