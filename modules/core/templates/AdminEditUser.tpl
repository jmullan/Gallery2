  {gallery->form controller="$controller"}
  {gallery->input type="hidden" name="formName"}AdminEditUser{/gallery->input}
  {gallery->input type="hidden" name="form.userId"}{$form.userId}{/gallery->input}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td align="center" colspan="2">
	{gallery->bigFontSize}
	{gallery->text text="Edit a user"}
	{/gallery->bigFontSize}
      </td>
    </tr>

    <tr>
      <td align="right" width="40%">
	{gallery->text text="Username"}
      </td>
      <td width="60%">
	{gallery->input type="hidden" name="form.userName"}{$form.userName}{/gallery->input}
	{$form.userName}
      </td>
    </tr>

    <tr>
      <td align="right">
	{gallery->text text="Full name"}
      </td>
      <td>
	{gallery->input type="text" name="form.fullName"}{$form.fullName}{/gallery->input}
	{gallery->warningFontColor}
	{gallery->text text="[required]"}
	{/gallery->warningFontColor}
      </td>
    </tr>

    {if isset($form.error.fullName.missing)}
    <tr>
      <td>
	&nbsp;
      </td>
      <td>
	{gallery->errorFontColor}
	{gallery->text text="You must enter a name"}
	{/gallery->errorFontColor}
      </td>
    </tr>
    {/if}
      
    {if $show.email}
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
    {/if}
      
    {if $show.language}
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
      <td colspan="2" align="right">
	&nbsp;
      </td>
    </tr>
    {/if}

    {if $show.password}
    <tr>
      <td rowspan="2" align="right">
	{gallery->text text="Enter a new password twice to change passwords, or leave it blank to leave password unchanged."}
      </td>
      <td>
	{gallery->input type="password" name="form.password1"}{/gallery->input}
	{gallery->warningFontColor}
	{gallery->text text="[required]"}
	{/gallery->warningFontColor}
      </td>
    </tr>
      
    <tr>
      <td>
	{gallery->input type="password" name="form.password2"}{/gallery->input}
	{gallery->warningFontColor}
	{gallery->text text="[required]"}
	{/gallery->warningFontColor}
      </td>
    </tr>

    {if isset($form.error.password.mismatch)}
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
    {/if}
      
    <tr>
      <td align="center" colspan="2">
	{gallery->input type="submit" name="form.action.save"}{gallery->text text="Save"}{/gallery->input}
	{gallery->input type="submit" name="form.action.undo"}{gallery->text text="Undo"}{/gallery->input}
	{gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
      </td>
    </tr>
      
  </table>
  {/gallery->form}

  