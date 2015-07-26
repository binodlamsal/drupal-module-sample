<?php global $user, $base_url;
 foreach($user->roles as $role){
     $userrole = $role;
  }

 ?>
<div class="eleven columns omega">
<?php //echo l("Share Email", "share/".arg(1) );  ?>
<ul class="tabs-nav"><li class="active"><a href="#tab1">Summary Information</a></li>
<li class=""><a href="#tab2">Detailed Information</a></li>
</ul>
<div class="tabs-container">
<div id="tab1" class="tab-content" style="display: block;">
<table class="standard-table unique">
    
<tr><th><?php print t('Loan Id');?></th><th><?php  print t('Loan Description');  ?></th></tr>
<tr><td><?php echo $vars->eid;  ?></td><td><?php echo $vars->loan_title;  ?></td></tr>
<tr><td>Finance Amount</td><td>$<?php echo $vars->fund_amount;  ?></td></tr>
<tr><td>Status</td><td><?php  
		if($vars->workflow_status == "0")
		echo "Open";
		if($vars->workflow_status == "1")
		echo "Application In Progress";
		if($vars->workflow_status == "2")
		echo "Funded";
		if($vars->workflow_status == "3")
		echo "Closed";
		
		
		  ?></td></tr>

<tr><td>Finance Type</td><td><?php  
		if($vars->funding_type == "0")
		echo "Cashflow";
		if($vars->funding_type == "1")
		echo "Equipment";
		if($vars->funding_type == "2")
		echo "Automotive";
		if($vars->funding_type == "3")
		echo "Commercial";
		
		
		  ?></td></tr>
<tr><td>Finance Sort</td><td>

<?php if($vars->funding_type == "0"){
	   
	   if($vars->sort_of_cashflow == "0"){
		   echo "Short-term";	   
	   } else if($vars->sort_of_cashflow == "1"){
	   	   echo "Long-term";	
	   } else if($vars->sort_of_cashflow == "2"){
	   	   echo "Unsure";	
	   }
	} elseif($vars->funding_type == "1"){
	   
	   if($vars->sort_of_equipment == "0"){
		   echo "Small Ticket";	   
	   } else if($vars->sort_of_equipment == "1"){
	   	   echo "Medium Ticket";	
	   } else if($vars->sort_of_equipment == "2"){
	   	   echo "Large Ticket";	
	   } else if($vars->sort_of_equipment == "4"){
	   	   echo "Residual";	
	   } else if($vars->sort_of_equipment == "5"){
	   	   echo "Vendor";	
	   } else if($vars->sort_of_equipment == "6"){
	   	   echo "Unsure";	
	   } 
	} elseif($vars->funding_type == "2"){
	   
	   if($vars->sort_of_automative == "0"){
		   echo "Business";	   
	   } else if($vars->sort_of_automative == "1"){
	   	   echo "Personal";	
	   } else if($vars->sort_of_automative == "3"){
	   	   echo "Unsure";	
	   }
	}
	elseif($vars->funding_type == "3"){
	   
	   if($vars->sort_of_commercial == "0"){
		   echo "Business";	   
	   } else if($vars->sort_of_commercial == "1"){
	   	   echo "Personal";	
	   } else if($vars->sort_of_commercial == "3"){
	   	   echo "Unsure";	
	   }
	}
	
	
	?>

</td></tr>


<tr><td>Current Industry</td><td><?php echo $vars->current_industry;  ?></td></tr>
<tr><td>Description</td><td><?php echo $vars->loan_description;  ?></td></tr>
<tr><td>Postcode/State</td><td><?php echo $vars->postcode;  ?>, <?php echo $vars->state;  ?></td></tr>
<tr><td>How long you have been trading</td><td>
<?php if($vars->trading_time == 0) 
      echo "Start-up";
	  elseif($vars->trading_time == 1) 
	  echo "1-2 Years";	
	  elseif($vars->trading_time == 2) 
	  echo "3-5 Years";	
	  elseif($vars->trading_time == 3) 
	  echo "5+ Years";	

?></td></tr>

<!--<tr><td>Credit History</td><td><?php /*if($vars->credit_history == "0")
		echo "Great";
		if($vars->credit_history == "1")
		echo "Some Defaults";
		if($vars->credit_history == "2")
		echo "Previous Bankrupt";
		if($vars->credit_history == "3")
		echo "Current Bankrupt";
		if($vars->credit_history == "3")
		echo "Unsure";*/
		
		
		  ?></td></tr>
