<?php

// $Id$

/**
 * @file
 */


/**
 * Implements hook_views_data().
 */
function workbench_moderation_views_data() {
  $data = array();

  $data['workbench_moderation_revision_state']['table']['group'] = t('Node Revision');
  $data['workbench_moderation_revision_state']['table']['join'] = array(
    'node_revisions' => array(
      'left_field' => 'vid',
      'field' => 'vid',
      'type' => 'INNER',
    ),
  );

  $data['workbench_moderation_revision_state']['state'] = array(
    'title' => t('Content Moderation state'),
    'help' => t('Content moderation state of the node revisision'),
    'filter' => array(
      'handler' => 'workbench_moderation_handler_filter_state',
    ),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}

function workbench_moderation_views_handlers() {
  return array(
    'handlers' => array(
      'workbench_moderation_handler_filter_state' => array(
        'parent' => 'views_handler_filter',
      ),
    )
  );
}
