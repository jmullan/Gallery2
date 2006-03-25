## mysql
# A_G1MigrateMap_1.0
ALTER TABLE DB_TABLE_PREFIXG1MigrateMap
  ADD INDEX DB_TABLE_PREFIXG1MigrateMap_41836(DB_COLUMN_PREFIXg1album, DB_COLUMN_PREFIXg1item);

UPDATE DB_TABLE_PREFIXSchema
  SET DB_COLUMN_PREFIXmajor=1, DB_COLUMN_PREFIXminor=1
  WHERE DB_COLUMN_PREFIXname='G1MigrateMap' AND DB_COLUMN_PREFIXmajor=1 AND DB_COLUMN_PREFIXminor=0;

# G1MigrateMap
CREATE TABLE DB_TABLE_PREFIXG1MigrateMap(
 DB_COLUMN_PREFIXitemId int(11) NOT NULL,
 DB_COLUMN_PREFIXg1album varchar(128) NOT NULL,
 DB_COLUMN_PREFIXg1item varchar(128),
 PRIMARY KEY(DB_COLUMN_PREFIXitemId),
 INDEX DB_TABLE_PREFIXG1MigrateMap_41836(DB_COLUMN_PREFIXg1album, DB_COLUMN_PREFIXg1item)
) TYPE=DB_TABLE_TYPE
/*!40100 DEFAULT CHARACTER SET utf8 */;

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('G1MigrateMap', 1, 1);

## postgres
# A_G1MigrateMap_1.0
CREATE INDEX DB_TABLE_PREFIXG1MigrateMap_41836 ON DB_TABLE_PREFIXG1MigrateMap(DB_COLUMN_PREFIXg1album, DB_COLUMN_PREFIXg1item);

UPDATE DB_TABLE_PREFIXSchema
  SET DB_COLUMN_PREFIXmajor=1, DB_COLUMN_PREFIXminor=1
  WHERE DB_COLUMN_PREFIXname='G1MigrateMap' AND DB_COLUMN_PREFIXmajor=1 AND DB_COLUMN_PREFIXminor=0;

# G1MigrateMap
CREATE TABLE DB_TABLE_PREFIXG1MigrateMap(
 DB_COLUMN_PREFIXitemId INTEGER NOT NULL,
 DB_COLUMN_PREFIXg1album VARCHAR(128) NOT NULL,
 DB_COLUMN_PREFIXg1item VARCHAR(128)
);

ALTER TABLE DB_TABLE_PREFIXG1MigrateMap ADD PRIMARY KEY (DB_COLUMN_PREFIXitemId);

CREATE INDEX DB_TABLE_PREFIXG1MigrateMap_41836 ON DB_TABLE_PREFIXG1MigrateMap(DB_COLUMN_PREFIXg1album, DB_COLUMN_PREFIXg1item);

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('G1MigrateMap', 1, 1);

## oracle
# A_G1MigrateMap_1.0
CREATE INDEX DB_TABLE_PREFIXG1MigrateMap_41836 ON DB_TABLE_PREFIXG1MigrateMap(DB_COLUMN_PREFIXg1album, DB_COLUMN_PREFIXg1item);

UPDATE DB_TABLE_PREFIXSchema
  SET DB_COLUMN_PREFIXmajor=1, DB_COLUMN_PREFIXminor=1
  WHERE DB_COLUMN_PREFIXname='G1MigrateMap' AND DB_COLUMN_PREFIXmajor=1 AND DB_COLUMN_PREFIXminor=0;

# G1MigrateMap
CREATE TABLE DB_TABLE_PREFIXG1MigrateMap(
 DB_COLUMN_PREFIXitemId INTEGER NOT NULL,
 DB_COLUMN_PREFIXg1album VARCHAR2(128) NOT NULL,
 DB_COLUMN_PREFIXg1item VARCHAR2(128)
);

CREATE INDEX DB_TABLE_PREFIXG1MigrateMap_41836
   ON DB_TABLE_PREFIXG1MigrateMap(DB_COLUMN_PREFIXg1album, DB_COLUMN_PREFIXg1item);

ALTER TABLE DB_TABLE_PREFIXG1MigrateMap
 ADD PRIMARY KEY (DB_COLUMN_PREFIXitemId)
;

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('G1MigrateMap', 1, 1);

## db2
# A_G1MigrateMap_1.0
CREATE INDEX DB_TABLE_PREFIXG1Mig6d_41836 ON DB_TABLE_PREFIXG1MigrateMap(DB_COLUMN_PREFIXg1album, DB_COLUMN_PREFIXg1item);

UPDATE DB_TABLE_PREFIXSchema
  SET DB_COLUMN_PREFIXmajor=1, DB_COLUMN_PREFIXminor=1
  WHERE DB_COLUMN_PREFIXname='G1MigrateMap' AND DB_COLUMN_PREFIXmajor=1 AND DB_COLUMN_PREFIXminor=0;

# G1MigrateMap
CREATE TABLE DB_TABLE_PREFIXG1MigrateMap(
 DB_COLUMN_PREFIXitemId INTEGER NOT NULL,
 DB_COLUMN_PREFIXg1album VARCHAR(128) NOT NULL,
 DB_COLUMN_PREFIXg1item VARCHAR(128)
);

ALTER TABLE DB_TABLE_PREFIXG1MigrateMap ADD PRIMARY KEY (DB_COLUMN_PREFIXitemId);

CREATE INDEX DB_TABLE_PREFIXG1Migde_41836
   ON DB_TABLE_PREFIXG1MigrateMap(DB_COLUMN_PREFIXg1album, DB_COLUMN_PREFIXg1item);

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('G1MigrateMap', 1, 1);

