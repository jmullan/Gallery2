{gallery->bannerbox}
  {gallery->title}
    Gallery Modules
  {/gallery->title}
{/gallery->bannerbox}

{gallery->detailedbox}
  {gallery->description}
    {gallery->text text="Gallery features come as separate modules.  You can download and install modules to add more features to your Gallery, or you can disable features if you don't want to use them.  In order to use a feature, you must install, configure (if necessary) and activate it.  If you don't wish to use a feature, you can deactivate it."}
  {/gallery->description}

  {gallery->body}
    {gallery->table width="100%"}
      {gallery->row}
	{gallery->column header="true"} {gallery->text text="Module Name"} {/gallery->column}
	{gallery->column header="true"} {gallery->text text="Version"} {/gallery->column}
	{gallery->column header="true"} {gallery->text text="Description"} {/gallery->column}
	{gallery->column header="true"} {gallery->text text="Actions"} {/gallery->column}
      {/gallery->row}

      {foreach from=$AdminModules.modules item=module}
	{gallery->row}
	  {gallery->column}
	    {$module.name}
	  {/gallery->column}
	  {gallery->column}
	    {$module.version}
	  {/gallery->column}
	  {gallery->column}
	    {$module.description}
	  {/gallery->column}	
	  {gallery->column}
	    {if (!empty($module.action))}
	      {if (empty($module.action.controller)) }
		{gallery->link url_return="true" url_view='core:SiteAdmin' url_subView=$module.action.view}
		  {$module.action.text}
		{/gallery->link}
	      {else}
		{gallery->link url_controller=$module.action.controller url_moduleName=$module.action.moduleName url_action=$module.action.action}
		  {$module.action.text}
		{/gallery->link}
	      {/if}
	    {else}
	      &nbsp;
	    {/if}
	  {/gallery->column}	
	{/gallery->row}
      {/foreach}
    {/gallery->table}
  {/gallery->body}
{/gallery->detailedbox}
