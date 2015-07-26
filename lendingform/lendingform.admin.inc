<?php

/**
 *
 * Admin page for gallery
 * 
 */
// Add all forms definitions
module_load_include('inc', 'lendingform', 'lendingform.form');
module_load_include('inc', 'lendingform', 'lendingform.constant');


//
// Project Listing page
// Also, support gallery create page
//
function lendingform_page_admin($tab = '') {
  global $user;
    foreach($user->roles as $role){
     $userrole = $role;
  }
  
  $module_path =  drupal_get_path('module', 'lendingform');
  //echo $module_path; exit;
	
	 drupal_add_js($module_path . '/scripts/assets/royalslider/jquery.royalslider.min.js');
	 drupal_add_css($module_path . '/scripts/assets/royalslider/royalslider.css');
	 drupal_add_js($module_path . '/scripts/validation.js');
	 drupal_add_css($module_path . '/scripts/assets/royalslider/skins/default/rs-default.css');

  
  
 // echo $userrole;
  $output = '';
  switch ($tab) {
    case 'create':
      $build['lendingform_create'] = drupal_get_form('lendingform_form');
	  
	  if(isset($_SESSION['customeuid']))
	  $userid = $_SESSION['customeuid'];
	  
	  if(($userrole == "anonymous user") || ($userrole == "client")){
		 if((!empty($userid)) || ($userrole == "client") ){
    	   $output = theme('user_form_result', array('vars' => $build));
		 } else {
		   drupal_goto("user");
		   exit;		 
		 }
      } else {   
     	 $output = drupal_render($build);
	  }
      break;
    default:
	
      // Link to add new gallery
      $output .= l(t('Enquiry Form'), 'admin/structure/enquiry/create', array('attributes' => array('class' => array('lendingform-btn-add'))))."<br/>";
	  $output .= l(t('Export Data in CSV Format'), 'exportcsv', array('attributes' => array('class' => array('lendingform-btn-add'))));
      // Project List
	 
	 /*echo "Hello"; exit;*/
	 $build['lendingform_filter'] = drupal_get_form('lendingform_filter_form');
     $build['lendingform_list'] = drupal_get_form('lendingform_list_form');
     $output .= drupal_render($build);
	  
  }
  return $output;
}


/**
 * Applies filters for node administration filters based on session.
 *
 * @param $query
 *   A SelectQuery to which the filters should be applied.
 */
function lendingform_build_filter_query(SelectQueryInterface $query) {
  // Build query
  $filter_data = isset($_SESSION['lendingform_overview_filter']) ? $_SESSION['lendingform_overview_filter'] : array();
 /* print_r($filter_data); exit;*/
  foreach ($filter_data as $index => $filter) {
  $filterVal = explode("-", $filter[1]);
  $key = $filterVal[0];
  $value = $filterVal[1];
    $query->condition('enq.' . $key, $value);
      
  }
  
}

function trend_csv_export($nodes){
	$filename = 'export.csv';
	$table = "enquiry";
	$csv_terminated = "\n";
	$csv_separator = ",";
	$csv_enclosed = '"';
	$csv_escaped = "\\";
	
	/*print_r($nodes); exit;*/
	
	$eids = array();
	foreach($nodes as $ids){
		array_push($eids, $ids);
	}
	$schema = drupal_get_schema($table);

	$fields_cnt = count($schema['fields']); 
	$schema_insert = '';
 	
	foreach ($schema['fields'] as $key=>$field)
	{
		$l = $csv_enclosed . str_replace($csv_enclosed, $csv_escaped . $csv_enclosed,
			stripslashes($key)) . $csv_enclosed;
		$schema_insert .= $l;
		$schema_insert .= $csv_separator;
	
	} // end for
 
	$out = trim(substr($schema_insert, 0, -1));
	$out .= $csv_terminated;
 
	
	$result = db_select('enquiry', 'e')
		->fields('e')
		->condition('e.eid', $eids, 'IN') 
		->execute()
		->fetchAll();
		
	foreach ($result as $row)
	{ 
	$data = array();
	$i = 0;
	foreach($row as $key => $value){
	$data[$i] = $value;
	$i++;
	}
	
		/*echo "<pre>";
		print_r($data); exit;*/
		$schema_insert = '';
		for ($j = 0; $j < $fields_cnt; $j++)
		{
			if ($data[$j] == '0' || $data[$j] != '')
			{
 
				if ($csv_enclosed == '')
				{
					$schema_insert .= $data[$j];
				} else
				{
					$schema_insert .= $csv_enclosed .
					str_replace($csv_enclosed, $csv_escaped . $csv_enclosed, $data[$j]) . $csv_enclosed;
				}
			} else
			{
				$schema_insert .= '';
			}
 
			if ($j < $fields_cnt - 1)
			{
				$schema_insert .= $csv_separator;
			}
		} // end for
 
		$out .= $schema_insert;
		$out .= $csv_terminated;
	} // end while
 
	header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
	header("Content-Length: " . strlen($out));
	// Output to browser with appropriate mime type, you choose ;)
	header("Content-type: text/x-csv");
	//header("Content-type: text/csv");
	//header("Content-type: application/csv");
	header("Content-Disposition: attachment; filename=$filename");
	echo $out;
	exit;
}



