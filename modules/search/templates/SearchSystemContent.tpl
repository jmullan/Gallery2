{g->title}
  {g->link arg1="view=search:SearchScan"}
    {g->text text="Search"}
  {/g->link}
{/g->title}

{g->element}
  {g->form arg1="view=`$SearchSystemContent.view`" method="GET"}
    {g->input type="hidden" name="form[formName]"}SearchSystemContent{/g->input}
    {g->input type="text" name="form[searchCriteria]" size="15"}{/g->input}
    {g->input type="hidden" name="form[useDefaultSettings]"}1{/g->input}
  {/g->form}
{/g->element}
