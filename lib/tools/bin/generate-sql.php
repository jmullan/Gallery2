<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2005 Bharat Mediratta
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */
if (!empty($_SERVER['SERVER_NAME'])) {
    print "You must run this from the command line\n";
    exit(1);
}

if (crc32("groupId") != 3984689328) {
    print "Your CRC32 is not returning the expected value!\n";
    print "This is probably because you're not on a 64-bit cpu\n";
    print "and we don't yet have a solution to generate the right\n";
    print "index keys on 32-bit cpus.  We'll fix this soon!\n";
    exit(1);
}

require_once(dirname(__FILE__) . '/XmlParser.inc');

foreach (glob('../xml-out/*.xml') as $xmlFile) {
    $p =& new XmlParser();
    $root = $p->parse($xmlFile);

    foreach (array('mysql', 'postgres', 'oracle') as $db) {
	$generatorClass = "${db}Generator";
	$generator = new $generatorClass;
	$output = $generator->createSql($root[0], 0, 0, null) . "\n";
	$base = basename($xmlFile);
	$base = preg_replace('/\.[^\.]*$/', '', $base);

	$fd = fopen("$db/$base.sql", "w");
	fwrite($fd, $output);
	fclose($fd);
    }
}

class BaseGenerator {
    function createSql($node, $index, $lastPeerIndex, $parent) {
	$output = '';

	$child = $node['child'] = isset($node['child']) ? $node['child'] : array();

	switch($node['name']) {
	case 'SCHEMA':
	    $output .= "INSERT INTO DB_TABLE_PREFIXSchema (\n";
	    $output .= " DB_COLUMN_PREFIXname,\n";
	    $output .= " DB_COLUMN_PREFIXmajor,\n";
	    $output .= " DB_COLUMN_PREFIXminor\n";
	    $output .= ") VALUES(";
	    $output .= "'" . $parent['child'][0]['content'] . "', " . $child[0]['content'] . ", " .
		(empty($child[1]['content']) ? '0' : $child[1]['content']);
	    $output .= ");\n\n";
	    break;

	case 'COLUMN':
	    /* column-name, column-type, column-size, not-null? */
	    $output .= ' DB_COLUMN_PREFIX' . $child[0]['content'];
	    $output .= ' ' . $this->columnDefinition($child);
	    break;

	default:
	    $output .= "1. UNIMPLEMLENTED: $node[name]";
	    break;
	}

	return $output;
    }

    function getIndexCrc($columns) {
	$buf = '';
	for ($i = 0; $i < count($columns); $i++) {
	    $buf .= $columns[$i]['content'];
	}
	return crc32($buf) % 100000;
    }

    function getNotNullElement($child) {
	for ($i = 0; $i < count($child); $i++) {
	    if ($child[$i]['name'] == 'NOT-NULL') {
		return $child[$i];
	    }
	}
	return null;
    }

    function setColumnDefinitionMap($map) {
	$this->_columnDefinitionMap = $map;
    }

    function columnDefinition($child, $includeNotNull=true) {
	$output = '';
	$key = $child[1]['content'] . '-' . $child[2]['content'];
	if (isset($this->_columnDefinitionMap[$key])) {
	    $output .= $this->_columnDefinitionMap[$key];
	} else {
	    $output .= "2. UNIMPLEMLENTED: $key";
	}

	if ($includeNotNull) {
	    if ($this->getNotNullElement($child)) {
		$output .= ' NOT NULL';
	    }
	}
	return $output;
    }

    function generateSchemaUpdate($child) {
	$output = "UPDATE DB_TABLE_PREFIXSchema\n";
	$output .= sprintf("  SET DB_COLUMN_PREFIXmajor=%d, DB_COLUMN_PREFIXminor=%d\n",
			   $child[2]['child'][0]['content'],
			   $child[2]['child'][1]['content']);
	$output .= sprintf("  WHERE DB_COLUMN_PREFIXname='%s' AND DB_COLUMN_PREFIXmajor=%d " .
			   "AND DB_COLUMN_PREFIXminor=%d;\n\n",
			   $child[0]['content'],
			   $child[1]['child'][0]['content'],
			   $child[1]['child'][1]['content']);
	return $output;
    }

