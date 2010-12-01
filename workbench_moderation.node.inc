<?php

/**
 * @file
 * Provides node functions
 *
 * @copyright (C) Copyright 2010 Palantir.net
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

  // Get all of the node revisions, each with its most recent moderation.
  $query = db_select('node', 'n');
  $query->leftJoin('node_revision', 'r', 'n.nid = r.nid');
  $query->leftJoin('users', 'u', 'r.uid = u.uid');
  $query->addField('n', 'vid', 'live_revision');
  $query->condition('n.nid', $node->nid)
    ->orderBy('r.vid', 'DESC')
    ->fields('r', array('nid', 'vid', 'title', 'log', 'uid', 'timestamp'))
    ->fields('u', array('name'));

  $revisions = $query->execute()
    ->fetchAllAssoc('vid');

  $rows = array();
  foreach ($revisions as $revision) {
    $row = array(
      'data' => array(
        'vid' => '',
        'info' => '',
        'date' => '',
        'revision' => '',
        'moderation' => '',
      ),
      'class' => array('revision'),
    );
    
    // Row classes.
    if ($revision->vid == $node->content_moderation['current']->vid) {
      $row['class'][] = 'current-revision';
    }
    if (isset($node->content_moderation['published']) && $revision->vid == $node->content_moderation['published']->vid) {
      $row['class'][] = 'published-revision';
    }
    else {
      $row['class'][] = 'unpublished-revision';
    }

    // Row data.
    $row['data']['vid'] = $revision->vid;
    $row['data']['info'] = '<div class="revision-title">' . check_plain($revision->title) . '</div>'
                         . '<div class="revision-log">' . filter_xss($revision->log) . '</div>'
                         . '<div class="revision-user">' . t('Revised by !user', array('!user' => theme('username', array('account' => $revision)))) . '</div>';
    $row['data']['date'] = l(format_date($revision->timestamp, 'short'), "node/{$node->nid}/moderation/{$revision->vid}/view");

    // Revision operations.
    $revision_operations = array();
    foreach (array('view', 'revert', 'delete') as $perm) {
      if (user_access("$perm revisions")) {
        $revision_operations[] =  l(t('!perm', array('!perm' => $perm)), "node/{$revision->nid}/revisions/{$revision->vid}/$perm", array('query' => array('destination' => $_GET['q'])));
      }
    }
    $row['data']['revision'] = implode(' | ', $revision_operations);
    
    // Get the moderation history of this revision.
    $query = db_select('workbench_moderation_node_history', 'm');
    $query->leftJoin('users', 'u', 'm.uid = u.uid');
    $query->condition('m.vid', $revision->vid)
      ->orderBy('m.stamp', 'DESC')
      ->fields('m')
      ->fields('u', array('name'));
    
    $moderations = $query->execute()
      ->fetchAllAssoc('hid');
  
    // Make sure it's an array.
    if (empty($moderations)) {
      $moderations = array();
      if ($revision->vid == $node->content_moderation['current']->vid) {
        $moderations = array($node->content_moderation['current']);
      }
    }

    // If this is the current revision, provide moderation links.
    if (!empty($node->content_moderation['published']) && $revision->vid == $node->content_moderation['published']->vid) {
      $row['data']['moderation'] = '<div class="moderation-state"><strong>' . t('This is the published revision.') . '</strong></div>';
      // Provide an unpublish link.
      if (user_access('unpublish live version')) {
        $row['data']['moderation'] .= '<div class="moderation-actions">' . l(t('Unpublish'), "node/{$revision->nid}/moderation/{$revision->live_revision}/unpublish") . '</div>';
      }
    }
    elseif ($revision->vid == $node->content_moderation['current']->vid) {
      $node_current = workbench_moderation_node_current_load($node);
      $row['data']['moderation'] = '<div class="moderation-state"><strong>' . t('This is the current revision. The current state is %state.', array('%state' => $node->content_moderation['current']->state)) . '</strong></div>'
                                 . '<div class="moderation-actions">' . theme('links', array('links' => workbench_moderation_get_moderation_links($node_current, array('query' => array('destination' => $_GET['q']))))) . '</div>';
    }
    
    // Build a table of the moderation history.
    $moderation_rows = array();
    $items = array();
    foreach ($moderations as $m) {
      if ($m->from_state) {
        $items[] = t('From @from_state --> @to_state on %date by !user',
                     array(
                      '@from_state' => $m->from_state,
                      '@to_state' => $m->state,
                      '%date' => format_date($m->stamp, 'short'),
                      '!user' => theme('username', array('account' => $m)),
                    ));
      }
      else {
        $items[] = t('Created as @to_state on %date by !user',
                     array(
                      '@from_state' => $m->from_state,
                      '@to_state' => $m->state,
                      '%date' => format_date($m->stamp, 'short'),
                      '!user' => theme('username', array('account' => $m)),
                    ));
      }
    }
    $row['data']['moderation'] .= theme('item_list', array('items' => $items));

    $rows[] = $row;
  }

  $header = array(t('Revision'), t('Title'), t('Date'), t('Revision Actions'), t('Moderation Actions'));
  return array('#markup' => theme('table', array('header' => $header, 'rows' => $rows)));
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
