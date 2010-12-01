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

  // Get all of the node revisions including state changes.
  $result = db_query('SELECT r.vid, r.title, r.log, r.uid, n.nid, n.vid AS live_revision, r.timestamp, u.name, cmnh.*
    FROM {node_revision} r
    LEFT JOIN {node} n ON n.nid = r.nid
    INNER JOIN {users} u ON u.uid = r.uid
    INNER JOIN {workbench_moderation_node_history} cmnh ON cmnh.vid = r.vid
    WHERE r.nid = :nid 
    ORDER BY r.vid DESC',
    array(':nid' => $node->nid));
  $revisions = array();
  foreach ($result as $revision) {
    $revisions[$revision->vid] = $revision;
  }

  if (empty($revisions)) {
    $revisions = array($node->vid => $node->content_moderation['current']);
  }

  $rows = array();
  foreach ($revisions as $revision) {
    $operations = array();
    foreach (array('view', 'revert', 'delete') as $perm) {
      if (user_access("$perm revisions")) {
        $operations[] =  l(t('!perm', array('!perm' => $perm)),"node/{$revision->nid}/revisions/{$revision->vid}/$perm", array('query' => array('destination' => $_GET['q'])));
      }
    }
    $text = implode(' | ', $operations);
    $class = 'revision';
    $revision_id = $revision->vid;

    // Is this the live node?
    if (isset($node->content_moderation['published']->vid) && $revision->vid == $node->content_moderation['published']->vid) {
      $text =  user_access('view revisions') ? l(t('Live revision'), "node/{$revision->nid}/moderation/{$revision->live_revision}/view") : t('Live revision');
      if ($node->status) {
        $text .= user_access('unpublish live version') ? ' | ' . l(t('Unpublish'), "node/{$revision->nid}/moderation/{$revision->live_revision}/unpublish") : '';
        $class = 'revision-live';
      }
      else {
        $text .= user_access('publish pending version') ? ' | ' . l(t('Publish'), "node/{$revision->nid}/moderation/{$revision->vid}/publish") : '';
        $class = 'revision-unpublished';
      }
      $revision_id = t('Original revision: @old_vid <br />Live revision: @vid', array('@old_vid' => $revision->vid, '@vid' => $revision->live_revision));
    }
    // Is this the current revision?
    elseif ($revision->vid == $node->content_moderation['current']->vid) {
      $text = t('Revision in moderation') . ' ' . $text . ' | ' . l(t('edit'), "node/{$node->nid}/edit");
      $class = 'revision-current';
    }
    if ($revision->from_state != $revision->state) {
      $state_change = t('From @state --> @to_state', array('@state' => $revision->from_state, '@to_state' => $revision->state));
    }
    else {
      $state_change = t('@state state edited', array('@state' => $revision->state));
    }

    $rows[] = array('data' => array(
      array('data' => $state_change, 'class' => $class),
      array('data' => l(format_date($revision->timestamp, 'short'), "node/{$node->nid}/moderation/{$revision->vid}/view"), 'class' => $class),
      array('data' => theme('username', array('account' => $revision)), 'class' => $class),
      array('data' => '<p class="revision-log">' . filter_xss($revision->log) . '</p>', 'class' => $class),
      array('data' => $revision_id, 'class' => $class),
      array('data' => $text, 'class' => $class)
      )
    );

  }

  $header = array(t('State change'), t('Date'), t('By'), t('Log'), t('Revision'), t('Status'));
  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Unpublish the live revision
 *
 * @param $node
 * @param $vid
 */
function workbench_moderation_node_unpublish_form($form, $form_state, $node) {
  // Ensure that this is the live revision.
  if ($node->vid != $node->content_moderation['published']->vid) {
    drupal_set_message(t('This is not the live revision of this node.'), 'error');
    drupal_goto("node/{$node->nid}/moderation");
  }

  $form = array();
  $form['node'] = array(
    '#value' => $node,
    '#type' => 'value'
  );
  $form['message'] = array(
    '#markup' =>  '<p>'. t('Are you sure that you want to unpublish the live version of this content? The current live revision will be set to moderation state %state.', array('%state' => workbench_moderation_state_none())) . '</p>',
  );
  return confirm_form($form, t('Unpublish "!title"?', array('!title' => $node->title)), "node/{$node->nid}/moderation");
}

/**
 * Submit handler for unpublishing a live revision of a node.
 * 
 * @param $form
 * @param $form_state
 */
function workbench_moderation_node_unpublish_form_submit($form, $form_state) {
  global $user;
  $node = $form['node']['#value'];

  // Remove the moderation record's "published" flag.
  $query = db_update('workbench_moderation_node_history')
    ->condition('hid', $node->content_moderation['published']->hid)
    ->fields(array('published' => 0))
    ->execute();

  // Save a new revision of the node.
  $node->revision = TRUE;
  $node->status = 0;
  $node->log = t('Unpublished by @user.', array('@user' => $user->name));
  $node->content_moderation['creating_new_revision'] = TRUE;
  $node->workbench_moderation_state_current = $node->content_moderation['published']->state;
  $node->workbench_moderation_state_new = variable_get('workbench_moderation_default_state_' . $node->type);
  node_save($node);

  drupal_set_message(t('The live revision of this content has been unpublished.'));
  drupal_goto("node/{$node->nid}/moderation");
}
