  {galleryForm controller="$controller"}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2"}
	{galleryBigFont}
	{galleryText text="Create a new user"}
	{/galleryBigFont}
      </td>
    </tr>

    <tr>
      <td align="right" width="40%">
	{galleryText text="Username"}
      </td>
      <td width="60%">
	{galleryInput name="form.username"}{$form.username}{/galleryInput}
	{galleryWarningFontColor}
	{galleryText text="[required]"}
	{/galleryWarningFontColor}
      </td>
    </tr>

    {if isset($form.error.username.missing)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{galleryErrorFontColor}
	{galleryText text="You must enter a username"}
	{/galleryErrorFontColor}
      </td>
    </tr>
    {/if}
      
    {if isset($form.error.username.exists)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{galleryErrorFontColor}
	{galleryText text="Username '%s' already exists"
	             arg1=$form.username}
	{/galleryErrorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="right">
	{galleryText text="Full name"}
      </td>
      <td>
	{galleryInput name="form.fullname"}{$form.fullname}{/galleryInput}
      </td>
    </tr>
      
    <tr>
      <td align="right">
	{galleryText text="Email address"}
      </td>
      <td>
	{galleryInput name="form.email"}{$form.email}{/galleryInput}
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
      <td align="right">
	{galleryText text="Password"}
      </td>
      <td>
	{galleryInput type="password" name="form.password1"}{/galleryInput}
	{galleryWarningFontColor}
	{galleryText text="[required]"}
	{/galleryWarningFontColor}
      </td>
    </tr>
      
    {if isset($form.error.password1.missing)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{galleryErrorFontColor}
	{galleryText text="You must enter a password"}
	{/galleryErrorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="right">
	{galleryText text="Verify password"}
      </td>
      <td>
	{galleryInput type="password" name="form.password2"}{/galleryInput}
	{galleryWarningFontColor}
	{galleryText text="[required]"}
	{/galleryWarningFontColor}
      </td>
    </tr>

    {if isset($form.error.password2.missing)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{galleryErrorFontColor}
	{galleryText text="You must enter the password a second time"}
	{/galleryErrorFontColor}
      </td>
    </tr>
    {/if}
      
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
      
    <tr>
      <td align="center" colspan="2">
	{galleryInput type="submit" name="form.action.create"}{galleryText text="Create User"}{/galleryInput}
	{galleryInput type="submit" name="form.action.cancel"}{galleryText text="Cancel"}{/galleryInput}
      </td>
    </tr>
      
  </table>
  {/galleryForm}

  