<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
  <head>
    <title>{g->text text="Package Results"}</title>
    <STYLE TYPE="text/css">
      {include file="gallery:lib/tools/repository/templates/stylesheet.css"}
    </STYLE>
  </head>
  <body>
    <h1>{g->text text="Package Successful"}</h1>
    <div class="section">
      {g->text text="You can review the results below."}
    </div>

    <h2>
      {g->text text="Plugins Packaged"}
    </h2>

    <div class="section">
      <table class="details" id="modules_listing">
        <tr>
          <th> {g->text text="Plugin ID"} </th>
          <th> {g->text text="Written"} </th>
          <th> {g->text text="Skipped"} </th>
        </tr>
        {foreach from=$results item=plugin}
        <tr>
          <td>
            {$plugin.pluginId}
          </td>
          <td>
            {foreach from=$plugin.packageInfo.packagesWritten item=package}
              {$package}<br>
            {/foreach}
          </td>
          <td>
            {foreach from=$plugin.packageInfo.packagesSkipped item=package}
              {$package}<br>
            {/foreach}
          </td>
        </tr>
        {/foreach}
      </table>
    </div>

  </body>
</html>