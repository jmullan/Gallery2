{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div style="width: 100%; text-align: right">
  <img id="AdminPlugins_legend_active_img_{$legendId}" src="{g->url href="modules/core/data/module-active.gif"}" width="13" height="13" alt="" style="display: none" />
  <span id="AdminPlugins_legend_active_msg_{$legendId}" style="margin-right: 10px; vertical-align: top; display: none">
    {g->text text="up to date"}
  </span>

  <img id="AdminPlugins_legend_inactive_img_{$legendId}" src="{g->url href="modules/core/data/module-inactive.gif"}" width="13" height="13" alt="" style="display: none" />
  <span id="AdminPlugins_legend_inactive_msg_{$legendId}" style="margin-right: 10px; vertical-align: top; display: none">
    {g->text text="disabled"}
  </span>

  <img id="AdminPlugins_legend_unupgraded_img_{$legendId}" src="{g->url href="modules/core/data/module-upgrade.gif"}" width="13" height="13" alt="" style="display: none" />
  <span id="AdminPlugins_legend_unupgraded_msg_{$legendId}" style="margin-right: 10px; vertical-align: top; display: none">
    {g->text text="upgrade required"}
  </span>

  <img id="AdminPlugins_legend_uninstalled_img_{$legendId}" src="{g->url href="modules/core/data/module-install.gif"}" width="13" height="13" alt="" style="display: none" />
  <span id="AdminPlugins_legend_uninstalled_msg_{$legendId}" style="margin-right: 10px; vertical-align: top; display: none">
    {g->text text="not installed"}
  </span>

  <img id="AdminPlugins_legend_incompatible_img_{$legendId}" src="{g->url href="modules/core/data/module-incompatible.gif"}" width="13" height="13" alt="" style="display: none" />
  <span id="AdminPlugins_legend_incompatible_msg_{$legendId}" style="margin-right: 10px; vertical-align: top; display: none">
    {g->text text="incompatible"}
  </span>
</div>
