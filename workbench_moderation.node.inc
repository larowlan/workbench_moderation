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
  global $user;

  drupal_add_css(drupal_get_path('module', 'workbench_moderation') . '/css/workbench_moderation.css');
  drupal_set_title(t('!title History', array('!title' => $node->title)));

  // Alert if there is no live node
  if (!isset($node->content_moderation['published'])) {
    drupal_set_message(t('Currently there is no live (published) version of this node.'));
  }

  // Get all of the node revisions including state changes.
  $query = db_select('node', 'n');
  $query->leftJoin('node_revision', 'r', 'n.nid = r.nid');
  $query->leftJoin('users', 'u', 'r.uid = u.uid');
  $query->leftJoin('workbench_moderation_node_history', 'moderation', 'r.vid = moderation.vid');
  $query->addField('n', 'vid', 'live_revision');
  $query->condition('n.nid', $node->nid)
    ->orderBy('moderation.current', 'DESC')
    ->orderBy('r.vid', 'DESC')
    ->fields('r', array('nid', 'vid', 'title', 'log', 'uid', 'timestamp'))
    ->fields('u', array('name'))
    ->fields('moderation');

  $revisions = $query->execute()
    ->fetchAllAssoc('vid');

  if (empty($revisions)) {
    $revisions = array($node->vid => $node->content_moderation['current']);
  }

  $node_current = $node;
  if (!$node->content_moderation['my_revision']->current) {
    $node_current = node_load($node->nid, $node->content_moderation['current']->vid);
  }

  $rows = array();
  foreach ($revisions as $revision) {
    $class = 'revision';
    $row = array(
      'vid' => array('data' => $revision->vid),
      'state' => array('data' => ''),
      'date' => array('data' => ''),
      'user' => array('data' => ''),
      'moderation' => array('data' => ''),
      'revision' => array('data' => ''),
    );

    // State and log information.
    if ($revision->from_state != $revision->state) {
      $state_change = t('From @state --> @to_state', array('@state' => $revision->from_state, '@to_state' => $revision->state));
    }
    else {
      $state_change = t('@state, edited', array('@state' => $revision->state));
    }
    $row['state']['data'] .= '<p class="workbench-moderation-transition">' . $state_change . '</p><p class="revision-log">' . filter_xss($revision->log) . '</p>';

    // Revision date.
    $row['date']['data'] = l(format_date($revision->timestamp, 'short'), "node/{$node->nid}/moderation/{$revision->vid}/view");

    // Revision user.
    $row['user']['data'] = theme('username', array('account' => $revision));

    // Moderation links.
    if ($revision->current) {
      $row['moderation']['data'] = theme('links', array('links' => workbench_moderation_get_moderation_links($node_current, array('query' => array('destination' => $_GET['q'])))));
      $class = 'revision-unpublished';
    }

    if ($revision->published) {
      $row['vid']['data'] = t('Original revision: @old_vid <br />Live revision: @vid', array('@old_vid' => $revision->vid, '@vid' => $revision->live_revision));
      $class = 'revision-live';

      if (user_access('unpublish live version')) {
        $row['moderation']['data'] .= l(t('Unpublish'), "node/{$revision->nid}/moderation/{$revision->live_revision}/unpublish");
      }
    }

    // Revision operations.
    $operations = array();
    foreach (array('view', 'revert', 'delete') as $perm) {
      if (user_access("$perm revisions")) {
        $operations[] =  l(t('!perm', array('!perm' => $perm)),"node/{$revision->nid}/revisions/{$revision->vid}/$perm", array('query' => array('destination' => $_GET['q'])));
      }
    }
    $row['revision']['data'] = implode(' | ', $operations);

    foreach (array_keys($row) as $key) {
      $row[$key]['class'] = $class;
    }

    $rows[] = $row;
  }

  $header = array(t('Revision'), t('State change'), t('Date'), t('By'), t('Moderation Actions'), t('Revision Actions'));
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
