
<center>
{gallery->successFontColor}
{gallery->biggerFontSize}
{gallery->text text="User '%s' has been successfully deleted."
             arg1=$username}
{/gallery->biggerFontSize}
{/gallery->successFontColor}

<br>
<br>

<a href="{gallery->url view='core:SiteAdmin' subView='core:AdminUsers'}">
{gallery->text text="Return to User Administration"}
</a>

</center>
