{*
 * $Revision: 1.9 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<ul>
  <li>
    {if isset($ShowTree.parentIds.$parentIndex)}
      {* Show my link and move on to the next parent *}
      {include file="gallery:modules/debug/templates/ShowTreeEntityLink.tpl"
	       entityId=$ShowTree.parentIds.$parentIndex}
      {include file="gallery:modules/debug/templates/ShowTreeEntity.tpl"
	       parentIndex=$parentIndex+1}
    {else}
      {* Show my link *}
      {include file="gallery:modules/debug/templates/ShowTreeEntityLink.tpl"
	       entityId=$ShowTree.entityId}

      {* Show my data *}
      <table>
	{assign var="entityId" value=$ShowTree.entityId}
	{foreach key=key item=value from=$ShowTree.entityTable.$entityId}
	  {if strcmp($key, '_className')}
	  <tr>
	    <td>
	      <i>{$key}</i>
	    </td><td>
	      {$value}
	    </td>
	  </tr>
	  {/if}
	{/foreach}
      </table>

      {* Show my children *}
      <ul>
	{foreach from=$ShowTree.childIds item=childId}
	  <li>
	    {include file="gallery:modules/debug/templates/ShowTreeEntityLink.tpl"
		     entityId=$childId}
	  </li>
	{/foreach}
      </ul>
    {/if}
  </li>
</ul>
