{gallery->simplebox}
  {gallery->title}
    {gallery->link url_view="search:SearchScan"}
      {gallery->text text="Search"}
    {/gallery->link}
  {/gallery->title}
  {gallery->body}
    {gallery->form action_view=$SearchSystemContent.view method="GET"}
      {gallery->input type="hidden" name="form.formName"}SearchSystemContent{/gallery->input}
      {gallery->input type="text" name="form.searchCriteria" size="15"}{/gallery->input}
      {gallery->input type="hidden" name="form.useDefaultSettings"}1{/gallery->input}
    {/gallery->form}
  {/gallery->body}
{/gallery->simplebox}
