{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="System Maintenance"} </h2>
</div>

{if isset($status.run)}
<div class="gbBlock">
  {capture name=taskTitle}<b>{$AdminMaintenance.tasks[$status.run.taskId].title}</b>{/capture}
  {if ($status.run.success)}
    <h2 class="giSuccess">
      {g->text text="Completed %s task successfully." arg1=$smarty.capture.taskTitle}
    </h2>
  {else}
    <h2 class="giError">
      {g->text text="The %s task failed to complete successfully." arg1=$smarty.capture.taskTitle}
    </h2>
  {/if}
</div>
{/if}

<div class="gbBlock">
  <table class="gbDataTable" width="100%">
    <tr>
      <th> {g->text text="Task name"} </th>
      <th> {g->text text="Last run"} </th>
      <th> {g->text text="Success/Fail"} </th>
      <th> {g->text text="Action"} </th>
    </tr>
    {foreach from=$AdminMaintenance.tasks key=taskId item=info}
    {cycle values="gbEven,gbOdd" assign="rowClass"}
    <tr class="{$rowClass}">
      <td>
        <span id="task-{$taskId}-toggle"
              class="giBlockToggle gcBackground1 gcBorder2"
              style="border-width: 1px"
              onclick="BlockToggle('task-{$taskId}-description', 'task-{$taskId}-toggle')">+</span>
	{g->text text=$info.title}
      </td>
      <td>
        {if isset($info.timestamp)}
	{g->date format="%X %x" timestamp=$info.timestamp}
        {else}
          {g->text text="Not run yet"}
        {/if}
      </td>
      <td>
        {if isset($info.success)}
        {if $info.success}
        <div class="giSuccess">
          {g->text text="Success"}
        </div>
        {else}
        <div class="giError">
          {g->text text="Failed"}
        </div>
        {/if}
        {else}
          {g->text text="Not run yet"}
        {/if}
      </td>
      <td>
        <a href="{g->url arg1="controller=core:AdminMaintenance" arg2="form[action][runTask]=1" arg3="taskId=`$taskId`"}">{g->text text="run now"}</a>
      </td>
    </tr>
    <tr class="{$rowClass}">
      <td colspan="4" style="width: 100%">
        <span id="task-{$taskId}-description" style="display: none">
          {g->text text=$info.description}
        </span>
      </td>
    </tr>
    {/foreach}
  </table>
</div>
