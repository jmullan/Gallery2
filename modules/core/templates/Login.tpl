  {galleryForm controller="$controller"}
  {galleryInput type="hidden" name="formName"}Login{/galleryInput}

  <!-- Embed the hidden return fields -->
  {foreach from=$return key=key item=value}
  {galleryInput type="hidden" name=$key|string_format:"return.%s"}{$value}{/galleryInput}
  {/foreach}

  <center>
    <table border="0" cellspacing="4" cellpadding="0">
      <tr>
	<td colspan="2" align="center">
	  {galleryBiggerFont}
	  {galleryText text="Gallery Login"}
	  {/galleryBiggerFont}
	</a>
	</td>
      </tr>

      <tr>
	<td>
	  &nbsp;
	</td>
      </tr>

      <tr>
	<td align="right">
	  {galleryText text="Username"}
	</td>
	<td>
	  {galleryInput type="text" name="form.username"}{$form.username}{/galleryInput}
	</td>
      </tr>

      {if !empty($form.error.username.missing)}
      <tr>
	<td colspan="2">
	  {galleryErrorFontColor}
	  {galleryText text="You must enter a username"}
	  {/galleryErrorFontColor}
	</td>
      </tr>
      {/if}

      <tr>
	<td align="right">
	  {galleryText text="Password"}
	</td>
	<td>
	  {galleryInput type="password" name="form.password"}{/galleryInput}
	</td>
      </tr>

      {if !empty($form.error.password.missing)}
      <tr>
	<td colspan="2">
	  {galleryErrorFontColor}
	  {galleryText text="You must enter a password"}
	  {/galleryErrorFontColor}
	</td>
      </tr>
      {/if}

      {if !empty($form.error.invalidPassword)}
      <tr>
	<td colspan="2">
	  {galleryErrorFontColor}
	  {galleryText text="Your login information is incorrect.  Please try again."}
	  {/galleryErrorFontColor}
	</td>
      </tr>
      {/if}

      <tr>
	<td>
	  &nbsp;
	</td>
      </tr>

      <tr>
	<td colspan="2" align="center">
	  {galleryInput type="submit" name="form.action.login"}{galleryText text="Login"}{/galleryInput}
	  {galleryInput type="submit" name="form.action.cancel"}{galleryText text="Cancel"}{/galleryInput}
	</td>
      </tr>

    </table>
  </center>
  {/galleryForm}
