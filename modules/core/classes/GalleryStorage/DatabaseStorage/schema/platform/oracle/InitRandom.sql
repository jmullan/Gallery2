
-- Initialize and seed the Oracle DBMS_RANDOM package

EXEC DBMS_RANDOM.INITIALIZE(TO_NUMBER(TO_CHAR(SYSTIMESTAMP,'sssssff3')));

