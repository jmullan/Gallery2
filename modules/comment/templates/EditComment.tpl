{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Edit comment"} </h2>
</div>

{if isset($form.action.preview)}
<div class="gbBlock">
  <h3> {g->text text="Comment Preview"} </h3>

  <h4> {$form.subject|markup} </h4>

  {$form.comment|markup}
</div>
{/if}

<div class="gbBlock">
  <h4>
    {g->text text="Commenter"}
    <span class="giSubtitle"> {g->text text="(required)"} </span>
  </h4>

  <input type="hidden" name="{g->formVar var="commentId"}" value="{$EditComment.comment.id}"/>
  <input type="text" name="{g->formVar var="form[commenterName]"}" value="{$form.commenterName}"/>

  {if isset($form.error.commenterName.missing)} 
  <div class="giError">
    {g->text text="You must enter a username."}
  </div>
  {/if} 
  {if isset($form.error.commenterName.invalid)} 
  <div class="giError">
    {g->text text="The username you entered is invalid."}
  </div>
  {/if} 

  <h4> {g->text text="Host"} </h4>
  <input type="text" name="{g->formVar var="form[host]"}" value="{$form.host}"/>

  <h4>
    {g->text text="Date"}
    <span class="giSubtitle"> {g->text text="(required)"} </span>
  </h4>

  <input type="text" name="{g->formVar var="form[date]"}" value="{$form.date}"/>

  {if isset($form.error.date.invalid)} 
  <div class="giError">
    {g->text text="The date you entered is invalid."}
  </div>
  {/if} 
  {if isset($form.error.date.missing)} 
  <div class="giError">
    {g->text text="You must enter a date"}
  </div>
  {/if} 

  <h4>
    {g->text text="Subject"}
    <span class="giSubtitle"> {g->text text="(required)"} </span>
  </h4>

  {include file="gallery:modules/core/templates/MarkupBar.tpl" 
	   viewL10domain="modules_core" 
	   element="subject" firstMarkupBar=true}

  <input type="text" id="subject" size="60" class="gcBackground1"
   name="{g->formVar var="form[subject]"}" value="{$form.subject}"
   onfocus="this.className=''" onblur="this.className='gcBackground1'"/>

  <script type="text/javascript">
    document.forms[0]['{g->formVar var="form[subject]"}'].focus();
  </script>

  {if isset($form.error.subject.missing)} 
  <div class="giError">
    {g->text text="You must enter a subject"}
  </div>
  {/if} 

  <h4>
    {g->text text="Comment"}
    <span class="giSubtitle"> {g->text text="(required)"} </span>
  </h4>

  {include file="gallery:modules/core/templates/MarkupBar.tpl" 
	   viewL10domain="modules_core" 
	   element="comment"}

  <textarea rows="15" cols="60" id="comment" class="gcBackground1"
   name="{g->formVar var="form[comment]"}"
   onfocus="this.className=''" onblur="this.className='gcBackground1'">{$form.comment}</textarea>

  {if isset($form.error.comment.missing)} 
  <div class="giError">
    {g->text text="You must enter a comment"}
  </div>
  {/if} 
</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][preview]"}" value="{g->text text="Preview"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
</div>
