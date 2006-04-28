{*
 * $Revision: 1.3 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1"><h2>
{if $form.mimeType}
  {g->text text="Edit MIME type: %s" arg1=$form.mimeType}
{else}
  {g->text text="New MIME type"}
{/if}
</h2></div>

{if isset($status.saved)}
<div class="gbBlock"><h2 class="giSuccess">
  {g->text text="Mime entry saved successfully"}
</h2></div>
{/if}

<div class="gbBlock">
  <h4> {g->text text="MIME type: "} </h4>

  <input type="text" size="25" name="{g->formVar var="form[mimeType]"}" value="{$form.mimeType}"/>
  <input type="checkbox"{if $form.viewable} checked="checked"{/if}
   name="{g->formVar var="form[viewable]"}"/>
  {g->text text="Viewable?"}
  {if isset($form.error.mimeType.missing)}
  <div class="giError">
    {g->text text="MIME type must be specified."}
  </div>
  {/if}

  <h4> {g->text text="Extensions"} </h4>

  {foreach from=$form.extensions item=extension name=inputs}
    <input type="text" size="5"
     name="{g->formVar var="form[extensions][]"}" value="{$extension}"/>
    {if isset($form.error.extensions.inuse.$extension)}
    <div class="giError">
      {g->text text="This extension is already in use and cannot be reused."}
    </div>
    {/if}
    <br/>
  {/foreach}

  <input type="text" size="5" name="{g->formVar var="form[extensions][]"}"/>
  {if isset($form.error.extensions.missing)}
  <div class="giError">
    {g->text text="You must specify at least one extension."}
  </div>
  {/if}
</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][apply]"}" value="{g->text text="Apply"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
</div>
