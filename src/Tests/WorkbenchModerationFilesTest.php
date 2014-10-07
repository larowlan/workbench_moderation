<?php

/**
 * @file
 * Contains \Drupal\workbench_moderation\Tests\WorkbenchModerationFilesTest.
 */

namespace Drupal\workbench_moderation\Tests;

use Drupal\file\Tests\FileFieldTestBase;
use Drupal\node\Entity\Node;

/**
 * Test moderation on nodes with with file attachments.
 *
 * @group workbench_moderation
 */
class WorkbenchModerationFilesTest extends FileFieldTestBase {
  protected $contentType;
  protected $fieldName;
  protected $moderatorUser;

  /**
   * {@inheritdoc}
   */
  public static $modules = [
    'node', 'file', 'file_module_test', 'field_ui', 'workbench_moderation',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();

    // Create a new content type and enable moderation on it.
    $type = $this->drupalCreateContentType();
    $this->contentType = $type->id();
    $type->setNewRevision(TRUE);
    $type->setThirdPartySetting('workbench_moderation', 'moderation', TRUE);
    $type->save();

    // Add a file field to the new content type.
    $this->fieldName = strtolower($this->randomMachineName());
    $this->createFileField($this->fieldName, 'node', $this->contentType);

    $this->moderatorUser = $this->drupalCreateUser(array(
      'access content',
      'access administration pages',
      'administer site configuration',
      'administer users',
      'administer permissions',
      'administer content types',
      'administer nodes',
      'bypass node access',
      'view revisions',
      'revert revisions',
      "edit any {$this->contentType} content",
      'view moderation history',
      'view moderation messages',
      'bypass workbench moderation',
    ));
    $this->drupalLogin($this->moderatorUser);
  }

  /**
   * Tests moderated file field.
   */
  public function testModeratedFileField() {
    // Create a new node with an uploaded file.
    $file = $this->getTestFile('text');
    $edit = array(
      'title' => $this->randomMachineName(),
      'files[' . $this->fieldName . '_0]' => drupal_realpath($file->getFileUri()),
    );
    $this->drupalPostForm("node/add/{$this->contentType}", $edit, t('Save'));

    // Get the new node.
    $node = $this->drupalGetNodeByTitle($edit['title']);
    $nid = $node->id();

    // Publish the node via the moderation form.
    $moderate = array('state' => workbench_moderation_state_published());
    $this->drupalPostForm("node/{$nid}/moderation", $moderate, t('Apply'));

    // Update the node; remove the first file and add a second file.
    $file = $this->getTestFile('text');
    $edit = array(
      'title' => $this->randomMachineName(10) . '_second',
      'files[' . $this->fieldName . '_0]' => drupal_realpath($file->getFileUri()),
    );
    $this->drupalPostForm("node/$nid/edit", array(), t('Remove'));
    $this->drupalPostForm(NULL, $edit, t('Save'));

    // Load the published node.
    $published = Node::load($nid, NULL, TRUE);

    // Check for a published revision.
    $this->assertTrue(isset($published->workbench_moderation->published), t('Workbench moderation has published revision'));

    // Load the draft revision.
    $draft = clone $published;
    $draft = workbench_moderation_node_current_load($draft);

    // Check that the draft revision is different from the published revision.
    $this->assertNotEqual($published->getRevisionId(), $draft->getRevisionId(), t('Workbench moderation loads second revision'));

    // Check that the original file is present on the published revision.
    $published_file = $published->{$this->fieldName}->entity;
    $this->assertFileExists($published_file, t('File is present on published revision'));

    // Check that the second file is present on the draft revision.
    $draft_file = $draft->{$this->fieldName}->entity;
    $this->assertFileExists($draft_file, t('File is present on draft revision'));
    $this->assertNotEqual($published_file->getFileUri(), $draft_file->getFileUri(), t('File on published revision is different from file on draft revision'));
  }

}
