  {gallery->form controller="$controller"}
  <center>
    <table border="1" cellspacing="0" cellpadding="5" width="80%">
      <tr>
	<th> {gallery->text text="Module Name"} </th>
	<th> {gallery->text text="Version"} </th>
	<th> {gallery->text text="Description"} </th>
	<th> {gallery->text text="Actions"} </th>
      </tr>

      {foreach from=$modules item=module}
      <tr>
	<td>
	  {$module.name}
	</td>
	<td>
	  {$module.version}
	</td>
	<td>
	  {$module.description}
	</td>	
	<td>
	  {if (!empty($module.action))}
	  {if (empty($module.action.controller)) }
	  <a href="{gallery->url view='core:SiteAdmin' subView=$module.action.view return_view='core:SiteAdmin' return_subView='core:AdminModules'}">
	    {$module.action.text}
	  </a>
	  {else}
	  <a href="{gallery->url controller=$module.action.controller moduleName=$module.action.moduleName action=$module.action.action}">
	    {$module.action.text}
	  </a>
	  {/if}
	  {else}
	  &nbsp;
	  {/if}
	</td>	
      </tr>
      {/foreach}
    </table>
  </center>
  {/gallery->form}
