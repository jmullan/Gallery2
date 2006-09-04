{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{assign var="prefix" value=$prefix|default:""}
{assign var="suffix" value=$suffix|default:""}
{*
 * The strip calls in this tpl are to avoid a safari bug where padding-right is lost
 * in floated containers for elements that have whitespace before the closing tag.
 *}
<div>
  <table width="100%" cellpadding="0" cellspacing="0"><tr>
    <td width="20%" align="left">
      <div class="first-and-previous">
	<table cellpadding="0" cellspacing="0"><tr>
	  {if isset($theme.navigator.first)}
	  <td>
	    <div class="buttonFirst"><a href="{g->url params=$theme.navigator.first.urlParams}"
	     title="{g->text text="First"}"></a></div>
	  </td>
	  {else}
	  <td>{g->text text="&nbsp;"}</td>
	  {/if}
	  {if isset($theme.navigator.back) && (!isset($theme.navigator.first) || $theme.navigator.back.urlParams != $theme.navigator.first.urlParams)}
	  <td>
	    <div class="buttonPrev"><a href="{g->url params=$theme.navigator.back.urlParams}"
	     title="{g->text text="Previous"}"></a></div>
	  </td>
	  {/if}
	</tr></table>
      </div>
    </td>
    <td align="center">
      {if $theme.pageType == 'album'}
	{if !empty($theme.jumpRange)}
	<div class="gsPages">
	  {g->block type="core.Pager"}
	</div>
	{else}
	  {g->text text="&nbsp;"}
	{/if}
      {elseif $theme.pageType == 'photo'}
	<table cellpadding="0" cellspacing="0">
	  <tr>
	  {if (isset($links) || isset($theme.itemLinks))}
	    {if !isset($links)}{assign var="links" value=$theme.itemLinks}{/if}

	    {foreach from=$links item=link}
	      {if $link.moduleId == "cart"}
	      <td class="gsActionIcon">
		<div class="buttonCart"><a href="{g->url params=$link.params}"
		 title="{$link.text}"></a></div>
	      </td>
	      {elseif $link.moduleId == "comment"}
		{if $link.params.view == "comment.AddComment" }
		<td class="gsActionIcon">
		  <div class="buttonAddComment"><a href="{g->url params=$link.params}"
		   title="{$link.text}"></a></div>
		</td>
		{/if}
	      {/if}
	    {/foreach}
	  {/if}
	  {if $theme.params.photoProperties}
	  {foreach from=$theme.params.photoBlocks item=block}
	    {if $block.0 == 'exif.ExifInfo'}
	      {if empty($item)} {assign var=item value=$theme.item} {/if}

	      {* Load up the EXIF data *}
	      {g->callback type="exif.LoadExifInfo" itemId=$item.id}

	      {if !empty($block.exif.LoadExifInfo.exifData)}
	      <td class="gsActionIcon">
		<div class="buttonExif"><a href="javascript:void(0);"
		 onclick="toggleExif('photo','exif'); return false;"
		 title="{g->text text="Photo Properties"}"></a></div>
	      </td>
	      {/if}
	    {/if}
	  {/foreach}
	  {/if}
	  {if $theme.params.fullSize && !empty($theme.sourceImage) && count($theme.imageViews) > 1}
	    {capture name="url"}{g->url arg1="view=core.DownloadItem"
				 arg2="itemId=`$theme.sourceImage.id`"}{/capture}
	    <td class="gsActionIcon">
	      <div class="buttonPopup"><a href="{$smarty.capture.url}" target="_blank"
	       onclick="popImage(this.href, '{$theme.item.title|escape:"quotes"}'); return false;"
	       title="{g->text text="Full Size"}"></a></div>
	    </td>
	  {/if}
	  </tr>
	</table>
      {/if}
    </td>
    <td width="20%" align="right" >
      <div class="next-and-last">
	<table cellpadding="0" cellspacing="0"><tr>
	  {if isset($theme.navigator.next) && (!isset($theme.navigator.last) || $theme.navigator.next.urlParams != $theme.navigator.last.urlParams)}
	  <td>
	    <div class="buttonNext"><a href="{g->url params=$theme.navigator.next.urlParams}"
	     title="{g->text text="Next"}"></a></div>
	  </td>
	  {/if}
	  {if isset($theme.navigator.last)}
	  <td>
	    <div class="buttonLast"><a href="{g->url params=$theme.navigator.last.urlParams}"
	     title="{g->text text="Last"}"></a></div>
	  </td>
	  {else}
	  <td>{g->text text="&nbsp;"}</td>
	  {/if}
	</tr></table>
      </div>
    </td>
  </tr></table>
</div>