    function isPrimaryKey($child) {
	return $this->isIndex($child) && !empty($child['attrs']['PRIMARY']);
    }

    function isIndex($child) {
	return $child['name'] == 'INDEX';
    }
}

class MySqlGenerator extends BaseGenerator {
    function MySqlGenerator() {
	$this->setColumnDefinitionMap(
	    array(
		'INTEGER-' => 'int(11)',
		'INTEGER-MEDIUM' => 'int(11)',
		'INTEGER-LARGE' => 'int(11)',
		'BIT-LARGE' => 'int(11)',
		'BIT-MEDIUM' => 'int(11)',
		'STRING-SMALL' => 'varchar(32)',
		'STRING-MEDIUM' => 'varchar(128)',
		'STRING-LARGE' => 'varchar(255)',
		'TEXT-' => 'text',
		'TEXT-MEDIUM' => 'text',
		'BOOLEAN-' => 'int(1)',
		'BOOLEAN-MEDIUM' => 'int(1)',
		'TIMESTAMP-' => 'datetime'));
    }

    function createSql($node, $index, $lastPeerIndex, $parent) {
	$output = '';

	$child = $node['child'] = isset($node['child']) ? $node['child'] : array();
	switch($node['name']) {
	case 'TABLE':
	    /* table-name, schema, column+, (key | index)* */
	    $output .= 'CREATE TABLE DB_TABLE_PREFIX' . $child[0]['content'] . "(\n";
	    for ($i = 2; $i < count($child); $i++) {
		$output .= $this->createSql($child[$i], $i, count($child) - 1, $node);
		if ($i < count($child) - 1) {
		    $output .= ',';
		}
		$output .= "\n";
	    }
	    $output .= ") TYPE=DB_TABLE_TYPE;\n\n";

	    /* Schema info */
	    $output .= $this->createSql($child[1], 0, 0, $node);
	    break;

	case 'ALTER':
	    /* column+ */
	    for ($i = 0; $i < count($child); $i++) {
		$output .= '  MODIFY COLUMN DB_COLUMN_PREFIX' . $child[$i]['child'][0]['content'];
		$output .= ' ' . $this->columnDefinition($child[$i]['child']);
		if ($i < count($child) - 1) {
		    $output .= ",\n";
		}
	    }
	    break;

	case 'CHANGE':
	    /* table-name, schema-from, schema-to, (add, alter, remove)+ */
	    if (count($child) > 3) {
		$output .= 'ALTER TABLE DB_TABLE_PREFIX' . $child[0]['content'] . "\n";
		$count = 0;
		foreach (array('REMOVE', 'ALTER', 'ADD') as $op) {
		    for ($i = 3; $i < count($child); $i++) {
			if ($child[$i]['name'] == $op) {
			    $output .= $this->createSql($child[$i], $i, count($child) - 1, $node);
			    if (++$count < count($child)-3) {
				$output .= ",\n";
			    }
			}
		    }
		}
		$output .= ";\n\n";
	    }
	    $output .= $this->generateSchemaUpdate($child);
	    break;

	case 'ADD':
	    /* (column, key, index)+ */
	    for ($i = 0; $i < count($child); $i++) {
		$c = $child[$i];
		switch($c['name']) {
		case 'COLUMN':
		    /* column-name */
		    $output .= '  ADD COLUMN DB_COLUMN_PREFIX' . $c['child'][0]['content'];
		    $output .= ' ' . $this->columnDefinition($c['child']);
		    break;

		case 'KEY':
		    $output .= '  ADD' . $this->createSql($c, 0, 0, null);
		    break;

		case 'INDEX':
		    /* column-name */
		    $output .= '  ADD INDEX ';
		    $nameKey = strtoupper('name_' . $this->getDbType());
		    $columns = $c['child'];
		    if (isset($c['attrs'][$nameKey])) {
			$output .= $c['attrs'][$nameKey];
		    } else {
			$output .= 'DB_TABLE_PREFIX' . $parent['child'][0]['content'] .
			    '_' . $this->getIndexCrc($columns);
		    }
		    $output .= '(';
		    for ($i = 0; $i < count($columns); $i++) {
			$output .= 'DB_COLUMN_PREFIX' . $columns[$i]['content'];
			if ($i < count($columns) - 1) {
			    $output .= ', ';
			}
		    }
		    $output .= ')';
		    break;

		default:
		    $output .= "3. UNIMPLEMLENTED: ADD $c[name]\n";
		}
		if ($i < count($child) - 1) {
		    $output .= ",\n";
		}
	    }
	    break;

	case 'REMOVE':
	    if (!isset($parent['name'])) {
		$output .= 'DROP TABLE DB_TABLE_PREFIX' . $node['child'][0]['content'] . ";\n\n";
		if ($node['child'][0]['content'] != 'Schema') {
		    $output .= "DELETE FROM DB_TABLE_PREFIXSchema WHERE DB_COLUMN_PREFIXname='" .
			$node['child'][0]['content'] . "';\n\n";
		}
	    } else if ($parent['name'] == 'CHANGE') {
		/* (column-name, key, index)+ */
		foreach ($child as $c) {
		    switch($c['name']) {
		    case 'COLUMN-NAME':
			$output .= '  DROP COLUMN DB_COLUMN_PREFIX' . $c['content'];
			break;

		    case 'KEY':
			$output .= '  DROP KEY DB_COLUMN_PREFIX' . $c['child'][0]['content'];
			break;

		    case 'INDEX':
			/* column-name */
			$output .= '  DROP INDEX ';
			$nameKey = strtoupper('name_' . $this->getDbType());
			if (isset($child[0]['attrs'][$nameKey])) {
			    $output .= $child[0]['attrs'][$nameKey];
			} else {
			    $output .= 'DB_TABLE_PREFIX' . $parent['child'][0]['content'] .
				'_' . $this->getIndexCrc($child[0]['child']);
			}
			break;

		    default:
			$output .= "4. UNIMPLEMENTED: REMOVE $c[name]\n";
		    }
		}
	    }
	    break;

	case 'KEY':
	    /* column-name+ */
	    if (!empty($node['attrs']['PRIMARY'])) {
		$output .= ' PRIMARY KEY(';
	    } else {
		$output .= ' UNIQUE KEY(';
	    }
	    for ($i = 0; $i < count($child); $i++) {
		$output .= 'DB_COLUMN_PREFIX' . $child[$i]['content'];
		if ($i < count($child) - 1) {
		    $output .= ', ';
		}
	    }
	    $output .= ')';
	    break;

	case 'INDEX':
	    /* column-name+ */
	    $crc = $this->getIndexCrc($child);
	    $output .= ' INDEX DB_TABLE_PREFIX' . $parent['child'][0]['content'] . '_' . $crc . '(';
	    for ($i = 0; $i < count($child); $i++) {
		$output .= 'DB_COLUMN_PREFIX' . $child[$i]['content'];
		if ($i < count($child) - 1) {
		    $output .= ', ';
		}
	    }
	    $output .= ')';
	    break;

	default:
	    $output .= parent::createSql($node, $index, $lastPeerIndex, $parent);
	}

	return $output;
    }

