<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Add Comment"}
      </div>
    </div>

    <div class="spacer">
      &nbsp;
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

      <input type="text" size="60" name="{g->formVar var="form[subject]"}" value="{$form.subject}"/>

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

      <textarea rows="15" cols="60" name="{g->formVar var="form[comment]"}">{$form.comment}</textarea>
    </div>

    {if isset($form.error.comment.missing)}
    <div class="giError">
      {g->text text="You must enter a comment!"}
    </div>
    {/if}
  </div>

  <div class="gbAdmin">
    <input type="submit" name="{g->formVar var="form[action][preview]"}" value="{g->text text="preview"}"/>
    <input type="submit" name="{g->formVar var="form[action][add]"}" value="{g->text text="save"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="cancel"}"/>
  </div>
</div>
