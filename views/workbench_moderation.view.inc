<?php
// $Id$


$view = new view;
$view->name = 'workbench_moderation';
$view->description = 'Listing of content by moderation state.';
$view->tag = 'Workbench';
$view->base_table = 'node';
$view->human_name = '';
$view->core = 0;
$view->api_version = '3.0-alpha1';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'access workbench';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '25';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
$handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 25, 50, 100, 200';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'nid' => 'nid',
  'log' => 'log',
  'state' => 'state',
  'vid' => 'vid',
  'title' => 'title',
  'type' => 'type',
  'name' => 'name',
  'timestamp' => 'timestamp',
  'current' => 'current',
  'stamp' => 'stamp',
  'nothing' => 'nothing',
  'moderation_actions' => 'moderation_actions',
);
$handler->display->display_options['style_options']['default'] = 'stamp';
$handler->display->display_options['style_options']['info'] = array(
  'nid' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'log' => array(
    'align' => '',
    'separator' => '',
  ),
  'state' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'vid' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'title' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'type' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'name' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'timestamp' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'current' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'stamp' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
  ),
  'nothing' => array(
    'align' => '',
    'separator' => '',
  ),
  'moderation_actions' => array(
    'align' => '',
    'separator' => '',
  ),
);
$handler->display->display_options['style_options']['override'] = 1;
$handler->display->display_options['style_options']['sticky'] = 0;
$handler->display->display_options['style_options']['order'] = 'desc';
/* Relationship: Node revision: User */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'node_revision';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
/* Relationship: Workbench Moderation: User */
$handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
$handler->display->display_options['relationships']['uid_1']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
$handler->display->display_options['relationships']['uid_1']['required'] = 0;
/* Field: Node: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
$handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['nid']['alter']['html'] = 0;
$handler->display->display_options['fields']['nid']['hide_empty'] = 0;
$handler->display->display_options['fields']['nid']['empty_zero'] = 0;
$handler->display->display_options['fields']['nid']['link_to_node'] = 0;
/* Field: Node revision: Log message */
$handler->display->display_options['fields']['log']['id'] = 'log';
$handler->display->display_options['fields']['log']['table'] = 'node_revision';
$handler->display->display_options['fields']['log']['field'] = 'log';
$handler->display->display_options['fields']['log']['exclude'] = TRUE;
$handler->display->display_options['fields']['log']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['log']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['log']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['log']['alter']['trim'] = 0;
$handler->display->display_options['fields']['log']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['log']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['log']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['log']['alter']['html'] = 0;
$handler->display->display_options['fields']['log']['hide_empty'] = 0;
$handler->display->display_options['fields']['log']['empty_zero'] = 0;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = 'Moderation Link';
$handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['text'] = 'View moderation history';
$handler->display->display_options['fields']['nothing']['alter']['make_link'] = 1;
$handler->display->display_options['fields']['nothing']['alter']['path'] = 'node/[nid]/moderation';
$handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
$handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
$handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
/* Field: Workbench Moderation: State */
$handler->display->display_options['fields']['state']['id'] = 'state';
$handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['fields']['state']['field'] = 'state';
$handler->display->display_options['fields']['state']['label'] = 'Moderation State';
$handler->display->display_options['fields']['state']['alter']['alter_text'] = 1;
$handler->display->display_options['fields']['state']['alter']['text'] = '<div>[state]</div><div>[nothing]</div>';
$handler->display->display_options['fields']['state']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['state']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['state']['alter']['trim'] = 0;
$handler->display->display_options['fields']['state']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['state']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['state']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['state']['alter']['html'] = 0;
$handler->display->display_options['fields']['state']['element_label_colon'] = 1;
$handler->display->display_options['fields']['state']['element_default_classes'] = 1;
$handler->display->display_options['fields']['state']['hide_empty'] = 0;
$handler->display->display_options['fields']['state']['empty_zero'] = 0;
/* Field: Workbench Moderation: Moderation Links */
$handler->display->display_options['fields']['moderation_actions']['id'] = 'moderation_actions';
$handler->display->display_options['fields']['moderation_actions']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['fields']['moderation_actions']['field'] = 'moderation_actions';
$handler->display->display_options['fields']['moderation_actions']['label'] = 'Moderate';
$handler->display->display_options['fields']['moderation_actions']['alter']['alter_text'] = 1;
$handler->display->display_options['fields']['moderation_actions']['alter']['text'] = '<div>[moderation_actions]</div>';
$handler->display->display_options['fields']['moderation_actions']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['moderation_actions']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['moderation_actions']['alter']['trim'] = 0;
$handler->display->display_options['fields']['moderation_actions']['alter']['word_boundary'] = 0;
$handler->display->display_options['fields']['moderation_actions']['alter']['ellipsis'] = 0;
$handler->display->display_options['fields']['moderation_actions']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['moderation_actions']['alter']['html'] = 0;
$handler->display->display_options['fields']['moderation_actions']['element_label_colon'] = 1;
$handler->display->display_options['fields']['moderation_actions']['element_default_classes'] = 1;
$handler->display->display_options['fields']['moderation_actions']['hide_empty'] = 0;
$handler->display->display_options['fields']['moderation_actions']['empty_zero'] = 0;
/* Field: Node Revision - Linked Title */
$handler->display->display_options['fields']['title_1']['id'] = 'title_1';
$handler->display->display_options['fields']['title_1']['table'] = 'node_revision';
$handler->display->display_options['fields']['title_1']['field'] = 'title';
$handler->display->display_options['fields']['title_1']['ui_name'] = 'Node Revision - Linked Title';
$handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['title_1']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['title_1']['alter']['make_link'] = 1;
$handler->display->display_options['fields']['title_1']['alter']['path'] = 'node/[nid]/current-revision';
$handler->display->display_options['fields']['title_1']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['title_1']['alter']['trim'] = 0;
$handler->display->display_options['fields']['title_1']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['title_1']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['title_1']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['title_1']['alter']['html'] = 0;
$handler->display->display_options['fields']['title_1']['element_label_colon'] = 1;
$handler->display->display_options['fields']['title_1']['element_default_classes'] = 1;
$handler->display->display_options['fields']['title_1']['hide_empty'] = 0;
$handler->display->display_options['fields']['title_1']['empty_zero'] = 0;
$handler->display->display_options['fields']['title_1']['link_to_node'] = 0;
$handler->display->display_options['fields']['title_1']['link_to_node_revision'] = 0;
/* Field: Node Revision - Title and Log Message */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node_revision';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['ui_name'] = 'Node Revision - Title and Log Message';
$handler->display->display_options['fields']['title']['alter']['alter_text'] = 1;
$handler->display->display_options['fields']['title']['alter']['text'] = '<div>[title_1]</div><div>[log]</div>';
$handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['title']['alter']['trim'] = 0;
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['title']['alter']['html'] = 0;
$handler->display->display_options['fields']['title']['element_label_colon'] = 1;
$handler->display->display_options['fields']['title']['element_default_classes'] = 1;
$handler->display->display_options['fields']['title']['hide_empty'] = 0;
$handler->display->display_options['fields']['title']['empty_zero'] = 0;
$handler->display->display_options['fields']['title']['link_to_node'] = 0;
$handler->display->display_options['fields']['title']['link_to_node_revision'] = 0;
/* Field: Node: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['type']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['type']['alter']['trim'] = 0;
$handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['type']['alter']['html'] = 0;
$handler->display->display_options['fields']['type']['element_label_colon'] = 1;
$handler->display->display_options['fields']['type']['element_default_classes'] = 1;
$handler->display->display_options['fields']['type']['hide_empty'] = 0;
$handler->display->display_options['fields']['type']['empty_zero'] = 0;
$handler->display->display_options['fields']['type']['link_to_node'] = 0;
$handler->display->display_options['fields']['type']['machine_name'] = 0;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
$handler->display->display_options['fields']['name']['label'] = 'Revision Author';
$handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['name']['alter']['trim'] = 0;
$handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['name']['alter']['html'] = 0;
$handler->display->display_options['fields']['name']['hide_empty'] = 0;
$handler->display->display_options['fields']['name']['empty_zero'] = 0;
$handler->display->display_options['fields']['name']['link_to_user'] = 1;
$handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
/* Field: Node revision: Created date */
$handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
$handler->display->display_options['fields']['timestamp']['table'] = 'node_revision';
$handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
/* Field: Workbench Moderation: Timestamp */
$handler->display->display_options['fields']['stamp']['id'] = 'stamp';
$handler->display->display_options['fields']['stamp']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['fields']['stamp']['field'] = 'stamp';
$handler->display->display_options['fields']['stamp']['label'] = 'Last moderated';
$handler->display->display_options['fields']['stamp']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['stamp']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['stamp']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['stamp']['alter']['trim'] = 0;
$handler->display->display_options['fields']['stamp']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['stamp']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['stamp']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['stamp']['alter']['html'] = 0;
$handler->display->display_options['fields']['stamp']['hide_empty'] = 0;
$handler->display->display_options['fields']['stamp']['empty_zero'] = 0;
$handler->display->display_options['fields']['stamp']['date_format'] = 'time ago';
/* Sort criterion: Node revision: Vid */
$handler->display->display_options['sorts']['vid']['id'] = 'vid';
$handler->display->display_options['sorts']['vid']['table'] = 'node_revision';
$handler->display->display_options['sorts']['vid']['field'] = 'vid';
$handler->display->display_options['sorts']['vid']['order'] = 'DESC';
/* Filter: Workbench Moderation: Type is moderated */
$handler->display->display_options['filters']['workbench_moderation_moderated_type']['id'] = 'workbench_moderation_moderated_type';
$handler->display->display_options['filters']['workbench_moderation_moderated_type']['table'] = 'node';
$handler->display->display_options['filters']['workbench_moderation_moderated_type']['field'] = 'workbench_moderation_moderated_type';
$handler->display->display_options['filters']['workbench_moderation_moderated_type']['value'] = '1';
/* Filter: Workbench Moderation: Current */
$handler->display->display_options['filters']['current']['id'] = 'current';
$handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['current']['field'] = 'current';
$handler->display->display_options['filters']['current']['value'] = '1';
/* Filter: Workbench Moderation: Published */
$handler->display->display_options['filters']['published']['id'] = 'published';
$handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['published']['field'] = 'published';
/* Filter: Workbench Moderation: State */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['value'] = array(
  'Review' => 'Review',
  'Approve' => 'Approve',
);
$handler->display->display_options['filters']['state']['exposed'] = TRUE;
$handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['label'] = 'Moderation State';
$handler->display->display_options['filters']['state']['expose']['use_operator'] = TRUE;
$handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
$handler->display->display_options['filters']['state']['expose']['reduce'] = 1;

