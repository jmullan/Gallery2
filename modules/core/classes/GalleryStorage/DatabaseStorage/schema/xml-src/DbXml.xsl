<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

  <xsl:output 
    method="xml" 
    indent="yes"
    doctype-system="../../../../tools/dtd/DatabaseDefinition2.0.dtd"/>

  <xsl:template match="class">
    <table>
      <table-name><xsl:value-of select="class-name"/></table-name>

      <xsl:apply-templates select="schema"/>

      <xsl:if test="requires-id">
        <column>
          <column-name>id</column-name>
          <column-type>INTEGER</column-type>
          <column-size>MEDIUM</column-size>
          <not-null/>
        </column>
      </xsl:if>

      <xsl:apply-templates select="map"/>
      <xsl:apply-templates select="member"/>

      <xsl:if test="requires-id">
        <index>
          <column-name>id</column-name>
        </index>
      </xsl:if>

      <xsl:for-each select="member[indexed]">
        <index>
          <column-name><xsl:value-of select="member-name"/></column-name>
        </index>
      </xsl:for-each>

      <xsl:for-each select="member[unique]">
        <key>
          <column-name><xsl:value-of select="member-name"/></column-name>
        </key>
      </xsl:for-each>

      <xsl:for-each select="map/member[unique]">
        <key>
          <column-name><xsl:value-of select="member-name"/></column-name>
        </key>
      </xsl:for-each>

    </table>
  </xsl:template>

  <xsl:template match="schema">
    <schema>
      <schema-major><xsl:value-of select="schema-major"/></schema-major>
      <schema-minor><xsl:value-of select="schema-minor"/></schema-minor>
    </schema>
  </xsl:template>

  <xsl:template match="member">
    <column>
      <column-name><xsl:value-of select="member-name"/></column-name>
      <column-type><xsl:value-of select="member-type"/></column-type>
      <xsl:if test="member-size">
        <column-size><xsl:value-of select="member-size"/></column-size>
      </xsl:if>
      <xsl:if test="not(member-size)">
        <column-size>MEDIUM</column-size>
      </xsl:if>
      <xsl:if test="required">
        <not-null/>
      </xsl:if>
    </column>
  </xsl:template>

  <xsl:template match="map">
    <xsl:for-each select="member">
      <column>
        <column-name><xsl:value-of select="member-name"/></column-name>
        <column-type><xsl:value-of select="member-type"/></column-type>
        <xsl:if test="member-size">
          <column-size><xsl:value-of select="member-size"/></column-size>
        </xsl:if>
        <xsl:if test="not(member-size)">
          <column-size>MEDIUM</column-size>
        </xsl:if>
        <xsl:if test="required">
          <not-null/>
        </xsl:if>
      </column>
    </xsl:for-each>

    <xsl:for-each select="key">
      <key>
        <xsl:for-each select="member-name">
          <column-name><xsl:value-of select="."/></column-name>
        </xsl:for-each>
      </key>
    </xsl:for-each>
  </xsl:template>

</xsl:stylesheet>
