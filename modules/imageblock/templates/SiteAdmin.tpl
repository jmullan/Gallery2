{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to SiteAdmin.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Image Block Admin"}
      </div>
    </div>

    <div class="spacer">
      &nbsp;
    </div>
  </div>

  {if isset($status.saved)}
  <div id="gsStatus">
    <div class="giStatus">
      {g->text text="Settings saved successfully"}
    </div>
  </div>
  {/if}

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Image Blocks"}
    </div>

    <input id="randomImage" type="checkbox" name="{g->formVar var="form[randomImage]"}" {if $form.randomImage}checked="checked"{/if}/>
    <label for="randomImage">
      {g->text text="Random Image"}
    </label>
    <br/>

    <input id="recentImage" type="checkbox" name="{g->formVar var="form[recentImage]"}" {if $form.recentImage}checked="checked"{/if}/>
    <label for="recentImage">
      {g->text text="Newest Image"}
    </label>
    <br/>

    <input id="viewedImage" type="checkbox" name="{g->formVar var="form[viewedImage]"}" {if $form.viewedImage}checked="checked"{/if}/>
    <label for="viewedImage">
      {g->text text="Most Viewed Image"}
    </label>
    <br/>

    <input id="randomAlbum" type="checkbox" name="{g->formVar var="form[randomAlbum]"}" {if $form.randomAlbum}checked="checked"{/if}/>
    <label for="randomAlbum">
      {g->text text="Random Album"}
    </label>
    <br/>

    <input id="recentAlbum" type="checkbox" name="{g->formVar var="form[recentAlbum]"}" {if $form.recentAlbum}checked="checked"{/if}/>
    <label for="recentAlbum">
      {g->text text="Newest Album"}
    </label>
    <br/>

    <input id="viewedAlbum" type="checkbox" name="{g->formVar var="form[viewedAlbum]"}" {if $form.viewedAlbum}checked="checked"{/if}/>
    <label for="viewedAlbum">
      {g->text text="Most Viewed Album"}
    </label>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Show"}
    </div>

    <input id="title" type="checkbox" name="{g->formVar var="form[title]"}" {if $form.title}checked="checked"{/if}/>
    <label for="title">
      {g->text text="Title"}
    </label>
    <br/>

    <input id="date" type="checkbox" name="{g->formVar var="form[date]"}" {if $form.date}checked="checked"{/if}/>
    <label for="date">
      {g->text text="Date"}
    </label>
    <br/>

    <input id="views" type="checkbox" name="{g->formVar var="form[views]"}" {if $form.views}checked="checked"{/if}/>
    <label for="views">
      {g->text text="View Count"}
    </label>
    <br/>

    <input id="owner" type="checkbox" name="{g->formVar var="form[owner]"}" {if $form.owner}checked="checked"{/if}/>
    <label for="owner">
      {g->text text="Owner"}
    </label>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="save"}"/>
    <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="reset"}"/>
  </div>

  <div class="gbAdmin">
    <div class="spacer">
      &nbsp;
    </div>

    <div class="giTitle">
      {g->text text="External Image Block"}
    </div>

    <div class="giDescription">
      {g->text text="Use a PHP block like the one shown below to include an image block in a PHP page outside of Gallery."}
    </div>
    <div class="giInfo">
      &lt;?php include('http://'.$_SERVER['HTTP_HOST'].'/gallery2/main.php?g2_view=imageblock:External&g2_blocks=randomImage&g2_show=title'); ?&gt;
    </div>
    <div class="giDescription">
      {g->text text="g2_blocks is a pipe(|) separate list chosen from: randomImage, recentImage, viewedImage, randomAlbum, recentAlbum, viewedAlbum.  g2_show is a pipe(|) separated list chosen from: title, date, views, owner; the value can also be: none.  If either parameter is omitted the site default defined above is used."}
    </div>
  </div>
</div>