/* Display: Needs Review Page */
$handler = $view->new_display('page', 'Needs Review Page', 'needs_review_page');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Needs Review';
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'use workbench_moderation needs review tab';
$handler->display->display_options['path'] = 'admin/workbench/needs-review';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Needs Review';
$handler->display->display_options['menu']['weight'] = '99';

/* Display: Drafts Page */
$handler = $view->new_display('page', 'Drafts Page', 'drafts_page');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'My Drafts';
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'use workbench_moderation my drafts tab';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'nid' => 'nid',
  'log' => 'log',
  'state' => 'state',
  'vid' => 'vid',
  'title' => 'title',
  'type' => 'type',
  'name' => 'name',
  'timestamp' => 'timestamp',
  'stamp' => 'stamp',
  'nothing' => 'nothing',
  'moderation_actions' => 'moderation_actions',
);
$handler->display->display_options['style_options']['default'] = 'stamp';
$handler->display->display_options['style_options']['info'] = array(
  'nid' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'log' => array(
    'align' => '',
    'separator' => '',
  ),
  'state' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'vid' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'title' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'type' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'name' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'timestamp' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'stamp' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
  ),
  'nothing' => array(
    'align' => '',
    'separator' => '',
  ),
  'moderation_actions' => array(
    'align' => '',
    'separator' => '',
  ),
);
$handler->display->display_options['style_options']['override'] = 1;
$handler->display->display_options['style_options']['sticky'] = 0;
$handler->display->display_options['style_options']['order'] = 'desc';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Node: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
$handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['nid']['alter']['html'] = 0;
$handler->display->display_options['fields']['nid']['hide_empty'] = 0;
$handler->display->display_options['fields']['nid']['empty_zero'] = 0;
$handler->display->display_options['fields']['nid']['link_to_node'] = 0;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = 'Moderation Link';
$handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['text'] = 'View moderation history';
$handler->display->display_options['fields']['nothing']['alter']['make_link'] = 1;
$handler->display->display_options['fields']['nothing']['alter']['path'] = 'node/[nid]/moderation';
$handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
$handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
$handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
/* Field: Workbench Moderation: State */
$handler->display->display_options['fields']['state']['id'] = 'state';
$handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['fields']['state']['field'] = 'state';
$handler->display->display_options['fields']['state']['label'] = 'Moderation State';
$handler->display->display_options['fields']['state']['alter']['alter_text'] = 1;
$handler->display->display_options['fields']['state']['alter']['text'] = '<div>[state]</div><div>[nothing]</div>';
$handler->display->display_options['fields']['state']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['state']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['state']['alter']['trim'] = 0;
$handler->display->display_options['fields']['state']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['state']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['state']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['state']['alter']['html'] = 0;
$handler->display->display_options['fields']['state']['element_label_colon'] = 1;
$handler->display->display_options['fields']['state']['element_default_classes'] = 1;
$handler->display->display_options['fields']['state']['hide_empty'] = 0;
$handler->display->display_options['fields']['state']['empty_zero'] = 0;
/* Field: Workbench Moderation: Moderation Links */
$handler->display->display_options['fields']['moderation_actions']['id'] = 'moderation_actions';
$handler->display->display_options['fields']['moderation_actions']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['fields']['moderation_actions']['field'] = 'moderation_actions';
$handler->display->display_options['fields']['moderation_actions']['label'] = 'Moderate';
$handler->display->display_options['fields']['moderation_actions']['alter']['alter_text'] = 1;
$handler->display->display_options['fields']['moderation_actions']['alter']['text'] = '<div>[moderation_actions]</div>';
$handler->display->display_options['fields']['moderation_actions']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['moderation_actions']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['moderation_actions']['alter']['trim'] = 0;
$handler->display->display_options['fields']['moderation_actions']['alter']['word_boundary'] = 0;
$handler->display->display_options['fields']['moderation_actions']['alter']['ellipsis'] = 0;
$handler->display->display_options['fields']['moderation_actions']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['moderation_actions']['alter']['html'] = 0;
$handler->display->display_options['fields']['moderation_actions']['element_label_colon'] = 1;
$handler->display->display_options['fields']['moderation_actions']['element_default_classes'] = 1;
$handler->display->display_options['fields']['moderation_actions']['hide_empty'] = 0;
$handler->display->display_options['fields']['moderation_actions']['empty_zero'] = 0;
/* Field: Node Revision - Linked Title */
$handler->display->display_options['fields']['title_1']['id'] = 'title_1';
$handler->display->display_options['fields']['title_1']['table'] = 'node_revision';
$handler->display->display_options['fields']['title_1']['field'] = 'title';
$handler->display->display_options['fields']['title_1']['ui_name'] = 'Node Revision - Linked Title';
$handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['title_1']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['title_1']['alter']['make_link'] = 1;
$handler->display->display_options['fields']['title_1']['alter']['path'] = 'node/[nid]/current-revision';
$handler->display->display_options['fields']['title_1']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['title_1']['alter']['trim'] = 0;
$handler->display->display_options['fields']['title_1']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['title_1']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['title_1']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['title_1']['alter']['html'] = 0;
$handler->display->display_options['fields']['title_1']['element_label_colon'] = 1;
$handler->display->display_options['fields']['title_1']['element_default_classes'] = 1;
$handler->display->display_options['fields']['title_1']['hide_empty'] = 0;
$handler->display->display_options['fields']['title_1']['empty_zero'] = 0;
$handler->display->display_options['fields']['title_1']['link_to_node'] = 0;
$handler->display->display_options['fields']['title_1']['link_to_node_revision'] = 0;
/* Field: Node revision: Log message */
$handler->display->display_options['fields']['log']['id'] = 'log';
$handler->display->display_options['fields']['log']['table'] = 'node_revision';
$handler->display->display_options['fields']['log']['field'] = 'log';
$handler->display->display_options['fields']['log']['exclude'] = TRUE;
$handler->display->display_options['fields']['log']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['log']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['log']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['log']['alter']['trim'] = 0;
$handler->display->display_options['fields']['log']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['log']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['log']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['log']['alter']['html'] = 0;
$handler->display->display_options['fields']['log']['hide_empty'] = 0;
$handler->display->display_options['fields']['log']['empty_zero'] = 0;
/* Field: Node Revision - Title and Log Message */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node_revision';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['ui_name'] = 'Node Revision - Title and Log Message';
$handler->display->display_options['fields']['title']['alter']['alter_text'] = 1;
$handler->display->display_options['fields']['title']['alter']['text'] = '<div>[title_1]</div><div>[log]</div>';
$handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['title']['alter']['trim'] = 0;
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['title']['alter']['html'] = 0;
$handler->display->display_options['fields']['title']['element_label_colon'] = 1;
$handler->display->display_options['fields']['title']['element_default_classes'] = 1;
$handler->display->display_options['fields']['title']['hide_empty'] = 0;
$handler->display->display_options['fields']['title']['empty_zero'] = 0;
$handler->display->display_options['fields']['title']['link_to_node'] = 0;
$handler->display->display_options['fields']['title']['link_to_node_revision'] = 0;
/* Field: Node: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['type']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['type']['alter']['trim'] = 0;
$handler->display->display_options['fields']['type']['alter']['word_boundary'] = 0;
$handler->display->display_options['fields']['type']['alter']['ellipsis'] = 0;
$handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['type']['alter']['html'] = 0;
$handler->display->display_options['fields']['type']['hide_empty'] = 0;
$handler->display->display_options['fields']['type']['empty_zero'] = 0;
$handler->display->display_options['fields']['type']['link_to_node'] = 0;
$handler->display->display_options['fields']['type']['machine_name'] = 0;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
$handler->display->display_options['fields']['name']['label'] = 'Revision author';
$handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['name']['alter']['trim'] = 0;
$handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['name']['alter']['html'] = 0;
$handler->display->display_options['fields']['name']['element_label_colon'] = 1;
$handler->display->display_options['fields']['name']['element_default_classes'] = 1;
$handler->display->display_options['fields']['name']['hide_empty'] = 0;
$handler->display->display_options['fields']['name']['empty_zero'] = 0;
$handler->display->display_options['fields']['name']['link_to_user'] = 1;
$handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
/* Field: Node revision: Created date */
$handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
$handler->display->display_options['fields']['timestamp']['table'] = 'node_revision';
$handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
/* Field: Workbench Moderation: Timestamp */
$handler->display->display_options['fields']['stamp']['id'] = 'stamp';
$handler->display->display_options['fields']['stamp']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['fields']['stamp']['field'] = 'stamp';
$handler->display->display_options['fields']['stamp']['label'] = 'Last moderated';
$handler->display->display_options['fields']['stamp']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['stamp']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['stamp']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['stamp']['alter']['trim'] = 0;
$handler->display->display_options['fields']['stamp']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['stamp']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['stamp']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['stamp']['alter']['html'] = 0;
$handler->display->display_options['fields']['stamp']['hide_empty'] = 0;
$handler->display->display_options['fields']['stamp']['empty_zero'] = 0;
$handler->display->display_options['fields']['stamp']['date_format'] = 'time ago';
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter: Workbench Moderation: Type is moderated */
$handler->display->display_options['filters']['workbench_moderation_moderated_type']['id'] = 'workbench_moderation_moderated_type';
$handler->display->display_options['filters']['workbench_moderation_moderated_type']['table'] = 'node';
$handler->display->display_options['filters']['workbench_moderation_moderated_type']['field'] = 'workbench_moderation_moderated_type';
$handler->display->display_options['filters']['workbench_moderation_moderated_type']['value'] = '1';
/* Filter: Workbench Moderation: Current */
$handler->display->display_options['filters']['current']['id'] = 'current';
$handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['current']['field'] = 'current';
$handler->display->display_options['filters']['current']['value'] = '1';
/* Filter: Workbench Moderation: Published */
$handler->display->display_options['filters']['published']['id'] = 'published';
$handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['published']['field'] = 'published';
$handler->display->display_options['filters']['published']['value'] = '0';
/* Filter: Workbench Moderation: State */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['value'] = array(
  'Draft' => 'Draft',
  'Review' => 'Review',
);
$handler->display->display_options['filters']['state']['exposed'] = TRUE;
$handler->display->display_options['filters']['state']['expose']['label'] = 'Moderation state';
$handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
$handler->display->display_options['filters']['state']['expose']['reduce'] = 1;
/* Filter: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
$handler->display->display_options['path'] = 'admin/workbench/drafts';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'My Drafts';
$handler->display->display_options['menu']['weight'] = '98';
$translatables['workbench_moderation'] = array(
  t('Defaults'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort By'),
  t('Asc'),
  t('Desc'),
  t('Items per page'),
  t('- All -'),
  t('Offset'),
  t('revision user'),
  t('moderator user'),
  t('Nid'),
  t('Log message'),
  t('Moderation Link'),
  t('View moderation history'),
  t('node/[nid]/moderation'),
  t('Moderation State'),
  t('<div>[state]</div><div>[nothing]</div>'),
  t('Moderate'),
  t('<div>[moderation_actions]</div>'),
  t('Title'),
  t('node/[nid]/current-revision'),
  t('<div>[title_1]</div><div>[log]</div>'),
  t('Type'),
  t('Revision Author'),
  t('Created date'),
  t('Last moderated'),
  t('Needs Review Page'),
  t('Needs Review'),
  t('Drafts Page'),
  t('My Drafts'),
  t('Revision author'),
  t('Moderation state'),
);

