  {galleryForm controller="$controller"}
  <table border="1" cellspacing="0" cellpadding="5" width="100%">
    <tr>
      <th> {galleryText text="Module Name"} </th>
      <th> {galleryText text="Version"} </th>
      <th> {galleryText text="Description"} </th>
      <th> {galleryText text="Actions"} </th>
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
	<a href="{galleryUrl view='core:SiteAdmin' subView=$module.action.view}">
	  {$module.action.text}
	</a>
	{else}
	<a href="{galleryUrl controller=$module.action.controller module=$module.action.module action=$module.action.action}">
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
  {/galleryForm}
