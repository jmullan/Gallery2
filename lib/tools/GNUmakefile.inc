SAXON_JAR ?= /usr/local/share/java/classes/saxon.jar
SAXON ?= java -jar $(SAXON_JAR)
VALIDATOR ?= rxp -d -s -V

