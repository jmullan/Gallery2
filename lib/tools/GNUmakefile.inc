# The Saxon settings are customized for the FreeBSD saxon port.  I'm stuck
# with JDK 1.1.8 on FreeBSD right now.  I could use a more recent JDK but
# I'd have to upgrade to FreeBSD 4.7+ which I don't want to do just yet.
# You can readily override these with your own means of calling Saxon
# by passing -DSAXON_JAR=... -DSAXON=... as a command line argument to make.
#
SAXON_JAR ?= /usr/local/share/java/classes/saxon.jar
SAXON ?= $(JAVA_HOME)/bin/java -classpath $(SAXON_JAR):$(JAVA_HOME)/lib/classes.zip com.icl.saxon.StyleSheet


VALIDATOR ?= rxp -d -s -V

