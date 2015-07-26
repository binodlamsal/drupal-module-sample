<div class="various-form-steps"> <?php //echo "<pre>"; print_r($vars);  ?>
<?php if(arg(2) == "success") { ?>
<div class="form-enquiry-success">
    <?php 
    
     $node = node_load(59);
  echo $node->body['und'][0]['value'];
    
    ?>
<!--<h3>Success!</h3>
<br />

Based on the information you have provided your funding 

enquiry is pre-qualified!<br /><br />



What happens next? One of our credit assessment team 

will be in contact within 24 hours to help complete your loan 

request.<br />
<br />


Once your loan request is completed it will be posted to our 

marketplace where matched lenders will compete for your 

business.<br /><br />



Remember, we do not share your contact information, 

lenders only contact us and there is no obligation to accept 

any loan offer.-->


</div>
<?php } elseif(arg(2) == "thanks") { ?>
<div class="form-enquiry-thanks">
    <?php 
    
     $node = node_load(60);
  echo $node->body['und'][0]['value'];
    
    ?>
<!--<h3>Thank you!</h3> <br />


Unfortunately, based on the information you have provided 

we are unable to pre-qualify your funding requirements 

automatically.<br /><br />



What happens next? One of our credit assessment team 

will be in contact within 24 hours to help complete your loan 

request.Once your loan request is completed it will be posted to our 

marketplace where matched lenders will compete for your 

business. Remember, we do not share your contact information, 

lenders only contact us and there is no obligation to accept 

any loan offer.-->

</div>
<?php } else { ?>


		   <?php   print drupal_render($vars['lendingform_create']);

  				   print drupal_render_children($vars);	?>
<?php } ?>
</div>