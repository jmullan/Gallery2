{g->title}
  {g->link url_view="search:SearchScan"}
    {g->text text="Search"}
  {/g->link}
{/g->title}

{g->element}
  {g->form action_view=$SearchSystemContent.view method="GET"}
    {g->input type="hidden" name="form[formName]"}SearchSystemContent{/g->input}
    {g->input type="text" name="form[searchCriteria]" size="15"}{/g->input}
    {g->input type="hidden" name="form[useDefaultSettings]"}1{/g->input}
  {/g->form}
{/g->element}
