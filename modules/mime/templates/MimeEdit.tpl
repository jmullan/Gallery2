{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  {if $form.mimeType}
  {g->text text="New MIME type"}
  {else}
  {g->text text="Edit MIME type: %s" arg1=$form.mimeType}
  {/if}
</div>

{if !empty($status)}
<div class="gbBlock">
  <h2 class="giSuccess">
    {if isset($status.saved)}
    {g->text text="Mime entry saved successfully"}
    {/if}
  </h2>
</div>
{/if}

<div class="gbBlock">  
  <h3 class="giTitle">
    {g->text text="MIME type: "}
  </h3>
  <input type="text" size="25" name="{g->formVar var="form[mimeType]"}" value="{$form.mimeType}"/>
  <input type="checkbox" name="{g->formVar var="form[viewable]"}" 
      {if $form.viewable}checked="checked"{/if} 
    /> {g->text text="Viewable?"} <p/>
  {if isset($form.error.mimeType.missing)}
  <div class="giError">
    {g->text text="MIME type must be specified."}
  </div>
  {/if}

  <h3 class="giTitle">
    {g->text text="Extensions"}
  </h3>
  {foreach from=$form.extensions item=extension name=inputs}
  <input type="text" size="5" value="{$extension}"
     name="{g->formVar var="form[extensions][]"}"/>
  {if isset($form.error.extensions.inuse.$extension)}
  <div class="giError">
    {g->text text="This extension is already in use and cannot be reused."}
  </div>
  {/if}
  <br/>
  {/foreach}
  <input type="text" size="5" name="{g->formVar var="form[extensions][]"}"/>
  <br/>
  {if isset($form.error.extensions.missing)}
  <div class="giError">
    {g->text text="You must specify at least one extension."}
  </div>
  {/if}
</div>
      
<div class="gbBlock gcBackground1">
  <input type="submit" name="{g->formVar var="form[action][save]"}" 
    value="{g->text text="Save"}"/>
  <input type="submit" name="{g->formVar var="form[action][apply]"}" 
    value="{g->text text="Apply"}"/>
  <input type="submit" name="{g->formVar var="form[action][cancel]"}" 
    value="{g->text text="Cancel"}"/>
</div>  

