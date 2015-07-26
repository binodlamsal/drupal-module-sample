<?php
/**
 *
 * entity: lendingforms : eg. node
 *
 */

/**
 * 
 * Form: Add/Edit form for lendingform
 * 
 */
function lendingform_form($form, &$form_state, $lendingform = NULL) {
  global $base_url, $user ;  
  /*echo "<pre>";*/
  foreach($user->roles as $role){
     $userrole = $role;
  }
  
  $options_postcode = postcode_dropdown_options();
  
 /* echo $userrole; exit;*/
  
  $form['#attributes'] = array(
      'class' => array(
          'lendingform-form-class',
      ),
  ); 
  
/*  echo "<pre>";
  print_r($lendingform); exit;*/

  if (empty($lendingform)) {
	
    $lendingform = lendingform_new('lendingform');
    $form_state['form_state'] = 'create';
    
  } 
  
  $weight = 0;

  $form['company_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Company Name'),
    '#default_value' =>$lendingform->company_name,
	'#weight' => $weight++,
	'#prefix' => '<div id="content-slider-1" class="royalSlider contentSlider rsDefault"><div> <div class="form-enquiry form-step1 clearfix"><div class="title"><h3>Step 1. Tell us about your company</h3></div><div class="form-item-enquiry">',
	'#required' => true,
        '#attributes' => array('placeholder' => 'Company Name'),
  );
  
  if(($userrole == 'administrator') || ($userrole == 'cashflow') || ($userrole == 'automotive') || ($userrole == 'equipment') || ($userrole == 'commercial')) {
  
	  $form['acn_abn'] = array(
		'#type' => 'textfield',
		'#title' => t('ACN/ABN'),
		'#default_value' =>$lendingform->ACN_ABN,
		'#weight' => $weight++,
		/*#required' => true,*/
	  );
  
  }
  
  $form['website'] = array(
    '#type' => 'textfield',
    '#title' => t('Website'),
	//'#rules' => array('url[absolute]'),
	'#weight' => $weight++,
    '#default_value' =>$lendingform->website,
          '#attributes' => array('placeholder' => 'http://www.domain.com/'),
  );
  
  $form['business_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Street'),
	'#required' => true,
	'#weight' => $weight++,
	'#prefix' => '<div class="form-item business_address"><div class="title"><h4>Business Address please fill in all fields</h4></div><div class="form-item-enquiry">',
    '#default_value' => $lendingform->business_address,
         '#attributes' => array('placeholder' => 'Street Name'),
  );
  
   $form['suburb'] = array(
    '#type' => 'textfield',
    '#title' => t('Suburb'),
	'#required' => true,
	'#weight' => $weight++,
    '#default_value' => $lendingform->suburb,
        '#attributes' => array('placeholder' => 'Suburb'),
  );
  
  $form['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
	'#required' => true,
	'#weight' => $weight++,
	'#prefix' => '<div class="form-item form-type-textfield form-item-state-content">',
    '#default_value' => $lendingform->state,
       '#attributes' => array('placeholder' => 'State'),
  );
  
  $form['postcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Postcode'),
	'#required' => true,
	/*'#options' => $options_postcode,*/
	'#weight' => $weight++,
	'#suffix' => '</div></div></div>',
    '#default_value' => $lendingform->postcode,
       '#attributes' => array('placeholder' => 'PostCode'),
  );
  
  $form['trading_time'] = array(
 	'#title' => t('How long you have been trading?'),
  	'#type' => 'select',
	'#required' => true,
	'#weight' => $weight++,
  	'#options' => array(t('Start-up'), t('1-2 Years'), t('3-5 Years'), t('5+ Years')),
	'#default_value' => $lendingform->trading_time,
	
 );
 
 $form['annual_turnover'] = array(
    '#type' => 'textfield',
    '#title' => t('Annual Turnover - best guess is fine'),
	'#required' => true,
	'#weight' => $weight++,
    '#default_value' => $lendingform->annual_turnover,
      '#attributes' => array('placeholder' => 'Annual Turnover - best guess is fine'),
  );
  
  if(($userrole == 'administrator') || ($userrole == 'cashflow') || ($userrole == 'automotive') || ($userrole == 'equipment') || ($userrole == 'commercial')) {
  
 $form['accounting_system'] = array(
    '#type' => 'select',
    '#title' => t('What Accounting System is used?'),
	'#options' => array(t('Xero'), t('MYOB'), t('Quicken'), t('Unsure')),
    '#default_value' => $lendingform->accounting_system,
	'#weight' => $weight++,
	/*'#required' => true,*/
  );
  
  $form['last_finincial_report'] = array(
    '#type' => 'checkbox',
    '#title' => t('Last Years Financial Reports available?'),
	'#options' => array(0 => 'No', 1 => 'Yes'),
    '#default_value' =>$lendingform->last_finincial_report,
	'#weight' => $weight++,
	/*'#required' => true,*/
  );
  
  $form['tax_portal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Tax Portal Report available?'),
	/*'#options' => array(0 => 'No', 1 => 'Yes'),*/
    '#default_value' =>$lendingform->tax_portal,
	'#weight' => $weight++,
	/*'#required' => true,*/
  ); 

  $form['bas_agent'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of BAS Agent?'),
    '#default_value' =>$lendingform->bas_agent,
	'#weight' => $weight++,
	/*'#required' => true,*/
  );
  
  $form['current_aged_receivables'] = array(
    '#type' => 'checkbox',
    '#title' => t('Current Aged Receivables Report?'),
	/*'#options' => array(0 => 'No', 1 => 'Yes'),*/
    '#default_value' =>$lendingform->current_aged_receivables,
	'#weight' => $weight++,
	/*'#required' => true,*/
  ); 
  
   $form['current_aged_creditors'] = array(
    '#type' => 'checkbox',
    '#title' => t('Current Aged Creditors Report?'),
	/*'#options' => array(0 => 'No', 1 => 'Yes'),*/
    '#default_value' =>$lendingform->current_aged_creditors,
	'#weight' => $weight++,
	/*'#required' => true,*/
  ); 
  
  $form['latest_management_accoutnts'] = array(
    '#type' => 'checkbox',
    '#title' => t('Latest Management Accounts?'),
	/*'#options' => array(0 => 'No', 1 => 'Yes'),*/
    '#default_value' => $lendingform->latest_management_accoutnts,
	'#weight' => $weight++,
	/*'#required' => true,*/
  ); 

  }
   
  
 $form['current_industry'] = array(
    '#type' => 'textfield',
    '#title' => t('Current Industry'),
	'#weight' => $weight++,
	'#required' => true,
    '#default_value' => $lendingform->current_industry,
       '#attributes' => array('placeholder' => 'Current Industry'),
  ); 
  
  if(($userrole == "anonymous user") || ($userrole == "client")){
   $form['credit_history'] = array(
 	'#title' => t('Credit History'),
  	'#type' => 'select',
  	'#required' => true,
	'#weight' => $weight++,
	'#suffix' => '<div id="edit-actions" class="form-actions form-wrapper"><button id="slider-next" class="button color right">Next</button></div></div></div><span class="rsTmb">Step 1</span></div>',
  	'#options' => array(t('Great'), t('Some Defaults'), t('Previous Bankrupt'), t('Current Bankrupt'), t('Unsure')),
	'#default_value' => $lendingform->credit_history,
 );
  } else {
	$form['credit_history'] = array(
 	'#title' => t('Credit History'),
  	'#type' => 'select',
  	'#required' => true,
	'#weight' => $weight++,
  	'#options' => array(t('Great'), t('Some Defaults'), t('Previous Bankrupt'), t('Current Bankrupt'), t('Unsure')),
	'#default_value' => $lendingform->credit_history,
 );
   
   }
 
 if(($userrole == 'administrator') || ($userrole == 'cashflow') || ($userrole == 'automotive') || ($userrole == 'equipment') || ($userrole == 'commercial')) {
 
  $form['loan_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Loan Title'),
	/*'#required' => true,*/
	'#weight' => $weight++,
    '#default_value' => $lendingform->loan_title,
	
  ); 
  
  $form['loan_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Loan Description'),
	'#weight' => $weight++,
	'#suffix' => '<div id="edit-actions" class="form-actions form-wrapper"><button id="slider-next" class="button color right">Next</button></div></div></div><span class="rsTmb">Step 1</span></div>',
    '#default_value' => $lendingform->loan_description,
	
  ); 
 
 }
 
 $form['funding_type'] = array(
    '#type' => 'select',
    '#title' => t('Funding Type'),
	'#options' => array(t('Cashflow'), t('Equipment'), t('Automotive'), t('Commercial')),
    '#required' => TRUE,
	'#weight' => $weight++,
	'#prefix' => '<div><div class="form-enquiry form-step2 clearfix"><div class="title"><h3>Step 2. What sort of funding are you looking for?</h3></div><div class="form-item-enquiry">',
    '#default_value' => $lendingform->funding_type,

  );
  
  if(($userrole == 'administrator') || ($userrole == 'cashflow') || ($userrole == 'automotive') || ($userrole == 'equipment') || ($userrole == 'commercial')) {
  
  $form['sort_of_cashflow'] = array(
    '#type' => 'select',
    '#title' => t('Sort of Cashflow Finance?'),
	'#options' => array(t('Short-term'), t('Long-term'), t('Unsure')),
   /* '#required' => TRUE,*/
	'#weight' => $weight++,
    '#default_value' => $lendingform->funding_type,

  );
  
  $form['sort_of_equipment'] = array(
    '#type' => 'select',
    '#title' => t('Sort of Equipment Finance?'),
	'#options' => array(t('Small Ticket'), t('Medium Ticket'), t('Large Ticket'), t('Residual'), t('Vendor'), t('Unsure')),
    /*'#required' => TRUE,*/
	'#weight' => $weight++,
    '#default_value' => $lendingform->sort_of_equipment,

  );
  
  $form['sort_of_automative'] = array(
    '#type' => 'select',
    '#title' => t('Sort of Automotive Finance?'),
	'#options' => array(t('Business'), t('Personal'), t('Unsure')),
    /*'#required' => TRUE,*/
	'#weight' => $weight++,
    '#default_value' => $lendingform->sort_of_automative,

  );
  
  $form['type_of_vechile'] = array(
    '#type' => 'select',
    '#title' => t('Type of Vehicle'),
	'#options' => array(t('New'), t('Used'), t('Unsure')),
    /*'#required' => TRUE,*/
	'#weight' => $weight++,
    '#default_value' => $lendingform->type_of_vechile,

  );
  
  $form['make'] = array(
    '#type' => 'textfield',
    '#title' => t('Make'),
    /*'#required' => TRUE,*/
	'#weight' => $weight++,
    '#default_value' =>  $lendingform->make,

  );
  
  $form['model'] = array(
    '#type' => 'textfield',
    '#title' => t('Model'),
    /*'#required' => TRUE,*/
	'#weight' => $weight++,
    '#default_value' => $lendingform->model,

  );
  
  $form['sort_of_commercial'] = array(
    '#type' => 'select',
    '#title' => t('Sort of Commercial Finance?'),
	'#options' => array(t('Business'), t('Personal'), t('Unsure')),
    /*'#required' => TRUE,*/
	'#weight' => $weight++,
    '#default_value' => $lendingform->sort_of_commercial,

  );
  
  $form['security_offered'] = array(
    '#type' => 'select',
    '#title' => t('Security Offered'),
	'#options' => array(t('First Mortgage'), t('Second Mortgage'), t('Other')),
    /*'#required' => TRUE,*/
	'#weight' => $weight++,
    '#default_value' => $lendingform->security_offered,

  );
  }
  
   $form['funding_need_amount'] = array(
    '#type' => 'textfield',
    '#title' => t('How much funding do you need?'),
	'#rules' => array('numeric'),
	'#required' => true,
	'#weight' => $weight++,
    '#default_value' => $lendingform->fund_amount,
//        '#attributes' => array('placeholder' => 'How much funding do you need?'),
	
  ); 
  
  $form['need_of_funding'] = array(
    '#type' => 'textarea',
    '#title' => t('Briefly tell us why you need funding?'),
	'#weight' => $weight++,
    '#default_value' => $lendingform->need_of_funding,
      '#attributes' => array('placeholder' => 'Briefly tell us why you need funding?'),
	
  ); 
  
  $form['referral_promo_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Partner/ Promo Code'),
	'#weight' => $weight++,
	'#suffix' => '<div id="edit-actions" class="form-actions form-wrapper"><button id="slider-next1" class="button color right">Next</button></div></div></div><span class="rsTmb">Step 2</span></div>',
    '#default_value' => $lendingform->promo_code,
        '#attributes' => array('placeholder' => 'Partner/ Promo Code'),
	
  ); 
  
    $form['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t("First Name"),
	'#required' => true,
	'#weight' => $weight++,
	'#prefix' => '<div><div class="form-enquiry form-step3 clearfix"><div class="title"><h3>Step 3. How can we contact you?</h3></div><div class="form-item-enquiry">',
    '#default_value' => $lendingform->first_name,
        '#attributes' => array('placeholder' => 'First Name'),
  );
  
   $form['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t("Last Name"),
	'#required' => true,
	'#weight' => $weight++,
    '#default_value' => $lendingform->last_name,
  '#attributes' => array('placeholder' => 'Last Name'),
       );
  
  $form['your_role'] = array(
    '#type' => 'textfield',
    '#title' => t("What is your position?"),
	'#required' => true,
	'#weight' => $weight++,
    '#default_value' => $lendingform->position,
      '#attributes' => array('placeholder' => 'Position'),
  );
  
  $form['best_contact_phone'] = array(
    '#type' => 'textfield',
    '#title' => t("Best Contact Phone?"),
	//'#rules' => array("numeric", 'length[10]'),
	'#required' => true,
	'#weight' => $weight++,
    '#default_value' => $lendingform->phone,
       '#attributes' => array('placeholder' => 'Only 10 digit numbers allowed.'),
  );
    
    
  
  if(($userrole == "anonymous user") || ($userrole == "client")){
  $form['best_email'] = array(
    '#type' => 'textfield',
    '#title' => t("Best Email?"),
	'#rules' => array('email'),
	'#required' => true,
	'#suffix' => '',
	'#weight' => $weight++,
    '#default_value' => $lendingform->email,
      '#attributes' => array('placeholder' => 'example@example.com'),
  ); 
  } else {
  $form['best_email'] = array(
    '#type' => 'textfield',
    '#title' => t("Best Email?"),
	'#rules' => array('email'),
	'#required' => true,
	'#weight' => $weight++,
    '#default_value' => $lendingform->email,
        '#attributes' => array('placeholder' => 'example@example.com'),
  ); 
  
  }
  
  if(($userrole == 'administrator') || ($userrole == 'cashflow') || ($userrole == 'automotive') || ($userrole == 'equipment') || ($userrole == 'commercial')) {
  
 $form['first_contact_date'] = array(
  '#type' => 'date_popup', 
  '#title' => "First Contact Date",
  '#weight' => $weight++,
  '#date_format' => 'Y-m-d h:i A',
  '#prefix' => '<div class="form-item form-item-date">',
  '#default_value' => $lendingform->first_contact_date,
);

$form['second_contact_date'] = array(
  '#type' => 'date_popup', 
  '#title' => "Second Contact Date",
  '#weight' => $weight++,
  '#date_format' => 'Y-m-d h:i A',
  '#default_value' => $lendingform->second_contact_date,
);

$form['third_contact_date'] = array(
  '#type' => 'date_popup', 
  '#title' => "Third Contact Date",
  '#weight' => $weight++,
  '#date_format' => 'Y-m-d h:i A',
  '#suffix' => '</div>',
  '#default_value' => $lendingform->third_contact_date,
);

$form['notes'] = array(
    '#type' => 'textfield',
    '#title' => t("Notes"),
	'#weight' => $weight++,
    '#default_value' => $lendingform->notes,
  );
  
 $form['lending_post_contact_email'] = array(
    '#type' => 'textfield',
    '#title' => t("Lending Post Contact Email"),
	/*'#required' => true,*/
	'#weight' => $weight++,
    '#default_value' => $lendingform->lending_post_contact_email,
  );
  
  $form['credit_risk'] = array(
    '#type' => 'textfield',
    '#title' => t("Credit Risk"),
	'#weight' => $weight++,
    '#default_value' => $lendingform->credit_risk,
  );
  
   $form['workflow_status'] = array(
    '#type' => 'select',
    '#title' => t("Workflow Status"),
	
	'#options' => array(t('Open'), t('Application In Progress'), t('Funded'), t('Closed')),
	'#weight' => $weight++,
    '#default_value' => $lendingform->workflow_status,
  );
  
  }
  
 
  // Attach fields from Field module.
  field_attach_form('lendingform', $lendingform, $form, $form_state);
 
 
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      '#weight' => $weight++,
	  '#suffix' => '</div></div><span class="rsTmb">Step 3</span></div></div>',
      '#submit' => array('lendingform_form_submit'),
  );

  $form_state['lendingform'] = $lendingform;
  
  $form['#validate'][] = 'lendingform_form_validate';
  	
  return $form;
  
  
}


