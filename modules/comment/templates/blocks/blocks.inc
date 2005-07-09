<?php
$blocks = array(
    'ViewComments' => array(
	'description' => 'Show comments',
	'vars' => array(
	    'show' => array(
		'description' => 'Number of comments',
		'type' => 'choice',
		'default' => '3',
		'choices' => array(
		    '1' => '1',
		    '2' => '2',
		    '3' => '3',
		    '4' => '4',
		    '5' => '5',
		    '10' => '10',
		    '20' => '20',
		    '30' => '30',
		    '50' => '50',
		    '100' => '100',
		    '999' => '999')))));
?>