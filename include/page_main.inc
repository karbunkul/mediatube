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
	$vars['url'] = 'http://tgasu.ru/tv';
	$vars['hello'] = 'Hello World!';
}