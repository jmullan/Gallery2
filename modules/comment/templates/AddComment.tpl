{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h1 class="giTitle">
	{g->text text="Add Comment"}
      </h1>
    </div>
  </div>

  {if isset($form.action.preview)}
  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Comment Preview"}
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{$form.subject|markup}
      </div>

      {$form.comment|markup}
    </div>
  </div>
  {/if}

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Posted by"}
      </div>

      {g->text text="%s (%s)" arg1=$AddComment.user.fullName arg2=$AddComment.host}
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Subject"}
      </div>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>

      {include file="gallery:modules/core/templates/MarkupBar.tpl" 
	       viewL10domain="modules_core" 
	       element="subject"
	       firstMarkupBar="true"}
      <input type="text" size="60" id="subject" name="{g->formVar var="form[subject]"}" value="{$form.subject}" onfocus="this.style.background='#fff';this.style.color='#333';" onblur="this.style.background='#eee';this.style.color='#333';"/>
      <script type="text/javascript">document.forms[0]['{g->formVar var="form[subject]"}'].focus();</script>

      {if isset($form.error.subject.missing)}
      <div class="giError">
	{g->text text="You must enter a subject!"}
      </div>
      {/if}
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Comment"}
      </div>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>

      {include file="gallery:modules/core/templates/MarkupBar.tpl" 
	       viewL10domain="modules_core" 
	       element="comment"}
      <textarea rows="15" cols="60" id="comment" name="{g->formVar var="form[comment]"}" onfocus="this.style.background='#fff';this.style.color='#333';" onblur="this.style.background='#eee';this.style.color='#333';">{$form.comment}</textarea>
    </div>

    {if isset($form.error.comment.missing)}
    <div class="giError">
      {g->text text="You must enter a comment!"}
    </div>
    {/if}
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][preview]"}" value="{g->text text="preview"}"/>
    <input type="submit" name="{g->formVar var="form[action][add]"}" value="{g->text text="save"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="cancel"}"/>
  </div>
</div>