/**
 * Returns the lendingform administration filters form array to enquiryform_admin_content().
 * @ingroup forms
 */
function lendingform_filter_form() {
  $session = isset($_SESSION['lendingform_overview_filter']) ? $_SESSION['lendingform_overview_filter'] : array();
  $filters = lendingform_filters();

  $i = 0;
  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show only items where'),
    '#theme' => 'exposed_filters__lendingform',
  );
  foreach ($session as $filter) {
    list($type, $value) = $filter;
    if ($type == 'term') {
      // Load term name from DB rather than search and parse options array.
      $value = module_invoke('taxonomy', 'term_lendingform', $value);
      $value = $value->name;
    }
    elseif ($type == 'language') {
      $value = $value == LANGUAGE_NONE ? t('Language neutral') : module_invoke('locale', 'language_name', $value);
    }
    else {
      $value = $filters[$type]['options'][$value];
    }
    $t_args = array('%property' => $filters[$type]['title'], '%value' => $value);
    if ($i++) {
      $form['filters']['current'][] = array('#markup' => t('and where %property is %value', $t_args));
    }
    else {
      $form['filters']['current'][] = array('#markup' => t('where %property is %value', $t_args));
    }
    if (in_array($type, array('type', 'language'))) {
      // Remove the option if it is already being filtered on.
      unset($filters[$type]);
    }
  }

  $form['filters']['status'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('clearfix')),
    '#prefix' => ($i ? '<div class="additional-filters">' . t('and where') . '</div>' : ''),
  );
  $form['filters']['status']['filters'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('filters')),
  );
  foreach ($filters as $key => $filter) {
    $form['filters']['status']['filters'][$key] = array(
      '#type' => 'select',
      '#options' => $filter['options'],
      '#title' => $filter['title'],
      '#default_value' => '[any]',
    );
  }

  $form['filters']['status']['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['filters']['status']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => count($session) ? t('Refine') : t('Filter'),
  );
  if (count($session)) {
    $form['filters']['status']['actions']['undo'] = array('#type' => 'submit', '#value' => t('Undo'));
    $form['filters']['status']['actions']['reset'] = array('#type' => 'submit', '#value' => t('Reset'));
  }

  drupal_add_js('misc/form.js');

  return $form;
}

/**
 * Form submission handler for lendingform_filter_form().
 */
function lendingform_filter_form_submit($form, &$form_state) {
  $filters = lendingform_filters();
  switch ($form_state['values']['op']) {
    case t('Filter'):
    case t('Refine'):
      // Apply every filter that has a choice selected other than 'any'.
      foreach ($filters as $filter => $options) {
        if (isset($form_state['values'][$filter]) && $form_state['values'][$filter] != '[any]') {
          // Flatten the options array to accommodate hierarchical/nested options.
          $flat_options = form_options_flatten($filters[$filter]['options']);
          // Only accept valid selections offered on the dropdown, block bad input.
          if (isset($flat_options[$form_state['values'][$filter]])) {
            $_SESSION['lendingform_overview_filter'][] = array($filter, $form_state['values'][$filter]);
          }
        }
      }
      break;
    case t('Undo'):
      array_pop($_SESSION['lendingform_overview_filter']);
      break;
    case t('Reset'):
      $_SESSION['lendingform_overview_filter'] = array();
      break;
  }
}


