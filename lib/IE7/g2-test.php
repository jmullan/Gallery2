<!-- dean.edwards/2004 -->
<!-- keeping code tidy! -->
<html xmlns:html="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
<title>IE7</title>
<base href="<?php printf("http://%s%s/", $_SERVER['HTTP_HOST'], dirname(dirname(dirname($_SERVER['PHP_SELF'])))); ?>"/>
<meta http-equiv="content-type" content="text/html; charset=ISO-8859-1"/>
<meta http-equiv="content-style-type" content="text/css"/>
<meta name="author" content="Dean Edwards"/>
<!-- compliance patch for microsoft browsers -->
<!--[if lt IE 7]><link rel="stylesheet" href="lib/IE7/ie7-html.css" type="text/css"/><![endif]-->
<link rel="stylesheet" href="lib/IE7/_private/ie7-page.css" type="text/css"/>
<style type="text/css">
</style>
</head>

<body>
<div class="document">
<div class="header">
<h1><img src="lib/IE7/_private/ie7-logo.gif" width="320" height="40" alt="IE7 { css2: auto; }"/></h1>
<hr />
</div>

<div class="content">

<h2>Test Page</h2>

<h3>Legend</h3>
<style type="text/css">
	#pass {background: white; color: black; height: 20px;}
	#fail {background: black; color: white; height: 20px;}
</style>
<div id="pass"><strong>&nbsp;PASS</strong></div>
<div id="fail"><strong>&nbsp;FAIL</strong></div>

<hr />

<h3>ie7-html.js</h3>
<style type="text/css">
	#ie7-html {background: black; height: 20px;}
	#ie7-html abbr {display: block; background: white; height: 20px;}
</style>
<div class="ie7-test" id="ie7-html"><abbr>&nbsp;</abbr></div>

<h3>ie7-css.js</h3>
<style type="text/css">
	#ie7-css {background: black; height: 20px;}
	#ie7-css > span {display: block; background: white; height: 20px;}
</style>
<div class="ie7-test" id="ie7-css"><span>&nbsp</span></div>

<h3>ie7-css-strict.js</h3>
<style type="text/css">
	#ie7-css-strict {background: black; height: 20px;}
	#ie7-css-strict > span.strict {display: block; background: white; height: 20px;}
	#ie7-css-strict > span {display: block; background: black}
</style>
<div class="ie7-test" id="ie7-css-strict"><span class="strict">&nbsp</span></div>

<h3>ie7-box-model.js</h3>
<style type="text/css">
	#ie7-box-model {background: black; height: 20px; overflow: hidden;}
	#ie7-box-model div.box {position: relative; top: -40px; background: white; height: 40px; border-top: 20px black solid;}
</style>
<div class="ie7-test" id="ie7-box-model"><div class="box"></div></div>

<h3>ie7-png.js</h3>
<style type="text/css">
	#ie7-png {background: white; height: 20px;}
	#ie7-png div.box {height: 20px; background: url(test.png);}
</style>
<div class="ie7-test" id="ie7-png"><div class="box"></div></div>

<h3>ie7-fixed.js</h3>
<style type="text/css">
	#ie7-fixed {background: white; height: 20px;}
	#ie7-fixed div.box {position: fixed; top: -20px; background: black; height: 20px;}
</style>
<div class="ie7-test" id="ie7-fixed"><div class="box"></div></div>
</div>

<div class="footer">
<hr />
</div>
</div>
</body>
</html>
