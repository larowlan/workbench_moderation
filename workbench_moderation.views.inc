<?php

// $Id$

/**
 * @file
 */

/**
 * Implementation of hook_views_handlers().
 */
function workbench_moderation_views_handlers() {
  return array(
    'handlers' => array(
      'workbench_moderation_handler_filter_state' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
    )
  );
}

/**
 * Implementation of hook_views_data().
 */
function workbench_moderation_views_data() {
  $data = array();

  $data['workbench_moderation_node_history']['table']['group'] = t('Workbench Moderation');
  $data['workbench_moderation_node_history']['table']['join'] = array(
    'node' => array(
      'left_table' => 'node_revision',
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'node_revision' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
  );

  $data['workbench_moderation_node_history']['state'] = array(
    'title' => t('State'),
    'help' => t('Content moderation state of the node revisision.'),
    'filter' => array(
      'handler' => 'workbench_moderation_handler_filter_state',
    ),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['workbench_moderation_node_history']['from_state'] = array(
    'title' => t('From state'),
    'help' => t('Previous content moderation state of the node revisision.'),
    'filter' => array(
      'handler' => 'workbench_moderation_handler_filter_state',
    ),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['workbench_moderation_node_history']['uid'] = array(
    'title' => t('User'),
    'help' => t('User who moderated this revision.'),
    'relationship' => array(
      'title' => t('User'),
      'label' => t('User'),
      'base' => 'users',
      'base field' => 'uid',
    ),
  );
  $data['workbench_moderation_node_history']['stamp'] = array(
    'title' => t('Timestamp'),
    'help' => t('The date this revision was moderated.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['workbench_moderation_node_history']['published'] = array(
    'title' => t('Published'),
    'help' => t('Whether or not this revision is published.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Published'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['workbench_moderation_node_history']['current'] = array(
    'title' => t('Current'),
    'help' => t('Whether or not this is the current revision.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Current'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}
