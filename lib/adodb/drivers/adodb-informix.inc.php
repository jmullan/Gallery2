<?php
/* 
V1.99 21 April 2002 (c) 2000-2002 John Lim. All rights reserved.
  Released under both BSD license and Lesser GPL library license. 
  Whenever there is any discrepancy between the two licenses, 
  the BSD license will take precedence. 
  Set tabs to 4 for best viewing.
  
  Latest version is available at http://php.weblogs.com/
  
  Informix port by Mitchell T. Young (mitch@youngfamily.org)
  
*/
 
class ADODB_informix extends ADOConnection {
	var $databaseType = "informix";	
	var $replaceQuote = "''"; // string to use to replace quotes
	var $fmtDate = "'Y-m-d'";
	var $fmtTimeStamp = "'Y-m-d H:i:s'";
	var $hasInsertID = true;
    var $hasAffectedRows = true;
	var $hasTop = 'first';
	# needs PORT  -- list all tables in current database (including views)
  	var $metaTablesSQL="select name from sysobjects where type='U' or type='V'";
	
	# needs PORT  -- list all columns for a given table
	var $metaColumnsSQL = "select c.name,t.name,c.length from syscolumns c join systypes t on t.xusertype=c.xusertype join sysobjects o on o.id=c.id where o.name='%s'";
	var $concat_operator = '+'; 
	var $lastQuery = false;
	var $has_insertid = true;
	
	var $_autocommit = true;
	
	function ADODB_informix() 
	{
		
		// alternatively, use older method:
		//putenv("DBDATE=Y4MD-");

		// force ISO date format		
		putenv('GL_DATE=%Y-%m-%d');	
	}
 
    function _insertid()
    {
		$sqlca =ifx_getsqlca($this->lastQuery);
		return @$sqlca["sqlerrd1"];
    }

    function _affectedrows()
    {
		if ($this->lastQuery) {
           return ifx_affected_rows ($this->lastQuery);
       } else 
 		return 0;
    }

    function BeginTrans()
	{       
        $this->Execute('BEGIN');
		$this->_autocommit = false;
    	return true;
	}
	
	function CommitTrans()
	{
        $this->Execute('COMMIT');
		$this->_autocommit = true;
		return true;
	}
	
	function RollbackTrans()
	{
         $this->Execute('ROLLBACK');
		 $this->_autocommit = true;
         return true;
	}


	/*	Returns: the last error message from previous database operation
		Note: This function is NOT available for Microsoft SQL Server.	*/	

	function ErrorMsg() {
		$this->_errorMsg = ifx_errormsg();
		return $this->_errorMsg;
	}

	// returns true or false
	function _connect($argHostname, $argUsername, $argPassword, $argDatabasename)
	{
		$dbs = $argDatabasename . "@" . $argHostname;
		$this->_connectionID = ifx_connect($dbs,$argUsername,$argPassword);
		if ($this->_connectionID === false) return false;
		#if ($argDatabasename) return $this->SelectDB($argDatabasename);
		return true;	
	}

	// returns true or false
	function _pconnect($argHostname, $argUsername, $argPassword, $argDatabasename)
	{
		$dbs = $argDatabasename . "@" . $argHostname;
		$this->_connectionID = ifx_pconnect($dbs,$argUsername,$argPassword);
		if ($this->_connectionID === false) return false;
		#if ($argDatabasename) return $this->SelectDB($argDatabasename);
		return true;	
	}
	
	// returns query ID if successful, otherwise false
	function _query($sql,$inputarr)
	{
		$this->lastQuery = ifx_query($sql,$this->_connectionID);
		if ($this->_autocommit) ifx_query('COMMIT',$this->_connectionID);
		return $this->lastQuery;
	}
	
	// returns true or false
	function _close()
	{ 
		$this->lastQuery = false;
		return ifx_close($this->_connectionID);
	}
}

	
/*--------------------------------------------------------------------------------------
	 Class Name: Recordset
--------------------------------------------------------------------------------------*/

class ADORecordset_informix extends ADORecordSet {	

	var $databaseType = "informix";
	var $canSeek = true;
	var $_fieldprops = false;
	
	function ADORecordset_informix($id)
	{
	global $ADODB_FETCH_MODE;
	
		$this->fetchMode = $ADODB_FETCH_MODE;
		return $this->ADORecordSet($id);
	}
	

	
	/*	Returns: an object containing field information. 
		Get column information in the Recordset object. fetchField() can be used in order to obtain information about
		fields in a certain query result. If the field offset isn't specified, the next field that wasn't yet retrieved by
		fetchField() is retrieved.	*/
	function &FetchField($fieldOffset = -1) 
	{
		if (empty($this->_fieldprops)) {
			$fp = ifx_fieldproperties($this->_queryID);
			foreach($fp as $k => $v) {
				$o = new ADOFieldObject;
				$o->name = $k;
				$arr = split(';',$v); //"SQLTYPE;length;precision;scale;ISNULLABLE" 
				$o->type = $arr[0];
				$o->max_length = $arr[1]; 
				$this->_fieldprops[] = $o;
			}
		}
		return $this->_fieldprops[$fieldOffset];
	}
	
	function _initrs()
	{
	    $this->_numOfRows = -1; // ifx_affected_rows not reliable, only returns estimate -- ($ADODB_COUNTRECS)? ifx_affected_rows($this->_queryID):-1;	
		$this->_numOfFields = ifx_num_fields($this->_queryID);
	}
	
	function _seek($row) 
	{
		return ifx_fetch_row($this->_queryID, $row);
	}		

	function _fetch($ignore_fields=false) 
	{
	
		$this->fields = ifx_fetch_row($this->_queryID);
		if (!is_array($this->fields)) return false;
		
		if ($this->fetchMode == ADODB_FETCH_NUM) {
			foreach($this->fields as $v) {
				$arr[] = $v;
			}
			$this->fields = $arr;
		}
		return true;
	}
	
	/*	close() only needs to be called if you are worried about using too much memory while your script
		is running. All associated result memory for the specified result identifier will automatically be freed.	*/
	function _close() 
	{
		return ifx_free_result($this->_queryID);		
	}

}
?>