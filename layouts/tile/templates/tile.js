function app_init() {
 // check for cookie; if found display image and remove cookie
 // precache..
 window.image_loaded = image_loaded;
}
var image_cache = new Image; // For precaching an image
var image_iscached = new Array(image_width.length); // Track precached images
function image_show(i) {
 if (image_width[i] < 0) {
  ui_sethtml('image_view', '<iframe style="width:100%;height:100%" frameborder="0" src="'+document.getElementById('img_'+i).href+'"></iframe>');
 } else {
  ui_sethtml('image_view', '<img src="'+document.getElementById('img_'+i).href+'" width="'+image_width[i]+'" height="'+image_height[i]+'" onload="image_loaded()"/>');
 }
 ui_sethtml('title', document.getElementById('title_'+i).innerHTML);
 ui_vis('image',1,1);
}
function image_loaded() {
 // precache..
}
function image_precache(i) {
 if (!image_iscached[i]) {
  image_iscached[i] = 1;
  image_cache.src = document.getElementById('img_'+i).href;
 }
}
function ui_vis(id,vis,scroll) {
 var obj = document.getElementById(id);
 if (scroll) obj.style.overflow = vis ? 'auto' : 'hidden';
 obj.style.visibility = vis ? 'inherit' : 'hidden';
}
function ui_sethtml(id,html) {
 document.getElementById(id).innerHTML = html;
}
function getcookie(k) {
 var i = document.cookie.indexOf(k+'=');
 if (i < 0) return;
 i += k.length+1;
 var e = document.cookie.indexOf(';', i);
 if (e < 0) e = document.cookie.length;
 return unescape(document.cookie.substring(i, e));
}