/**
  ajax handlerfor lendingform create/edit form
 */
function lendingform_submit_ajax_callback($form, &$form_state) {   
  
  if (!form_get_errors()) {
    global $base_url;
    $lendingform = $form_state['lendingform'];
    $gid = $lendingform->gid;
    
    $redirect_url = $base_url."/lendingform/".$pid;
//    $redirect_url = lendingform_view9_get_urlname($pid);
    $commands = array();
    $commands[] = ajax_command_invoke(NULL, "lendingformRedirect", array($redirect_url));   
    return array('#type' => 'ajax', '#commands' => $commands);
  } else {
    $error = form_get_errors();
    $commands = array();
    if (isset($error['title'])) {
      $commands[] = ajax_command_invoke('#edit-title', addClass, array('error'));
    }
    
    form_clear_error();
    unset($_SESSION['messages']['error']);

    //$commands[] = ajax_command_invoke('#mrd_1', 'click');
    return array('#type' => 'ajax', '#commands' => $commands);
  }
}

/**
 * Validate: lendingform_form
 */
function lendingform_form_validate($form, &$form_state) {
  $enquiry = $form_state['lendingform'];
/*
  // Validate textfield for the maximum length of 255
  $length = strlen($form_state['values']['title']);

  if ($length > 255) {
    form_set_error('title', t('Maximum length of title is 255 characters.'));
  }
  
  // Field validation.
  field_attach_form_validate('lendingform', $lendingform, $form, $form_state);*/
}

