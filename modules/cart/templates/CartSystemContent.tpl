{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbMenu">

  <h3 class="giTitle">
    {g->text text="Your Cart"}
  </h3>

  <ul>
    <li>
    {g->text one="You have %d item in your cart" many="You have %s items in your cart" count=$CartSystemContent.count arg1=$CartSystemContent.count}
    </li>
  {foreach from=$CartSystemContent.links item=link}
    <li>
      <a href="{g->url params=$link.params}">
        {$link.text}
      </a>
    </li>
  {/foreach}
  </ul>

</div>
