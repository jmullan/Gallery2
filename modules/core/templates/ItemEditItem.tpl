{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbAdmin">
  {if isset($ItemEditItem.can.changePathComponent)}
  <div class="gbDataEntry">
    <h2 class="giTitle">
      {g->text text="Name"}
    </h2>
    <div class="giSubtitle">
      {g->text text="required"}
    </div>
    <p class="giDescription">
      {g->text text="The name of this item on your hard disk.  It must be unique in this album.  Only use alphanumeric characters, underscores or dashes."}
    </p>
    
    {strip}
    {foreach from=$ItemAdmin.parents item=parent}
    {if empty($parent.parentId)}
    /
    {else}
    {$parent.pathComponent}/
    {/if}
    {/foreach}
    {/strip}
    <input type="text" size="40" name="{g->formVar var="form[pathComponent]"}" value="{$form.pathComponent}"/>

    {if !empty($form.error.pathComponent.invalid)}
    <div class="giError">
      {g->text text="Your name contains invalid characters.  Please choose another."}
    </div>
    {/if}
    
    {if !empty($form.error.pathComponent.missing)}
    <div class="giError">
      {g->text text="You must enter a name for this item."}
    </div>
    {/if}
    
    {if !empty($form.error.pathComponent.collision)}
    <div class="giError">
      {g->text text="The name you entered is already in use.  Please choose another."}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbDataEntry">
    <h3 class="giTitle">
      {g->text text="Title"}
    </h3>
    <p class="giDescription">
      {g->text text="The title of this item."}
    </p>

    {include file="gallery:modules/core/templates/MarkupBar.tpl" 
             viewL10domain="modules_core" 
	     element="title"
	     firstMarkupBar=true}
    <input id="title" type="text" size="40" name="{g->formVar var="form[title]"}" value="{$form.title}"/>
  </div>
  {if !empty($form.error.title.missingRootTitle)}
    <div class="giError">
      {g->text text="The root album must have a title."}
    </div>
  {/if}

  <div class="gbDataEntry">
    <h3 class="giTitle">
      {g->text text="Summary"}
    </h3>
    <p class="giDescription">
      {g->text text="The summary of this item."}
    </p>

    {include file="gallery:modules/core/templates/MarkupBar.tpl" 
             viewL10domain="modules_core" 
	     element="summary"}
    <input id="summary" type="text" size="40" name="{g->formVar var="form[summary]"}" value="{$form.summary}"/>
  </div>

  <div class="gbDataEntry">
    <h3 class="giTitle">
      {g->text text="Keywords"}
    </h3>
    <p class="giDescription">
      {g->text text="Keywords are not visible, but are searchable."}
    </p>
    <textarea rows="2" cols="60" name="{g->formVar var="form[keywords]"}">{$form.keywords}</textarea>
  </div>

  <div class="gbDataEntry">
    <h3 class="giTitle">
      {g->text text="Description"}
    </h3>
    <p class="giDescription">
      {g->text text="This is the long description of the item."}
    </p>
    {include file="gallery:modules/core/templates/MarkupBar.tpl" 
             viewL10domain="modules_core" 
	     element="description"}
    <textarea id="description" rows="4" cols="60" name="{g->formVar var="form[description]"}">{$form.description}</textarea>
  </div>
</div>

<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="%s Date and Time" arg1=$ItemEditItem.typeName.0}
  </h2>

  <p class="giDescription">
    {if !empty($ItemEditItem.isItemPhoto)}
    {g->text text="Set the date and time when this image was captured."}
    {elseif !empty($ItemEditItem.isItemUnknown)}
    {g->text text="Set the date and time to be displayed for this item."}
    {else}
    {g->text text="Set the date and time to be displayed for this %s." arg1=$ItemEditItem.typeName.1}
    {/if}
  </p>

  <p>
    {capture name=originationTimestampField}{g->formVar var="form[originationTimestampSplit]"}{/capture}
    {g->text text="Date:"}
    {html_select_date time=$form.originationTimestamp field_array=$smarty.capture.originationTimestampField start_year="1970" end_year="+0"}
    {g->text text="Time:"}
    {html_select_time time=$form.originationTimestamp field_array=$smarty.capture.originationTimestampField"}
    <br/>
  </p>

  {if !empty($ItemEditItem.originationTimestamp)}
  <script type="text/javascript" language="javascript">
  // <![CDATA[
  function setOriginationTimestamp() {ldelim}
    var frm = document.gItemAdmin;
    frm.elements['{$smarty.capture.originationTimestampField}[Date_Month]'].value = '{$ItemEditItem.originationTimestamp.Date_Month}';
    frm.elements['{$smarty.capture.originationTimestampField}[Date_Day]'].value = '{$ItemEditItem.originationTimestamp.Date_Day}';
    frm.elements['{$smarty.capture.originationTimestampField}[Date_Year]'].value = '{$ItemEditItem.originationTimestamp.Date_Year}';
    frm.elements['{$smarty.capture.originationTimestampField}[Time_Hour]'].value = '{$ItemEditItem.originationTimestamp.Time_Hour}';
    frm.elements['{$smarty.capture.originationTimestampField}[Time_Minute]'].value = '{$ItemEditItem.originationTimestamp.Time_Minute}';
    frm.elements['{$smarty.capture.originationTimestampField}[Time_Second]'].value = '{$ItemEditItem.originationTimestamp.Time_Second}';
  {rdelim}
  // ]]>
  </script>
  <p>
    {g->text text="Use the original capture date and time from file information (e.g. Exif tag):"}
    <br/>
    <a href="#" onclick="javascript:setOriginationTimestamp();return false;">
      {$ItemEditItem.originationTimestamp.timestamp|date_format:"%B %d %Y, %H:%M:%S"}
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

<div class="gbButtons">
  <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" name="{g->formVar var="form[action][undo]"}" value="{g->text text="Undo"}"/>
</div>