/**
 * Submit: lendingform_form
 */
function lendingform_form_submit($form, &$form_state) {
  global $user;
  global $base_url;
  foreach($user->roles as $role){
     $userrole = $role;
  }
  $input = $form_state['input'];

  $enquiry = (object) $form_state['lendingform'];
  
  if(isset($_SESSION['customeuid'])) 
  $enquiry->user_id = $_SESSION['customeuid'];
 
  $enquiry->company_name = $form_state['values']['company_name'];
  if(($userrole == 'administrator') || ($userrole == 'cashflow') || ($userrole == 'automotive') || ($userrole == 'equipment') || ($userrole == 'commercial')) {
  	$enquiry->ACN_ABN = $form_state['values']['acn_abn'];
  }
  $enquiry->website = $form_state['values']['website'];
  $enquiry->business_address = $form_state['values']['business_address'];
  $enquiry->suburb = $form_state['values']['suburb'];
  $enquiry->state = $form_state['values']['state'];
  $enquiry->postcode = $form_state['values']['postcode'];
  $enquiry->trading_time = $form_state['values']['trading_time'];
  $enquiry->annual_turnover = $form_state['values']['annual_turnover'];
  if(($userrole == 'administrator') || ($userrole == 'cashflow') || ($userrole == 'automotive') || ($userrole == 'equipment') || ($userrole == 'commercial')) {
  $enquiry->accounting_system = $form_state['values']['accounting_system'];
  $enquiry->last_finincial_report = $form_state['values']['last_finincial_report'];
  $enquiry->tax_portal = $form_state['values']['tax_portal'];
  $enquiry->bas_agent = $form_state['values']['bas_agent'];
  
  $enquiry->current_aged_receivables = $form_state['values']['current_aged_receivables'];
  $enquiry->current_aged_creditors = $form_state['values']['current_aged_creditors'];
  $enquiry->latest_management_accoutnts = $form_state['values']['latest_management_accoutnts'];
  }
  $enquiry->current_industry = $form_state['values']['current_industry'];
  
  $enquiry->credit_history = $form_state['values']['credit_history'];
  
  if(($userrole == 'administrator') || ($userrole == 'cashflow') || ($userrole == 'automotive') || ($userrole == 'equipment') || ($userrole == 'commercial')) {
  $enquiry->loan_title = $form_state['values']['loan_title'];
  $enquiry->loan_description = $form_state['values']['loan_description'];
  }
  
  $enquiry->funding_type = $form_state['values']['funding_type'];
  
  if(($userrole == 'administrator') || ($userrole == 'cashflow') || ($userrole == 'automotive') || ($userrole == 'equipment') || ($userrole == 'commercial')) {
  $enquiry->sort_of_cashflow = $form_state['values']['sort_of_cashflow'];
  $enquiry->sort_of_equipment = $form_state['values']['sort_of_equipment'];
  $enquiry->sort_of_automative = $form_state['values']['sort_of_automative'];
  $enquiry->type_of_vechile = $form_state['values']['type_of_vechile'];
  
  $enquiry->make = $form_state['values']['make'];
  $enquiry->model = $form_state['values']['model'];
  $enquiry->sort_of_commercial = $form_state['values']['sort_of_commercial'];
  $enquiry->security_offered = $form_state['values']['security_offered'];
  }
  $enquiry->fund_amount = $form_state['values']['funding_need_amount'];
  $enquiry->need_of_funding = $form_state['values']['need_of_funding'];
  /*print_r($enquiry->need_of_funding); exit;*/
  $enquiry->promo_code = $form_state['values']['referral_promo_code'];
  $enquiry->first_name = $form_state['values']['first_name'];
  
  $enquiry->last_name = $form_state['values']['last_name'];
  $enquiry->position = $form_state['values']['your_role'];
  $enquiry->phone = $form_state['values']['best_contact_phone'];
  $enquiry->email = $form_state['values']['best_email'];
  if(($userrole == 'administrator') || ($userrole == 'cashflow') || ($userrole == 'automotive') || ($userrole == 'equipment') || ($userrole == 'commercial')) {
  $enquiry->first_contact_date = $form_state['values']['first_contact_date'];
  $enquiry->second_contact_date = $form_state['values']['second_contact_date'];
  $enquiry->third_contact_date = $form_state['values']['third_contact_date'];
  $enquiry->notes = $form_state['values']['notes'];
  $enquiry->lending_post_contact_email = $form_state['values']['lending_post_contact_email'];
  $enquiry->workflow_status = $form_state['values']['workflow_status'];
  $enquiry->credit_risk = $form_state['values']['credit_risk'];
  }
  
  $idforemail = $enquiry->eid;
  
  
  /*echo "<pre>"; 
  print_r($enquiry);
  exit;*/

  // Notify field widgets.
  
  field_attach_submit('lendingform', $enquiry, $form, $form_state);

	if($form_state['values']['credit_history'] == 3){
		drupal_goto("loan/enquiry/thanks");
		exit;
	}	
	
  // Save the lendingform.
  $enq = lendingform_save($enquiry);
  
   $query = db_select('users', 'u')->fields('u', array('uid', 'name', 'mail'));
  if($form_state['values']['funding_type'] == 0){
	 $query->condition('ur.rid', array(6,3), 'IN');	  
		  
  } elseif($form_state['values']['funding_type'] == 1){
	 $query->condition('ur.rid', array(7,3), 'IN'); 
	  
  } elseif($form_state['values']['funding_type'] == 2){
	 $query->condition('ur.rid', array(8,3), 'IN'); 
	  
  } elseif($form_state['values']['funding_type'] == 3){
	 $query->condition('ur.rid', array(9,3), 'IN'); 
  }
  	$query->groupBy('u.uid');
    $query->innerJoin('users_roles', 'ur', 'u.uid = ur.uid');
    $results = $query->execute()->fetchAll();
		foreach($results as $res){
		$emailto = $res->mail; 
		/*$emailto = "binod@view9.com.np";*/
		 if (!empty($idforemail)) {
		$sMessageContent = "<html><head></head><body>Enquiry[#".$enq->eid."] has been updated by ".$user->name;
		 } else {
			$sMessageContent = "<html><head></head><body>Enquiry[#".$enq->eid."] has been updated by ".$user->name;	 
		}
		$sMessageContent .= "<hr /><html><head></head><body><h1><a href='".$base_url."/admin/structure/enquiry/".$enq->eid."/edit?destination=admin/structure/enquiry' target = '_blank'>".$form_state['values']['company_name']."-".$form_state['values']['loan_title']."</a></h1>";
       $sMessageContent .= "<ul><li>Name :".$form_state['values']['first_name']." ".$form_state['values']['last_name']."</li><li>Email ". $form_state['values']['best_email'] ."</li><li>Loan amount : $". number_format($form_state['values']['funding_need_amount'], 2) ."</li><li>Phone :". $form_state['values']['best_contact_phone'] ."</li><li>Loan Description :". $form_state['values']['loan_description'] ."</li></ul><hr />";
	   
	   $sMessageContent .= "You have receive this notification becasue you are involved in lendingpost.<br/> For fruther more information please click ".l($base_url."/user", $base_url."/user", array('attributes' => array('target' => array('_blank'))))."";
	   
	   $sMessageContent .= "</body></html>";
	  
		  if (!empty($idforemail)) {
		  $title = "Enquiry[#".$enq->eid."] has been updated by ".$user->eid;
		  _custom_simple_mail($title, $sMessageContent, $emailto);	
		  
		  } else{
			  
			  $title = "Enquiry[#".$idforemail."] has been posted by ".$user->eid;
			   _custom_simple_mail($title, $sMessageContent, $emailto);	  
		 
		  } 
	
	}
 
  // Notify the user.
  drupal_set_message(t('Enquiry Saved.'));
  /*drupal_flush_all_caches();*/
  if(cache_clear_all('lendingform', 'cache', TRUE)){
	  echo "Cache clear success";  exit; 
	} else {
		echo "Unsuccess"; exit;
		}

  
  if(($userrole == "anonymous user") || ($userrole == "client")){
     $form_state['redirect'] = 'loan/enquiry/success/';
   } else {
     $form_state['redirect'] = 'admin/structure/enquiry/';
   }
}

