<?php

/*
 * Smarty plugin
 * -------------------------------------------------------------
 * Type:     modifier
 * Name:     repeat
 * Purpose:  repeat a word a couple of times
 * -------------------------------------------------------------
 */
function smarty_modifier_print_r($object) {
    print "<pre>";
    print_r($object);
    print "<pre>";
}

?>
