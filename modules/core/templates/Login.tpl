  {gallery->form controller="$controller"}
  {gallery->input type="hidden" name="form.formName"}Login{/gallery->input}

  <!-- Embed the hidden return fields -->
  {foreach from=$return key=key item=value}
  {gallery->input type="hidden" name=return.$key}{$value}{/gallery->input}
  {/foreach}

    <table border="0" cellspacing="4" cellpadding="0">
	<tr>
	  <td colspan="2" align="center">
	    {gallery->biggerFontSize}
	    {gallery->text text="Gallery Login"}
	    {/gallery->biggerFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td align="right">
	    {gallery->text text="Username"}
	  </td>
	  <td>
	    {gallery->input type="text" name="form.username"}{$form.username}{/gallery->input}
	  </td>
	</tr>

	<!-- {if !empty($form.error.username.missing)} -->
	<tr>
	  <td colspan="2">
	    {gallery->errorFontColor}
	    {gallery->text text="You must enter a username"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<tr>
	  <td align="right">
	    {gallery->text text="Password"}
	  </td>
	  <td>
	    {gallery->input type="password" name="form.password"}{/gallery->input}
	  </td>
	</tr>
	
	<!-- {if !empty($form.error.password.missing)} -->
	<tr>
	  <td colspan="2">
	    {gallery->errorFontColor}
	    {gallery->text text="You must enter a password"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.error.invalidPassword)} -->
	<tr>
	  <td colspan="2">
	    {gallery->errorFontColor}
	    {gallery->text text="Your login information is incorrect.  Please try again."}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>
	
	<tr>
	  <td colspan="2" align="center">
	    {gallery->input type="submit" name="form.action.login"}{gallery->text text="Login"}{/gallery->input}
	    {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
	  </td>
	</tr>
	
    </table>
    {/gallery->form}
