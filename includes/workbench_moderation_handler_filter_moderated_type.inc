<?php

/**
 * Filter by whether a node type has moderation enabled or not.
 */
class workbench_moderation_handler_filter_moderated_type extends views_handler_filter_boolean_operator {
  function query() {
    if (!isset($this->value) || $this->value === NULL) { return; }

    $operator = ($this->value ? "IN" : "NOT IN");
    $node_types = workbench_moderation_moderate_node_types();

    $this->ensure_my_table();
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $node_types, $operator);
  }
}