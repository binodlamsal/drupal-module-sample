
	jQuery(document).ready(function($) {
  // Please note that autoHeight option has some conflicts with options like imageScaleMode, imageAlignCenter and autoScaleSlider
  // it's recommended to disable them when using autoHeight module
   var rsi = $('#content-slider-1').royalSlider({
    autoHeight: true,
    arrowsNav: false,
    fadeinLoadedSlide: false,
    controlNavigationSpacing: 0,
    controlNavigation: 'tabs',
    imageScaleMode: 'none',
    imageAlignCenter:false,
    loop: false,
    loopRewind: false,
    numImagesToPreload: 6,
    keyboardNavEnabled: true,
    usePreloader: false,
	sliderDrag:false,
    sliderTouch: false,
	navigateByClick: false,
visibleNearby: {
        navigateByCenterClick: false
}
  }).data('royalSlider');
  $('#slider-next').click(function() {
    rsi.next();
	formPos = $("#lendingform-form").offset();
			formTop = formPos.top;
			$('html, body').animate({
				scrollTop: formPos.top - 30
			}, 'fast');
	return false;
  });
  $('#slider-next1').click(function() {
    rsi.next();
	formPos = $("#lendingform-form").offset();
			formTop = formPos.top;
			$('html, body').animate({
				scrollTop: formPos.top - 30
			}, 'fast');
	return false;
  });
});



jQuery(document).ready(function($) {
	var formPos;
	var formTop;
	$("#lendingform-form .rsTabs span.rsTmb").click(function(){
		formPos = $("#lendingform-form").offset();
			formTop = formPos.top;
			$('html, body').animate({
				scrollTop: formPos.top - 30
			}, 'fast');
	});
	
	var mySliderInstance = $("#content-slider-1").data("royalSlider");
	var error = 1;
	$("#edit-submit").click(function(){
			
			
			if($("#edit-first-name").val() == ""){
				$("#edit-first-name").addClass("error");
				error = (error+1);
			} else {
				$("#edit-first-name").removeClass("error");
				
			}
			
			if($("#edit-last-name").val() == ""){
				$("#edit-last-name").addClass("error");
				error = (error+1);
			}else {
				$("#edit-last-name").removeClass("error");
				
			}
			
			if($("#edit-your-role").val() == ""){
				$("#edit-your-role").addClass("error");
				error = (error+1);
			}else {
				$("#edit-your-role").removeClass("error");
				
			}
			
			if($("#edit-best-contact-phone").val() == ""){
				$("#edit-best-contact-phone").addClass("error");
				error = (error+1);
			}else {
				$("#edit-best-contact-phone").removeClass("error");
				
			}
			
		if($("#edit-best-email").val() == ""){
   		$("#edit-best-email").addClass("error");
    	error = (error+1);
   		} else {
              	$("#edit-best-email").removeClass("error");
          }
		  
	    var atpos=$("#edit-best-email").val();
		var regex = /^([a-zA-Z0-9_.+-])+\@(([a-zA-Z0-9-])+\.)+([a-zA-Z0-9]{2,4})+$/;
		if(!regex.test(atpos) ) {
			$("#edit-best-email").addClass("error");
			error = (error+1);
			
		} else {
			$("#edit-best-email").removeClass("error");
		}
		  
			
			if($("#edit-captcha-response").val() == ""){
				$("#edit-captcha-response").addClass("error");
				error = (error+1);
				
			}else {
				$("#edit-captcha-response").removeClass("error");
				
			}
			
			
			if($("#edit-funding-need-amount").val() == ""){
				$("#edit-funding-need-amount").addClass("error");
				error = (error+1);
				mySliderInstance.goTo(1); 
			}else {
				$("#edit-funding-need-amount").removeClass("error");
				
			}
			
			var amt = $("#edit-funding-need-amount").val();
			if(amt != ""){
			if(isNaN(amt)){
				$("#edit-funding-need-amount").addClass("error");
				error = (error+1);
				mySliderInstance.goTo(1);
			}else {
				$("#edit-funding-need-amount").removeClass("error");
				
			}
			}
			
			
			if($("#edit-company-name").val() == ""){
				$("#edit-company-name").addClass("error");
				error = (error+1);
				mySliderInstance.goTo(0);
		    }else {
				$("#edit-company-name").removeClass("error");
				
			}
			
			
			if($("#edit-business-address").val() == ""){
				$("#edit-business-address").addClass("error");
				error = (error+1);
				mySliderInstance.goTo(0); 
			}else {
				$("#edit-business-address").removeClass("error");
			}
			
			
			if($("#edit-suburb").val() == ""){
				$("#edit-suburb").addClass("error");
				error = (error+1);
				mySliderInstance.goTo(0); 
			}else {
				$("#edit-suburb").removeClass("error");
				
			}
			
			
			if($("#edit-state").val() == ""){
				$("#edit-state").addClass("error");
				error = (error+1);
				mySliderInstance.goTo(0); 
			}else {
				$("#edit-state").removeClass("error");
				
			}
			
			
			if($("#edit-postcode").val() == ""){
				$("#edit-postcode").addClass("error");
				error = (error+1);
				mySliderInstance.goTo(0); 
			}else {
				$("#edit-postcode").removeClass("error");
				
			}
			
			
			if($("#edit-annual-turnover").val() == ""){
				$("#edit-annual-turnover").addClass("error");
				error = (error+1);
				mySliderInstance.goTo(0); 
			}else {
				$("#edit-annual-turnover").removeClass("error");
				
			}
			
			
			if($("#edit-current-industry").val() == ""){
				$("#edit-current-industry").addClass("error");
				error = (error+1);
				mySliderInstance.goTo(0); 
			}else {
				$("#edit-current-industry").removeClass("error");
				
			}
			formPos = $("#lendingform-form").offset();
			formTop = formPos.top;
			$('html, body').animate({
				scrollTop: formPos.top - 30
			}, 'fast');
			if(error > 1){
				error = 1;
				return false;
				
				}
			
	})
});

