{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{literal}
<script type="text/javascript">
  // <![CDATA[
  function updateStatus(title, description, percentComplete) {
    document.getElementById('ImmediateStatus_title').innerHTML = title;
    document.getElementById('ImmediateStatus_description').innerHTML = description;

    var progressMade = Math.round(percentComplete * 100);
    var progressToGo = document.getElementById('ImmediateStatus_progressToGo');

    if (progressMade == 100) {
      progressToGo.style.display = 'none';
    } else {
      progressToGo.style.display = 'inline-block';
      progressToGo.style.width = (100 - progressMade) + "%";
    }

    document.getElementById('ImmediateStatus_progressMade').style.width = progressMade + "%"
  }
  // ]]>
</script>
{/literal}

<div id="gsContent" class="gcBorder1">
<div class="gbBlock gcBackground1">
  <h2> {$ImmediateStatus.pageTitle} </h2>
</div>

<div class="gbBlock">
  <h3>
    <span id="ImmediateStatus_title">{$ImmediateStatus.sectionTitle}</span>
  </h3>

  <p class="giDescription">
    <span id="ImmediateStatus_description">{$ImmediateStatus.sectionDescription}</span>
  </p>

  <table width="100%" cellspacing="0" cellpadding="0"><tr>
    <td id="ImmediateStatus_progressMade" class="giStatusProgressMade" style="width:0%">&nbsp;</td>
    <td id="ImmediateStatus_progressToGo" class="giStatusProgressToGo" style="width:100%; border-left: none')">&nbsp;</td>
  </tr></table>
</div>

{* do not modify the following line *}
SPLIT ON THIS LINE

</div>
