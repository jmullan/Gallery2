{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbMenu">
  <form id="LoginSystemContent" action="{g->url}" method="post">
    <div>
      {g->hiddenFormVars}
      <input type="hidden" name="{g->formVar var="controller"}" value="core:UserLogin" />
      <input type="hidden" name="{g->formVar var="form[formName]"}" value="UserLogin" />
    </div>

    <p>
      <input class="giFormUsername" type="text" size="10" name="{g->formVar var="form[username]"}"
		id="userName"
		value="{g->text text="Username"}"
		onfocus="var field = document.getElementById('LoginSystemContent').userName; if (field.value == '{g->text text="Username"}') {ldelim} field.value = '' {rdelim}"
		onblur="var field = document.getElementById('LoginSystemContent').userName; if (field.value == '') {ldelim} field.value = '{g->text text="Username"}' {rdelim}"
      /> <br />

      <input class="giFormPassword" type="password" size="10" name="{g->formVar var="form[password]"}"/>
      <input type="submit" name="{g->formVar var="form[action][login]"}" value="{g->text text="Login"}"/>
    </p>
  </form>
</div>
