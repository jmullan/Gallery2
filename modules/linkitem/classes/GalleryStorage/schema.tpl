## mysql
# A_GalleryLinkItem_1.0
ALTER TABLE DB_TABLE_PREFIXLinkItem
  MODIFY COLUMN DB_COLUMN_PREFIXlink text NOT NULL;

UPDATE DB_TABLE_PREFIXSchema
  SET DB_COLUMN_PREFIXmajor=1, DB_COLUMN_PREFIXminor=1
  WHERE DB_COLUMN_PREFIXname='LinkItem' AND DB_COLUMN_PREFIXmajor=1 AND DB_COLUMN_PREFIXminor=0;

# GalleryLinkItem
CREATE TABLE DB_TABLE_PREFIXLinkItem(
 DB_COLUMN_PREFIXid int(11) NOT NULL,
 DB_COLUMN_PREFIXlink text NOT NULL,
 PRIMARY KEY(DB_COLUMN_PREFIXid)
) DB_TABLE_TYPE
/*!40100 DEFAULT CHARACTER SET utf8 */;

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('LinkItem', 1, 1);

## postgres
# A_GalleryLinkItem_1.0
ALTER TABLE DB_TABLE_PREFIXLinkItem ADD COLUMN DB_COLUMN_PREFIXlinkTemp text;

UPDATE DB_TABLE_PREFIXLinkItem SET DB_COLUMN_PREFIXlinkTemp = CAST(DB_COLUMN_PREFIXlink AS text);

ALTER TABLE DB_TABLE_PREFIXLinkItem DROP DB_COLUMN_PREFIXlink;

ALTER TABLE DB_TABLE_PREFIXLinkItem RENAME DB_COLUMN_PREFIXlinkTemp to DB_COLUMN_PREFIXlink;

ALTER TABLE DB_TABLE_PREFIXLinkItem ALTER DB_COLUMN_PREFIXlink SET NOT NULL;

UPDATE DB_TABLE_PREFIXSchema
  SET DB_COLUMN_PREFIXmajor=1, DB_COLUMN_PREFIXminor=1
  WHERE DB_COLUMN_PREFIXname='LinkItem' AND DB_COLUMN_PREFIXmajor=1 AND DB_COLUMN_PREFIXminor=0;

# GalleryLinkItem
CREATE TABLE DB_TABLE_PREFIXLinkItem(
 DB_COLUMN_PREFIXid INTEGER NOT NULL,
 DB_COLUMN_PREFIXlink text NOT NULL
);

ALTER TABLE DB_TABLE_PREFIXLinkItem ADD PRIMARY KEY (DB_COLUMN_PREFIXid);

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('LinkItem', 1, 1);

## oracle
# A_GalleryLinkItem_1.0
ALTER TABLE DB_TABLE_PREFIXLinkItem ADD (DB_COLUMN_PREFIXlinkTemp VARCHAR2(4000));

UPDATE DB_TABLE_PREFIXLinkItem SET DB_COLUMN_PREFIXlinkTemp = DB_COLUMN_PREFIXlink;

ALTER TABLE DB_TABLE_PREFIXLinkItem DROP (DB_COLUMN_PREFIXlink);

ALTER TABLE DB_TABLE_PREFIXLinkItem RENAME COLUMN DB_COLUMN_PREFIXlinkTemp TO DB_COLUMN_PREFIXlink;

ALTER TABLE DB_TABLE_PREFIXLinkItem MODIFY (DB_COLUMN_PREFIXlink NOT NULL);

UPDATE DB_TABLE_PREFIXSchema
  SET DB_COLUMN_PREFIXmajor=1, DB_COLUMN_PREFIXminor=1
  WHERE DB_COLUMN_PREFIXname='LinkItem' AND DB_COLUMN_PREFIXmajor=1 AND DB_COLUMN_PREFIXminor=0;

# GalleryLinkItem
CREATE TABLE DB_TABLE_PREFIXLinkItem(
 DB_COLUMN_PREFIXid INTEGER NOT NULL,
 DB_COLUMN_PREFIXlink VARCHAR2(4000) NOT NULL
);

ALTER TABLE DB_TABLE_PREFIXLinkItem
 ADD PRIMARY KEY (DB_COLUMN_PREFIXid)
;

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('LinkItem', 1, 1);

## db2
# A_GalleryLinkItem_1.0
ALTER TABLE DB_TABLE_PREFIXLinkItem ADD COLUMN DB_COLUMN_PREFIXlinkTemp VARCHAR(10000);

UPDATE DB_TABLE_PREFIXLinkItem SET DB_COLUMN_PREFIXlinkTemp = CAST(DB_COLUMN_PREFIXlink AS VARCHAR(10000));

ALTER TABLE DB_TABLE_PREFIXLinkItem DROP DB_COLUMN_PREFIXlink;

ALTER TABLE DB_TABLE_PREFIXLinkItem RENAME DB_COLUMN_PREFIXlinkTemp to DB_COLUMN_PREFIXlink;

ALTER TABLE DB_TABLE_PREFIXLinkItem ALTER DB_COLUMN_PREFIXlink SET NOT NULL;

UPDATE DB_TABLE_PREFIXSchema
  SET DB_COLUMN_PREFIXmajor=1, DB_COLUMN_PREFIXminor=1
  WHERE DB_COLUMN_PREFIXname='LinkItem' AND DB_COLUMN_PREFIXmajor=1 AND DB_COLUMN_PREFIXminor=0;

# GalleryLinkItem
CREATE TABLE DB_TABLE_PREFIXLinkItem(
 DB_COLUMN_PREFIXid INTEGER NOT NULL,
 DB_COLUMN_PREFIXlink VARCHAR(10000) NOT NULL
);

ALTER TABLE DB_TABLE_PREFIXLinkItem ADD PRIMARY KEY (DB_COLUMN_PREFIXid);

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('LinkItem', 1, 1);

## mssql
# A_GalleryLinkItem_1.0
ALTER TABLE DB_TABLE_PREFIXLinkItem ADD DB_COLUMN_PREFIXlinkTemp NVARCHAR(MAX);

UPDATE DB_TABLE_PREFIXLinkItem SET DB_COLUMN_PREFIXlinkTemp = CAST(DB_COLUMN_PREFIXlink AS NVARCHAR(MAX));

ALTER TABLE DB_TABLE_PREFIXLinkItem DROP DB_COLUMN_PREFIXlink;

ALTER TABLE DB_TABLE_PREFIXLinkItem RENAME DB_COLUMN_PREFIXlinkTemp to DB_COLUMN_PREFIXlink;

ALTER TABLE DB_TABLE_PREFIXLinkItem ALTER DB_COLUMN_PREFIXlink SET NOT NULL;

UPDATE DB_TABLE_PREFIXSchema
  SET DB_COLUMN_PREFIXmajor=1, DB_COLUMN_PREFIXminor=1
  WHERE DB_COLUMN_PREFIXname='LinkItem' AND DB_COLUMN_PREFIXmajor=1 AND DB_COLUMN_PREFIXminor=0;

# GalleryLinkItem
CREATE TABLE DB_TABLE_PREFIXLinkItem(
 DB_COLUMN_PREFIXid INT NOT NULL,
 DB_COLUMN_PREFIXlink NVARCHAR(MAX) NOT NULL
);

ALTER TABLE DB_TABLE_PREFIXLinkItem ADD PRIMARY KEY (DB_COLUMN_PREFIXid);

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('LinkItem', 1, 1);

