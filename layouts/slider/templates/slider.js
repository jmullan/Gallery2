//Class app
var app_ww, app_wh, app_wx, app_wy; // Window width/height, position
var app_agent = navigator.userAgent.toLowerCase(); // Client sniff..
var app_version = parseInt(navigator.appVersion);
var app_is_ie = app_agent.indexOf('msie')>=0 && app_agent.indexOf('opera')<0;
var app_is_safari = app_agent.indexOf('safari')>=0;
if (document.all&&window.attachEvent) { // IE-Win
  window.attachEvent("onunload", app_setcookie);  
} else if (window.addEventListener) { // Others
  window.addEventListener("unload", app_setcookie, false);
}
function app_getwinsize() {
 var obj = image_div.offsetParent;
 if (obj && obj.tagName != 'BODY' && obj.tagName != 'HTML') {
  app_ww = obj.offsetWidth; app_wh = obj.offsetHeight;
  app_wx = obj.offsetLeft;  app_wy = obj.offsetTop;
 } else {
  if (typeof(window.innerWidth)=='number') {
   app_ww = window.innerWidth; app_wh = window.innerHeight;
  } else if (document.documentElement.clientHeight) {
   app_ww = document.documentElement.clientWidth; app_wh = document.documentElement.clientHeight;
  } else {
   app_ww = document.body.clientWidth; app_wh = document.body.clientHeight;
  }
  app_wx = app_wy = 0;
 }
}
function app_init() {
 image_div = document.getElementById('image');
 thumb_div = document.getElementById('thumbs');
 title_div = document.getElementById('titlebar');
 titlebar_ht = title_div.offsetHeight + (app_is_ie?1:0);
 thumbs_ht = data_maxth + 15;
 thumbs_wd = data_maxtw + 15;
 app_getwinsize();
 image_setsize();
 document.getElementById('options').style.bottom = toolbar_getheight() + 'px';
 var attr = document.createAttribute('onresize');
 attr.value = 'app_onresize()';
 document.body.attributes.setNamedItem(attr);
 document.onkeypress = app_onkeypress;
 if (app_is_ie) { //For IE:
  document.body.onresize = app_onresize;
  document.onkeydown = app_onkeydown;
 }
 if (app_is_safari) { //For Safari:
  document.onresize = app_onresize;
 }
 var i = app_getcookie();
 if (i < -1) image_show(data_view >= 0 ? data_view : 0);
}
function app_onresize() {
 app_getwinsize();
 if (app_is_ie) image_setsize();
 image_fit();
}
function app_setcookie() {
 var c = thumbs_horiz + ';' + slide_order + ';' + (slide_delay/1000) + ';';
 var s = image_index + ';';
 var d = new Date();
 d.setTime(d.getTime() + 90*24*60*60*1000); // 90 day cookie
 document.cookie = 'G2_slider=' + escape(c) + ';expires=' + d.toUTCString() +
  ';path=' + app_path;
 document.cookie = 'G2_slider_' + data_name + '=' + escape(s) +
  ';path=' + app_path;
}
function app_getcookie() {
 var c = getcookie('G2_slider'), i,j,v,n,it=1,r=-2;
 if (c) {
  for (i=0, j = c.indexOf(';', 0); j >= 0; i = j+1, j = c.indexOf(';', i)) {
   v = c.substring(i,j);
   n = parseInt(v);
   switch (it++) {
    case 1: if (n==0) thumbs_horizvert(); break;
    case 2: ui_select('slide_order', n); slide_setorder(n); break;
    case 3: ui_select('slide_delay', n); slide_setdelay(n); break;
   }
  }
 }
 c = getcookie('G2_slider_'+data_name); it=1;
 if (c) {
  for (i=0, j = c.indexOf(';', 0); j >= 0; i = j+1, j = c.indexOf(';', i)) {
   v = c.substring(i,j);
   n = parseInt(v);
   switch (it++) {
    case 1: r=n; if (n >= 0) image_show(n); break;
   }
  }
 }
 return r;
}
function app_onkeypress(event) {
 if (app_is_ie) event = window.event; //For IE
 var keyCode = event.keyCode ? event.keyCode : event.which; //For Moz
 if (event.ctrlKey || event.altKey || event.shiftKey || event.metaKey) return;
 if (app_is_safari) switch (keyCode) { //For Safari
  case 63232: keyCode=38; break;  case 63273: keyCode=36; break;
  case 63233: keyCode=40; break;  case 63275: keyCode=35; break;
  case 63234: keyCode=37; break;  case 63276: keyCode=33; break;
  case 63235: keyCode=39; break;  case 63277: keyCode=34; break;
 }
 if (keyCode==32) slide_onoff();
 if (keyCode < 33 || keyCode > 40) return;
 var obj = document.getElementById('text');
 switch (keyCode) {
  case 37: image_prev(); break; //Left
  case 39: image_next(); break; //Right
  case 38: if (image_iszoomable) image_zoom(1); break; //Up
  case 40: if (image_iszoomable) image_zoom(0); break; //Down
  case 33: if (thumbs_horiz) thumb_div.scrollLeft -= app_ww-5; //PageUp
                        else thumb_div.scrollTop -= app_wh-5;
           break;
  case 34: if (thumbs_horiz) thumb_div.scrollLeft += app_ww-5; //PageDown
                        else thumb_div.scrollTop += app_wh-5;
           break;
  case 35: if (thumbs_horiz) thumb_div.scrollLeft = thumb_div.scrollWidth; //End
                        else thumb_div.scrollTop = thumb_div.scrollHeight;
           break;
  case 36: if (thumbs_horiz) thumb_div.scrollLeft = 0; //Home
                        else thumb_div.scrollTop = 0;
           break;
 }
}
function app_onkeydown() {
 if (window.event.keyCode >= 33 && window.event.keyCode <= 40)
 { app_onkeypress(window.event); window.event.returnValue = false; }
}
//Class image :: div image :: span image_view
var image_index=0; // Index of visible image
var image_zoomable=0, image_zoomon=0; // Image is larger than view area, is zoomed to full size
var image_cache = new Image; // For precaching an image
var image_iscached = new Array(data_count); // Track precached images
var image_div, thumb_div;
function image_setsize() {
 image_div.style.bottom = toolbar_getheight() + 'px';
 if (app_is_ie) {
  image_div.style.height = (app_wh-toolbar_getheight())+'px';
  if (!thumbs_horiz) thumb_div.style.height = (app_wh-toolbar_getheight())+'px';
  image_div.style.width = thumbs_horiz ? '100%' : (app_ww-thumbs_wd)+'px';
 }
}
function image_show(i) {
 slide_reset();
 image_index = i;
 if (data_iw[i] < 0) {
  ui_sethtml('image_view', '<iframe name="view" style="width:100%;height:100%" frameborder="0" src="'+document.getElementById('img_'+i).href+'"></iframe>');
  document.fit_size.className = document.full_size.className = 'off';
 } else {
  var s = image_fit(1);
  ui_sethtml('image_view', '<img name="view" src="' + document.getElementById('img_'+i).href
   + '" ' + s + ' onload="image_loaded()">');
 }
 ui_sethtml('title', document.getElementById('title_'+image_index).innerHTML);
 toolbar_setbuttons();
 if (slide_inprog && !slide_on && !slide_order) slide_inprog = 0;
}
function image_loaded() {
 var i = slide_nextindex(); if (i >= 0) image_precache(i);
 slide_go(1,i);
}
function image_fit(getstr) {
 if (!getstr && !document.view) return;
 var w = data_iw[image_index], h = data_ih[image_index];
 var aw = image_div.offsetWidth, ah = image_div.offsetHeight, a=0;
 if (w > aw || h > ah) {
  image_iszoomable = 1;
  if ((a = h/w) < ah/aw) {
   w = aw; h = Math.round(aw*a);
  } else {
   w = Math.round(ah/a); h = ah;
  }
 } else image_iszoomable = 0;
 if (image_zoomon) {
  if (getstr || !image_iszoomable) image_zoom(0,1);
  else { image_zoom(1); return; }
 }
 document.getElementById('image_view').style.paddingTop = Math.floor((ah-h)/2)+'px';
 document.fit_size.className = 'off';
 document.full_size.className = image_iszoomable?'on':'off';
 if (getstr) {
  return 'width="' + w + '" height="' + h + '"';
 } else {
  document.view.width = w;
  document.view.height = h;
 }
}
function image_zoom(on,noresize) { // Set full/fit size
 image_div.style.overflow = on?'auto':'hidden';
 if (!on) image_div.scrollLeft = image_div.scrollTop = 0;
 if (image_zoomon=on) {
  document.full_size.className = 'off';
  document.fit_size.className = 'on';
  var h = image_div.offsetHeight - data_ih[image_index];
  document.getElementById('image_view').style.paddingTop = max(Math.floor(h/2),0) + 'px';
  document.view.width = data_iw[image_index];
  document.view.height = data_ih[image_index];
 } else if (!noresize) { image_fit(); }
}
function image_precache(i) {
 if (!image_iscached[i]) {
  image_iscached[i] = 1;
  image_cache.src = document.getElementById('img_'+i).href;
 }
}
function image_next() {
 var i = slide_nextindex(); if (i >= 0) image_show(i);
}
function image_prev() {
 var i = slide_previndex(); if (i >= 0) image_show(i);
}
//Class toolbar :: div toolbar(tools_left,title,tools_right)
var titlebar_ht, thumbs_ht, thumbs_wd; // Height of titlebar, height/width of thumb bar
var thumbs_horiz=1; // Thumbnail display is horizontal or vertical
var options_on=0; // Slideshow options are visible
function toolbar_getheight() { return titlebar_ht + (thumbs_horiz?thumbs_ht:0); }
function toolbar_setbuttons() {
 var i = slide_nextindex(), j = slide_previndex();
 document.next_img.className = i>=0?'on':'off';
 document.next_off.className = i<0?'on':'off';
 document.prev_img.className = j>=0?'on':'off';
 document.prev_off.className = j<0?'on':'off';
}
function options_onoff() {
 if (!options_on) set_itemLinks(image_index);
 ui_vis('options', options_on=options_on?0:1);
}
function thumbs_horizvert() {
 if (thumbs_horiz=thumbs_horiz?0:1) {
  title_div.style.marginBottom = thumbs_ht + 'px';
  thumb_div.style.bottom = '0px';
  thumb_div.style.top = '';
  thumb_div.style.height = thumbs_ht + 'px';
  thumb_div.style.width = '100%';
  image_div.style.left = '0px';
 } else {
  image_div.style.left = thumbs_wd + 'px';
  thumb_div.style.width = thumbs_wd + 'px';
  thumb_div.style.height = '';
  thumb_div.style.top = '0px';
  thumb_div.style.bottom = '20px';
  title_div.style.marginBottom = '0px';
 }
 var imgs = thumb_div.getElementsByTagName('IMG'), cls = thumbs_horiz?'hthumb':'vthumb';
 for (var i=0; i < imgs.length; i++)
  imgs[i].className = cls;
 image_setsize();
 image_fit();
 document.getElementById('options').style.bottom = toolbar_getheight() + 'px';
}
//Class slide
var slide_on=0; // Slideshow is running
var slide_timer; // Timer to load next slide
var slide_order=1; // Direction: 1=forward, -1=reverse, 0=random
var slide_randomorder = new Array(data_count); // Random index order
var slide_delay=5000; // Milliseconds between slides
var slide_inprog=0; // Slideshow in progress (may be paused)
function slide_reset() { clearTimeout(slide_timer); }
function slide_go(i,j) {
 if (slide_on) {
  if (!i) j = slide_nextindex();
  if (j >= 0) slide_timer = setTimeout('slide_next()', slide_delay);
  else { slide_inprog = 0; slide_onoff(); }
 }
}
function slide_onoff() {
 if (!data_count) return;
 slide_on = slide_on?0:1;
 slide_setbutton();
 if (slide_on) {
  var t = 'slide_next()', d = 1500;
  if (!slide_inprog) {
   if (!slide_order) slide_fillrandom(1);
   if (slide_nextindex() < 0) {
    d = 5;
    if (slide_order>0) t = 'image_show(0)';
    else if (slide_order<0) t = 'image_show('+(data_count-1)+')';
    else t = 'image_show('+slide_randomorder[0]+')';
   }
  }
  slide_inprog = 1;
  slide_timer = setTimeout(t, d);
 } else slide_reset();
 toolbar_setbuttons();
}
function slide_next() {
 var i = slide_nextindex(); if (i >= 0) image_show(i); else slide_onoff();
}
function slide_nextindex(x) {
 if (slide_on && !slide_order) {
  for (var i=0,j=0; i < data_count; i++)
   if (slide_randomorder[i]==image_index) { j=i+(x?-1:1); break; }
  return (j>=0 && j<data_count) ? slide_randomorder[j] : -1;
 }
 var j = image_index + (x?-1:1)*(slide_on?slide_order:1);
 return (j>=0 && j<data_count) ? j : -1;
}
function slide_previndex() {
 return slide_nextindex(1);
}
function slide_fillrandom(lockfirst) {
 var i,j,k; for (i=0; i < data_count; i++) slide_randomorder[i] = i;
 if (lockfirst=lockfirst?1:0) {
  slide_randomorder[0] = image_index; slide_randomorder[image_index] = 0;
 }
 for (i=data_count-1; i > lockfirst; i--) {
  j = lockfirst ? random_int(i)+1 : random_int(i+1);
  k = slide_randomorder[i];
  slide_randomorder[i] = slide_randomorder[j];
  slide_randomorder[j] = k;
 }
}
function slide_setorder(o) {
 slide_order = parseInt(o);
 slide_setbutton();
 if (!slide_on) slide_inprog = 0;
}
function slide_setdelay(d) {
 slide_delay = parseInt(d)*1000;
 if (slide_on) { slide_reset(); slide_go(); }
}
function slide_setbutton() {
 document.slide_poz.className = slide_on?'on':'off';
 document.slide_fwd.className = (!slide_on&&slide_order>0)?'on':'off';
 document.slide_rev.className = (!slide_on&&slide_order<0)?'on':'off';
 document.slide_rand.className = (!slide_on&&!slide_order)?'on':'off';
}
//Item Links
function set_itemLinks(idx) {
 var list = document.getElementById('linkList'), links = document.getElementById('links_' + idx), i;
 while (list.options.length > 1) { list.options[1] = null; }
 for (i = 0; i < links.options.length; i++) {
  list.options[i+1] = new Option(links.options[i].text, links.options[i].value);
 }
 list.options[0].selected = true;
 list = document.getElementById('photoActions');
 list.style.display = (links.options.length > 0) ? 'inline' : 'none';
}
//UI Util
function ui_vis(id,vis,scroll) {
 var obj = document.getElementById(id);
 if (scroll) obj.style.overflow = vis ? 'auto' : 'hidden';
 obj.style.visibility = vis ? 'inherit' : 'hidden';
}
function ui_sethtml(id,html) {
 document.getElementById(id).innerHTML = html;
}
function ui_select(id,val) {
 var obj = document.getElementById(id), i;
 for (i=0; i < obj.options.length; i++) {
  if (obj.options[i].value == val) {
   obj.options[i].selected = 1; break;
  }
 }
}
//Util
function max(a,b) { return (a>b)?a:b; }
function min(a,b) { return (a<b)?a:b; }
function random_int(i) { return Math.floor(i*(Math.random()%1)); }
function getcookie(k) {
 var i = document.cookie.indexOf(k+'=');
 if (i < 0) return;
 i += k.length+1;
 var e = document.cookie.indexOf(';', i);
 if (e < 0) e = document.cookie.length;
 return unescape(document.cookie.substring(i, e));
}
