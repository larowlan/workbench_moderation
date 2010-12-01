// $Id;

/**
 * @file
 * Provides javascript services
 */


(function ($) {


/**
 * Handle moderation settings
 */
Drupal.behaviors.contentModeration = {};
Drupal.behaviors.contentModeration.attach = function(context) {

  // On page load either show or uncheck the moderation options
  var checked = $('#edit-node-options-moderation').attr('checked');
  if (checked) {
    // Ensure that revisions is checked and published is not
    $('#edit-node-options-revision').attr('checked', true);
    $('#edit-node-options-status').attr('checked', false);
    // Disable revisions and publishing
    $('#edit-node-options-status').attr('disabled', true);
    $('#edit-node-options-revision').attr('disabled', true);
    $('.form-item-content-moderation-default-state').show();
  }

  // On page load either show or uncheck the moderation options
  else {
    var checked = $('#edit-node-options-revisions').attr('checked');
    if (! checked) {
      // Disable revisions and publishing
      $('#edit-node-options-moderation').attr('disabled', true);
      $('#edit-node-options-moderation').attr('checked', false);
      $('.form-item-content-moderation-default-state').hide();
    }
  }

  $('#edit-node-options-revision').bind('click', function () {
    if ($(this).attr('checked')) {
      $('#edit-node-options-moderation').attr('disabled', false);
    }
    else {
      // Moderation is not possible
      $('#edit-node-options-moderation').attr('checked', false);
      $('#edit-node-options-moderation').attr('disabled', 'disabled');
      $('.form-item-content-moderation-default-state').hide('slow');
    }
  });

  $('#edit-node-options-moderation').bind('click', function () {
    if ($(this).attr('checked')) {
      // Ensure that revisions is checked and published is not
      $('#edit-node-options-revision').attr('checked', true);
      $('#edit-node-options-status').attr('checked', false);
      // Disable revisions and publishing
      $('#edit-node-options-status').attr('disabled', true);;
      $('#edit-node-options-revision').attr('disabled', true);
      // Show the moderation options
      $('.form-item-content-moderation-default-state').show('slow');

    }
    else {
      // Show revision and published
      $('#edit-node-options-status').attr('disabled', false);;
      $('#edit-node-options-revision').attr('disabled', false);
      // Hide the moderation options
      $('.form-item-content-moderation-default-state').hide('slow');
    }

  });

};


})(jQuery);