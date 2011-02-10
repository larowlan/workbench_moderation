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
  foreach ($states as $i => $state) {
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
    '#description' => t('Enter name of the new state.')
  );
  $new_state['description'] = array(
    '#type' => 'textfield',
    '#maxlength' => 255,
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
 * Form builder function for module transition settings.
 *
 *@TODO
 *  Provide weighting of transition states.
 */
function workbench_moderation_admin_settings_transitions($form, &$form_state) {
  $form['new'] = array(
    '#type' => 'fieldset',
    '#title' => 'Create new',
  );

  $form['new']['new_transition_from'] = array(
    '#type' => 'select',
    '#title' => 'New transition from',
    '#default_value' => array(),
    '#options' => array_merge(array(0 => t('Choose a state')), workbench_moderation_states_get()),
  );

  $form['new']['new_transition_to'] = array(
    '#type' => 'select',
    '#title' => 'to',
    '#default_value' => array(),
    '#options' => array_merge(array(0 => t('Choose a state')), workbench_moderation_states_get()),
  );

  $form['new']['submit_transitions'] = array(
    '#type' => 'submit',
    '#value' => t('Create')
  );

  $form['delete'] = array(
    '#type' => 'fieldset',
    '#title' => 'Delete transitions',
  );

  $options = array();
  foreach (workbench_moderation_transitions_get() as $from_state => $states) {
    foreach ($states as $to_state) {
      $options[$from_state . '---' . $to_state] = $from_state . ' -> ' . $to_state;
    }
  }
  $form['delete']['delete_transitions'] = array(
    '#type' => 'checkboxes',
    '#title' => 'Delete existing transitions',
    '#default_value' => array(),
    '#options' => $options,
    '#description' => t('Select all states you want to delete.<br/> Please note: deleting an existing transition will not have any impact on states involved.')
  );
  $form['delete']['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete')
  );

  return $form;
}

/**
 * Form submit handler for moderation transitions.
 *
 * @TODO:
 *  Proper cleanup when transitions are deleted.
 */
function workbench_moderation_admin_settings_transitions_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  foreach ($form_values['delete_transitions'] as $transition => $action) {
    // Check for a valid action and delete as needed.
    if (is_string($action)) {
      $transinfo = explode('---', $transition);
      db_delete('workbench_moderation_transitions')
        ->condition('from_name', $transinfo[0])
        ->condition('to_name', $transinfo[1])
        ->execute();
    }
  }
  // Check for the creation of new transitions.
  if ($form_values['new_transition_from'] != '0' && $form_values['new_transition_to'] != '0' ) {
    $new_transition = (object) NULL;
    $new_transition->from_name = $form_values['new_transition_from'];
    $new_transition->to_name = $form_values['new_transition_to'];
    $new_transition->ntype = 'all';
    drupal_write_record('workbench_moderation_transitions', $new_transition);
  }
  // Return a message.
  drupal_set_message(t('Your settings have been saved.'));
}