function lendingform_filters() {
  // Regular filters
  $filters['status'] = array(
    'title' => t('status'),
    'options' => array(
      '[any]' => t('any'),
      'workflow_status-0'  => t('Open'),
      'workflow_status-1'  => t('Application in progress'),
      'workflow_status-2'  => t('Funded'),
      'workflow_status-3'  => t('Closed'),
    ),
  );
  // Include translation states if we have this module enabled
  if (module_exists('translation')) {
    $filters['status']['options'] += array(
      'translate-0' => t('Up to date translation'),
      'translate-1' => t('Outdated translation'),
    );
  }

  $filters['type'] = array(
    'title' => t('type'),
    'options' => array(
      '[any]' => t('any'),
	  'funding_type-0' => t('Cashflow'),
	  'funding_type-1' => t('Equipment'),
	  'funding_type-2' => t('Automotive'),
	  'funding_type-3' => t('Commercial'),
    ),
  );

  // Language filter if there is a list of languages
  if ($languages = module_invoke('locale', 'language_list')) {
    $languages = array(LANGUAGE_NONE => t('Language neutral')) + $languages;
    $filters['language'] = array(
      'title' => t('language'),
      'options' => array(
        '[any]' => t('any'),
      ) + $languages,
    );
  }
  return $filters;
}


function trend_mass_update($nodes, $updates) {

  if (count($nodes) > 10) {
    $batch = array(
      'operations' => array(
        array('_node_mass_update_batch_process', array($nodes, $updates))
      ),
      'finished' => '_node_mass_update_batch_finished',
      'title' => t('Processing'),
      // We use a single multi-pass operation, so the default
      // 'Remaining x of y operations' message will be confusing here.
      'progress_message' => '',
      'error_message' => t('The update has encountered an error.'),
      // The operations do not live in the .module file, so we need to
      // tell the batch engine which file to load before calling them.
      'file' => drupal_get_path('module', 'lendingform') . '/lendingform.admin.inc',
    );
    batch_set($batch);
  }
  else {
    foreach ($nodes as $nid) {
      _node_mass_update_helper($nid, $updates);
    }
    drupal_set_message(t('The update has been performed.'));
  }
}

function _node_mass_update_helper($nid, $updates) {
  $node = lendingform_load($nid, NULL, TRUE);
  // For efficiency manually save the original node before applying any changes.
  $node->original = clone $node;
  foreach ($updates as $name => $value) {
    $node->$name = $value;
  }
  lendingform_save($node);
  return $node;
}


/**
 * Executes a batch operation for node_mass_update().
 *
 * @param array $nodes
 *   An array of node IDs.
 * @param array $updates
 *   Associative array of updates.
 * @param array $context
 *   An array of contextual key/values.
 */
function _node_mass_update_batch_process($nodes, $updates, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($nodes);
    $context['sandbox']['nodes'] = $nodes;
  }

  // Process nodes by groups of 5.
  $count = min(5, count($context['sandbox']['nodes']));
  for ($i = 1; $i <= $count; $i++) {
    // For each nid, load the node, reset the values, and save it.
    $nid = array_shift($context['sandbox']['nodes']);
    $node = _node_mass_update_helper($nid, $updates);

    // Store result for post-processing in the finished callback.
    $context['results'][] = l($node->title, 'node/' . $node->nid);

    // Update our progress information.
    $context['sandbox']['progress']++;
  }

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Menu callback: Reports the status of batch operation for node_mass_update().
 *
 * @param bool $success
 *   A boolean indicating whether the batch mass update operation successfully
 *   concluded.
 * @param int $results
 *   The number of nodes updated via the batch mode process.
 * @param array $operations
 *   An array of function calls (not used in this function).
 */
function _node_mass_update_batch_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('The update has been performed.'));
  }
  else {
    drupal_set_message(t('An error occurred and processing did not complete.'), 'error');
    $message = format_plural(count($results), '1 item successfully processed:', '@count items successfully processed:');
    $message .= theme('item_list', array('items' => $results));
    drupal_set_message($message);
  }
}





/**
 * Function that creates form for listing gallery
 * This function provide the gallery listing in the form of table
 * @return <type>
 */
function lendingform_list_form($form, $form_state) {
    if (isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'delete') {
        return lendingform_multiple_delete_confirm($form, $form_state, array_filter($form_state['values']['gallerys']));
    }
    
    $form['admin'] = lendingpost_admin_enquiries();
    return $form;
}

