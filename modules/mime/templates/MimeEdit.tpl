{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
        {g->text text="MIME edit - "} {$MimeEdit.mimeType}
      </h2>
    </div>
  </div>
  <div class="gbAdmin">  
    <h3 class="giTitle">
      {g->text text="MIME type: "}
    </h3>
    <input type="text" size="25" name="{g->formVar var="form[mimeType]"}" value="{$MimeEdit.mimeType}"/>
    <input type="checkbox" name="{g->formVar var="form[viewable]"}" 
        {if $MimeEdit.viewable}checked="checked"{/if} 
      /> {g->text text="Viewable?"} <p/>
    {if isset($form.error.mimeType.missing)}
    <div class="giError">
      {g->text text="MIME type must be specified."}
    </div>
    {/if}
    <h3 class="giTitle">
      {g->text text="Extensions"}
    </h3>
    {foreach from=$MimeEdit.extensions item=extension name=inputs}
    <input type="text" size="5" value="{$extension}"
       name="{g->formVar var="form[extension][`$smarty.foreach.inputs.iteration`]"}"/>
    <br/>
    {/foreach}
    <input type="text" size="5" name="{g->formVar var="form[extension][0]"}"/>
    <br/>
    {if isset($form.error.ext.missing)}
    <div class="giError">
      {g->text text="You must specify at least one extension."}
    </div>
    {/if}
  </div>
      
  <div class="gbBottomFlag">
    <div class="gbButtons">
      <input type="submit" name="{g->formVar var="form[action][save]"}" 
        value="{g->text text="Save"}"/>
      <input type="submit" name="{g->formVar var="form[action][apply]"}" 
        value="{g->text text="Apply"}"/>
      <input type="submit" name="{g->formVar var="form[action][cancel]"}" 
        value="{g->text text="Cancel"}"/>
    </div>
  </div>
</div>  

