{galleryForm view="$view" method="GET"}
{galleryInput type="hidden" name="formName"}Search{/galleryInput}
<a href="{galleryUrl view="search:Search" return_view=$return.view return_itemId=$return.itemId}">
{galleryText text="Search: "}
</a>
{galleryInput type="text" name="form.searchCriteria" size="15"}{/galleryInput}
{galleryInput type="hidden" name="form.useDefaultSettings"}1{/galleryInput}

<!-- Embed the hidden return fields -->
{foreach from=$return key=key item=value}
{galleryInput type="hidden" name=$key|string_format:"return.%s"}{$value}{/galleryInput}
{/foreach}

{/galleryForm}
