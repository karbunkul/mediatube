<?php
class Mediatube{
  public function get_categories($fields){
    $query = format_string('SELECT !fields FROM {mediatube_categories}', array('!fields' => implode(',',$fields)));
    $res = db_query_range($query, 0,5);
    
    $rows = array();
    while ( $row = $res->fetchAssoc() ){
      $rows[] = $row;
    }
    return $rows;
  }
}
