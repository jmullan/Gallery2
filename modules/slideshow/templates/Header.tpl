{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to Header.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<title>
  {if isset($SlideShow.item.title)}
    {g->text text="Slideshow for %s" arg1=$SlideShow.item.title}
  {else}
    {g->text text="Slideshow"}
  {/if}
</title>
<script type="text/JavaScript">
    //<![CDATA[
    var agent = navigator.userAgent.toLowerCase();
    var appver = parseInt(navigator.appVersion);
    var bCanBlend = (agent.indexOf('msie') != -1) && (agent.indexOf('opera') == -1) && 
                    (appver >= 4) && (agent.indexOf('msie 4') == -1) && 
                    (agent.indexOf('msie 5.0') == -1);
    var filterNames = new Array(16), filters = new Array(16);
    filterNames[0] = '{g->text text="Blend"}';
    filters[0] = 'progid:DXImageTransform.Microsoft.Fade(duration=1)';
    filterNames[1] = '{g->text text="Blinds"}';
    filters[1] = 'progid:DXImageTransform.Microsoft.Blinds(duration=1,bands=20)';
    filterNames[2] = '{g->text text="Checkerboard"}';
    filters[2] = 'progid:DXImageTransform.Microsoft.Checkerboard(duration=1,squaresX=20,squaresY=20)';
    filterNames[3] = '{g->text text="Diagonal"}';
    filters[3] = 'progid:DXImageTransform.Microsoft.Strips(duration=1,motion=rightdown)';
    filterNames[4] = '{g->text text="Doors"}';
    filters[4] = 'progid:DXImageTransform.Microsoft.Barn(duration=1,orientation=vertical)';
    filterNames[5] = '{g->text text="Gradient"}';
    filters[5] = 'progid:DXImageTransform.Microsoft.GradientWipe(duration=1)';
    filterNames[6] = '{g->text text="Iris"}';
    filters[6] = 'progid:DXImageTransform.Microsoft.Iris(duration=1,motion=out)';
    filterNames[7] = '{g->text text="Pinwheel"}';
    filters[7] = 'progid:DXImageTransform.Microsoft.Wheel(duration=1,spokes=12)';
    filterNames[8] = '{g->text text="Pixelate"}';
    filters[8] = 'progid:DXImageTransform.Microsoft.Pixelate(duration=1,maxSquare=10)';
    filterNames[9] = '{g->text text="Radial"}';
    filters[9] = 'progid:DXImageTransform.Microsoft.RadialWipe(duration=1,wipeStyle=clock)';
    filterNames[10] = '{g->text text="Rain"}';
    filters[10] = 'progid:DXImageTransform.Microsoft.RandomBars(duration=1,orientation=vertical)';
    filterNames[11] = '{g->text text="Slide"}';
    filters[11] = 'progid:DXImageTransform.Microsoft.Slide(duration=1,slideStyle=push)';
    filterNames[12] = '{g->text text="Snow"}';
    filters[12] = 'progid:DXImageTransform.Microsoft.RandomDissolve(duration=1,orientation=vertical)';
    filterNames[13] = '{g->text text="Spiral"}';
    filters[13] = 'progid:DXImageTransform.Microsoft.Spiral(duration=1,gridSizeX=40,gridSizeY=40)';
    filterNames[14] = '{g->text text="Stretch"}';
    filters[14] = 'progid:DXImageTransform.Microsoft.Stretch(duration=1,stretchStyle=push)';
    filterNames[15] = '{g->text text="RANDOM"}';
    filters[15] = 'RANDOM';
    // ]]>
</script>
{g->style}
