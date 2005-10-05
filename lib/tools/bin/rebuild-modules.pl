#!/usr/bin/perl
use strict;
chomp(my $CURDIR = `pwd`);
chomp(my $MAKE = `(which gmake || which make) 2>/dev/null`);

if (!$MAKE) {
  die "Unable to locate 'make' or 'gmake'";
}

my @SCHEMAS = <modules/*/classes/GalleryStorage/DatabaseStorage/schema>;
foreach my $schema (@SCHEMAS) {
  (my $module = $schema) =~ s|(modules/.*?)/.*|$1|;
  chdir("$CURDIR/$schema/xml-src") || die "Unable to chdir to $schema/xml-src";
  print STDERR "Validating $module\n";
  if (system("$MAKE -s validate")) {
    exit;
  }
}

foreach my $schema (@SCHEMAS) {
  (my $module = $schema) =~ s|(modules/.*?)/.*|$1|;
  print STDERR "Building $module\n";
  chdir("$CURDIR/$schema") || die;
  system("$MAKE -s clean && $MAKE -s && $MAKE -s clean") and die;
}
