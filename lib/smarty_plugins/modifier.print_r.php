<?php

/*
 * Smarty plugin
 * -------------------------------------------------------------
 * Type:     modifier
 * Name:     print_r
 * Purpose:  Dump out the object, reasonably formatted
 * -------------------------------------------------------------
 */
function smarty_modifier_print_r($object) {
    print "<pre>";
    print_r($object);
    print "<pre>";
}

?>
