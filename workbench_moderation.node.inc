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
  if (!isset($node->content_moderation['published'])) {
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
  if (empty($revisions)) {
    $revisions = array($node->vid => $node->content_moderation['current']);
  }
  if ($revisions) {
    foreach ($revisions as $revision) {
      $row = array();
      $operations = array();
      extract((array) $revision);

      foreach (array('view', 'revert', 'delete') as $perm) {
        if (user_access("$perm revisions")) {
          $operations[] =  l(t('!perm', array('!perm' => $perm)),"node/$nid/revisions/$vid/$perm");
        }
      }
      $text = implode(' | ', $operations);
      $class = 'revision';
      $revision_id = $vid;

      // Is this the live node?
      if (isset($node->content_moderation['published']->vid) && $vid == $node->content_moderation['published']->vid) {
        $text =  user_access('view revisions') ? l(t('Live revision'), "node/$nid/revisions/$vid/view") : t('Live revision');
        if ($node->status) {
          $text .= user_access('unpublish live version') ? ' | ' . l(t('Unpublish'), "node/$nid/moderation/$vid/unpublish") : '';
          $class = 'revision-live';
        }
        else {
          $text .= user_access('publish pending version') ? ' | ' . l(t('Publish'), "node/$nid/moderation/$vid/publish") : '';
          $class = 'revision-unpublished';
        }
        $revision_id = t('Original revision: @old_vid <br />Live revision: @vid', array('@old_vid' => $vid, '@vid' =>$node->vid));
      }
      // Is this the current revision?
      elseif ($vid == $node->content_moderation['current']->vid) {
        $text = t('Revision in moderation') . ' ' . $text . ' | ' . l(t('edit'), "node/{$node->nid}/edit");
        $class = 'revision-current';
      }
      if ($from_state != $state) {
        $state_change = t('From @state --> @to_state', array('@state' => $from_state, '@to_state' => $state));
      }
      else {
        $state_change = t('@state state edited', array('@state' => $state));
      }
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
  // TODO: Return something useful or hide the tab.
  return t('There are no revisions to review.');
}

/**
 * Unpublish the live revision
 *
 * @param $node
 * @param $vid
 */
function workbench_moderation_node_status_form($form, $form_state, $node, $vid) {
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

  // Make a new revision of the node.
  $node->revision = TRUE;

/*  $form['moderate'] = array(
    '#title' => t('Change modertation state'),
    '#type' => 'fieldset',
  );
*/
  $status = ($node->status) ? t('unpublish') : t('publish');
  $state = ($node->status) ? workbench_moderation_state_none() : workbench_moderation_state_published();
  $form['message'] = array(
    '#markup' =>  '<p>'. t('Are you sure that you want to %status this revision? The live version of this content
      will be set to moderation state: %state.', array('%status' => $status, '%state' => $state)) . '</p>',
  );
  $form['node'] = array(
    '#value' => $node,
    '#type' => 'value'
  );
  $form['status'] = array(
    '#type' => 'value',
    '#value' => !$node->status,
  );
  return confirm_form($form, 
    t('!status "!title"?', array('!status' => ucwords($status), '!title' => $node->title)),
    "node/{$node->nid}/moderation"
  );
}

/**
 * Submit handler for unpublishing a live revision of a node.
 * 
 * @param $form
 * @param $form_state
 */
function workbench_moderation_node_status_form_submit($form, $form_state) {
  global $user;
  $node = $form_state['values']['node'];
  $node->status = (int) $form_state['values']['status'];
  $message = ($node->status) ? t('published') : t('unpublished');
  $node->log = t('!message by @user.', array('!message' => ucwords($message), '@user' => $user->name));
  node_save($node);
  // Update the moderation history.
  // Set all versions to historic.
  db_update('workbench_moderation_node_history')
    ->fields(array('current' => 0, 'published' => 0))
    ->condition('nid', $node->nid)
    ->execute();
  // Set new version to current.
  $data = array(
    'nid' => $node->nid,
    'vid' => $node->vid,
    'from_state' => $node->content_moderation['current']->state,
    'state' => ($node->status) ? workbench_moderation_state_published() : workbench_moderation_state_none(),
    'uid' => $user->uid,
    'stamp' => $node->changed,
    'published' => 1,
    'current' => 1,
  );
  drupal_write_record('workbench_moderation_node_history', $data);
  drupal_set_message(t('The live revision of this content has been %message.', array('%message' => $message)));
}
