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
	{g->text text="Edit comment"}
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

      {include file="gallery:modules/core/templates/MarkupBar.tpl" 
	       viewL10domain="modules_core" 
	       element="subject"
	       firstMarkupBar=true}
      <input type="text" size="60" id="subject" name="{g->formVar var="form[subject]"}" value="{$form.subject}" onfocus="this.style.background='#fff';this.style.color='#333';" onblur="this.style.background='#eee';this.style.color='#333';"/>
      <script type="text/javascript">document.forms[0]['{g->formVar var="form[subject]"}'].focus();</script>

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

      {include file="gallery:modules/core/templates/MarkupBar.tpl" 
	       viewL10domain="modules_core" 
	       element="comment"}
      <textarea rows="15" cols="60" id="comment" name="{g->formVar var="form[comment]"}" onfocus="this.style.background='#fff';this.style.color='#333';" onblur="this.style.background='#eee';this.style.color='#333';">{$form.comment}</textarea>

      {if isset($form.error.comment.missing)} 
      <div class="giError">
	{g->text text="You must enter a comment"}
      </div>
      {/if} 
    </div>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][preview]"}" value="{g->text text="Preview"}"/>
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
</div>