    function getDbType() {
	return 'mysql';
    }
}

class PostgresGenerator extends BaseGenerator {
    function PostgresGenerator() {
	$this->setColumnDefinitionMap(
	    array(
		'INTEGER-' => 'INTEGER',
		'INTEGER-MEDIUM' => 'INTEGER',
		'INTEGER-LARGE' => 'INTEGER',
		'BIT-LARGE' => 'BIT(32)',
		'BIT-MEDIUM' => 'BIT(32)',
		'STRING-SMALL' => 'VARCHAR(32)',
		'STRING-MEDIUM' => 'VARCHAR(128)',
		'STRING-LARGE' => 'VARCHAR(255)',
		'TEXT-' => 'text',
		'TEXT-MEDIUM' => 'text',
		'BOOLEAN-' => 'SMALLINT',
		'BOOLEAN-MEDIUM' => 'SMALLINT',
		'TIMESTAMP-' => 'datetime'));
    }

    function createSql($node, $index, $lastPeerIndex, $parent) {
	$output = '';

	$child = $node['child'] = isset($node['child']) ? $node['child'] : array();
	switch($node['name']) {
	case 'CHANGE':
	    /* table-name, schema-from, schema-to, (add, alter, remove)+ */
	    for ($i = 3; $i < count($child); $i++) {
		$output .= $this->createSql($child[$i], $i, count($child) - 1, $node);
	    }
	    $output .= $this->generateSchemaUpdate($child);
	    break;

	case 'REMOVE':
	    if (!isset($parent['name'])) {
		$output .= 'DROP TABLE DB_TABLE_PREFIX' . $node['child'][0]['content'] . ";\n\n";
		if ($node['child'][0]['content'] != 'Schema') {
		    $output .= "DELETE FROM DB_TABLE_PREFIXSchema WHERE DB_COLUMN_PREFIXname='" .
			$node['child'][0]['content'] . "';\n\n";
		}
	    } else if ($parent['name'] == 'CHANGE') {
		/* (column-name, key, index)+ */
		for ($i = 0; $i < count($child); $i++) {
		    $c = $child[$i];
		    switch($c['name']) {
		    case 'COLUMN-NAME':
			/* column-name */
			$output .= 'ALTER TABLE DB_TABLE_PREFIX' . $parent['child'][0]['content'];
			$output .= ' DROP COLUMN DB_COLUMN_PREFIX' . $c['content'];
			$output .= ";\n\n";
			break;

		    case 'KEY':
			$output .= 'ALTER TABLE DB_TABLE_PREFIX' .
			    $parent['child'][0]['content'] . ";\n\n";
			$output .= '  DROP KEY DB_COLUMN_PREFIX' . $c['child'][0]['content'];
			$output .= ";\n\n";
			break;

		    case 'INDEX':
			/* column-name */
			$output .= 'DROP INDEX ';
			$nameKey = strtoupper('name_' . $this->getDbType());
			if (isset($c['attrs'][$nameKey])) {
			    $output .= $c['attrs'][$nameKey];
			} else {
			    $output .= 'DB_TABLE_PREFIX' . $parent['child'][0]['content'] .
				'_' . $this->getIndexCrc($c['child']);
			}
			$output .= ";\n\n";
			break;

		    default:
			$output .= "5. UNIMPLEMENTED: REMOVE $c[name]\n";
		    }
		}
	    }
	    break;

	case 'ADD':
	    /* (column, key, index)+ */
	    foreach ($child as $c) {
		switch($c['name']) {
		case 'COLUMN':
		    /* column-name */
		    $output .= 'ALTER TABLE DB_TABLE_PREFIX' . $parent['child'][0]['content'];
		    $output .= ' ADD COLUMN DB_COLUMN_PREFIX' . $c['child'][0]['content'];
		    $output .= ' ' . $this->columnDefinition($c['child']);
		    $output .= ";\n\n";
		    break;

		case 'KEY':
		    /* column-name+ */
		    $output .= 'ALTER TABLE DB_TABLE_PREFIX' . $parent['child'][0]['content'] .
			' ADD ';
		    if (!empty($c['attrs']['PRIMARY'])) {
			$output .= 'PRIMARY KEY(';
		    } else {
			$output .= 'UNIQUE KEY(';
		    }
		    for ($i = 0; $i < count($child); $i++) {
			$output .= 'DB_COLUMN_PREFIX' . $c['child'][0]['content'];
			if ($i < count($child) - 1) {
			    $output .= ', ';
			}
		    }
		    $output .= ')';
		    $output .= ";\n\n";
		    break;

		case 'INDEX':
		    /* column-name */
		    $output .= 'CREATE INDEX ';
		    $nameKey = strtoupper('name_' . $this->getDbType());
		    $columns = $c['child'];
		    if (isset($c['attrs'][$nameKey])) {
			$output .= $c['attrs'][$nameKey];
		    } else {
			$output .= 'DB_TABLE_PREFIX' . $parent['child'][0]['content'] .
			    '_' . $this->getIndexCrc($columns);
		    }
		    $output .= ' ON ' . 'DB_TABLE_PREFIX' . $parent['child'][0]['content'] . '(';
		    for ($i = 0; $i < count($columns); $i++) {
			$output .= 'DB_COLUMN_PREFIX' . $columns[$i]['content'];
			if ($i < count($columns) - 1) {
			    $output .= ', ';
			}
		    }
		    $output .= ')';
		    $output .= ";\n\n";
		    break;

		default:
		    $output .= "6. UNIMPLEMLENTED: ADD $c[name]\n";
		}
	    }
	    break;

	case 'TABLE':
	    /* table-name, schema, column+, (key | index)* */
	    $output .= 'CREATE TABLE DB_TABLE_PREFIX' . $child[0]['content'] . "(\n";
	    for ($i = 2; $i < count($child); $i++) {
		if ($child[$i]['name'] != 'COLUMN') {
		    $output .= "\n";
		    break;
		}
		if ($i > 2) {
		    $output .= ",\n";
		}
		$output .= $this->createSql($child[$i], $i, count($child) - 1, $node);
		$firstNonColumn = $i + 1;
	    }
	    $output .= ");\n\n";

	    for ($i = $firstNonColumn; $i < count($child); $i++) {
		if ($child[$i]['name'] == 'INDEX') {
		    $crc = $this->getIndexCrc($child[$i]['child']);
		    $output .= 'CREATE INDEX DB_TABLE_PREFIX' . $child[0]['content'] . '_' . $crc .
			' ON DB_TABLE_PREFIX' . $child[0]['content'] . "(";
		    for ($j = 0; $j < count($child[$i]['child']); $j++) {
			$output .= 'DB_COLUMN_PREFIX' . $child[$i]['child'][$j]['content'];
			if ($j < count($child[$i]['child']) - 1) {
			    $output .= ", ";
			}
		    }
		    $output .= ");\n\n";
		} else /* key */ {
		    if (!empty($child[$i]['attrs']['PRIMARY'])) {
			$output .= 'ALTER TABLE DB_TABLE_PREFIX' . $child[0]['content'] .
			    ' ADD PRIMARY KEY (';
			$columns = $child[$i]['child'];
			for ($j = 0; $j < count($columns); $j++) {
			    $output .= 'DB_COLUMN_PREFIX' . $columns[$j]['content'];
			    if ($j < count($columns) - 1) {
				$output .= ', ';
			    }
			}
			$output .= ");\n\n";
		    } else {
			$crc = $this->getIndexCrc($child[$i]['child']);
			$output .= 'CREATE UNIQUE INDEX DB_TABLE_PREFIX' . $child[0]['content'] .
			    '_' . $crc . ' ON DB_TABLE_PREFIX' . $child[0]['content'] . "(";
			for ($j = 0; $j < count($child[$i]['child']); $j++) {
			    $output .= 'DB_COLUMN_PREFIX' . $child[$i]['child'][$j]['content'];
			    if ($j < count($child[$i]['child']) - 1) {
				$output .= ", ";
			    }
			}
			$output .= ");\n\n";
		    }
		}
	    }

	    /* Schema info */
	    $output .= $this->createSql($child[1], 0, 0, $node);
	    break;

	case 'ALTER':
	    /* column+ */
	    for ($i = 0; $i < count($child); $i++) {
		$output .= 'ALTER TABLE DB_TABLE_PREFIX' . $parent['child'][0]['content'] .
		    ' ADD COLUMN DB_COLUMN_PREFIX' . $child[$i]['child'][0]['content'] . 'Temp';
		$output .= ' ' . $this->columnDefinition($child[$i]['child'], false) . ";\n\n";
		$output .= 'UPDATE DB_TABLE_PREFIX' . $parent['child'][0]['content'] .
		    ' SET DB_COLUMN_PREFIX' . $child[$i]['child'][0]['content'] . 'Temp' .
		    ' = CAST(DB_COLUMN_PREFIX' . $child[$i]['child'][0]['content'] . ' AS ' .
		    $this->columnDefinition($child[$i]['child'], false) . ");\n\n";
		$output .= 'ALTER TABLE DB_TABLE_PREFIX' . $parent['child'][0]['content'] .
		    ' DROP DB_COLUMN_PREFIX' . $child[$i]['child'][0]['content'] . ";\n\n";
		$output .= 'ALTER TABLE DB_TABLE_PREFIX' . $parent['child'][0]['content'] .
		    ' RENAME DB_COLUMN_PREFIX' . $child[$i]['child'][0]['content'] . 'Temp' .
		    ' to DB_COLUMN_PREFIX' . $child[$i]['child'][0]['content'] . ";\n\n";
		if ($this->getNotNullElement($child[$i]['child'])) {
		    $output .= 'ALTER TABLE DB_TABLE_PREFIX' . $parent['child'][0]['content'] .
			' ALTER DB_COLUMN_PREFIX' . $child[$i]['child'][0]['content'] .
			" SET NOT NULL;\n\n";
		}
	    }
	    break;

	default:
	    $output .= parent::createSql($node, $index, $lastPeerIndex, $parent);
	}

	return $output;
    }

