{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to FileViewerLegalFile.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsHeader">
  <div class="gbTitleBanner">
    <div class="giTitle">
      {g->text text="Source code for file: %s" arg1=$FileViewer.fileName} 
    </div>
  </div>
</div>

<div id="gsAdminContents">
  {foreach name=lineWalker from=$FileViewer.lines item=line}
  {if ($smarty.foreach.lineWalker.iteration == $FileViewer.currentLine)}
  <span style="background: #cdcdcd">
  {/if}

    <span style="min-width:50px">
      <a name="{$smarty.foreach.lineWalker.iteration}">
	{$smarty.foreach.lineWalker.iteration}
      </a>
    </span>
    {$line|escape|replace:" ":"&nbsp;"|replace:"\t":"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"}
    
  {if ($smarty.foreach.lineWalker.iteration == $FileViewer.currentLine)}
    </span>
  {/if}

  <br/>
  {/foreach}
</div>
