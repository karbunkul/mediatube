<?php
/**
 * Implements hook_block_info().
 */

function mediatube_block_info(){
 $blocks['mediatube'] = array(
  'info' => t('MediaTube playlists'),
  'cache' => DRUPAL_NO_CACHE,
 );

 return $blocks;
}

/**
 * Implements hook_block_view().
 */

function mediatube_block_view($delta = ''){
 $block = array();
 $block['subject'] = t('Playlists');
 $block['content'] = theme('mediatube_playlists_block');
 
 if ( user_access('mediatube playlist administer')){
  $block['content'] .= '<br/><div>' . l(t('Administer'), 'admin/config/media/mediatube/playlists') . '</div>';
 }
 
 return $block;
}