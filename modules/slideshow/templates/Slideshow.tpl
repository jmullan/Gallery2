{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to Slideshow.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
    {if empty($SlideShow.itemList)}
      <div> <!-- TODO: We need a class for this div -->
	{g->text text="This album has no photos to show in a slideshow."}
	<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$SlideShow.item.id`"}">
	  {g->text text="Back to Album View"}
	</a>
      </div>
      {else}
      {foreach from=$SlideShow.itemList key=i item=it}
      <div style="visibility:hidden;position:absolute">
	{foreach from=$it.sources key=j item=source}
	<a id="item_{$i}_{$j}" 
	  href="{g->url arg1="view=core:DownloadItem" arg2="itemId=`$source.id`" 
	                 arg3="serialNumber=`$source.serialNumber`"}"></a>
	{/foreach}

	<a id="href_{$i}" href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$it.id`"}"></a>
	<span id="title_{$i}">{$it.data.title|markup}</span>
	<span id="summary_{$i}">{$it.data.summary|markup}</span>
	<span id="date_{$i}">
	  {if isset($it.exif.DateTime)}
	  {$it.exif.DateTime.title}: {$it.exif.DateTime.value}
	  {else}
	  {capture name="date"}{g->date timestamp=$it.data.modificationTimestamp}{/capture}
	  {g->text text="Date: %s" arg1=$smarty.capture.date}
	  {/if}
	</span>
	<span id="description_{$i}">{$it.data.description|markup}</span>
      </div>
      {/foreach}

      <script type="text/JavaScript">
	// <![CDATA[
	var image = new Image(), timer, iDelay = 15000, iDir = 1, iSize = 0;
	var bPause = 0, bShowText = 0, bShowTools = 1;
	var linkStop, spanPause, spanText, toolText;
	var toolBar, textBanner, spanTitle, spanSummary, spanDate, spanDescription;
	var index = {$SlideShow.start}, count = {$SlideShow.count};
	var is_cached = new Array(count), item_map = new Array(count);
	for (i=0; i < count; i++) is_cached[i] = new Array(0,0,0,0,0,0);
	{foreach from=$SlideShow.itemList key=i item=it}
	item_map[{$i}] = new Array({foreach
	  from=$it.sizeClassMap key=j item=idx}{if $j>0},{/if}{$idx}{/foreach});
	{/foreach}
	{literal}
	function random_int(i) {
	  return Math.floor(i*(Math.random()%1));
	}
	var random_order = new Array(count);
	for (i=0; i < count; i++) random_order[i] = i;
	for (i=count-1; i > 0; i--) {
	  j = random_int(i+1);
	  k = random_order[i];
	  random_order[i] = random_order[j];
	  random_order[j] = k;
	}
	function move_index(by) {
	  if (iDir==0/*random*/) {
	    random_index = 0;
	    for (i = 0; i < count; i++)
	      if (random_order[i] == index) {
	        random_index = i;
	        break;
	      }
	    return random_order[(random_index+by+count)%count];
	  }
	  else return (index+(by*iDir)+count)%count;
	}
	function preload(i) {
	  if (!is_cached[i][iSize]) {
	    is_cached[i][iSize] = 1;
	    image.src = document.getElementById('item_'+i+'_'+item_map[i][iSize]).href;
	  }
	}
	function slide_view_start() {
	  if (bShowText) show_text();
	  preload(move_index(1));
	  if (!bPause) timer = setTimeout('goto_next_photo()', iDelay);
	}
	function goto_next_photo() {
	  index = move_index(1);
	  if (bCanBlend) apply_filter();
	  document.images.slide.src = document.getElementById('item_'+index+'_'+item_map[index][iSize]).href;
	  linkStop.href = document.getElementById('href_'+index).href;
	  if (bCanBlend) document.images.slide.filters[0].Play();
	}
	function show_text() {
	  spanTitle.innerHTML = document.getElementById('title_'+index).innerHTML;
	  spanSummary.innerHTML = document.getElementById('summary_'+index).innerHTML;
	  spanDate.innerHTML = document.getElementById('date_'+index).innerHTML;
	  spanDescription.innerHTML =
	    document.getElementById('description_'+index).innerHTML;
	}
	function text_onoff() {
	  bShowText = bShowText ? 0 : 1;
	  if (bShowText) show_text(); else {
	    spanTitle.innerHTML = spanSummary.innerHTML =
	    spanDate.innerHTML = spanDescription.innerHTML = '';
	  }
	  textBanner.style.visibility = bShowText ? 'visible' : 'hidden';
	  spanText.innerHTML = bShowText ? {/literal}'{g->text text="Hide More Info"}'
	       			  : '{g->text text="Show More Info"}'; {literal}
	}
	function start_stop() {
	  bPause = bPause ? 0 : 1;
	  if (bPause) clearTimeout(timer);
	  else goto_next_photo();
	  spanPause.innerHTML = bPause ? {/literal}'{g->text text="Resume"}'
	       			: '{g->text text="Pause"}'; {literal}
	}
	function jump(by) {
	  index = move_index(by);
	  clearTimeout(timer);
	  goto_next_photo();
	}
	function apply_filter() {
	  f = filters[document.getElementById('filter').selectedIndex];
	  if (f == 'RANDOM') f = filters[random_int(filters.length)];
	  document.images.slide.style.filter = f;
	  document.images.slide.filters[0].Apply();
	}
	function new_size(size) {
	  iSize = size;
	  jump(-1);
	}
	function new_order(direct) {
	  iDir = direct;
	}
	function new_delay(delay) {
	  iDelay = delay*1000;
	  jump(-1);
	}
	function tools_onoff() {
	  bShowTools = bShowTools ? 0 : 1;
	  toolBar.style.visibility = bShowTools ? 'visible' : 'hidden';
	  toolBar.style.position = bShowTools ? 'static' : 'absolute';
	  toolText.innerHTML = bShowTools ? {/literal}'{g->text text="[-]"}'
	       			  : '{g->text text="[+]"}'; {literal}
	}
	{/literal}
        // ]]>
      </script>

      <div style="float:left">
	<a onclick="tools_onoff();return false">
	  <span id="tools" class="breadcrumb_item" style="margin:0px;padding:0px">
	    {g->text text="[-]"}
	  </span>
        </a>
      </div>

      <div id="toolbar">
	<a id="stop" href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$SlideShow.itemList[$SlideShow.start].id`"}">
	  {g->text text="Stop"}
	</a>
	&nbsp;
	<a href="#" onclick="start_stop();return false">
	  <span id="pause">{g->text text="Pause"}</span>
        </a>
	&nbsp;
	<a href="#" onclick="jump(-2);return false">
	  {g->text text="Back One Image"}
	</a>
	&nbsp;
	<a href="#" onclick="text_onoff();return false">
	  <span id="moreInfo">{g->text text="Show More Info"}</span>
        </a>
	&nbsp;

	{g->text text="delay: "}
	<select onchange="new_delay(this.value)">
	  <option value="3">{g->text text="3 seconds"}</option>
	  <option value="5">{g->text text="5 seconds"}</option>
	  <option value="10">{g->text text="10 seconds"}</option>
	  <option selected="selected" value="15">{g->text text="15 seconds"}</option>
	  <option value="20">{g->text text="20 seconds"}</option>
	</select>
	&nbsp;

	{g->text text="direction: "}
	<select onchange="new_order(this.value)">
	  <option value="1">{g->text text="forward"}</option>
	  <option value="-1">{g->text text="reverse"}</option>
	  <option value="0">{g->text text="random"}</option>
	</select>
	&nbsp;

	{g->text text="max size: "}
	<select onchange="new_size(this.value)">
	  <option value="0">{g->text text="320x200"}</option>
	  <option value="1">{g->text text="640x480"}</option>
	  <option value="2">{g->text text="800x600"}</option>
	  <option value="3">{g->text text="1024x768"}</option>
	  <option value="4">{g->text text="1280x1024"}</option>
	  <option value="5">{g->text text="no limit"}</option>
	</select>
	&nbsp;

	<script type="text/JavaScript">{literal}
	  // <![CDATA[
	  if (bCanBlend) {
	    document.write('&nbsp; {/literal}{g->text
		     text="fade: "}{literal}<select id="filter">');
	    for (i = 0; i < filterNames.length; i++) {
	      document.write('<option>'+filterNames[i]);
	    }
	    document.write('<'+'/select>'); // in 2 pieces for valid HTML4.01
	  }
	  {/literal}
	  // ]]>
	</script>
      </div>

      <div> <!-- TODO: We need a class for this div -->
	<div class="gbItemImage">
          <img id="slide" alt="" src=""/>
	</div>
      </div>

      <div id="textBanner" style="visibility:hidden">
	<div class="gbTopFlag">
	  <div class="giTitle"><span id="title"></span></div>
	  <div class="giDescription"><span id="summary"></span></div>
	  <div class="giInfo">
	    <span>
	      <span id="date"></span>
	    </span>
	    <span>
	      <span id="description"></span>
	    </span>
	  </div>
	</div>
      </div>

      <script type="text/JavaScript">
	// <![CDATA[
	linkStop = document.getElementById('stop');
	spanPause = document.getElementById('pause');
	spanText = document.getElementById('moreInfo');
	toolText = document.getElementById('tools');
	toolBar = document.getElementById('toolbar');
	textBanner = document.getElementById('textBanner');
	spanTitle = document.getElementById('title');
	spanSummary = document.getElementById('summary');
	spanDate = document.getElementById('date');
	spanDescription = document.getElementById('description');
	document.images.slide.onload = slide_view_start;
	document.images.slide.onerror = goto_next_photo;
	document.images.slide.src =
	document.getElementById('item_{$SlideShow.start}_'+item_map[{$SlideShow.start}][iSize]).href;
        // ]]>
      </script>
      {/if}
