  {gallery->form controller="$controller"}
  {gallery->input type="hidden" name="form.formName"}AdminCreateUser{/gallery->input}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2"}
	{gallery->bigFontSize}
	{gallery->text text="Create a new user"}
	{/gallery->bigFontSize}
      </td>
    </tr>

    <tr>
      <td align="right" width="40%">
	{gallery->text text="Username"}
      </td>
      <td width="60%">
	{gallery->input type="text" name="form.userName"}{$form.userName}{/gallery->input}
	{gallery->warningFontColor}
	{gallery->text text="[required]"}
	{/gallery->warningFontColor}
      </td>
    </tr>

    {if isset($form.error.userName.missing)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{gallery->errorFontColor}
	{gallery->text text="You must enter a username"}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    {if isset($form.error.userName.exists)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{gallery->errorFontColor}
	{gallery->text text="Username '%s' already exists"
	             arg1=$form.userName}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="right">
	{gallery->text text="Full name"}
      </td>
      <td>
	{gallery->input type="text" name="form.fullName"}{$form.fullName}{/gallery->input}
      </td>
    </tr>
      
    <tr>
      <td align="right">
	{gallery->text text="Email address"}
      </td>
      <td>
	{gallery->input type="text" name="form.email"}{$form.email}{/gallery->input}
	{gallery->warningFontColor}
	{gallery->text text="[required]"}
	{/gallery->warningFontColor}
      </td>
    </tr>
      
    {if isset($form.error.email.missing)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{gallery->errorFontColor}
	{gallery->text text="You must enter an email address"}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="right">
	{gallery->text text="Language"}
      </td>
      <td>
	{gallery->select name="form.language"}
	  {html_options options=$languageList selected=$form.language}
	{/gallery->select}
      </td>
    </tr>
      
    <tr>
      <td align="right">
	{gallery->text text="Password"}
      </td>
      <td>
	{gallery->input type="password" name="form.password1"}{/gallery->input}
	{gallery->warningFontColor}
	{gallery->text text="[required]"}
	{/gallery->warningFontColor}
      </td>
    </tr>
      
    {if isset($form.error.password1.missing)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{gallery->errorFontColor}
	{gallery->text text="You must enter a password"}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="right">
	{gallery->text text="Verify password"}
      </td>
      <td>
	{gallery->input type="password" name="form.password2"}{/gallery->input}
	{gallery->warningFontColor}
	{gallery->text text="[required]"}
	{/gallery->warningFontColor}
      </td>
    </tr>

    {if isset($form.error.password2.missing)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{gallery->errorFontColor}
	{gallery->text text="You must enter the password a second time"}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    {if isset($form.error.password2.mismatch)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{gallery->errorFontColor}
	{gallery->text text="The passwords you entered did not match"}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    <tr>
      <td align="center" colspan="2">
	{gallery->input type="submit" name="form.action.create"}{gallery->text text="Create User"}{/gallery->input}
	{gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
      </td>
    </tr>
      
  </table>
  {/gallery->form}

  