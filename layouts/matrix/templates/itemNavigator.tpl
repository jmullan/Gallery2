{g->linkset}
  {if isset($layout.navigator.first)}
    {g->item}
      {g->title}
	{strip}
	  {g->link params=$layout.navigator.first}
	    {g->text text="first"}
	  {/g->link}
	{/strip}
      {/g->title}
    {/g->item}
  {/if}
  {if isset($layout.navigator.back)}
    {g->item}
      {g->title}
	{strip}
	  {g->link params=$layout.navigator.back}
	    {g->text text="back"}
	  {/g->link}
	{/strip}
      {/g->title}
    {/g->item}
  {/if}
  {if isset($layout.navigator.next)}
    {g->item}
      {g->title}
	{strip}
	  {g->link params=$layout.navigator.next}
	    {g->text text="next"}
	  {/g->link}
	{/strip}
      {/g->title}
    {/g->item}
  {/if}
  {if isset($layout.navigator.last)}
    {g->item}
      {g->title}
	{strip}
	  {g->link params=$layout.navigator.last}
	    {g->text text="last"}
	  {/g->link}
	{/strip}
      {/g->title}
    {/g->item}
  {/if}
{/g->linkset}
