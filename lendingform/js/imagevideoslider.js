(function($) {
        $('#video-gallery').royalSlider({
            arrowsNav: false,
            fadeinLoadedSlide: true,
            controlNavigationSpacing: 0,
            controlNavigation: 'thumbnails',
            thumbs: {
                autoCenter: false,
                fitInViewport: true,
                orientation: 'horizantal',
                spacing: 0,
                paddingBottom: 0
            },
            keyboardNavEnabled: true,
            imageScaleMode: 'fill',
            imageAlignCenter: true,
            slidesSpacing: 0,
            loop: false,
            loopRewind: true,
            numImagesToPreload: 3,
            video: {
                autoHideArrows: true,
                autoHideControlNav: false,
                autoHideBlocks: true
            },
            autoScaleSlider: true,
            autoScaleSliderWidth: 960,
            autoScaleSliderHeight: 450
        });
    })(jQuery);


//(function ($) {
//    $(function() {
//      $('#full-width-slider').royalSlider({    
//        arrowsNav: true,
//          arrowsNavAutoHide: false,
//          startSlideId: 0,
//          loop: true,
//          navigateByClick: true,
//          transitionType:'fade',
//          transitionSpeed: 1500,
//          controlsInside: true,
//          controlNavigation: 'bullets',
//          autoPlay: {
//                  // autoplay options go gere
//                  enabled: true,
//                  pauseOnHover: false
//          }
//      });
//    });
//})(jQuery);