    function getDbType() {
	return 'postgres';
    }
}

class OracleGenerator extends BaseGenerator {
    function OracleGenerator() {
	$this->setColumnDefinitionMap(
	    array(
		'INTEGER-' => 'INTEGER',
		'INTEGER-MEDIUM' => 'INTEGER',
		'INTEGER-LARGE' => 'INTEGER',
		'BIT-LARGE' => 'BIT(32)',
		'BIT-MEDIUM' => 'BIT(32)',
		'STRING-SMALL' => 'VARCHAR2(32)',
		'STRING-MEDIUM' => 'VARCHAR2(128)',
		'STRING-LARGE' => 'VARCHAR2(255)',
		'TEXT-' => 'VARCHAR2(4000)',
		'TEXT-MEDIUM' => 'VARCHAR2(4000)',
		'BOOLEAN-' => 'NUMBER(1)',
		'BOOLEAN-MEDIUM' => 'NUMBER(1)',
		'TIMESTAMP-' => 'datetime'));
    }

    function createSql($node, $index, $lastPeerIndex, $parent) {
	$output = '';

	$child = $node['child'] = isset($node['child']) ? $node['child'] : array();
	switch($node['name']) {
	case 'CHANGE':
	    /* table-name, schema-from, schema-to, (add, alter, remove)+ */
	    $alters = 0;
	    for ($i = 3; $i < count($child); $i++) {
		if (!$this->isIndex($child[$i]['child'][0]) ||
		    $this->isPrimaryKey($child[$i]['child'][0])) {
		    $alters++;
		}
	    }

	    if ($alters) {
		$output .= 'ALTER TABLE DB_TABLE_PREFIX' . $node['child'][0]['content'] . "\n";
		for ($i = 3; $i < count($child); $i++) {
		    if (!$this->isIndex($child[$i]['child'][0]) ||
			$this->isPrimaryKey($child[$i]['child'][0])) {
			$output .= $this->createSql($child[$i], $i, count($child) - 1, $node);
			$output .= "\n";
		    }
		}
		$output .= ";\n\n";
	    }

	    for ($i = 3; $i < count($child); $i++) {
		if ($this->isIndex($child[$i]['child'][0]) &&
		        !$this->isPrimaryKey($child[$i]['child'][0])) {
		    $output .= $this->createSql($child[$i], $i, count($child) - 1, $node);
		    $output .= ";\n\n";
		}
	    }

	    $output .= $this->generateSchemaUpdate($child);
	    break;

	case 'REMOVE':
	    if (!isset($parent['name'])) {
		$output .= 'DROP TABLE DB_TABLE_PREFIX' . $node['child'][0]['content'] . ";\n\n";
		$output .= "DELETE FROM DB_TABLE_PREFIXSchema WHERE DB_COLUMN_PREFIXname='" .
		    $node['child'][0]['content'] . "';\n\n";
	    } else if ($parent['name'] == 'CHANGE') {
		/* (column-name, key, index)+ */
		foreach ($child as $c) {
		    switch($c['name']) {
		    case 'COLUMN-NAME':
			/* column-name */
			$output .= ' DROP (DB_COLUMN_PREFIX' . $c['content'] . ')';
			break;

		    case 'KEY':
			$output .= '  DROP UNIQUE (DB_COLUMN_PREFIX' .
			    $c['child'][0]['content'] . ')';
			break;

		    case 'INDEX':
			/* column-name */
			$output .= 'DROP INDEX ';
			$nameKey = strtoupper('name_' . $this->getDbType());
			if (isset($child[0]['attrs'][$nameKey])) {
			    $output .= $child[0]['attrs'][$nameKey];
			} else {
			    $output .= 'DB_TABLE_PREFIX' . $parent['child'][0]['content'] .
				'_' . $this->getIndexCrc($child[0]['child']);
			}
			break;

		    default:
			$output .= "7. UNIMPLEMENTED: REMOVE $c[name]\n";
		    }
		}
	    }
	    break;

	case 'ADD':
	    /* (column, key, index)+ */
	    foreach ($child as $c) {
		switch($c['name']) {
		case 'COLUMN':
		    /* column-name */
		    $output .= '  ADD (DB_COLUMN_PREFIX' . $c['child'][0]['content'];
		    $output .= ' ' . $this->columnDefinition($c['child']) . ')';
		    break;

		case 'KEY':
		    /* column-name+ */
		    $output .= '  ADD ';
		    if (!empty($c['attrs']['PRIMARY'])) {
			$output .= 'PRIMARY KEY(';
		    } else {
			$output .= 'UNIQUE KEY(';
		    }
		    for ($i = 0; $i < count($child); $i++) {
			$output .= 'DB_COLUMN_PREFIX' . $c['child'][0]['content'];
			if ($i < count($child) - 1) {
			    $output .= ', ';
			}
		    }
		    $output .= ')';
		    break;

		case 'INDEX':
		    /* column-name */
		    $output .= 'CREATE INDEX ';
		    $nameKey = strtoupper('name_' . $this->getDbType());
		    $columns = $child[0]['child'];
		    if (isset($child[0]['attrs'][$nameKey])) {
			$output .= $child[0]['attrs'][$nameKey];
		    } else {
			$output .= 'DB_TABLE_PREFIX' . $parent['child'][0]['content'] .
			    '_' . $this->getIndexCrc($columns);
		    }
		    $output .= "\n  ON DB_TABLE_PREFIX" . $parent['child'][0]['content'] . '(';
		    for ($i = 0; $i < count($columns); $i++) {
			$output .= 'DB_COLUMN_PREFIX' . $columns[$i]['content'];
			if ($i < count($columns) - 1) {
			    $output .= ', ';
			}
		    }
		    $output .= ')';
		    break;

		default:
		    $output .= "8. UNIMPLEMLENTED: ADD $c[name]\n";
		}
	    }
	    break;

	case 'TABLE':
	    /* table-name, schema, column+, (key | index)* */
	    $output .= 'CREATE TABLE DB_TABLE_PREFIX' . $child[0]['content'] . "(\n";
	    for ($i = 2; $i < count($child); $i++) {
		if ($child[$i]['name'] != 'COLUMN') {
		    $output .= "\n";
		    break;
		}
		if ($i > 2) {
		    $output .= ",\n";
		}
		$output .= $this->createSql($child[$i], $i, count($child) - 1, $node);
		$firstNonColumn = $i + 1;
	    }
	    $output .= ");\n\n";

	    $keyColumns = array();
	    for ($i = $firstNonColumn; $i < count($child); $i++) {
		if ($child[$i]['name'] == 'INDEX') {
		    $crc = $this->getIndexCrc($child[$i]['child']);
		    $output .= 'CREATE INDEX DB_TABLE_PREFIX' . $child[0]['content'] . '_' . $crc .
			"\n  " . ' ON DB_TABLE_PREFIX' . $child[0]['content'] . "(";
		    for ($j = 0; $j < count($child[$i]['child']); $j++) {
			$output .= 'DB_COLUMN_PREFIX' . $child[$i]['child'][$j]['content'];
			if ($j < count($child[$i]['child']) - 1) {
			    $output .= ", ";
			}
		    }
		    $output .= ");\n\n";
		} else {
		    $keys[] = $child[$i];
		}
	    }

	    if (!empty($keys)) {
		$output .= 'ALTER TABLE DB_TABLE_PREFIX' . $child[0]['content'] . "\n";
		foreach ($keys as $key) {
		    if (!empty($key['attrs']['PRIMARY'])) {
			$output .= ' ADD PRIMARY KEY (';
		    } else {
			$output .= ' ADD UNIQUE (';
		    }
		    for ($i = 0; $i < count($key['child']); $i++) {
			$output .= 'DB_COLUMN_PREFIX' . $key['child'][$i]['content'];
			if ($i < count($key['child']) - 1) {
			    $output .= ', ';
			}
		    }
		    $output .= ")\n";
		}
		$output .= ";\n\n";
	    }

	    /* Schema info */
	    $output .= $this->createSql($child[1], 0, 0, $node);
	    break;

	case 'COLUMN':
	    /* column-name, column-type, column-size, not-null? */
	    $output .= ' DB_COLUMN_PREFIX' . $child[0]['content'];
	    $output .= ' ' . $this->columnDefinition($child, false);
	    if ($notNull = $this->getNotNullElement($child)) {
		if (empty($notNull['attrs']['EMPTY']) || $notNull['attrs']['EMPTY'] != 'allowed') {
		    $output .= ' NOT NULL';
		}
	    }
	    break;

	case 'ALTER':
	    /* column+ */
	    $output .= '  MODIFY (';
	    for ($i = 0; $i < count($child); $i++) {
		$output .= 'DB_COLUMN_PREFIX' . $child[$i]['child'][0]['content'];
		$output .= ' ' . $this->columnDefinition($child[$i]['child'], false);
		if ($notNull = $this->getNotNullElement($child[$i]['child'])) {
		    if (empty($notNull['attrs']['EMPTY']) ||
			$notNull['attrs']['EMPTY'] != 'allowed') {
			$output .= ' NOT NULL';
		    }
		}
		if ($i < count($child) - 1) {
		    $output .= ', ';
		}
	    }
	    $output .= ')';
	    break;

	case 'ADD':
	    /* (column, key, index)+ */
	    foreach ($child as $c) {
		switch($c['name']) {
		case 'COLUMN':
		    /* column-name */
		    $output .= '  ADD (DB_COLUMN_PREFIX' . $c['child'][0]['content'];
		    $output .= ' ' . $this->columnDefinition($c['child']) . ')';
		    break;

		default:
		    $output .= "9. UNIMPLEMENTED: ADD $c[name]\n";
		}
		$output .= ";\n\n";
	    }
	    break;

	case 'REMOVE':
	    if (!isset($parent['name'])) {
		$output .= 'DROP TABLE DB_TABLE_PREFIX' . $node['child'][0]['content'] . ";\n\n";
		if ($node['child'][0]['content'] != 'Schema') {
		    $output .= "DELETE FROM DB_TABLE_PREFIXSchema WHERE DB_COLUMN_PREFIXname='" .
			$node['child'][0]['content'] . "';\n\n";
		}
	    } else if ($parent['name'] == 'CHANGE') {
		/* (column-name, key, index)+ */
		foreach ($child as $c) {
		    switch($c['name']) {
		    case 'COLUMN':
			/* column-name */
			$output .= '  DROP DB_COLUMN_PREFIX' . $c['child'][0]['content'];
			break;

		    default:
			$output .= "10. UNIMPLEMENTED: REMOVE $c[name]\n";
		    }
		    $output .= ")";
		}
	    }
	    break;

	default:
	    $output .= parent::createSql($node, $index, $lastPeerIndex, $parent);
	}

	return $output;
    }

    function getDbType() {
	return 'oracle';
    }
}
?>
