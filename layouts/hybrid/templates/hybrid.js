//Class app
var app_ww, app_wh, app_wx, app_wy; // Window width/height, position
var app_agent = navigator.userAgent.toLowerCase(); // Client sniff..
var app_version = parseInt(navigator.appVersion);
var app_is_ie = app_agent.indexOf('msie')>=0 && app_agent.indexOf('opera')<0;
var app_is_safari = app_agent.indexOf('safari')>=0;
if (document.all&&window.attachEvent) { // IE-Win
  window.attachEvent("onload", app_onload);
  window.attachEvent("onunload", app_setcookie);
} else if (window.addEventListener) { // Others
  window.addEventListener("load", app_onload, false);
  window.addEventListener("unload", app_setcookie, false);
}
function app_getwinsize() {
 var obj = document.getElementById('gsContent').offsetParent;
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
 app_getwinsize();
 sidebar_wd = document.getElementById('sidebar').offsetWidth;
 //Get titlebar height and size album content:
 album_div = document.getElementById('gsAlbumContent');
 album_setsize(1);
 album_title_maxht = document.getElementById('album_titlebar').offsetHeight;
 album_title_minht = max(18,
  document.getElementById('album_title').offsetHeight)+2;
 album_setsize(2);
 //Get toolbar/text height and size image content:
 toolbar_ht = document.getElementById('toolbar').offsetHeight;
 text_ht = document.getElementById('text').offsetHeight;
 image_div = document.getElementById('image');
 image_setsize();
 var attr = document.createAttribute('onresize');
 attr.value = 'app_onresize()';
 document.body.attributes.setNamedItem(attr);
 document.onkeypress = app_onkeypress;
 if (app_is_ie) { //For IE:
  document.body.onresize = app_onresize;
  document.onkeydown = app_onkeydown;
  album_div.style.width = '100%';
  app_onresize();
 }
 if (app_is_safari) { //For Safari:
  document.onresize = app_onresize;
  document.getElementById('album_tools').style.width = '38px';
  document.getElementById('tools_left').style.width = '57px';
  document.getElementById('tools_right').style.width = '76px';
  document.getElementById('tools_right').style.paddingRight = '8px';
 }
 window.image_loaded = image_loaded;
 var i = app_getcookie();
 if (i < -1 && data_view >= 0) image_show(data_view);
}
function app_onload() {
 if (data_count>0) image_precache(0);
}
function app_onresize() {
 app_getwinsize();
 if (app_is_ie) { album_setsize(); image_setsize();
     document.getElementById('popup').style.height = Math.floor(app_wh*0.8)+'px';
     document.getElementById('sidebar').style.height = app_wh+'px'; }
 if (image_on) image_fit();
}
function app_setcookie() {
 var c = slide_order + ';' + (slide_delay/1000) + ';' + sidebar_on + ';' +
  album_detailson + ';' + album_itemlinkson + ';' + text_on + ';';
 var s = (image_on ? image_index : -1) + ';' + album_div.scrollTop + ';';
 var d = new Date();
 d.setTime(d.getTime() + 90*24*60*60*1000); // 90 day cookie
 document.cookie = 'G2_hybrid=' + escape(c) + ';expires=' + d.toUTCString() +
  ';path=' + app_path;
 document.cookie = 'G2_hybrid_' + data_name + '=' + escape(s) +
  ';path=' + app_path;
}
function app_getcookie() {
 var c = getcookie('G2_hybrid'), i,j,v,n,it=1,r=-2;
 if (c) {
  for (i=0, j = c.indexOf(';', 0); j >= 0; i = j+1, j = c.indexOf(';', i)) {
   v = c.substring(i,j);
   n = parseInt(v);
   switch (it++) {
    case 1: ui_select('slide_order', n); slide_setorder(n); break;
    case 2: ui_select('slide_delay', n); slide_setdelay(n); break;
    case 3: if (!n) sidebar_onoff(); break;
    case 4: if (!n) album_detailsonoff(); break;
    case 5: if (!n) album_itemlinksonoff(); break;
    case 6: if (n) text_onoff(); break;
   }
  }
 }
 c = getcookie('G2_hybrid_'+data_name); it=1;
 if (c) {
  for (i=0, j = c.indexOf(';', 0); j >= 0; i = j+1, j = c.indexOf(';', i)) {
   v = c.substring(i,j);
   n = parseInt(v);
   switch (it++) {
    case 1: r=n; if (n >= 0) image_show(n); break;
    case 2: album_div.scrollTop = n; break;
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
 else if (keyCode==27) { if (popup_on) popup_vis(0);
                         else if (image_on) image_vis(0); }
 if (keyCode < 33 || keyCode > 40) return;
 var obj = document.getElementById('text');
 if (!image_on) switch (keyCode) {
  case 38: album_div.scrollTop -= 22; break; //Up
  case 40: album_div.scrollTop += 22; break; //Down
  case 33: album_div.scrollTop -= album_div.clientHeight-5; break; //PageUp
  case 34: album_div.scrollTop += album_div.clientHeight-5; break; //PageDown
  case 35: album_div.scrollTop = album_div.scrollHeight; break; //End
  case 36: album_div.scrollTop = 0; break; //Home
  case 37: if (sidebar_on) sidebar_onoff(); break; //Left
  case 39: if (!sidebar_on) sidebar_onoff(); break; //Right
 } else switch (keyCode) {
  case 37: image_prev(); break; //Left
  case 39: image_next(); break; //Right
  case 38: if (!text_on) text_onoff(); break; //Up
  case 40: if (text_on) text_onoff(); break; //Down
  case 33: if (text_on) obj.scrollTop -= obj.clientHeight-5; break; //PageUp
  case 34: if (text_on) obj.scrollTop += obj.clientHeight-5; break; //PageDown
 }
}
function app_onkeydown() {
 if (window.event.keyCode >= 33 && window.event.keyCode <= 40)
 { app_onkeypress(window.event); window.event.returnValue = false; }
}
//Class album :: div gsContent(album_titlebar(album_tools),gsAlbumContent)
var album_title_minht, album_title_maxht; // Min/max height of title bar
var album_title_borderht=app_is_ie?0:1; // Height of titlebar border
var album_div; // album_content div
var album_detailson=1; // Details are visible
var album_itemlinkson=1; // Item links are visible
function album_gettitleht() {
 return album_detailson ? album_title_maxht : album_title_minht;
}
function album_setsize(x) {
 if (!x || x==1) {
  document.getElementById('gsContent').style.left = sidebar_getwidth() + 'px';
  if (app_is_ie) document.getElementById('gsContent').style.width =
   (app_ww-sidebar_getwidth()) + 'px';
 }
 if (!x || x==2) {
  album_div.style.top = album_gettitleht() + 'px';
  if (app_is_ie) album_div.style.height = (app_wh-album_gettitleht()) + 'px';
 }
}
function album_detailsonoff() {
 album_detailson = album_detailson?0:1;
 album_setsize(2);
 document.getElementById('album_info').style.visibility =
  album_detailson ? 'inherit' : 'hidden';
 document.getElementById('album_summary').style.visibility =
  album_detailson ? 'inherit' : 'hidden';
 document.getElementById('album_titlebar').style.height =
  album_detailson ? '' : (album_title_minht-album_title_borderht)+'px';
 ui_sethtml('dtl_link', album_detailson ? 'hide details' : 'show details');
}
function album_itemlinksonoff() {
 var imgs = album_div.getElementsByTagName('IMG');
 album_itemlinkson = album_itemlinkson?0:1;
 for (var i=0; i < imgs.length; i++)
  if (imgs[i].className=='hid' || imgs[i].className=='vis')
   imgs[i].className = album_itemlinkson ? 'vis' : 'hid';
 ui_sethtml('lnk_link', album_itemlinkson?'hide item links':'show item links');
}
//Class sidebar :: div sidebar
var sidebar_on=1; // Sidebar is visible
var sidebar_wd; // Sidebar width (when visible)
function sidebar_getwidth() { return sidebar_on?sidebar_wd:0; }
function sidebar_onoff() {
 document.getElementById('sidebar_max').className = sidebar_on?'on':'off';
 document.getElementById('sidebar_min').className = sidebar_on?'off':'on';
 ui_vis('sidebar', (sidebar_on = sidebar_on?0:1), 1);
 album_setsize(1);
}
//Class image :: div image :: div image_view
var image_on=0; // Image is visible
var image_index=0; // Index of visible image
var image_zoomon=0; // Image is zoomed to full size
var image_cache = new Image; // For precaching an image
var image_iscached = new Array(data_count); // Track precached images
var image_div; // Image div
function image_setsize() {
 image_div.style.bottom = toolbar_getheight() + 'px';
 if (app_is_ie) image_div.style.height = (app_wh-toolbar_getheight())+'px';
}
function image_vis(on) {
 if (!on && slide_on) slide_onoff();
 if (sidebar_on) ui_vis('sidebar', on?0:1, 1); //For IE
 ui_vis('image',on,on?0:1);
 toolbar_vis(image_on=on);
 album_div.style.overflow = image_on?'hidden':'auto'; //For firefox
 if (!on) image_div.scrollTop = image_div.scrollLeft = 0; //For firefox
 if (!on && !document.view) ui_sethtml('image_view', '');
}
function image_show(i) {
 if (!image_on) image_vis(1);
 slide_reset();
 image_index = i;
 if (data_iw[i] < 0) {
  ui_sethtml('image_view', '<iframe style="width:100%;height:'+(app_wh-toolbar_getheight()-4)+'px" frameborder="0" src="'+document.getElementById('img_'+i).href+'"></iframe>');
  document.getElementById('fit_size').className = document.getElementById('full_size').className = 'off';
 } else {
  var s = image_fit(1);
  ui_sethtml('image_view', '<img name="view" src="' + document.getElementById('img_'+i).href
   + '" ' + s + ' onload="image_loaded()">');
 }
 ui_sethtml('title', document.getElementById('title_'+image_index).innerHTML);
 text_fill();
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
 var aw = app_ww, ah = app_wh - toolbar_getheight(), a=0;
 if (w > aw || h > ah) {
  if ((a = h/w) < ah/aw) {
   w = aw; h = Math.round(aw*a);
  } else {
   w = Math.round(ah/a); h = ah;
  }
 }
 if (image_zoomon) {
  if (getstr || !a) image_zoom(0,1);
  else { image_zoom(1); return; }
 }
 document.getElementById('image_view').style.paddingTop = Math.floor((ah-h)/2)+'px';
 document.getElementById('fit_size').className = 'off';
 document.getElementById('full_size').className = a?'on':'off';
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
  document.getElementById('full_size').className = 'off';
  document.getElementById('fit_size').className = 'on';
  var h = app_wh - toolbar_getheight() - data_ih[image_index];
  document.getElementById('image_view').style.paddingTop =
   max(Math.floor(h/2),0) + 'px';
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
var toolbar_ht; // Height of toolbar/title
function toolbar_getheight() { return toolbar_ht + (text_on?text_ht:0); }
function toolbar_vis(on) {
 ui_vis('toolbar', on);
 if (text_on) ui_vis('text', on, 1);
}
function toolbar_setbuttons() {
 var i = slide_nextindex(), j = slide_previndex();
 document.getElementById('next_img').className = i>=0?'on':'off';
 document.getElementById('next_off').className = i<0?'on':'off';
 document.getElementById('prev_img').className = j>=0?'on':'off';
 document.getElementById('prev_off').className = j<0?'on':'off';
}
//Class text :: div text
var text_on=0; // Text is visible
var text_ht; // Height when visible
function text_fill() {
 if (text_on) ui_sethtml('text',
              document.getElementById('text_'+image_index).innerHTML);
}
function text_onoff() {
 if ((text_on = text_on?0:1) && data_count>0) text_fill();
 document.getElementById('text_on').className = text_on?'off':'on';
 document.getElementById('text_off').className = text_on?'on':'off';
 document.getElementById('toolbar').style.paddingBottom =
  (text_on?text_ht:0)+'px';
 image_setsize();
 if (image_on) {
  ui_vis('text', text_on, 1);
  image_fit();
 }
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
  if (slide_inprog) {
   if (!image_on) image_vis(1);
  } else {
   if (!slide_order) slide_fillrandom(image_on);
   if (!image_on || slide_nextindex() < 0) {
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
 document.getElementById('slide_poz').className = slide_on?'on':'off';
 document.getElementById('slide_fwd').className = (!slide_on&&slide_order>0)?'on':'off';
 document.getElementById('slide__fwd').className = (slide_order>0)?'on':'off';
 document.getElementById('slide_rev').className = (!slide_on&&slide_order<0)?'on':'off';
 document.getElementById('slide__rev').className = (slide_order<0)?'on':'off';
 document.getElementById('slide_rand').className = (!slide_on&&!slide_order)?'on':'off';
 document.getElementById('slide__rand').className = (!slide_order)?'on':'off';
}
//Class popup :: div popup,popup_titlebar
var popup_on=0; // Popup is visible
var popup_timer; // Timer for hiding popup menu
function popup_info(i) {
 window.frames[0].document.location.replace(
  document.getElementById('info_' + (i>=0 ? i : image_index)).href);
 popup_vis(1);
}
function popup_vis(on) {
 ui_vis('popup', popup_on=on);
 ui_vis('popup_titlebar', on);
 if (!app_is_ie)
  document.getElementById('popup').scrolling = on?'auto':'off'; //For firefox
}
function popup_menu(event,i,ii) {
 clearTimeout(popup_timer);
 var pop = document.getElementById('popup_menu');
 pop.style.visibility = 'hidden';
 var links = ii>=0 ? '<a href="" onclick="popup_info(' + ii +
                     ');this.blur();return false">item details</a><br>' : '';
 var obj = document.getElementById('links_'+i);
 if (obj) links += obj.innerHTML;
 ui_sethtml('popup_links', links);
 // IE: window.event,offsetX/Y,srcElement  Moz: event,layerX/Y,target
 if (app_is_ie) event = window.event;
 var pw = pop.offsetWidth, ph = pop.offsetHeight;
 var iw = event.target ? event.target.width : event.srcElement.width;
 var ix = event.offsetX ? event.offsetX : (event.layerX-event.target.x);
 var iy = event.offsetY ? event.offsetY : (event.layerY-event.target.y);
 if (app_is_ie) { ix+=2; iy+=2; } //IE, but not Safari
 var px = event.clientX - ix + iw - pw - app_wx;
 var py = min(event.clientY - iy, app_wh - ph) - app_wy;
 pop.style.left = px+'px';
 pop.style.top = py+'px';
 pop.style.visibility = 'visible';
}
//UI Util
function ui_vis(id,vis,scroll) {
 var obj = document.getElementById(id);
 //if (!nopos) obj.style.position = vis ? 'static' : 'absolute';
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
