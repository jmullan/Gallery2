{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
	<h2>{g->text text="Confirmation"}</h2>
</div>

{if !empty($status)}
<div class="gbBlock"><h2 class="giSuccess">
  {if isset($status.sent)}
    {g->text text="eCard sent successfully"}
  {/if}
</h2></div>
{/if}

<form action="{g->url}" method="post" enctype="application/x-www-form-urlencoded" id="sendEcardForm">
<div>
	{g->hiddenFormVars}
	<input type="hidden" name="{g->formVar var="controller"}" value="ecard.SendEcard" />
	<input type="hidden" name="{g->formVar var="form[formName]"}" value="{$form.formName}" />
	<input type="hidden" name="{g->formVar var="itemId"}" value="{$Confirmation.itemId}"/>
</div>

<div class="gbBlock gcBackground1">
	<input type="submit" class="inputTypeSubmit"
	  name="{g->formVar var="form[action][new]"}" value="{g->text text="Send another eCard"}"/>
	<input type="submit" class="inputTypeSubmit"
	  name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Done"}"/>
</div>

</form>
