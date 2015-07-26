<?php
 drupal_add_js(drupal_get_path('module', 'gallery') . '/scripts/royalslider/jquery-1.8.3.min.js'); 
 drupal_add_js(drupal_get_path('module', 'gallery') . '/scripts/royalslider/jquery.royalslider.min.js'); 
 drupal_add_js(drupal_get_path('module', 'gallery') . '/js/imagevideoslider.js',  array('scope' => 'footer'));
         
 drupal_add_css(drupal_get_path('module', 'gallery') . '/scripts/royalslider/royalslider.css');
 drupal_add_css(drupal_get_path('module', 'gallery') . '/scripts/royalslider/skins/default/rs-default.css');
 drupal_add_css(drupal_get_path('module', 'gallery') . '/scripts/royalslider/inner-gallery.css');
if(count($vars) > 0):

global $base_url;
?>
<div id="video-gallery" class="royalSlider videoGallery rsDefault">
    <?php

foreach ($vars as $var => $value) {
    $gallery = gallery_load($value->gid);
    ?>
    <article>
     
        <?php
        $files = field_get_items('gallery', $gallery, 'gallery_image');

        if (!empty($files)) {
            foreach ($files as $keys => $value):
                $imageThumbnail = field_view_value('gallery', $gallery, 'gallery_image', $files[$keys], array(
                    'type' => 'image',
                    'settings' => array(
                        'image_style' => 'thumbnail',
                    ),
                ));
                $image = field_view_value('gallery', $gallery, 'gallery_image', $files[$keys], array(
                    'type' => 'image',
                    
                ));
                ?>
                    <a class="rsImg" data-rsbigimg="<?php print file_create_url($files[$keys]['uri']); ?>" href="<?php print file_create_url($files[$keys]['uri']); ?>">
                        <div class="rsTmb">
                <?php print render($imageThumbnail); ?>

                        </div>
                    </a>
            <?php
            endforeach;
        }
        ?>
  
   

       
      
    </article>



    <?php
   
} 
 
endif;
?>
 </div>