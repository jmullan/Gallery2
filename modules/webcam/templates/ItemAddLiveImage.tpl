{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gsContents">
  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="Enter a URL below to a webcam or other live image anywhere on the net."}
    </p>

    {if empty($form.imageUrl) || !empty($form.error)}
    <div class="gbDataEntry">
      <h3 class="giTitle">
        {g->text text="URL"}
      </h3>

      <input type="text" size="60" name="{g->formVar var="form[imageUrl]"}" value="{$form.imageUrl}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>

      {if isset($form.error.imageUrl.missing)}
      <div class="giError">
        {g->text text="You must enter a URL to an image"}
      </div>
      {/if}

      {if isset($form.error.imageUrl.invalid)}
      <div class="giError">
        {g->text text="The URL entered must begin with http://"}
      </div>
      {/if}

      {if isset($form.error.imageUrl.unavailable)}
      <div class="giError">
        {g->text text="The image URL you specified is unavailable"}
      </div>
      {/if}

      {if isset($form.error.imageUrl.notImage)}
      <div class="giError">
        {g->text text="The image URL you specified is not an image type"}
      </div>
      {/if}
    </div>

    <input type="submit" name="{g->formVar var="form[action][checkUrl]"}" value="{g->text text="Check URL"}" class="button"/>

    {else}

    <strong>
      {g->text text="URL: %s" arg1=$form.imageUrl}
      <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=core:ItemAdd" arg3="itemId=`$ItemAdmin.item.id`" arg4="addPlugin=ItemAddLiveImage"}">{g->text text="change"}</a>
    </strong><br/>

    <img src="{$form.imageUrl}" alt="{$form.imageUrl}"/>
    <br />

    <input type="hidden" name="{g->formVar var="form[imageUrl]"}" value="{$form.imageUrl}"/>
  
    <div class="gbBottomFlag">
      <div class="gbButtons">
        <input type="submit" name="{g->formVar var="form[action][addLiveImage]"}" value="{g->text text="Add Image"}"/>
      </div>
    </div>
    {/if}
  </div>
</div>
