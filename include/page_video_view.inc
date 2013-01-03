<?php

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