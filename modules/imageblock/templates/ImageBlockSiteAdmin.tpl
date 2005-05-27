{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Image Block Admin"} </h2>
</div>

{if isset($status.saved)}
<div class="gbBlock"><h2 class="giSuccess">
  {g->text text="Settings saved successfully"}
</h2></div>
{/if}

<div class="gbBlock">
  <h3> {g->text text="Image Blocks"} </h3>

  <input type="checkbox" id="cbRandomImage"
   name="{g->formVar var="form[randomImage]"}" {if $form.randomImage}checked="checked"{/if}/>
 <label for="cbRandomImage">
    {g->text text="Random Image"}
  </label>
  <br/>

  <input type="checkbox" id="cbRecentImage"
   name="{g->formVar var="form[recentImage]"}" {if $form.recentImage}checked="checked"{/if}/>
  <label for="cbRecentImage">
    {g->text text="Newest Image"}
  </label>
  <br/>

  <input type="checkbox" id="cbViewedImage"
   name="{g->formVar var="form[viewedImage]"}" {if $form.viewedImage}checked="checked"{/if}/>
  <label for="cbViewedImage">
    {g->text text="Most Viewed Image"}
  </label>
  <br/>

  <input type="checkbox" id="cbRandomAlbum"
   name="{g->formVar var="form[randomAlbum]"}" {if $form.randomAlbum}checked="checked"{/if}/>
  <label for="cbRandomAlbum">
    {g->text text="Random Album"}
  </label>
  <br/>

  <input type="checkbox" id="cbRecentAlbum"
   name="{g->formVar var="form[recentAlbum]"}" {if $form.recentAlbum}checked="checked"{/if}/>
  <label for="cbRecentAlbum">
    {g->text text="Newest Album"}
  </label>
  <br/>

  <input type="checkbox" id="cbViewedAlbum"
   name="{g->formVar var="form[viewedAlbum]"}" {if $form.viewedAlbum}checked="checked"{/if}/>
  <label for="cbViewedAlbum">
    {g->text text="Most Viewed Album"}
  </label>
  <br/>

  <input type="checkbox" id="cbDailyImage"
   name="{g->formVar var="form[dailyImage]"}" {if $form.dailyImage}checked="checked"{/if}/>
  <label for="cbDailyImage">
    {g->text text="Picture of the Day"}
  </label>
  <br/>

  <input type="checkbox" id="cbWeeklyImage"
   name="{g->formVar var="form[weeklyImage]"}" {if $form.weeklyImage}checked="checked"{/if}/>
  <label for="cbWeeklyImage">
    {g->text text="Picture of the Week"}
  </label>
  <br/>

  <input type="checkbox" id="cbMonthlyImage"
   name="{g->formVar var="form[monthlyImage]"}" {if $form.monthlyImage}checked="checked"{/if}/>
  <label for="cbMonthlyImage">
    {g->text text="Picture of the Month"}
  </label>
  <br/>

  <input type="checkbox" id="cbDailyAlbum"
   name="{g->formVar var="form[dailyAlbum]"}" {if $form.dailyAlbum}checked="checked"{/if}/>
  <label for="cbDailyAlbum">
    {g->text text="Album of the Day"}
  </label>
  <br/>

  <input type="checkbox" id="cbWeeklyAlbum"
   name="{g->formVar var="form[weeklyAlbum]"}" {if $form.weeklyAlbum}checked="checked"{/if}/>
  <label for="cbWeeklyAlbum">
    {g->text text="Album of the Week"}
  </label>
  <br/>

  <input type="checkbox" id="cbMonthlyAlbum"
   name="{g->formVar var="form[monthlyAlbum]"}" {if $form.monthlyAlbum}checked="checked"{/if}/>
  <label for="cbMonthlyAlbum">
    {g->text text="Album of the Month"}
  </label>
  <br/>
</div>

<div class="gbBlock">
  <h3> {g->text text="Show"} </h3>

  <input type="checkbox" id="cbTitle"
   name="{g->formVar var="form[title]"}" {if $form.title}checked="checked"{/if}/>
  <label for="cbTitle">
    {g->text text="Title"}
  </label>
  <br/>

  <input type="checkbox" id="cbDate"
   name="{g->formVar var="form[date]"}" {if $form.date}checked="checked"{/if}/>
  <label for="cbDate">
    {g->text text="Date"}
  </label>
  <br/>

  <input type="checkbox" id="cbViews"
   name="{g->formVar var="form[views]"}" {if $form.views}checked="checked"{/if}/>
  <label for="cbViews">
    {g->text text="View Count"}
  </label>
  <br/>

  <input type="checkbox" id="cbOwner"
   name="{g->formVar var="form[owner]"}" {if $form.owner}checked="checked"{/if}/>
  <label for="cbOwner">
    {g->text text="Owner"}
  </label>
  <br/>
</div>

{if isset($ImageBlockSiteAdmin.list)}
<div class="gbBlock">
  <h3> {g->text text="Frames"} </h3>

  <p class="giDescription">
    <a href="{$ImageBlockSiteAdmin.sampleUrl}"> {g->text text="View samples"} </a>
  </p>

  <table class="gbDataTable"><tr>
    <td>
      {g->text text="Album Frame"}
    </td><td>
      <select name="{g->formVar var="form[albumFrame]"}">
	{html_options options=$ImageBlockSiteAdmin.list selected=$form.albumFrame}
      </select>
    </td>
  </tr><tr>
    <td>
      {g->text text="Photo Frame"}
    </td><td>
      <select name="{g->formVar var="form[itemFrame]"}">
	{html_options options=$ImageBlockSiteAdmin.list selected=$form.itemFrame}
      </select>
    </td>
  </tr></table>
</div>
{/if}

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
</div>

<div class="gbBlock">
  <h3> {g->text text="External Image Block"} </h3>

  <p class="giDescription">
    {g->text text="Use a PHP block like the one shown below to include an image block in a PHP page outside of Gallery."}
  </p>
  <p class="giInfo">
    &lt;?php @readfile('{g->url arg1="view=imageblock.External" arg2="blocks=randomImage" arg3="show=title"}'); ?&gt;
  </p>
  <table class="gbDataTable"><tr>
    <td> {$ImageBlockSiteAdmin.prefix}blocks&nbsp;*</td>
    <td> {g->text text="Pipe(|) separate list chosen from: randomImage, recentImage, viewedImage, randomAlbum, recentAlbum, viewedAlbum, dailyImage, weeklyImage, monthlyImage, dailyAlbum, weeklyAlbum, monthlyAlbum, specificItem"} </td>
  </tr><tr>
    <td> {$ImageBlockSiteAdmin.prefix}show&nbsp;*</td>
    <td> {g->text text="Pipe(|) separated list chosen from: title, date, views, owner, heading, fullSize; the value can also be: none"} </td>
  </tr><tr>
    <td> {$ImageBlockSiteAdmin.prefix}itemId </td>
    <td> {g->text text="Limit the item selection to the subtree of the gallery under the album with the given id; or the id of the item to display when used with specificItem block type"} </td>
  </tr><tr>
    <td> {$ImageBlockSiteAdmin.prefix}maxSize </td>
    <td> {g->text text="Scale images to this maximum size"} </td>
  </tr><tr>
    <td> {$ImageBlockSiteAdmin.prefix}linkTarget </td>
    <td> {g->text text="Add a link target (for example, to open links in a new browser window)"} </td>
  {if isset($ImageBlockSiteAdmin.list)}
  </tr><tr>
    <td> {$ImageBlockSiteAdmin.prefix}itemFrame&nbsp;*</td>
    <td> {g->text text="Image frame to use around images"} </td>
  </tr><tr>
    <td> {$ImageBlockSiteAdmin.prefix}albumFrame&nbsp;*</td>
    <td> {g->text text="Image frame to use around albums"} </td>
  {/if}
  </tr></table>
  <p class="giDescription">
    {g->text text="If any parameter marked with * is omitted then the site default defined above is used."}
  </p>
  {if isset($ImageBlockSiteAdmin.list)}
  <p class="giDescription">
    {g->text text="Image frames require CSS to be displayed correctly. Include the following in the %s section to support image frames." arg1="&lt;head&gt;"}
  </p>
  <p class="giInfo">
    &lt;?php @readfile('{g->url arg1="view=imageblock.ExternalCSS" arg2="frames=wood"}'); ?&gt;
  </p>
  <p class="giDescription">
    {g->text text="Specify the frame id (or pipe separated list of ids) in the frames parameter. Omit the parameter to support the image frames configured above."}
  </p>
  {/if}
</div>