/**
 * Remove/handle form validation errors
 * : not our concern right now
 */
function lendingform_handle_errors() {
  if (form_get_errors()) {
    $error = form_get_errors();
    form_clear_error();
    unset($_SESSION['messages']['error']);
  }
}


function postcode_dropdown_options(){
   	$query =  db_select('postcode_db', 'p');
	$query -> fields('p', array('postcode'));
	$query -> distinct();
	$result = $query->execute()->fetchAll();
	
	$first_element = array('' => '');
	foreach($result as $res){
	    $first_element[$res->postcode] = $res->postcode;
	}
	return $first_element;		
	}

/**
 * Modal Form: confirmation action
 */
function view9_lendingform_delete_confirm($form, &$form_state, $gallery) {
    if (isset($form_state['gallery'])) {
      $gallery = $form_state['gallery'];
    }
    $form['#gallery'] = $gallery;
    // Always provide entity id in the same form key as in the entity edit form.
    $form['pid'] = array('#type' => 'value', '#value' => $gallery->pid);
    return confirm_form($form, t('Are you sure you want to delete this lendingform?'), 'gallerys', t('This action cannot be undone.'), t('Delete'), t('Cancel')
    );
}

/**
 * Modal Form Submit: Delete data are submitted here and deleted
 */
function view9_lendingform_delete_confirm_submit($form, &$form_state) {
    if ($form_state['values']['confirm']) {
        $gallery = lendingform_load($form_state['values']['pid']);
        lendingform_delete($form_state['values']['pid']);
        watchdog(PROJECT_ENTITY, t("Project $gallery->pid was deleted"));
        $form_state['redirect'] = 'gallery/' . $gallery->pid;
    } else {
        $form_state['redirect'] = 'gallerys';
    }
}




/**
 * Modal Form: confirmation action
 */
function view9_lendingform_create_ajax_confirm($form, &$form_state, $gallery) {
    if (isset($form_state['gallery'])) {
      $gallery = $form_state['gallery'];
    }
    $form['#gallery'] = $gallery;
    $form['pid'] = array('#type' => 'value', '#value' => $gallery->pid);
    return confirm_form($form, t('Are you sure you want to create this lendingform?'), 'gallerys', t('Are you sure you want to create this lendingform?'), t('Ok'), t('Cancel')
    );
}

/**
 * Modal Form Submit: Delete data are submitted here and deleted
 */
function view9_lendingform_create_ajax_confirm_submit($form, &$form_state) {
    if ($form_state['values']['confirm']) {
        $gallery = lendingform_load($form_state['values']['gid']);
        //gallery_delete($form_state['values']['pid']);
        watchdog(PROJECT_ENTITY, t("$gallery->pid was created"));
        $form_state['redirect'] = '';
    } else {
        $form_state['redirect'] = 'gallerys';
    }
}