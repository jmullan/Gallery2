
<div class="gbBlock gcBackground1">
  <h2> {ldelim}g->text text="My First Page"{rdelim} </h2>
</div>

<div class="gbBlock">
  Hello, my name is <b>{$authorFullName}</b>.  This is my first Gallery 2 page!
</div>

<div class="gbBlock">
  The item you chose for this action was: <b>{ldelim}$MyPage.item.title|default:$MyPage.item.pathComponent{rdelim}</b>
</div>
<div class="gbBlock">
  {ldelim}if empty($MyPage.value){rdelim}
  There is no value yet for this item.
  {ldelim}else{rdelim}
  The value in the database for this item is: <b>{ldelim}$MyPage.value{rdelim}</b>
  {ldelim}/if{rdelim}
</div>

<form action="{ldelim}g->url{rdelim}" method="post">
  <div>
    {ldelim}g->hiddenFormVars{rdelim}
    <input type="hidden" name="{ldelim}g->formVar var="controller"{rdelim}" value="{$moduleId}.MyPage"/>
    <input type="hidden" name="{ldelim}g->formVar var="form[formName]"{rdelim}" value="{ldelim}$form.formName}"/>
    <input type="hidden" name="{ldelim}g->formVar var="itemId"{rdelim}" value="{ldelim}$MyPage.item.id}"/>
  </div>

  <div class="gbBlock">
    {ldelim}g->text text="Enter a value for this item:"{rdelim}
    <input type="text" name="{ldelim}g->formVar var="form[value]"{rdelim}"/>
  </div>

  <div class="gbBlock gcBackground1">
    <input type="submit" class="inputTypeSubmit"
      name="{ldelim}g->formVar var="form[action][save]"{rdelim}" value="{ldelim}g->text text="Save"{rdelim}"/>
  </div>
</form>


