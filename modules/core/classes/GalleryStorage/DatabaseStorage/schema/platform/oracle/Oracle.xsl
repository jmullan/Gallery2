<?xml version="1.0" encoding="utf-8"?>
<!-- XXX: This hasn't been tested against the DatabaseChangeDefinition DTD -->

<xsl:stylesheet 
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:saxon="http://icl.com/saxon"
  extension-element-prefixes="saxon"
  version="1.0">

  <xsl:output method="text"/>
  <xsl:variable name="tablePrefix">DB_TABLE_PREFIX</xsl:variable>
  <xsl:variable name="columnPrefix">DB_COLUMN_PREFIX</xsl:variable>

  <!-- TABLE -->
  <xsl:template match="table">
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE <xsl:value-of select="$tablePrefix"/><xsl:value-of select="table-name"/> (
  <xsl:for-each select="column">
    <xsl:call-template name="column"/>
    <xsl:if test="position()!=last()">
      ,
    </xsl:if>
  </xsl:for-each>
    );

  <xsl:for-each select="index">
    CREATE INDEX <xsl:call-template name="indexName"> 
      <xsl:with-param name="num">_I<xsl:value-of select="position()"/></xsl:with-param>
    </xsl:call-template>
    ON <xsl:value-of select="$tablePrefix"/><xsl:value-of select="/table/table-name"/>
    (<xsl:call-template name="indexColumns"/>);

  </xsl:for-each>

  <xsl:for-each select="key">
    <xsl:if test="@primary='true'">
    ALTER TABLE <xsl:value-of select="$tablePrefix"/><xsl:value-of select="/table/table-name"/>
    ADD PRIMARY KEY (<xsl:call-template name="indexColumns"/>);
    </xsl:if>

    <xsl:if test="@primary!='true'">
    CREATE UNIQUE INDEX <xsl:call-template name="indexName"> 
      <xsl:with-param name="num">_U<xsl:value-of select="position()"/></xsl:with-param>
    </xsl:call-template>
    ON <xsl:value-of select="$tablePrefix"/><xsl:value-of select="/table/table-name"/>
    (<xsl:call-template name="indexColumns"/>);
    </xsl:if>
  </xsl:for-each>

    INSERT INTO <xsl:value-of select="$tablePrefix"/>Schema (
      <xsl:value-of select="$columnPrefix"/>name,
      <xsl:value-of select="$columnPrefix"/>major,
      <xsl:value-of select="$columnPrefix"/>minor
      ) VALUES (
      '<xsl:value-of select="table-name"/>',
      <xsl:value-of select="schema/schema-major"/>,
      <xsl:value-of select="schema/schema-minor"/>
      );

  </xsl:template>

  <!-- CHANGE -->
  <xsl:template match="change">

    <xsl:if test="count(add) or count(remove) or count(alter)">
      ALTER TABLE <xsl:value-of select="$tablePrefix"/><xsl:value-of select="table-name"/>

    <xsl:if test="count(add)">
      <xsl:apply-templates select="add"/>
    </xsl:if>

    <xsl:if test="count(add) and (count(remove) or count(alter))">
      , 
    </xsl:if>
    
    <xsl:if test="count(remove)">
      <xsl:apply-templates select="remove"/>
      <xsl:if test="count(alter)">,</xsl:if>
    </xsl:if>
    
    <xsl:if test="count(remove) and count(alter)">
      , 
    </xsl:if>
    
    <xsl:if test="count(alter)">
      <xsl:apply-templates select="alter"/>
    </xsl:if>
      ;
    </xsl:if>

    UPDATE <xsl:value-of select="$tablePrefix"/>Schema 
      SET <xsl:value-of select="$columnPrefix"/>major=<xsl:value-of select="schema-to/schema-major"/>,
          <xsl:value-of select="$columnPrefix"/>minor=<xsl:value-of select="schema-to/schema-minor"/>
      WHERE <xsl:value-of select="$columnPrefix"/>name='<xsl:value-of select="table-name"/>' AND
          <xsl:value-of select="$columnPrefix"/>major=<xsl:value-of select="schema-from/schema-major"/> AND
          <xsl:value-of select="$columnPrefix"/>minor=<xsl:value-of select="schema-from/schema-minor"/>;

  </xsl:template>

  <!-- Change/add -->
  <xsl:template match="add">
    
    <xsl:for-each select="column">
      ADD COLUMN <xsl:call-template name="column"/>
    <xsl:if test="position()!=last()">
      ,
    </xsl:if>
    </xsl:for-each>

    <xsl:if test="count(column) and (count(key) or count(index))">,</xsl:if>

    <xsl:for-each select="key">
      ADD UNIQUE KEY (<xsl:call-template name="key"/>)
    <xsl:if test="position()!=last()">
      ,
    </xsl:if>
    </xsl:for-each>
  
    <xsl:if test="count(key) and count(index)">,</xsl:if>
    
    <xsl:for-each select="indexName">
      ADD INDEX (<xsl:call-template name="indexName"/>)
    <xsl:if test="position()!=last()">
      ,
    </xsl:if>
    </xsl:for-each>
  </xsl:template>

  <!-- Change/remove -->
  <xsl:template match="remove">
    <xsl:for-each select="column">
      DROP COLUMN COLUMN_PREFIX<xsl:value-of select="column-name"/>
    <xsl:if test="position()!=last()">
      ,
    </xsl:if>
    </xsl:for-each>

    <xsl:if test="count(column) and (count(key) or count(index))">,</xsl:if>

    <xsl:for-each select="index">
      DROP INDEX COLUMN_PREFIX<xsl:value-of select="column-name"/>
    <xsl:if test="position()!=last()">
      ,
    </xsl:if>
    </xsl:for-each>

    <xsl:if test="count(key) and count(index)">
      ,
    </xsl:if>
    
    <xsl:for-each select="key">
      DROP KEY COLUMN_PREFIX<xsl:value-of select="column-name"/>
    <xsl:if test="position()!=last()">
      ,
    </xsl:if>
    </xsl:for-each>
  </xsl:template>

  <!-- Change/alter -->
  <xsl:template match="alter">
    <xsl:for-each select="column">
      MODIFY COLUMN <xsl:call-template name="column"/>
    <xsl:if test="position()!=last()">
      ,
    </xsl:if>
    </xsl:for-each>
  </xsl:template>

  <!-- General purpose column definition -->
  <xsl:template name="column">
    <xsl:value-of select="$columnPrefix"/><xsl:value-of select="column-name"/> 
  <xsl:choose>
    <xsl:when test="column-type='INTEGER'">
      INTEGER
    </xsl:when>
    <xsl:when test="column-type='BIT'">
      INTEGER
    </xsl:when>
    <xsl:when test="column-type='STRING'">
      VARCHAR2(
      <xsl:choose>
        <xsl:when test="column-size='SMALL'">
          32
        </xsl:when>
        <xsl:when test="column-size='MEDIUM'">
          128
        </xsl:when>
        <xsl:when test="column-size='LARGE'">
          255
        </xsl:when>
      </xsl:choose>
      )
    </xsl:when>
    <xsl:when test="column-type='TEXT'">
      VARCHAR2(4000)
    </xsl:when>
    <xsl:when test="column-type='BOOLEAN'">
      NUMBER(1)
    </xsl:when>
    <xsl:when test="column-type='TIMESTAMP'">
      TIMESTAMP
    </xsl:when>
    <xsl:otherwise>
      UNKNOWN COLUMN TYPE: <xsl:value-of select="column-type"/>
    </xsl:otherwise>
  </xsl:choose>
  <xsl:if test="not-null[@empty='disallowed']">
    NOT NULL
  </xsl:if>
  </xsl:template>

  <!-- General purpose key definition -->
  <xsl:template name="key">
    <xsl:variable name="keyColumnName" saxon:assignable="yes"/>
    <xsl:for-each select="column-name">
      <xsl:value-of select="$columnPrefix"/><xsl:value-of select="."/>

      <saxon:assign name="keyColumnName"><xsl:value-of select="."/></saxon:assign>
      <xsl:for-each select="/table/column">
        <xsl:if test="column-name=$keyColumnName">
          <xsl:if test="column-type='TEXT'">
          (255)
          </xsl:if>
        </xsl:if>
      </xsl:for-each>

      <xsl:if test="position()!=last()">
        ,
      </xsl:if>
    </xsl:for-each>
  </xsl:template>
  
  <!-- General purpose index definition -->
  <xsl:template name="indexName">
    <xsl:param name="num">0</xsl:param>
    <xsl:value-of select="/table/table-name"/>
    <xsl:value-of select="$num"/>
  </xsl:template>

  <xsl:template name="indexColumns">
    <xsl:for-each select="column-name">
      <xsl:value-of select="$columnPrefix"/><xsl:value-of select="."/>
      <xsl:if test="position()!=last()">
        ,
      </xsl:if>
    </xsl:for-each>
  </xsl:template>

</xsl:stylesheet>
