{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ShowTreeEntityLink.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
    <a href="{g->url arg1="view=debug:ShowTree" arg2="entityId=$entityId"}">
      {g->text text="%d: (%s)" arg1=$entityId arg2=$ShowTree.entityTable.$entityId._className}
    </a>

    {if !empty($ShowTree.isItem.$entityId)}
    <a href="{g->url arg1="itemId=$entityId"}">
      {g->text text="[browse]"}
    </a>
    {/if}

  