function lendingform_multiple_delete_confirm($form, &$form_state, $gallerys) {
  $form['gallerys'] = array('#prefix' => '<ul>', '#suffix' => '</ul>', '#tree' => TRUE);
  // array_filter returns only elements with TRUE values
  foreach ($gallerys as $eid => $value) {
    $loan_title = db_query('SELECT loan_title FROM {enquiry} WHERE eid = :eid', array(':eid' => $eid))->fetchField();
    $form['gallerys'][$eid] = array(
      '#type' => 'hidden',
      '#value' => $eid,
      '#prefix' => '<li>',
      '#suffix' => check_plain($loan_title) . "</li>\n",
    );
  }
  $form['operation'] = array('#type' => 'hidden', '#value' => 'delete');
  $form['#submit'][] = 'lendingform_multiple_delete_confirm_submit';
  $confirm_question = format_plural(count($gallerys),
                                  'Are you sure you want to delete this item?',
                                  'Are you sure you want to delete these items?');
  return confirm_form($form,
                    $confirm_question,
                    'admin/structure/enquiry', t('This action cannot be undone.'),
                    t('Delete'), t('Cancel'));
}

function lendingform_multiple_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {    
    lendingform_delete_multiple(array_keys($form_state['values']['gallerys']));
    $count = count($form_state['values']['gallerys']);
    watchdog('gallery', 'Deleted @count posts.', array('@count' => $count));
    drupal_set_message(format_plural($count, 'Deleted 1 post.', 'Deleted @count posts.'));
  }
  $form_state['redirect'] = 'admin/structure/enquiry';
}

/**
 * Form builder: Builds the gallery administration overview.
 */
function lendingpost_admin_enquiries() {
	
	
	  global $user;
		foreach($user->roles as $role){
		 $userrole = $role;
	  }
   
    $admin_access = user_access(PERM_ADMINISTER_LENDINGFORM);
	
    //Add the bulk operation for gallery entity
    // Build the 'Update options' form.
     $form['options'] = array(
        '#type' => 'fieldset',
        '#title' => t('Update options'),
        '#attributes' => array('class' => array('container-inline')),
        '#access' => $admin_access,
    );
	
    $options = array();
	
    foreach (module_invoke_all('enquiry_operations') as $operation => $array) {
		
        $options[$operation] = $array['label'];
    }
   
    $form['options']['operation'] = array(
        '#type' => 'select',
        '#title' => t('Operation'),
        '#title_display' => 'invisible',
        '#options' => $options,
        '#default_value' => 'approve',
    );
    $form['options']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Update'),
        '#validate' => array('lendingform_form_list_validate'),
        '#submit' => array('lendingform_form_list_submit'),
    );


    $header = array(
        'title_en' => array('data' => t('Loan Title'), 'field' => 'enq.eid', 'sort' => 'DESC'),
		'name' => array('data' => t('Name'), 'field' => 'enq.first_name'),
		'loan' => array('data' => t('Loan Amount')),
		'loan_type' => array('data' => t('Loan type')),
		'workflow_status' => array('data' => t('Status')),
		'changed' => array('data' => t('Changed')),      
        'operations' => array('data' => t('Operations')),
    );


    //Listing of trends for administration
    $query = db_select('enquiry', 'enq'); 	
	lendingform_build_filter_query($query);
	if(($userrole == 'cashflow') || ($userrole == 'automotive') || ($userrole == 'equipment') || ($userrole == 'commercial')){
			if($userrole == 'cashflow') 
			$cond = 0;
			if($userrole == 'equipment') 
			$cond = 1;
			if($userrole == 'automotive') 
			$cond = 2;
			if($userrole == 'commercial') 
			$cond = 3;
			
			
		$query->condition('funding_type', $cond);	
	}
	
    $count_query = clone $query;
    $count_query->addExpression('COUNT(enq.eid)');

    $query = $query->extend('PagerDefault')->extend('TableSort');
    $query
            ->fields('enq', array('eid', 'loan_title', 'company_name', 'funding_type', 'first_name', 'last_name', 'fund_amount', 'workflow_status', 'changed'))
            ->limit(50)
            ->orderByHeader($header)
            ->setCountQuery($count_query);
	// restrict gallery display by areas the user is assigned to
	
    $result = $query->execute();
	

    $destination = drupal_get_destination();
    $options = array();

    foreach ($result as $row)
    { /*  echo $row->first_name; exit;*/
		if($row->funding_type == '0')
			$type = "Cashflow";	
		elseif($row->funding_type == '1')
		    $type = "Equipment";
		elseif($row->funding_type == '2')
		    $type = "Automotive";
		elseif($row->funding_type == '3')
		    $type = "Commercial";
			
			
		if($row->workflow_status == 0)
			$status = "Open";
		elseif($row->workflow_status == 1)
			$status = "Application in progress";
		elseif($row->workflow_status == 2)
			$status = "Funded";
		elseif($row->workflow_status == 3)
			$status = "Closed";	
			
			
			
        $options[$row->eid] = array(
            'title_en' => array('data' => array(
                    '#type' => 'link',
                    '#title' => $row->loan_title."-".$row->company_name,
                    '#href' => "enquiry/$row->eid",
            )),
			'name' => check_plain($row->first_name ." ".$row->last_name),    
			'loan' => check_plain("$".$row->fund_amount), 
			'loan_type' => check_plain("".$type), 
			'workflow_status' => check_plain("".$status),
			'changed' => format_date($row->changed, 'short'),          
            'operations' => array('data' =>array(
                array(
                    '#prefix' => '<ul class="links inline">',),
                array(
                    '#prefix' => '<li>',
                    '#suffix' => '</li>',
                    '#type' => 'link',
                    '#title' => t('edit'),
                    '#href' => "admin/structure/enquiry/$row->eid/edit",
                    '#attributes' => array('class' => array('edit')),
                    '#options' => array('query' => $destination)
					),
			    array(
                    '#prefix' => '<li>',
                    '#suffix' => '</li>',
                    '#type' => 'link',
                    '#title' => t('delete'),
                    '#href' => "admin/structure/enquiry/$row->eid/delete",
                    '#attributes' => array('class' => array('edit')),
                    '#options' => array('query' => $destination)
					),					
                array(
                    '#suffix' => '</ul>',),

            )),
        );
    }  
    
    // Only use a tableselect when the current user is able to perform any
    // operations.
	/*$admin_access = 1;*/
    if ($admin_access) {
        $form['gallerys'] = array(
            '#type' => 'tableselect',
            '#header' => $header,
            '#options' => $options,
            '#empty' => t('No trends available.'),  
            '#attributes' => array (
                'id' => 'gallery-result-table',
            )
        );
    }
    // Otherwise, use a simple table.
    else {
        $form['gallerys'] = array(
            '#theme' => 'table',
            '#header' => $header,
            '#rows' => $options,
            '#empty' => t('No trends available.'),
        );
    }

    $form['pager']['#markup'] = theme('pager');

    return $form;
}

