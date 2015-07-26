<?php global $user; 
foreach($user->roles as $role){
     $userrole = $role;
  }
?>

 <?php $path = current_path();
?>
<?php
function _wefrpe_ajax_save_pager_team($url) {
    /* THANK YOU DRUPAL! => Known problem with pagers in AJAX Loaded elements */
    $q_backup = $_GET['q'];
    $_GET['q'] = $url;
    echo theme('pager', array('tags' => array('', 'Prev', NULL, 'Next', '')));
    $_GET['q'] = $q_backup;
} ?>  
<table class="standard-table green">
	
    
    <tr><th><strong>Type</strong></th><th><strong>Loan Description</strong></th><th><strong>Location</strong></th><th><strong>Amount</strong></th><th><strong>Status</strong></th></tr>
<?php foreach($vars as $var) {
	 	$enquiry = lendingform_load($var->eid);
	  ?>
      
      
	    <tr  <?php if($enquiry->workflow_status == "2"){ echo "class='funded'"; } ?> ><td class="imgContainer"><?php  
		if($enquiry->funding_type == "0"){
		 	$node = node_load(11);
			echo "Cashflow";
		}
		if($enquiry->funding_type == "1"){
			$node = node_load(10);
			echo "Equipment";
		}
		if($enquiry->funding_type == "2"){
			$node = node_load(9);
			echo "Automotive";
		}
		if($enquiry->funding_type == "3"){
			$node = node_load(8);
			echo "Commercial";
		}
		
		$files = field_get_items('node', $node, 'field_icon_image');
 	    if (!empty($files)) {
               foreach ($files as $keys => $value):
                                
                   $imageOutput = field_view_value('node', $node, 'field_icon_image', $files[$keys], array(
                                    'type' => 'image',
                                    'settings' => array(
                                        'image_style' => 'loanboard_icon', 
                                       /* 'image_link' => 'content',*/
                                    ),

                                ));
                            endforeach;
         print render($imageOutput);
					    }
		
		  ?></td><td>
          
<span style="text-decoration:underline;"><?php echo l($enquiry->eid." ".$enquiry->loan_title, "enquiry/".$enquiry->eid );  ?></span><br />

<?php 
$desc = $enquiry->loan_description;
  if ((strlen($desc)) > 500) {
     $description =  substr(strip_tags(render($desc)), 0, 500) . ".....";
      print $description;
  }else{
      print $desc;
  }
 ?></td><td><?php echo $enquiry->postcode;  ?></td><td>$<?php echo number_format($enquiry->fund_amount, 2);  ?></td><td><?php  
		if($enquiry->workflow_status == "0")
		echo "Open";
		if($enquiry->workflow_status == "1")
		echo "Application In Progress";
		if($enquiry->workflow_status == "2")
		echo "Funded";
		if($enquiry->workflow_status == "3")
		echo "Closed";
		
		
		  ?></td></tr>	
<?php	} ?>
</table>
 <?php
_wefrpe_ajax_save_pager_team($path);
?>
<br /><br />

<?php  if($userrole == "anonymous user"){ ?>
<p>To view more information please <?php echo l("login/signup", "user"); ?></p>
<?php } ?>