<tr><td>Last year financial reports avaliable?</td><td>
<?php /*if($vars->last_finincial_report == "0")
	   	echo "YES";
	  else {
	  	echo "NO";
	  }*/
?>
</td></tr>
<tr><td>Tax portal report avaliable?</td><td>
<?php /*if($vars->tax_portal == "0")
	   	echo "YES";
	  else {
	  	echo "NO";
	  }*/
?></td></tr>
<tr><td>Current Receivables Report avaliable?</td><td><?php /*if($vars->current_aged_receivables == "0")
	   	echo "YES";
	  else {
	  	echo "NO";
	  }*/
?></td></tr>
<tr><td>Current Creditors Report avaliable</td><td><?php /*if($vars->current_aged_creditors == "0")
	   	echo "YES";
	  else {
	  	echo "NO";
	  }*/
?></td></tr>
<tr><td>Latest Management Accounts</td><td><?php /* if($vars->latest_management_accoutnts == "0")
	   	echo "YES";
	  else {
	  	echo "NO";
	  }*/
?></td></tr>
<tr><td>Annual Turnover</td><td><?php //echo $vars->annual_turnover;  ?></td></tr>-->
<tr><td>Lending Post Contact Email<br>
<span style="font-size:13px;"><em>
"For more email please contact us by valid email or call directly on 1800 LEND POST"</em></span></td><td> <a href="mailto:sushil.jakibanja@gmail.com">cashflow@lendingpost.com.au</a></td></tr>

</table>

