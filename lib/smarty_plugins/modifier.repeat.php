<?php

/*
 * Smarty plugin
 * -------------------------------------------------------------
 * Type:     modifier
 * Name:     repeat
 * Purpose:  repeat a word a couple of times
 * -------------------------------------------------------------
 */
function smarty_modifier_repeat($string,$times=1)
{
	return str_repeat($string, $times);
}

?>
