{gallery->form view="$view" method="GET"}
{gallery->input type="hidden" name="form.formName"}SearchSystemContent{/gallery->input}
<a href="{gallery->url view="search:SearchScan" return_view=$return.view return_itemId=$return.itemId}">
{gallery->text text="Search: "}
</a>
{gallery->input type="text" name="form.searchCriteria" size="15"}{/gallery->input}
{gallery->input type="hidden" name="form.useDefaultSettings"}1{/gallery->input}

<!-- Embed the hidden return fields -->
{foreach from=$return key=key item=value}
{gallery->input type="hidden" name=return.$key}{$value}{/gallery->input}
{/foreach}

{/gallery->form}
