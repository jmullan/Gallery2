{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemEditPhoto.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Thumbnail"}
  </h2>
  
  <p class="giDescription">
    {g->text text="Set the size of the thumbnail.  The largest side of the thumbnail will be no larger than this value."}
  </p>
  
  {if $ItemEditPhoto.editSizes.can.createThumbnail}
  <input type="text" size="6" name="{g->formVar var="form[thumbnail][size]"}" value="{$form.thumbnail.size}"/>
  {else}
  <b>
    {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot create or modify a thumbnail."}
    {if $ItemEditPhoto.isAdmin} 
    <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminModules"}">
      {g->text text="site admin"}
    </a>
    {/if}
  </b>
  {/if}

  {if !empty($form.error.thumbnail.size.missing)}
  <div class="giError">
    {g->text text="You must enter a thumbnail size"}
  </div>
  {/if}
  
  {if !empty($form.error.thumbnail.size.invalid)}
  <div class="giError">
    {g->text text="You must enter a number (greater than zero)"}
  </div>
  {/if}
</div>

<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Resized Photos"}
  </h2>

  <p class="giDescription">
    {g->text text="These sizes are alternate resized versions of the original you would like to have available for viewing."}
  </p>

  {if $ItemEditPhoto.editSizes.can.createThumbnail}
  {counter start=0 assign=index}
  {foreach from=$form.resizes item=resize}
  <input type="checkbox" name="{g->formVar var="form[resizes][$index][active]"}" {if $form.resizes.$index.active}checked="checked"{/if}/>
  <input type="text" size="6" name="{g->formVar var="form[resizes][$index][size]"}" value="{$form.resizes.$index.size}"/>

  <br/>

  {if !empty($form.error.resizes.$index.size.missing)}
  <div class="giError">
    {g->text text="You must enter a valid size"}
  </div>
  {/if}
      
  {if !empty($form.error.resizes.$index.size.invalid)}
  <div class="giError">
    {g->text text="You must enter a number (greater than zero)"}
  </div>
  {/if}
  {counter}
  {/foreach}
  {else}
  <b>
    {g->text text="There are no graphics toolkits enabled that support this type of photo, so we cannot create or modify resized versions."}
    {if $ItemEditPhoto.isAdmin} 
    <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminModules"}">
      {g->text text="site admin"}
    </a>
    {/if}
  </b>
  {/if}
</div>

<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Capture Date and Time"}
  </h2>
  
  <p class="giDescription">
    {g->text text="Set the date and time when this image was captured."}
  </p>

  <p>
    {capture name=originationTimestampField}{g->formVar var="form[originationTimestamp]"}{/capture}
    {g->text text="Date:"}
    {html_select_date time=$form.originationTimestamp field_array=$smarty.capture.originationTimestampField start_year="1970" end_year="+0"}
    {g->text text="Time:"}
    {html_select_time time=$form.originationTimestamp field_array=$smarty.capture.originationTimestampField"}
    <br/>
  </p>

  {if $ItemEditPhoto.originationTimestamp.timestamp}
  <script type="text/javascript" language="javascript">
  // <![CDATA[
  function setOriginationTimestamp(hour, min, sec, mon, day, year) {ldelim}
    var frm = document.gItemAdmin;
    frm.elements['{$smarty.capture.originationTimestampField}[Date_Month]'].value = '{$ItemEditPhoto.originationTimestamp.Date_Month}';
    frm.elements['{$smarty.capture.originationTimestampField}[Date_Day]'].value = '{$ItemEditPhoto.originationTimestamp.Date_Day}';
    frm.elements['{$smarty.capture.originationTimestampField}[Date_Year]'].value = '{$ItemEditPhoto.originationTimestamp.Date_Year}';
    frm.elements['{$smarty.capture.originationTimestampField}[Time_Hour]'].value = '{$ItemEditPhoto.originationTimestamp.Time_Hour}';
    frm.elements['{$smarty.capture.originationTimestampField}[Time_Minute]'].value = '{$ItemEditPhoto.originationTimestamp.Time_Minute}';
    frm.elements['{$smarty.capture.originationTimestampField}[Time_Second]'].value = '{$ItemEditPhoto.originationTimestamp.Time_Second}';
  {rdelim}
  // ]]>
  </script>
  <p>
    {g->text text="Use the original capture date and time from file information (e.g. Exif tag):"}
    <br/>
    <a href="#" onclick="javascript:setOriginationTimestamp();return false;">
      {$ItemEditPhoto.originationTimestamp.timestamp|date_format:"%B %d %Y, %H:%M:%S"}
    </a>
  </p>
  {/if}

  {if !empty($form.error.originationTimestamp.invalid)}
  <div class="giError">
    {g->text text="You must enter a valid date and time"}
  </div>
  {/if}
</div>

{* Include our extra ItemEditOptions *}
{foreach from=$ItemEdit.options item=option}
  {include file="gallery:`$option.file`" l10Domain=$option.l10Domain}
{/foreach}

<div class="gbAdmin">
  <input type="hidden" name="{g->formVar var="mode"}" value="editSizes"/>
  <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" name="{g->formVar var="form[action][undo]"}" value="{g->text text="Undo"}"/>
</div>

