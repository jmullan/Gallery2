{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to EditComment.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Edit comment"}
      </div>
    </div>

    <div class="spacer">
      &nbsp;
    </div>
  </div>

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Commenter"}
      </div>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>

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
    </div>
      
    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Host: "}
      </div>

      <input type="text" name="{g->formVar var="form[host]"}" value="{$form.host}"/>
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Date: "}
      </div>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>

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
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Subject: "}
      </div>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>

      <input type="text" size="60" name="{g->formVar var="form[subject]"}" value="{$form.subject}"/>

      {if isset($form.error.subject.missing)} 
      <div class="giError">
	{g->text text="You must enter a subject"}
      </div>
      {/if} 
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Comment: "}
      </div>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>

      <textarea rows="15" cols="60" name="{g->formVar var="form[comment]"}">{$form.comment}</textarea>

      {if isset($form.error.comment.missing)} 
      <div class="giError">
	{g->text text="You must enter a comment"}
      </div>
      {/if} 
    </div>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
</div>
