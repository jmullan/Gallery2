      {gallery->form view="$view" method="GET"}
      {gallery->input type="hidden" name="formName"}FilterMembers{/gallery->input}
      {gallery->input type="hidden" name="itemId"}{$itemId}{/gallery->input}
  
    <table border="0" cellspacing="0" cellpadding="0" width="100%">
	<tr>
	  <td>
	    <center>
	      {gallery->biggerFontSize}
	      {gallery->text text="Debug Tree"}
	      {/gallery->biggerFontSize}
	    </center>
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>

	    <!-- {foreach from=$parentIds item=parentId} -->
	    <ul>
	      <li> {include file="ShowTreeEntityLink.tpl" entityId=$parentId}
		<!-- {/foreach} -->

		<ul>
		  <li> {include file="ShowTreeEntityLink.tpl" entityId=$entityId}

		    {include file="ShowTreeEntity.tpl" entityId=$entityId}
		    <ul>
		      <!-- {foreach from=$childIds item=childId} -->
		      <li>  {include file="ShowTreeEntityLink.tpl" entityId=$childId}
			<!-- {/foreach} -->
		    </ul>
		</ul>
		<!-- {foreach from=$parentIds item=parentId} -->
	    </ul>
	    <!-- {/foreach} -->
	  </td>
	</tr>

    </table>
    {/gallery->form}

