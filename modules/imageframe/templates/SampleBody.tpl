{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="giTitle">
  {g->text text="Image Frame Samples"}
</div>
<div class="gbMenu">
  {foreach from=$ImageFrameSample.list key=frame item=name}
    <div style="float:left;margin:6px">
    {$name}<br/>
    {imageframe frame=$frame}
      {if isset($ImageFrameSample.item)}
	{g->image item=$ImageFrameSample.item image=$ImageFrameSample.thumb
		  maxSize=150 id="%ID%" class="%CLASS%"}
      {else}
	<img src="{g->url href="modules/imageframe/images/sample.jpg"}"
	     width="150" height="126" id="%ID%" class="%CLASS%"/>
      {/if}
    {/imageframe}
    </div>
  {/foreach}
</div>
