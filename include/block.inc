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
 $block['subject'] = 'Playlists';
 
 $block['content'] = theme('mediatube_playlists_block');
 /*
 $items = Mediatube::get_categories(array('title'));
 
 $block['content'] = array(
  'para' => array(
   '#items' => $items[0],
   '#attributes' => array('class' => 'menu'),
   '#theme' => 'item_list',
   
  ),
 );
*/
 return $block;
}