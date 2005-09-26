TOOLDIR     = ../../../../../../../lib/tools
SRCDIR      = ../xml-out

all: sql

sql:
	php -f $(TOOLDIR)/bin/generate-sql.php $(SRCDIR)

clean:

scrub:
	rm -rf oracle/*.sql
	rm -rf postgres/*.sql
	rm -rf mysql/*.sql
