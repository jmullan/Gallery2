{gallery->form action_controller="$controller"}
  {gallery->input type="hidden" name="form.formName"}{$form.formName}{/gallery->input}

  {gallery->main}
    {gallery->pathbar}
      {gallery->item}
	{gallery->text text="Your Account"}
      {/gallery->item}
      {if ($UserAdmin.show.userInPathbar)}
	{gallery->item}
	  {$UserAdmin.user.fullName|default:$UserAdmin.user.userName}
	{/gallery->item}
      {/if}
    {/gallery->pathbar}

    {gallery->sidebar}
      {gallery->component}
	{gallery->simplebox}
	  {gallery->body}
	    {gallery->listingbox}
	      {gallery->title}
		{gallery->text text="User Options"}
	      {/gallery->title}
	      {foreach from=$UserAdmin.subViewChoices item=choice}
		{if ($UserAdmin.subViewName == $choice.view)}
		  {gallery->item selected="true"}
		    {$choice.name}
		  {/gallery->item}
		{else}
		  {gallery->item}
		    {gallery->link url_view='core:UserAdmin' url_subView=$choice.view}
		      {$choice.name}
		    {/gallery->link}
		  {/gallery->item}
		{/if}
	      {/foreach}
	    {/gallery->listingbox}
	  {/gallery->body}
	{/gallery->simplebox}
      {/gallery->component}
      
      {gallery->component}
	{gallery->simplebox}
	  {gallery->body}
	    {gallery->listingbox}
	      {gallery->title}
		{gallery->text text="Navigation"}
	      {/gallery->title}
	      {gallery->group}
		{gallery->item}
		  {gallery->link}
		    {gallery->text text="Browse Gallery"}
		  {/gallery->link}
		{/gallery->item}
	      {/gallery->group}
	    {/gallery->listingbox}
	  {/gallery->body}
	{/gallery->simplebox}
      {/gallery->component}
    {/gallery->sidebar}

    {gallery->component}
      {include file=$UserAdmin.viewBodyFile l10Domain=$UserAdmin.viewL10Domain}
    {/gallery->component}

  {/gallery->main}
{/gallery->form}
