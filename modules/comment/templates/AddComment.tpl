{*
 * $Revision: 1.26 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Add Comment"} </h2>
</div>

{if isset($form.action.preview)}
<div class="gbBlock">
  <h3> {g->text text="Comment Preview"} </h3>

  <h4> {$form.subject|markup} </h4>

  {$form.comment|markup}
</div>
{/if}

<form action="{g->url}" method="post" enctype="application/x-www-form-urlencoded"
 id="addCommentForm">
  <div>
    {g->hiddenFormVars}
    <input type="hidden" name="{g->formVar var="controller"}" value="comment.AddComment"/>
    <input type="hidden" name="{g->formVar var="form[formName]"}" value="{$form.formName}"/>
    <input type="hidden" name="{g->formVar var="itemId"}" value="{$AddComment.itemId}"/>
  </div>

  <div class="gbBlock">
    <h4> {g->text text="Posted by"} </h4>
    {g->text text="%s (%s)" arg1=$user.fullName arg2=$AddComment.host}

    <h4>
      {g->text text="Subject"}
      <span class="giSubtitle"> {g->text text="(required)"} </span>
    </h4>

    {include file="gallery:modules/core/templates/MarkupBar.tpl" viewL10domain="modules_core"
	     element="subject" firstMarkupBar=true}

    <input type="text" id="subject" size="60" class="gcBackground1"
	   name="{g->formVar var="form[subject]"}" value="{$form.subject}"
	   onfocus="this.className=''" onblur="this.className='gcBackground1'"/>
    <script type="text/javascript">
      document.getElementById('addCommentForm')['{g->formVar var="form[subject]"}'].focus();
    </script>

    {if isset($form.error.subject.missing)}
    <div class="giError">
      {g->text text="You must enter a subject!"}
    </div>
    {/if}

    <h4>
      {g->text text="Comment"}
      <span class="giSubtitle"> {g->text text="(required)"} </span>
    </h4>

    {include file="gallery:modules/core/templates/MarkupBar.tpl" viewL10domain="modules_core"
	     element="comment"}

    <textarea rows="15" cols="60" id="comment" class="gcBackground1"
      name="{g->formVar var="form[comment]"}"
      onfocus="this.className=''" onblur="this.className='gcBackground1'">{$form.comment}</textarea>

    {if isset($form.error.comment.missing)}
    <div class="giError">
      {g->text text="You must enter a comment!"}
    </div>
    {/if}
  </div>

  <div class="gbBlock gcBackground1">
    <input type="submit" class="inputTypeSubmit"
      name="{g->formVar var="form[action][preview]"}" value="{g->text text="Preview"}"/>
    <input type="submit" class="inputTypeSubmit"
      name="{g->formVar var="form[action][add]"}" value="{g->text text="Save"}"/>
    <input type="submit" class="inputTypeSubmit"
      name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
</form>
