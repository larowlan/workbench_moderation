<?php

// $Id$

/**
 * @file
 *
 * Provides node functions
 */


/**
 * Displays the current moderated version of the node
 *
 * @param $node
 *   Object, Drupal node object
 * @return html
 */
function workbench_moderation_node_current_view($node) {
  if (! workbench_moderation_node_is_current($node)) {
    // Load the current node
    $current_node = workbench_moderation_node_current_load($node);
    drupal_set_message(t('You are viewing the current moderated version of this
      !type. This is currently in state: !state.',
      array(
        '!type' => $node->type,
        '!state' => $current_node->content_moderation['current']->state
      )
    ));
    menu_set_active_item("node/{$current_node->nid}/moderation");
    return node_page_view($current_node);
  }
  // Node is current redirect and alert user
  drupal_set_message(t('This !type is the current version.', array('!type' => $node->type)));
  drupal_goto('node/' . $node->nid);
}


/**
 * Display a node's moderation history
 */
function workbench_moderation_node_history_view($node) {
  drupal_add_css(drupal_get_path('module', 'workbench_moderation') . '/css/workbench_moderation.css');
  drupal_set_title(t('!title History', array('!title' => $node->title)));

  // Alert if there is no live node
  if (! isset($node->content_moderation['published'])) {
    drupal_set_message(t('Currently there is no live (published) version of this node.'));
  }

  // Get all of the node revisions including state changes
  $revisions = array();
  $result = db_query('SELECT r.vid, r.title, r.log, r.uid, n.vid, n.nid AS current_vid, r.timestamp, u.name, cmnh.*
    FROM {node_revision} r
    LEFT JOIN {node} n ON n.vid = r.vid
    INNER JOIN {users} u ON u.uid = r.uid
    INNER JOIN {workbench_moderation_node_history} cmnh ON cmnh.vid = r.vid
    WHERE r.nid = :nid 
    ORDER BY r.vid DESC',
    array(':nid' => $node->nid));

  foreach ($result as $revision) {
    $revisions[$revision->vid] = $revision;
  }

  if ($revisions) {
    foreach ($revisions as $revision) {
      $row = array();
      $operations = array();
      extract((array) $revision);

      $text = l(t('view'),"node/$nid/revisions/$vid/view") . ' | ' .
        // @TODO this should likely be permissioned
        l(t('revert'), "node/$nid/revisions/$vid/revert");

      $class = 'revision';
      $revision_id = $vid;

      // Is this the live node?
      if (isset($node->content_moderation['published']->vid) && $vid == $node->content_moderation['published']->vid) {
        $text =  t('Live revision') . ' | ' . l(t('Unpublish'), "node/$nid/moderation/$vid/unpublish");
        $class = 'revision-live';
        $revision_id = t('Original revision: !old_vid <br />Live revision: !vid', array('!old_vid' => $vid, '!vid' =>$node->vid));
      }
      // Is this the current revision?
      elseif ($vid == $node->content_moderation['current']->vid) {
        $text = t('Revision in moderation') . ' ' . $text . ' | ' . l(t('edit'), "node/{$node->nid}/edit");
        $class = 'revision-current';
      }
   
      $state_change = t('From !state --> !to_state', array('!state' => $from_state, '!to_state' => $state));

      $row = array('data' => array(
        array('data' => $state_change, 'class' => $class),
        array('data' => l(format_date($timestamp, 'short'), "node/$node->nid/revisions/$vid/view"), 'class' => $class),
        array('data' => theme('username', array('account' => $revision)), 'class' => $class),
        array('data' => '<p class="revision-log">' . filter_xss($log) . '</p>', 'class' => $class),
        array('data' => $revision_id, 'class' => $class),
        array('data' => $text, 'class' => $class)
        )
      );
      $rows[] = $row; 
    }
    $header = array(t('State change'), t('Date'), t('By'), t('Log'), t('Revision'), t('Status'));
    return theme('table', array('header' => $header, 'rows' => $rows));
  }
}


/**
 * Unpublish the live revision
 *
 * @param $node
 * @param $vid
 */
function workbench_moderation_node_unpublish_form($form, $form_state, $node, $vid) {
  // Ensure that this is the live revision
  if ($node->vid != $node->content_moderation['published']->vid) {
    drupal_set_message(t('This is not the live revision of this node.'), 'error');
    drupal_goto(request_uri());
  }

  // Alert the user of what will happen
  drupal_set_message();

  // Set the context of the moderation operation
  menu_set_active_item("node/{$node->nid}/moderation");
  $form = array();

  $form['moderate'] = array(
    '#title' => t('Change modertation state'),
    '#type' => 'fieldset',
  );

  $form['node'] = array(
    '#value' => $node,
    '#type' => 'value'
  );

  return confirm_form($form,
    t('Are you sure that you want to unpublish the live
      revision of this content? When you unpublish this revision, this revision
      will be set to moderation state: !state. The current revision of this
      content will remain the current one.', array('!state' => workbench_moderation_state_none())),
    "node/{$node->nid}/moderation"
  );
}

/**
 * Submit handler for unpublishing a live revision of a node.
 * 
 * @param $form
 * @param $form_state
 */
function workbench_moderation_node_unpublish_form_submit($form, $form_state) {
  global $user;
  $node = $form_state['values']['node'];

  // Update the moderation history.
  $data = array(
    'hid' => $node->content_moderation['published']->hid,
    'from_state' => workbench_moderation_state_none(),
    'state' => workbench_moderation_state_none(),
    'uid' => $user->uid,
    'published' => 0,
  );
  drupal_write_record('workbench_moderation_node_history', $data, 'hid');

  // Now update the node status to unpublished
  $data = array(
    'nid' => $node->nid,
    'status' => 0,
    'log' => t('Unpublished by moderation'),
  );
  drupal_write_record('node', $data, 'nid');

  // Update the revision log.
  $data['vid'] = $node->vid;
  drupal_write_record('node_revison', $data, 'vid');

  drupal_set_message(t('The live revision of this content has been unpublished.'));
}
