<?php

// $Id$

/**
 * @file
 *   Filter state handlers.
 */
class workbench_moderation_handler_filter_state extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Moderation Status');
      $this->value_options = workbench_moderation_states_get();
    }
  }
}
