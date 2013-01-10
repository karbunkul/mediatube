<?php
/**
 * Main page callback.
 **/
function page_main_callback() {
 return theme('mediatube_dashboard');
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

function title_video(){
 return 'Video ' . arg(1);
}