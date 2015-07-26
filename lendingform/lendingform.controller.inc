<?php

/**
 * @file
 * Provides a central controller for status entity.
 *
 */
class LendingformController extends DrupalDefaultEntityController {

	/**
	 * Create a default status.
	 *
	 * @return
	 *   A status object with all default fields initialized.
	 */
	public function create() {
		return (object) array(
								'eid' => '',
								'user_id' => '',
								'company_name' => '',
								'ACN_ABN' => '',
								'website' => '',
								'business_address' => '',
								'suburb' => '',
								'state' => '',
								'postcode' => '',
								'trading_time' => '',
								'annual_turnover' => '',
								'accounting_system' => '',
								'last_finincial_report' => '',
								'tax_portal' => '',
								'bas_agent' => '',
								'current_aged_receivables' => '',
								'current_aged_creditors' => '',
								'latest_management_accoutnts' => '',
								'current_industry' => '',
								'credit_history' => '',
								'loan_title' => '',
								'loan_description' => '',
								'funding_type' => '',
								'sort_of_cashflow' => '',
								'sort_of_equipment' => '',
								'sort_of_automative' => '',
								'type_of_vechile' => '',
								'make' => '',
								'model' => '',
								'sort_of_commercial' => '',
								'security_offered' => '',
								'fund_amount' => '',
								'need_of_funding' => '',
								'promo_code' => '',
								'first_name' => '',
								'last_name' => '',
								'position' => '',
								'phone' => '',
								'email' => '',
								'first_contact_date' => '',
								'second_contact_date' => '',
								'third_contact_date' => '',
								'email' => '',
								'notes' => '',
								'lending_post_contact_email' => '',
								'workflow_status' => '',
								'credit_risk' => '',	
								'created'=> '',
					            'changed'=> '',							
		);
	}

	/**
	 * Permanently saves the given entity.
	 *
	 * In case of failures, an exception is thrown.
	 *
	 * @param $lendingform
	 *   The entity to save.
	 *
	 * @return
	 *   SAVED_NEW or SAVED_UPDATED depending on the operation performed.
	 */
	public function save($enquiry) {
		
		$transaction = db_transaction();
		try {
			global $user;
			$enquiry->is_new = empty($enquiry->eid);
			// Setting the timestamp fields.
			if (empty($enquiry->created)) {
				$enquiry->created = REQUEST_TIME;
			}
			$enquiry->changed = REQUEST_TIME;
			$enquiry->revision_timestamp = REQUEST_TIME;
			$update_status = TRUE;
      
			// Giving modules the opportunity to prepare field data for saving.
			field_attach_presave(LENDINGFORM_ENTITY, $enquiry);
			if ($enquiry->is_new) {
				/*echo LENDINGFORM_ENTITY; exit;*/
				// Saving the new status.
				drupal_write_record(LENDINGFORM_ENTITY, $enquiry);
				$op = 'insert';
			} else {
				//exit;
				// Saving the updated status.
				drupal_write_record(LENDINGFORM_ENTITY, $enquiry, 'eid');
				$op = 'update';
			}
			// Saving fields.
			$function = 'field_attach_' . $op;
			$function(LENDINGFORM_ENTITY, $enquiry);
			module_invoke_all('entity_' . $op, $enquiry, 'lendingform');
			// Clearing internal gleperties.
			unset($enquiry->is_new);
			// Ignoring slave server temporarily to give time for the saved order to be glepagated to the slave.
			db_ignore_slave();
			return $enquiry;
		} catch (Exception $e) {
			$transaction->rollback();
			watchdog_exception(LENDINGFORM_ENTITY, $e, NULL, WATCHDOG_ERROR);
			return FALSE;
		}
	
		}

	/**
	 * Delete permanently saved entities.
	 *
	 * In case of failures, an exception is thrown.
	 *
	 * @param $gids
	 *   An array of entity IDs.
	 *
	 */
	public function delete($eids) {
		if (!empty($eids)) {
			$statuses = $this->load($eids, array());
			$transaction = db_transaction();
			try {
				db_delete('enquiry')
								->condition('eid', $eids, 'IN')
								->execute();
				foreach ($statuses as $status_id => $status) {
					field_attach_delete('enquiry', $status);
				}
				db_ignore_slave();
			} catch (Exception $e) {
				$transaction->rollback();
				watchdog_exception('enquiry', $e, NULL, WATCHDOG_ERROR);
				return FALSE;
			}
			module_invoke_all('lendingform_delete', $status, 'enquiry');
			// Clearing the page and block and status caches.
			cache_clear_all();
			$this->resetCache();
		}
		return TRUE;
	}

  
  
  /**
   * Get total number of lendingforms
   */
  public function lendingform_total_count() {
    $query = db_select(LENDINGFORM_BASE_TABLE, 'gle')
            ->fields('gle');
    // execute the query
    $result = $query->execute();
    
    return  $result->rowCount();
  }
     
    
      /**
   * Load all lendingforms
    * 
   * @param type $name
   */
  public function lendingform_load_all() {
    $query = db_select(LENDINGFORM_BASE_TABLE, 'gle')
            ->fields('gle');            
    $result = $query->execute();
    
    while ($row = $result->fetchAll()) {
      // return the result immediately
      return $row;
    }
    
    // no result
    return FALSE;
    
  }  
  
}

