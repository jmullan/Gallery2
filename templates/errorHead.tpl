{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<title>
  {g->text text="Error"}
</title>
{g->style}
{literal}
<style type="text/css">
  <!--
  .toggle {
    padding-left: .3em;
    padding-right: 0.3em;
    border: solid black 1px;
    background: #eee;
  }
  #trace {
    padding-top: 8px;
  }
  //-->
</style>
<script type="text/javascript">
  <!--
  function toggle(objId, togId) {
    var o = document.getElementById(objId), t = document.getElementById(togId);
    if (o.style.display == 'none') {
      o.style.display = 'block';
      t.innerHTML = '-';
    } else {
      o.style.display = 'none';
      t.innerHTML = '+';
    }
  }
  //-->
</script>
{/literal}
