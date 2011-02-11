<?php
// $Id$
/**
 * @file
 *  Administrative functions for content moderation for Workbench.
 *
 * @copyright (C) Copyright 2010 Palantir.net
 */

/**
 * Administration form for states. Administrators can use this form to add, delete, reorder, and
 * update the description for states.
 */
function workbench_moderation_admin_states_form($form, &$form_state) {
  $form['states'] = array(
    '#tree' => TRUE,
  );

  // List existing states.
  $states = workbench_moderation_states();
  foreach ($states as $state) {
    $form['states'][$state->name]['state'] = array(
      '#type' => 'value',
      '#value' => $state,
    );
    $form['states'][$state->name]['name'] = array(
      '#type' => 'value',
      '#value' => $state->name,
    );
    $form['states'][$state->name]['label'] = array(
      '#markup' => $state->name,
    );
    $form['states'][$state->name]['description'] = array(
      '#type' => 'textfield',
      '#default_value' => $state->description,
    );
    $form['states'][$state->name]['weight'] = array(
      '#type' => 'weight',
      '#default_value' => $state->weight,
    );
    $form['states'][$state->name]['delete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete'),
      '#title_display' => 'invisible',
      '#default_value' => FALSE,
    );
    if ($state->name == workbench_moderation_state_published() || $state == workbench_moderation_state_none()) {
      $form['states'][$state->name]['delete']['#disabled'] = TRUE;
    }
  }

  // Provide fields to create a new state.
  $new_state['name'] = array(
    '#type' => 'textfield',
    '#size' => 30,
    '#maxlength' => 255,
    '#title' => t('New state'),
    '#description' => t('Enter name of the new state.')
  );
  $new_state['description'] = array(
    '#type' => 'textfield',
    '#maxlength' => 255,
    '#title' => '&nbsp;',
    '#description' => 'Enter a description of the new state.'
  );
  $new_state['weight'] = array(
    '#type' => 'weight',
  );
  $form['states'][] = $new_state;

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Theme function to transform the states administration form into a reorderable table.
 */
function theme_workbench_moderation_admin_states_form($variables) {
  $form = $variables['form'];

  drupal_add_tabledrag('workbench-moderation-states', 'order', 'sibling', 'workbench-moderation-state-weight');

  $header = array(
    t('Name'),
    t('Description'),
    array('data' => t('Delete'), 'class' => array('checkbox')),
    t('Weight'),
  );

  $rows = array();
  foreach (element_children($form['states']) as $key) {
    $element = &$form['states'][$key];

    $row = array(
      'data' => array(),
      'class' => array('draggable'),
    );
    $row['data']['name'] = drupal_render($element['name']) . drupal_render($element['label']);
    $row['data']['description'] = drupal_render($element['description']);
    $row['data']['delete'] = drupal_render($element['delete']);

    $element['weight']['#attributes']['class'] = array('workbench-moderation-state-weight');
    $row['data']['weight'] = drupal_render($element['weight']);

    $rows[] = $row;
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'workbench-moderation-states')));
  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Form submit handler for moderation state administration.
 */
function workbench_moderation_admin_states_form_submit($form, &$form_state) {
  foreach ($form_state['values']['states'] as $key => $info) {
    if (!empty($info['delete'])) {
      workbench_moderation_state_delete($info['state']);
      drupal_set_message(t('%state has been deleted.', array('%state' => $key)));
    }
    elseif (!empty($info['name'])) {
      $state = (object) array(
        'name' => $info['name'],
        'description' => $info['description'],
        'weight' => $info['weight'],
      );
      workbench_moderation_state_save($state);
    }
  }

  drupal_set_message(t('Your settings have been saved.'));
}

/**
 * Administration form to create and delete moderation transitions. Transition ordering is based on
 * state ordering.
 */
function workbench_moderation_admin_transitions_form($form, &$form_state) {
  $form['transitions'] = array(
    '#tree' => TRUE,
  );

  // List existing states.
  $transitions = workbench_moderation_transitions();
  foreach ($transitions as $transition) {
    $element = array();

    $element['transition'] = array(
      '#type' => 'value',
      '#value' => $transition,
    );
    $element['from_name'] = array(
      '#markup' => check_plain($transition->from_name),
    );
    $element['to_name'] = array(
      '#markup' => check_plain($transition->to_name),
    );
    $element['delete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete'),
      '#title_display' => 'invisible',
      '#default_value' => FALSE,
    );

    $form['transitions'][] = $element;
  }

  // Provide fields to create a new transition.
  $options = drupal_map_assoc(array_keys(workbench_moderation_states()));
  array_unshift($options, t('- Choose state -'));
  $element = array();
  $element['from_name'] = array(
    '#type' => 'select',
    '#title' => t('New transition'),
    '#options' => $options,
  );
  $element['to_name'] = array(
    '#type' => 'select',
    '#title' => '&nbsp;',
    '#options' => $options,
  );
  $form['transitions']['new'] = $element;

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Theme function to transform the transitions administration form into a table.
 */
function theme_workbench_moderation_admin_transitions_form($variables) {
  $form = $variables['form'];

  $header = array(
    t('From'),
    '',
    t('To'),
    array('data' => t('Delete'), 'class' => array('checkbox')),
  );

  $rows = array();
  foreach (element_children($form['transitions']) as $key) {
    $element = &$form['transitions'][$key];
    $row = array('data' => array());
    $row['data']['from'] = drupal_render($element['from_name']);
    $row['data'][] = '--&gt;';
    $row['data']['to'] = drupal_render($element['to_name']);
    $row['data']['delete'] = drupal_render($element['delete']);
    $rows[] = $row;
  }

  drupal_add_css(drupal_get_path('module', 'workbench_moderation') . '/css/workbench_moderation.css');
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('width-auto'))));
  $output .= drupal_render_children($form);

  return $output;
}

function workbench_moderation_admin_transitions_form_validate($form, &$form_state) {
  $new = $form_state['values']['transitions']['new'];
  if (!empty($new['from_name']) && !empty($new['to_name'])) {
    if ($new['from_name'] == $new['to_name']) {
      form_set_error('transitions][new', t('To and from states of a new transition must be different.'));
    }
    else {
      foreach (workbench_moderation_transitions() as $t) {
        if ($new['from_name'] == $t->from_name && $new['to_name'] == $t->to_name) {
          form_set_error('transitions][new', t('This transition already exists.'));
          break;
        }
      }
    }
  }
}

/**
 * Form submit handler for moderation transitions.
 */
function workbench_moderation_admin_transitions_form_submit($form, &$form_state) {
  foreach ($form_state['values']['transitions'] as $transition) {
    if (!empty($transition['delete'])) {
      workbench_moderation_transition_delete($transition['transition']);
      drupal_set_message(t('%from --&gt; %to has been deleted.', array('%from' => $transition['transition']->from_name, '%to' => $transition['transition']->to_name)));
    }
    elseif (!empty($transition['from_name']) && !empty($transition['to_name'])) {
      $new_transition = (object) array(
        'from_name' => $transition['from_name'],
        'to_name' => $transition['to_name'],
      );
      workbench_moderation_transition_save($new_transition);
      drupal_set_message(t('%from --&gt; %to has been created.', array('%from' => $new_transition->from_name, '%to' => $new_transition->to_name)));
    }
  }
}
