{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
	<h2>{g->text text="eCard"}</h2>
</div>

{if !empty($status)}
<div class="gbBlock"><h2 class="giSuccess">
  {if isset($status.saved)}
    {g->text text="Settings saved successfully"}
  {/if}
</h2></div>
{/if}

<div class="gbBlock">
	<p class="giDescription">
		{g->text text="You can use the following keywords: %from% (sender e-mail), %fromName% (sender name), %to% (recipient e-mail), %toName% (recipient name)."}
	</p>

	<h4>{g->text text="E-mail sender:"}
		<span class="giSubtitle"> {g->text text="(leave empty for user defined sender name)"}</span></h4>
	<input type="text" id="giFormFrom" size="60"
		name="{g->formVar var="form[from]"}" value="{$form.from}" />
		
	<h4>{g->text text="E-mail subject:"}</h4>
	<input type="text" id="giFormSubject" size="60"
		name="{g->formVar var="form[subject]"}" value="{$form.subject}" />

	<h4>{g->text text="E-mail BCC:"}</h4>
	<input type="text" id="giFormBCC" size="60"
		name="{g->formVar var="form[bcc]"}" value="{$form.bcc}" />

	<h4>{g->text text="E-mail header:"}</h4>	
	<textarea rows="5" cols="60" id="giFormHeader"
		name="{g->formVar var="form[header]"}">{$form.header}</textarea>
	
	<h4>{g->text text="E-mail footer:"}</h4>
	<textarea rows="5" cols="60" id="giFormFooter"
		name="{g->formVar var="form[footer]"}">{$form.footer}</textarea>

	<h4>{g->text text="E-mail format:"}</h4>
	<select name="{g->formVar var="form[format]"}">
		{html_options options=$AdminEcard.formatList selected=$form.format}
	</select>
</div>

<div class="gbBlock gcBackground1">
	<input type="submit" class="inputTypeSubmit"
		name="{g->formVar var="form[action][save]"}" value="{g->text text="Save Settings"}"/>
	<input type="submit" class="inputTypeSubmit"
		name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
</div>
