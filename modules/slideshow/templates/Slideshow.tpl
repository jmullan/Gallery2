{foreach from=$itemlist key=i item=it}
<a id="item_{$i}" href="{$it.src}"></a>
<a id="href_{$i}" href="{$it.href}"></a>
{/foreach}
<script language="JavaScript">
var index;
var next = {$start};
var count = {$count};
var images = new Array;
var item_ids = new Array;
{foreach from=$itemlist key=i item=it}
item_ids[{$i}] = '{$it.id}';
{/foreach}
var timer;

{literal}
function preload_photo(i) {
  if (!images[i]) {
    images[i] = new Image;
    images[i].src = document.getElementById("item_"+i).href;
  }
}
function slide_view_start() {
  /* Start preloading next photo to be viewed,
   * then start timer for viewing the current one */
  next++;
  if (next >= count) next = 0;
  preload_photo(next);
  clearTimeout(timer);
  timer = setTimeout('goto_next_photo()', 15000);
}
function goto_next_photo() {
  index = next;
  wait_for_current_photo();
}
function show_current_photo() {
  if (!images[index] || !images[index].complete) {
    preload_photo(index);
    return 0;
  }
  document.slide.src = images[index].src;
  document.getElementById("stop").href = document.getElementById("href_"+index).href;
  return 1;
}
function wait_for_current_photo() {
  if (!show_current_photo()) {
    clearTimeout(timer);
    timer = setTimeout('wait_for_current_photo()', 500);
  }
}
{/literal}
</script>
{g->main}
  {g->breadcrumb}
    {g->item}
      {g->title}
        {g->link id="stop" arg1="view=core:ShowItem"
                           arg2="itemId=`$itemlist.$start.id`"}
          {g->text text="Stop"}
        {/g->link}
      {/g->title}
    {/g->item}
  {/g->breadcrumb}
  {g->pagebox}
    {g->box style="canvas"}
      {g->itemview}
        {g->media}
          <img name="slide"
               src="{$itemlist.$start.src}" onLoad="slide_view_start()">
        {/g->media}
      {/g->itemview}
    {/g->box}
  {/g->pagebox}
{/g->main}
