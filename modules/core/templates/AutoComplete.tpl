{if $callCount == 1}
<script type="text/javascript" src="{g->url href="lib/javascript/AutoComplete.js"}"></script>
<script type="text/javascript" src="{g->url href="lib/javascript/XmlHttp.js"}"></script>
{/if}
<script type="text/javascript">
  // <![CDATA[
  autoCompleteAttach('{$element}', '{$url}');
  // ]]>
</script>

