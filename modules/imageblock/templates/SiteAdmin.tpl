{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Image Block Admin"}
      </h2>
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
    <h3 class="giTitle">
      {g->text text="Image Blocks"}
    </h3>
    <ul class="gbAdminList">
      <li>
        <input id="randomImage" type="checkbox" name="{g->formVar var="form[randomImage]"}" {if $form.randomImage}checked="checked"{/if}/>
        <label for="randomImage">
          {g->text text="Random Image"}
        </label>
      </li>

      <li>
        <input id="recentImage" type="checkbox" name="{g->formVar var="form[recentImage]"}" {if $form.recentImage}checked="checked"{/if}/>
        <label for="recentImage">
          {g->text text="Newest Image"}
        </label>
      </li>

      <li>
        <input id="viewedImage" type="checkbox" name="{g->formVar var="form[viewedImage]"}" {if $form.viewedImage}checked="checked"{/if}/>
        <label for="viewedImage">
          {g->text text="Most Viewed Image"}
        </label>
      </li>

      <li>
        <input id="randomAlbum" type="checkbox" name="{g->formVar var="form[randomAlbum]"}" {if $form.randomAlbum}checked="checked"{/if}/>
        <label for="randomAlbum">
          {g->text text="Random Album"}
        </label>
      </li>

      <li>
        <input id="recentAlbum" type="checkbox" name="{g->formVar var="form[recentAlbum]"}" {if $form.recentAlbum}checked="checked"{/if}/>
        <label for="recentAlbum">
          {g->text text="Newest Album"}
        </label>
      </li>

      <li>
        <input id="viewedAlbum" type="checkbox" name="{g->formVar var="form[viewedAlbum]"}" {if $form.viewedAlbum}checked="checked"{/if}/>
        <label for="viewedAlbum">
          {g->text text="Most Viewed Album"}
        </label>
      </li>

      <li>
        <input id="dailyImage" type="checkbox" name="{g->formVar var="form[dailyImage]"}" {if $form.dailyImage}checked="checked"{/if}/>
        <label for="dailyImage">
          {g->text text="Picture of the Day"}
        </label>
      </li>

      <li>
        <input id="weeklyImage" type="checkbox" name="{g->formVar var="form[weeklyImage]"}" {if $form.weeklyImage}checked="checked"{/if}/>
        <label for="weeklyImage">
          {g->text text="Picture of the Week"}
        </label>
      </li>

      <li>
        <input id="monthlyImage" type="checkbox" name="{g->formVar var="form[monthlyImage]"}" {if $form.monthlyImage}checked="checked"{/if}/>
        <label for="monthlyImage">
          {g->text text="Picture of the Month"}
        </label>
      </li>

      <li>
        <input id="dailyAlbum" type="checkbox" name="{g->formVar var="form[dailyAlbum]"}" {if $form.dailyAlbum}checked="checked"{/if}/>
        <label for="dailyAlbum">
          {g->text text="Album of the Day"}
        </label>
      </li>

      <li>
        <input id="weeklyAlbum" type="checkbox" name="{g->formVar var="form[weeklyAlbum]"}" {if $form.weeklyAlbum}checked="checked"{/if}/>
        <label for="weeklyAlbum">
          {g->text text="Album of the Week"}
        </label>
      </li>

      <li>
        <input id="monthlyAlbum" type="checkbox" name="{g->formVar var="form[monthlyAlbum]"}" {if $form.monthlyAlbum}checked="checked"{/if}/>
        <label for="monthlyAlbum">
          {g->text text="Album of the Month"}
        </label>
      </li>
    </ul>

    <h3 class="giTitle">
      {g->text text="Show"}
    </h3>
    <ul class="gbAdminList">
      <li>
        <input id="title" type="checkbox" name="{g->formVar var="form[title]"}" {if $form.title}checked="checked"{/if}/>
        <label for="title">
          {g->text text="Title"}
        </label>
      </li>

      <li>
        <input id="date" type="checkbox" name="{g->formVar var="form[date]"}" {if $form.date}checked="checked"{/if}/>
        <label for="date">
          {g->text text="Date"}
        </label>
      </li>

      <li>
        <input id="views" type="checkbox" name="{g->formVar var="form[views]"}" {if $form.views}checked="checked"{/if}/>
        <label for="views">
          {g->text text="View Count"}
        </label>
      </li>

      <li>
        <input id="owner" type="checkbox" name="{g->formVar var="form[owner]"}" {if $form.owner}checked="checked"{/if}/>
        <label for="owner">
          {g->text text="Owner"}
        </label>
      </li>
    </ul>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
  </div>

  <div class="gbAdmin">

    <h3 class="giTitle">
      {g->text text="External Image Block"}
    </h3>

    <p class="giDescription">
      {g->text text="Use a PHP block like the one shown below to include an image block in a PHP page outside of Gallery."}
    </p>
    <p class="giInfo">
      &lt;?php @readfile('{g->url arg1="view=imageblock:External" arg2="blocks=randomImage" arg3="show=title"}'); ?&gt;
    </p>
    <table class="gbDataTable">
      <tr>
	<td> g2_blocks </td>
	<td> {g->text text="Pipe(|) separate list chosen from: randomImage, recentImage, viewedImage, randomAlbum, recentAlbum, viewedAlbum, dailyImage, weeklyImage, monthlyImage, dailyAlbum, weeklyAlbum, monthlyAlbum, specificItem"} </td>
      </tr><tr>
	<td> g2_show </td>
	<td> {g->text text="Pipe(|) separated list chosen from: title, date, views, owner, heading, fullSize; the value can also be: none"} </td>
      </tr><tr>
	<td> g2_itemId </td>
	<td> {g->text text="Limit the item selection to the subtree of the gallery under the album with the given id; or the id of the item to display when used with specificItem block type"} </td>
      </tr><tr>
	<td> g2_maxSize </td>
	<td> {g->text text="Scale images to this maximum size"} </td>
      </tr><tr>
	<td> g2_linkTarget </td>
	<td> {g->text text="Add a link target (for example, to open links in a new browser window)"} </td>
      </tr>
    </table>
    <p class="giDescription">
      {g->text text="If either g2_blocks or g2_show is omitted the site default defined above is used."}
    </p>
  </div>
</div>
