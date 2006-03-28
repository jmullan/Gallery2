## mysql
# RssMap
CREATE TABLE DB_TABLE_PREFIXRssMap(
 DB_COLUMN_PREFIXfeedName varchar(128) NOT NULL,
 DB_COLUMN_PREFIXitemId int(11) NOT NULL,
 DB_COLUMN_PREFIXownerId int(11) NOT NULL,
 DB_COLUMN_PREFIXparams text NOT NULL,
 PRIMARY KEY(DB_COLUMN_PREFIXfeedName),
 INDEX DB_TABLE_PREFIXRssMap_75985(DB_COLUMN_PREFIXitemId),
 INDEX DB_TABLE_PREFIXRssMap_21573(DB_COLUMN_PREFIXownerId)
) TYPE=DB_TABLE_TYPE
/*!40100 DEFAULT CHARACTER SET utf8 */;

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('RssMap', 1, 0);

## postgres
# RssMap
CREATE TABLE DB_TABLE_PREFIXRssMap(
 DB_COLUMN_PREFIXfeedName VARCHAR(128) NOT NULL,
 DB_COLUMN_PREFIXitemId INTEGER NOT NULL,
 DB_COLUMN_PREFIXownerId INTEGER NOT NULL,
 DB_COLUMN_PREFIXparams text NOT NULL
);

ALTER TABLE DB_TABLE_PREFIXRssMap ADD PRIMARY KEY (DB_COLUMN_PREFIXfeedName);

CREATE INDEX DB_TABLE_PREFIXRssMap_75985 ON DB_TABLE_PREFIXRssMap(DB_COLUMN_PREFIXitemId);

CREATE INDEX DB_TABLE_PREFIXRssMap_21573 ON DB_TABLE_PREFIXRssMap(DB_COLUMN_PREFIXownerId);

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('RssMap', 1, 0);

## oracle
# RssMap
CREATE TABLE DB_TABLE_PREFIXRssMap(
 DB_COLUMN_PREFIXfeedName VARCHAR2(128) NOT NULL,
 DB_COLUMN_PREFIXitemId INTEGER NOT NULL,
 DB_COLUMN_PREFIXownerId INTEGER NOT NULL,
 DB_COLUMN_PREFIXparams VARCHAR2(4000) NOT NULL
);

CREATE INDEX DB_TABLE_PREFIXRssMap_75985
   ON DB_TABLE_PREFIXRssMap(DB_COLUMN_PREFIXitemId);

CREATE INDEX DB_TABLE_PREFIXRssMap_21573
   ON DB_TABLE_PREFIXRssMap(DB_COLUMN_PREFIXownerId);

ALTER TABLE DB_TABLE_PREFIXRssMap
 ADD PRIMARY KEY (DB_COLUMN_PREFIXfeedName)
;

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('RssMap', 1, 0);

## db2
# RssMap
CREATE TABLE DB_TABLE_PREFIXRssMap(
 DB_COLUMN_PREFIXfeedName VARCHAR(128) NOT NULL,
 DB_COLUMN_PREFIXitemId INTEGER NOT NULL,
 DB_COLUMN_PREFIXownerId INTEGER NOT NULL,
 DB_COLUMN_PREFIXparams VARCHAR(15000) NOT NULL
);

ALTER TABLE DB_TABLE_PREFIXRssMap ADD PRIMARY KEY (DB_COLUMN_PREFIXfeedName);

CREATE INDEX DB_TABLE_PREFIXRssMa42_75985
   ON DB_TABLE_PREFIXRssMap(DB_COLUMN_PREFIXitemId);

CREATE INDEX DB_TABLE_PREFIXRssMa42_21573
   ON DB_TABLE_PREFIXRssMap(DB_COLUMN_PREFIXownerId);

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('RssMap', 1, 0);

## mssql
# RssMap
CREATE TABLE DB_TABLE_PREFIXRssMap(
 DB_COLUMN_PREFIXfeedName NVARCHAR(128) NOT NULL,
 DB_COLUMN_PREFIXitemId INT NOT NULL,
 DB_COLUMN_PREFIXownerId INT NOT NULL,
 DB_COLUMN_PREFIXparams NVARCHAR(4000) NOT NULL
);

ALTER TABLE DB_TABLE_PREFIXRssMap ADD PRIMARY KEY (DB_COLUMN_PREFIXfeedName);

CREATE INDEX DB_TABLE_PREFIXRssMap_75985 ON DB_TABLE_PREFIXRssMap(DB_COLUMN_PREFIXitemId);

CREATE INDEX DB_TABLE_PREFIXRssMap_21573 ON DB_TABLE_PREFIXRssMap(DB_COLUMN_PREFIXownerId);

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('RssMap', 1, 0);

