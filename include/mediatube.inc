<?php
class Mediatube {
  public function get_categories($fields){
    $query = format_string('SELECT !fields FROM {mediatube_categories}', array('!fields' => implode(',',$fields)));
    $res = db_query_range($query, 0,5);
    
    $rows = array();
    while ( $row = $res->fetchAssoc() ){
      $rows[] = $row;
    }
    return $rows;
  }
  
  private function get_category_info($cid, $field = 'title'){
    $row = db_query('SELECT * FROM {mediatube_categories} t WHERE t.cid = :cid', array(':cid' => $cid))->fetchAssoc();
    if ( count($row) > 0 ){
      return $row[$field];
    }else{
      return FALSE;
    }
  }
  
  public function get_category_title($alias){
    $res = Mediatube::get_category_info($alias);
    if ( !$res ){
      $row = db_query('SELECT cid FROM {mediatube_categories} WHERE alias = :alias', array(':alias' => $alias))->fetchAssoc();
      if ( isset($row['cid']) ){
        return Mediatube::get_category_info($row['cid']);        
      }else{
        return FALSE;
      }
    }else{
      return $res;
    }
  }
  
  public function get_category_cid($alias){
    $db_alias = db_query('SELECT cid,alias FROM {mediatube_categories} WHERE alias = :alias', array(':alias' => $alias))->fetchAssoc();
   if ( $db_alias ){
    return $db_alias['cid'];
   }else{
    $db_cid = db_query('SELECT cid FROM {mediatube_categories} WHERE cid = :cid', array(':cid' => $alias))->fetchAssoc();
    if ( $db_cid ){
      return $db_cid['cid'];
    }else{
      return FALSE;
    }
   }
  }
  
  public function video_info($alias){
    $db_alias = db_query('SELECT * FROM {mediatube_movies} WHERE alias = :alias', array(':alias' => $alias))->fetchAssoc();
    if ( $db_alias ){
      return $db_alias;
    }else{
     $db_vid = db_query('SELECT * FROM {mediatube_movies} WHERE vid = :vid', array(':vid' => $alias))->fetchAssoc();
      if ( $db_vid ){
        return $db_vid;
      }else{
        return FALSE;
      } 
    }
  }
}
