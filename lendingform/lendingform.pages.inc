<?php

/**
 *
 * entity: lendingform : eg. nlab
 *
 */
// Add all forms definitions
module_load_include('inc', 'lendingform', 'lendingform.form');


// List lendingforms / create .................................................................

/**
 * Function for listing for all the lendingformes
 * @return <type> themed array
 */
function lendingform_listing($op) {
  $output = '';
  
  // No access for subdomain
  if (lendingform_siemens_is_subdomain()) {
    return drupal_not_found();
  }
  
  // Default: List of lendingforms
  if (empty($op)) {
    $op = 'list';
    // Link to add new lendingform
    if (!lendingform_siemens_is_subdomain()) {
      $output .= '<ul  class="action-links"><li>';
      $output .= l(t('Create New Project'), 'lendingforms/create');
      $output .= '</li></ul>';
    }
    // Project List block
    $block = block_load('views', 'lendingforms-block');
    $block = _block_get_renderable_array(_block_render_blocks(array($block)));
    $output .= drupal_render($block);
  }
  else {
    // check what to do
    switch ($op) {
      case 'create' :
        drupal_set_title(t('Create Project'));
        $output = drupal_get_form('lendingform_form');
        break;
    }
  }

  return $output;
}


// Search User  .................................................................


/**
 * 
 * Search for users
 * to be added as team member
 * 
 * @param type $uids
 */
function lendingform_search_user($search = NULL) {
  
  $users = array();
  if (empty($search)) {
    $users = entity_load('user');
  } else {
    // Search users
    $users = entity_get_controller(PROJECT_ENTITY)->search_users($search);
  }
  
  $users_name_and_id = array();
  foreach ($users as $user) {
    $users_name_and_id[] = array(
        'uid' => $user->uid,
        'name' => lendingform_siemens_format_username($user),
    );
  }

  echo json_encode($users_name_and_id);
  
  exit();
}






// Modal Forms ..............................................................................



/**
 * edit citation form wrapper
 *
 * @param $lendingform
 *
 */
function siemens_lendingform_edit_form_wrapper($lendingform) {    
    ctools_include('modal');
    ctools_include('ajax');

    $form_state = array(
        'title' => t('Edit Project'),
        'ajax' => TRUE,
    );
    $output = ctools_modal_form_wrapper('siemens_lendingform_delete_confirm', $form_state);

    if ($form_state['executed']) {
        $returnback = drupal_get_query_parameters();
        if (isset($returnback['returnback'])) {
            drupal_goto($returnback['returnback'], array('query' => array('tab' => 2)));
        } else {

            $commands = array();
            $commands[] = ctools_modal_command_dismiss();            
            
            $citation_list = siemens_citations_get_citations($lendingform->entity_id);
            $commands[] = ajax_command_html('#siemens-existing-references', $citation_list);

            print ajax_render($commands);
            exit();
        }
    }

    print ajax_render($output);
    exit();
}



/**
 * Create Project confirmation form
 *
 * @param $lendingform
 *
 */
function siemens_lendingform_create_form_wrapper($lendingform) {
  
  // No access for subdomain
  if (lendingform_siemens_is_subdomain()) {
    return drupal_not_found();
  }
  
    ctools_include('modal');
    ctools_include('ajax');

    $form_state = array(
        'title' => t('Create Project'),
        'ajax' => TRUE,
    );
    $output = ctools_modal_form_wrapper('siemens_lendingform_create_ajax_confirm', $form_state);

    if ($form_state['executed']) {
        $returnback = drupal_get_query_parameters();
        if (isset($returnback['returnback'])) {
            drupal_goto($returnback['returnback'], array('query' => array('tab' => 2)));
        } else {

            $commands = array();
            $commands[] = ctools_modal_command_dismiss();            
            
            $citation_list = siemens_citations_get_citations($lendingform->entity_id);
            $commands[] = ajax_command_html('#siemens-existing-references', $citation_list);

            print ajax_render($commands);
            exit();
        }
    }

    print ajax_render($output);
    exit();
}






// Project Elements export page ..............................................................................


function lendingform_export_page() {
  global $lendingform_global;
  global $base_url;
  $html = '';
  
  // only accessible in subdomain
  if (!lendingform_siemens_is_subdomain()) {
    return drupal_not_found();
  }
  
  if (variable_get('lendingform_siemens_cron_once_' . $lendingform_global->pid, 0) == 1) {
    return drupal_not_found();
  }
  
  // description
  $html .= 'Export progress';
  $html .= '<div id="lendingform-export-bar-wrapper"></div>';
  $html .= '<div id="lendingform-progress-value">0%</div>';
  $html .= '<div id="lendingform-export-message"></div>';
  $html .= '<div id="lendingform-export-complete" style="display:none" class="messages status"><h2 class="element-invisible">Status message</h2>completed ' . l(t('continue'), $base_url) .'</div>';
  
  
  // call for transfering of elements
  $exports = module_invoke_all('lendingform_export_transfer');
  
  
  // Pass data to javascript for ajax processing
  $data = array('siemens_lendingform_export' => array('data' => $exports));
  drupal_add_js($data, array('type' => 'setting'));
  
  
  return $html;
}