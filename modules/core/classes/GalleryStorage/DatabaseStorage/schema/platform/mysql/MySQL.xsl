<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet 
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:saxon="http://icl.com/saxon"
  extension-element-prefixes="saxon"
  version="1.0">

  <xsl:strip-space elements="*"/>
  <xsl:output method="text"/>
  <xsl:variable name="tablePrefix">g2_</xsl:variable>
  <xsl:variable name="columnPrefix">g_</xsl:variable>

  <xsl:template match="table">
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE <xsl:value-of select="$tablePrefix"/><xsl:value-of select="table-name"/> (
  <xsl:apply-templates select="column"/>
  <xsl:if test="count(//table/key)">
    , 
  </xsl:if>
  <xsl:apply-templates select="key"/>
  <xsl:if test="count(//table/index)">
    , 
  </xsl:if>
  <xsl:apply-templates select="index" xmlns:saxon="http://icl.com/saxon"/>
    ) TYPE=MyISAM;

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

  <xsl:template match="column">
    g_<xsl:value-of select="column-name"/> 
  <xsl:choose>
    <xsl:when test="column-type='INTEGER'">
      int(11)
    </xsl:when>
    <xsl:when test="column-type='STRING'">
      varchar(
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
      text
    </xsl:when>
    <xsl:when test="column-type='BOOLEAN'">
      int(1)
    </xsl:when>
    <xsl:when test="column-type='TIMESTAMP'">
      datetime
    </xsl:when>
    <xsl:otherwise>
      UNKNOWN COLUMN TYPE: <xsl:value-of select="column-type"/>
    </xsl:otherwise>
  </xsl:choose>
  <xsl:if test="not-null">
    NOT NULL
  </xsl:if>
  <xsl:if test="position()!=last()">
    ,
  </xsl:if>
  </xsl:template>

  <xsl:template match="key">
    <xsl:variable name="keyColumnName" saxon:assignable="yes"/>
    UNIQUE KEY (
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
    )
    <xsl:if test="position()!=last()">
      ,
    </xsl:if>
  </xsl:template>
  
  <xsl:template match="index">
    <xsl:variable name="indexColumnName" saxon:assignable="yes"/>
    INDEX (
    <xsl:for-each select="column-name">
      <xsl:value-of select="$columnPrefix"/><xsl:value-of select="."/>

      <saxon:assign name="indexColumnName"><xsl:value-of select="."/></saxon:assign>
      <xsl:for-each select="/table/column">
        <xsl:if test="column-name=$indexColumnName">
          <xsl:if test="column-type='TEXT'">
          (255)
          </xsl:if>
        </xsl:if>
      </xsl:for-each>
    </xsl:for-each>
    )
    <xsl:if test="position()!=last()">
      ,
    </xsl:if>
  </xsl:template>
  
</xsl:stylesheet>
