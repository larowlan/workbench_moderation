/**
 * @file
 * README file for Workbench Moderation.
 */

Workbench Moderation
Arbitrary moderation states and unpublished drafts for nodes

CONTENTS
--------

1.  Introduction
1.1   Concepts
2.  Installation
3.  Configuration
3.1 States
3.2 Transitions
3.3 Checking permissions
3.3.1 Recommended permissions
4.  Using the module
5.  Troubleshooting
6.  Developer notes
7.  Feature roadmap


----
1.  Introduction

Workbench Moderation 

----
1.1  Concepts

Workbench Moderation adds arbitrary moderation states to Drupal core's "unpublished" and "published" node states, and affects the behavior of node revisions when nodes are published. Moderation states are tracked per-revision; rather than moderating nodes, Workbench Moderation moderates revisions.

----
1.1.1  Arbitrary publishing states

In Drupal, nodes may be either unpublished or published. In typical configurations, unpublished nodes are accessible only to the user who created the node and to users with administrative privileges; published nodes are visible to any visitor. For simple workflows, this allows authors and editors to maintain drafts of content. However, when content needs to be seen by multiple people before it is published--for example, when a site has an editorial or moderation workflow--there are limited ways to keep track of nodes' status. Workbench Moderation provides moderation states, so that unpublished content may be reviewed and approved before it gets published.

----
1.1.2  Node revision behavior

Workbench Moderation affects the behavior of Drupal’s node revisions. When revisions are enabled for a particular node type, editing a node creates a new revision. This lets users see how a node has changed over time and revert unwanted or accidental edits. Workbench Moderation maintains this revision behavior: any time a node is edited, a new version is created.

When there are multiple versions of a node--it has been edited multiple times, and each round of editing has been saved in a revision--there is one "current" revision. The current revision will always be the revision displayed in the node editing form when a user goes to edit a piece of content.

In Drupal core, publishing a node makes the current revision visible to site visitors (in a typical configuration). Once a node is published, its current revision is always the published version. Workbench Moderation changes this; it allows you to use an older revision of a node as the published version, while continuing to edit a newer draft.

@see workbench_moderation-core_revisions.png
@see workbench_moderation-wm_revisions.png

Internally, Workbench Moderation does this by managing the version of the node stored in the {node} table. Drupal core looks in this table for the "current revision" of a node. Drupal core equates the "current revision" of a node with both the editable revision and, if the node is published, the published revision. Workbench Moderation separates these two concepts; it stores the published revision of a node in the {node} table, but uses the latest revision in the {node_revision} table when the node is edited. Workbench Moderation's treatment of revisions is identical to that of Drupal core until a node is published.

----
1.1.3  Moderation states and revisions

Workbench Moderation maintains moderation states for revisions, rather than for nodes. Since each revision may reflect a unique version of a node, the state may need to be revisited when a new revision is created. This also allows users to track the moderation history of a particular revision, right up through the point where it is published.

Revisions are a linear; revision history may not fork. This means that only the latest revision--Workbench Moderation calls this the "current draft"--may be edited or moderated.

----
2. Installation

Install the module and enable it according to Drupal standards.

After installation, enable moderation on a content type by visiting its configuration page:

    Admin > Structure > Content Types > [edit Article]

In the tab block at the bottom of the form, select the "Publishing options" tab. In this tab under "Default Options", Workbench Moderation has added a checkbox, "Enable moderation of revisions". To enable moderation on this node type, check the boxes labeled "create new revision" (required) and "enable moderation of revisions", and then save the node type.

----
3.  Configuration

Workbench Moderation's configuration section is located at:

    Admin > Configuration > Workbench > Workbench Moderation

This administration section provides tabs to configure states, transitions, and to check whether your permissions are configured to enable full use of moderation features.

----
3.1  Configuring states

Workbench Moderation provides three default moderation states: "Draft", "Needs Review", and "Published". The Draft and Published states are required. You can edit, add, and remove states at:

    Admin > Configuration > Workbench > Workbench Moderation > States

----
3.2  Configuring transitions

Workbench Moderation also provides transitions between these three states. You can add and remove transitions at:

    Admin > Configuration > Workbench > Workbench Moderation > Transitions

----
3.3  Checking permissions

In order to use moderation effectively, users need a complex set of permissions. If non-administrative users encounter access denied (403) errors or fail to see notifications about moderation states, the "Check permissions" tab can help you determine what permissions are missing. Visit:

    Admin > Configuration > Workbench > Workbench Moderation > Check Permissions

Select a Drupal role, an intended moderation task, and the relevant node types, and Workbench Moderation will give you a report of possible missing permissions. Permissions configuration depends heavily on your configuration, so the report may flag permissions as missing even when a particular role has enough access to perform a particular moderation task.

----
3.3.1  Recommended permissions

  For reference, these are the permission sets recommended by the "Check Permissions" tab:

    Author:
      Node:
        access content
        view own unpublished content
        view revisions
        create [content type] content
        edit own [content type] content
      Workbench Moderation:
        view moderation messages
        use workbench_moderation my drafts tab
    
    Editor:
      Node:
        access content
        view revisions
        revert revisions
        edit any [content type] content
      Workbench:
        view all unpublished content
      Workbench Moderation:
        view moderation messages
        view moderation history
        use workbench_moderation my drafts tab
        use workbench_moderation needs review tab
    
    Moderator:
      Node:
        access content
        view revisions
        edit any [content type] content
      Workbench:
        view all unpublished content
      Workbench Moderation:
        view moderation messages
        view moderation history
        use workbench_moderation needs review tab
    Publisher
      Node:
        access content
        view revisions
        revert revisions
        edit any [content type] content
      Workbench:
        view all unpublished content
      Workbench Moderation:
        view moderation messages
        view moderation history
        use workbench_moderation needs review tab
        unpublish live revision

----
4.  Using the module

----
5.  Troubleshooting

----
6.  Developer notes

----
7.  Feature roadmap
