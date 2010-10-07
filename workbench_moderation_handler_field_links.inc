<?php

// $Id$

class workbench_moderation_handler_field_links extends views_handler_field {
  function render($values) {
    if ($values->{$this->aliases['current']}) {
      $nid = $values->{$this->field_alias};
      return implode(', ', workbench_moderation_get_moderation_links($nid, $_GET['q']));
    }
    return '';
  }
}