/**
 * Implements hook_gallery_operations().
 */
function lendingform_enquiry_operations() {
    //exit;
  $operations = array(
    'open' => array(
      'label' => t('Change status to Open'),
      'callback' => 'trend_mass_update',
      'callback arguments' => array('updates' => array('workflow_status' => TREND_OPEN)),
    ),
    'in_progress' => array(
      'label' => t('Chage status to Inprogress'),
      'callback' => 'trend_mass_update',
      'callback arguments' => array('updates' => array('workflow_status' => TREND_IN_PROGRESS)),
    ),
	 'funded' => array(
      'label' => t('Change status to Funded'),
      'callback' => 'trend_mass_update',
      'callback arguments' => array('updates' => array('workflow_status' => TREND_FUNDED)),
    ),
    'closed' => array(
      'label' => t('Change status to Closed'),
      'callback' => 'trend_mass_update',
      'callback arguments' => array('updates' => array('workflow_status' => TREND_CLOSED)),
    ),
    'delete' => array(
      'label' => t('Delete selected enquires'),
      'callback' => NULL,
    ),
	'Export in CSV' => array(
      'label' => t('Export in CSV format'),
      'callback' => 'trend_csv_export',
    ),
  );
  return $operations;
}

/**
 * Validate gallery_form_list form submissions.
 *
 * Check if any gallery have been selected to perform the chosen
 * 'Update option' on.
 */
function lendingform_form_list_validate($form, &$form_state) {
  // Error if there are no items to select.
  if (!is_array($form_state['values']['gallerys']) || !count(array_filter($form_state['values']['gallerys']))) {
    form_set_error('', t('No items selected.'));
  }
}


/**
 * Process gallery_form_list_submit form submissions.
 *
 * Execute the chosen 'Update option' on the selected trends.
 */
function lendingform_form_list_submit($form, &$form_state) {
/*	exit;*/
  $operations = module_invoke_all('enquiry_operations');
  $operation = $operations[$form_state['values']['operation']];
  // Filter out unchecked trends
  $gallerys = array_filter($form_state['values']['gallerys']);
  if ($function = $operation['callback']) {
    // Add in callback arguments if present.
    if (isset($operation['callback arguments'])) {
      $args = array_merge(array($gallerys), $operation['callback arguments']);
    }
    else {
      $args = array($gallerys);
    }
    call_user_func_array($function, $args);

    cache_clear_all();
  }
  else {
    // We need to rebuild the form to go to a second step. For example, to
    // show the confirmation form for the deletion of trends.
    $form_state['rebuild'] = TRUE;
  }
}