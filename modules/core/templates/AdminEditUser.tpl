  {galleryForm controller="$controller"}
  {galleryInput type="hidden" name="formName"}AdminEditUser{/galleryInput}
  {galleryInput type="hidden" name="form.userid"}{$form.userid}{/galleryInput}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2">
	{galleryBigFont}
	{galleryText text="Edit a user"}
	{/galleryBigFont}
      </td>
    </tr>

    <tr>
      <td align="right" width="40%">
	{galleryText text="Username"}
      </td>
      <td width="60%">
	{galleryInput type="hidden" name="form.username"}{$form.username}{/galleryInput}
	{$form.username}
      </td>
    </tr>

    <tr>
      <td align="right">
	{galleryText text="Full name"}
      </td>
      <td>
	{galleryInput type="text" name="form.fullname"}{$form.fullname}{/galleryInput}
      </td>
    </tr>
      
    {if $isAnonymous}
    <tr>
      <td align="center" colspan="2">
	{galleryText text="This is the anonymous user."}
      </td>
    </tr>
    {else}
    <tr>
      <td align="right">
	{galleryText text="Email address"}
      </td>
      <td>
	{galleryInput type="text" name="form.email"}{$form.email}{/galleryInput}
	{galleryWarningFontColor}
	{galleryText text="[required]"}
	{/galleryWarningFontColor}
      </td>
    </tr>
      
    {if isset($form.error.email.missing)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{galleryErrorFontColor}
	{galleryText text="You must enter an email address"}
	{/galleryErrorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="right">
	{galleryText text="Language"}
      </td>
      <td>
	{gallerySelect name="form.language"}
	  {html_options options=$languageList selected=$form.language}
	{/gallerySelect}
      </td>
    </tr>

    <tr>
      <td colspan="2" align="right">
	&nbsp;
      </td>
    </tr>

    <tr>
      <td rowspan="2" align="right">
	{galleryText text="Enter a new password twice to change passwords, or leave it blank to leave password unchanged."}
      </td>
      <td>
	{galleryInput type="password" name="form.password1"}{/galleryInput}
	{galleryWarningFontColor}
	{galleryText text="[required]"}
	{/galleryWarningFontColor}
      </td>
    </tr>
      
    <tr>
      <td>
	{galleryInput type="password" name="form.password2"}{/galleryInput}
	{galleryWarningFontColor}
	{galleryText text="[required]"}
	{/galleryWarningFontColor}
      </td>
    </tr>

    {if isset($form.error.password2.mismatch)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{galleryErrorFontColor}
	{galleryText text="The passwords you entered did not match"}
	{/galleryErrorFontColor}
      </td>
    </tr>
    {/if}

    {/if}
      
    <tr>
      <td align="center" colspan="2">
	{galleryInput type="submit" name="form.action.save"}{galleryText text="Save"}{/galleryInput}
	{galleryInput type="submit" name="form.action.undo"}{galleryText text="Undo"}{/galleryInput}
	{galleryInput type="submit" name="form.action.cancel"}{galleryText text="Cancel"}{/galleryInput}
      </td>
    </tr>
      
  </table>
  {/galleryForm}

  