</div>
<div id="tab2" class="tab-content" style="display: none;">
<?php if(($userrole == "anonymous user") || ($userrole == "client")){ ?> 

	This information is only visible to registered lenders.
    <p><span>Email us at <u><a href="mailto:lender@lendingpost.com.au">lender@lendingpost.com.au</a></u></span></p>
    
		
 <?php  }  else {

drupal_add_js(drupal_get_path('theme', 'lendingpost') . '/js/fancybox/jquery.fancybox.pack.js');
drupal_add_css(drupal_get_path('theme', 'lendingpost') . '/js/fancybox/jquery.fancybox.css');
   ?>



<table class="standard-table unique">
    
<tr><th><?php print t('Loan Id');?></th><th><?php  print t('Loan Description');  ?></th></tr>
<tr><td><?php echo $vars->eid;  ?></td><td><?php echo $vars->loan_title;  ?></td></tr>
<tr><td>Finance Amount</td><td>$<?php echo $vars->fund_amount;  ?></td></tr>
<tr><td>Status</td><td><?php  
		if($vars->workflow_status == "0")
		echo "Open";
		if($vars->workflow_status == "1")
		echo "Application In Progress";
		if($vars->workflow_status == "2")
		echo "Funded";
		if($vars->workflow_status == "3")
		echo "Closed";
		
		
		  ?></td></tr>

<tr><td>Finance Type</td><td><?php  
		if($vars->funding_type == "0")
		echo "Cashflow";
		if($vars->funding_type == "1")
		echo "Equipment";
		if($vars->funding_type == "2")
		echo "Automotive";
		if($vars->funding_type == "3")
		echo "Commercial";
		
		
		  ?></td></tr>
<tr><td>Finance Sort</td><td>

<?php if($vars->funding_type == "0"){
	   
	   if($vars->sort_of_cashflow == "0"){
		   echo "Short-term";	   
	   } else if($vars->sort_of_cashflow == "1"){
	   	   echo "Long-term";	
	   } else if($vars->sort_of_cashflow == "2"){
	   	   echo "Unsure";	
	   }
	} elseif($vars->funding_type == "1"){
	   
	   if($vars->sort_of_equipment == "0"){
		   echo "Small Ticket";	   
	   } else if($vars->sort_of_equipment == "1"){
	   	   echo "Medium Ticket";	
	   } else if($vars->sort_of_equipment == "2"){
	   	   echo "Large Ticket";	
	   } else if($vars->sort_of_equipment == "4"){
	   	   echo "Residual";	
	   } else if($vars->sort_of_equipment == "5"){
	   	   echo "Vendor";	
	   } else if($vars->sort_of_equipment == "6"){
	   	   echo "Unsure";	
	   } 
	} elseif($vars->funding_type == "2"){
	   
	   if($vars->sort_of_automative == "0"){
		   echo "Business";	   
	   } else if($vars->sort_of_automative == "1"){
	   	   echo "Personal";	
	   } else if($vars->sort_of_automative == "3"){
	   	   echo "Unsure";	
	   }
	}
	elseif($vars->funding_type == "3"){
	   
	   if($vars->sort_of_commercial == "0"){
		   echo "Business";	   
	   } else if($vars->sort_of_commercial == "1"){
	   	   echo "Personal";	
	   } else if($vars->sort_of_commercial == "3"){
	   	   echo "Unsure";	
	   }
	}
	
	
	?>

</td></tr>


<tr><td>Current Industry</td><td><?php echo $vars->current_industry;  ?></td></tr>
<tr><td>Description</td><td><?php echo $vars->loan_description;  ?></td></tr>
<tr><td>Postcode/State</td><td><?php echo $vars->postcode;  ?>, <?php echo $vars->state;  ?></td></tr>
<tr><td>How long you have been trading</td><td>
<?php if($vars->trading_time == 0) 
      echo "Start-up";
	  elseif($vars->trading_time == 1) 
	  echo "1-2 Years";	
	  elseif($vars->trading_time == 2) 
	  echo "3-5 Years";	
	  elseif($vars->trading_time == 3) 
	  echo "5+ Years";	

?></td></tr>
<tr><td>Annual Turnover</td><td><?php echo $vars->annual_turnover;  ?></td></tr>
<tr><td>Credit History</td><td><?php if($vars->credit_history == "0")
		echo "Great";
		if($vars->credit_history == "1")
		echo "Some Defaults";
		if($vars->credit_history == "2")
		echo "Previous Bankrupt";
		if($vars->credit_history == "3")
		echo "Current Bankrupt";
		if($vars->credit_history == "3")
		echo "Unsure";
		
		
		  ?></td></tr>
<tr><td>Last year financial reports avaliable?</td><td>
<?php if($vars->last_finincial_report == "0")
	   	echo "YES";
	  else {
	  	echo "NO";
	  }
?>
</td></tr>
<tr><td>Tax portal report avaliable?</td><td>
<?php if($vars->tax_portal == "0")
	   	echo "YES";
	  else {
	  	echo "NO";
	  }
?></td></tr>
<tr><td>Current Receivables Report avaliable?</td><td><?php if($vars->current_aged_receivables == "0")
	   	echo "YES";
	  else {
	  	echo "NO";
	  }
?></td></tr>
<tr><td>Current Creditors Report avaliable</td><td><?php if($vars->current_aged_creditors == "0")
	   	echo "YES";
	  else {
	  	echo "NO";
	  }
?></td></tr>
<tr><td>Latest Management Accounts</td><td><?php if($vars->latest_management_accoutnts == "0")
	   	echo "YES";
	  else {
	  	echo "NO";
	  }
?></td></tr>
<tr><td>Lending Post Contact Email<br>
<span style="font-size:13px;"><em>
"For more email please contact us by valid email or call directly on 1800 LEND POST"</em></span></td><td> <a href="mailto:sushil.jakibanja@gmail.com">cashflow@lendingpost.com.au</a></td></tr>

</table>
 
 <a data-fancybox-type="iframe" class="button color right" id="preview2" href="<?php echo $base_url; ?>/sharethis.php?id=<?php echo arg(1); ?>" id="preview2">Share Email</a>
 <?php //echo l("Share Email", "share/".arg(1),   array('attributes' => array('class' => array('button', ' color', 'right'))) );  ?> 
<?php } ?>
</div>

</div>
</div>
<script type="text/javascript">
jQuery("#preview2").click(function() {
	var myUrl = jQuery(this).attr('href');
      jQuery.fancybox({
    		 'width'        : '35%',
			 'height'       : '30%',
			 'autoScale'        : false, 
			 'type'         : 'iframe',
			 'overlayShow'   : false,
			 'transitionIn'  : 'elastic',
			 'transitionOut' : 'elastic',
              href       : myUrl
	
		});
         return false;
 }); 

  </script>