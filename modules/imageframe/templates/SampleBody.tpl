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
    {if isset($ImageFrameSample.item)}
      {include file=$ImageFrameSample.frame.template
       ImageFrame_data=$ImageFrameSample.frame.data ImageFrame_frame=$frame
       item=$ImageFrameSample.item image=$ImageFrameSample.thumb}
    {else}
      {include file=$ImageFrameSample.frame.template
       ImageFrame_data=$ImageFrameSample.frame.data ImageFrame_frame=$frame
       src=$ImageFrameSample.sample}
      {* Can also add ImageFrame_pre= and ImageFrame_post= params. Example:
       * {capture name="link"}<a href="{g->url arg1="view=core:ShowItem"
       *                                       arg2="itemId=`$itemId`"}">{/capture}
       * ImageFrame_pre=$smarty.capture.link ImageFrame_post="</a>" *}
    {/if}
    </div>
  {/foreach}
</div>
