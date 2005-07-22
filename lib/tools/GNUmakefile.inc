# If SAXON_JAR isn't set in the environment,  check for it in a couple of obvious places
SAXON_JAR ?= $(shell for path in /usr/local/share/java/classes/saxon.jar /usr/share/java/saxon.jar /usr/local/share/saxon/saxon.jar; do if test -f $${path}; then echo $${path}; break; fi; done;)

# You can override the SAXON command in the environment
#
# TODO: switch to the 'java -jar' format when Debian gets a version of
#       Saxon new enough to support it.
SAXON ?= java -classpath $(SAXON_JAR):$(TOOLDIR)/CRC32.jar com.icl.saxon.StyleSheet

# You can override the VALIDATOR command also
VALIDATOR ?= rxp -s -V
