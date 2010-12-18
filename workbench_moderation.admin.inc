<?php

/**
 * @file
 *  Content moderation for Workbench.
 *
 * @copyright (C) Copyright 2010 Palantir.net
 */

/**
 * Form builder function for module settings.
 *
 * Defining states
 */
function workbench_moderation_admin_settings_states($form, &$form_state) {
  $form['new'] = array(
    '#type' => 'fieldset',
    '#title' => 'Create new',
  );
  $form['new']['new_state_name'] = array(
    '#type' => 'textfield',
    '#title' => 'Create new state',
    '#size' => 60,
    '#maxlength' => 255,
    '#description' => t('Enter name of new state.')
  );

  $form['new']['new_state_description'] = array(
    '#type' => 'textarea',
    '#description' => 'Enter an optional description of new state.'
  );

  $form['new']['submit_states'] = array(
    '#type' => 'submit',
    '#value' => t('Create')
  );
  $form['delete'] = array(
    '#type' => 'fieldset',
    '#title' => 'Delete state',
    '#tree' => TRUE,
    '#description' => 'Select all states you want to delete <br/> Please note:
      when deleting an existing state all transitions involving this state
      will also be deleted.'
  );

  $states = workbench_moderation_states_get();
  foreach ($states as $state => $state_description) {

    $form['delete']['states'][$state] = array(
      '#type' => 'checkbox',
      '#title' => $state,
      '#description' => ($state_description != $state) ? $state_description : '',
      '#default_value' => FALSE,
   );
   // Live and none states can not be deleted
    if ($state == workbench_moderation_state_published() || $state == workbench_moderation_state_none()) {
      $form['delete']['states'][$state]['#disabled'] = TRUE;
      $form['delete']['states'][$state]['#title'] .= t(' (This state can not be deleted.)');
    }
  }

  $form['delete']['submit_states'] = array(
    '#type' => 'submit',
    '#value' => t('Delete')
  );

  return $form;
}


/**
 * Form builder function for module settings.
 *
 * Defining transitions
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
    '#description' => t('Select all states you want to delete <br/> Please note: deleting an existing transition will not have any impact on states involved.')
  );
  $form['delete']['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete')
  );

  return $form;
}


function workbench_moderation_admin_settings_states_submit($form, &$form_state) {
  // Delete any selected states
  foreach ($form_state['values']['delete']['states'] as $state => $action ) {
    // @TODO nodes that are in these moderated states need to be updated to the
    //       previous state? Need to figure this one out- probably can just be
    //       handled by an alert to the user
    if ($action) {
      // Remove the moderation state
      db_query("DELETE FROM {workbench_moderation_states} WHERE name = :name", array(':name' => $state));
      // Remove this state from transitions
      db_query("DELETE FROM {workbench_moderation_transitions} WHERE from_name = :name OR to_name = :name", array(':name' => $state));
    }
  }
  // Add a new step
  if ($form_state['values']['new_state_name']) {
    $new_state = (object) NULL;
    $new_state->name = $form_state['values']['new_state_name'];
    $new_state->description = isset($form_state['values']['new_state_description']) ? $form_state['values']['new_state_description'] : $new_state->name;
    drupal_write_record('workbench_moderation_states', $new_state);
  }
  drupal_set_message(t('Your settings have been saved.'));
}

function workbench_moderation_admin_settings_transitions_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  foreach ( $form_values['delete_transitions'] as $transition => $action ) {
    if ( is_string($action) ) {
      $transinfo = explode('---', $transition);
      db_query("DELETE FROM {workbench_moderation_transitions} WHERE from_name = :from_name AND to_name = :to_name", array(
        ':from_name' => $transinfo[0],
        ':to_name' => $transinfo[1],
      ));
    }
  }
  if ($form_values['new_transition_from'] != '0' && $form_values['new_transition_to'] != '0' ) {
    $new_transition = (object) NULL;
    $new_transition->from_name = $form_values['new_transition_from'];
    $new_transition->to_name = $form_values['new_transition_to'];
    $new_transition->ntype = 'all';
    drupal_write_record('workbench_moderation_transitions', $new_transition);
  }
  drupal_set_message(t('Your settings have been saved.'));
}
