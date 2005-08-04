#!/usr/local/bin/perl
#
# Filter the contents of our MANIFEST files based on an original file list
# and a new file list.  The build process uses this to winnow down the
# file list when we make smaller packages.
#
use strict;
use File::Basename;
use Cwd;
use String::CRC32;
use Getopt::Long;

my $BASEDIR = dirname($0) . '/../../..';
my $FILES = undef;
my $ORIG_FILES = undef;

GetOptions("basedir:s" => \$BASEDIR,
	   "files:s" => \$FILES,
	   "originalFiles:s" => \$ORIG_FILES);
$| = 1;

chdir($BASEDIR);

my %filterFiles;
open(FD, "<$ORIG_FILES") || die;
while (<FD>) {
  chomp;
  s|^gallery2/||;
  $filterFiles{$_}++;
}
close(FD);

open(FD, "<$FILES") || die;
while (<FD>) {
  chomp;
  s|^gallery2/||;
  $filterFiles{$_}--;
}
close(FD);

# Find all manifest files and filter them
chomp(my @manifests = `find . -name MANIFEST`);

foreach my $manifest (@manifests) {
  open(IFD, "<$manifest") || die;
  open(OFD, ">${manifest}.new") || die;
  foreach my $line (<IFD>) {
    if ($line =~ /^(#|R\t)/) {
      print OFD $line;
      next;
    }

    split(/\t/, $line);
    my $file = $_[0];

    if (!defined($filterFiles{$file})) {
      die "Unexpected file <$file>";
    }

    if ($filterFiles{$file}) {
      print OFD $line;
    }
  }
  close(IFD);
  close(OFD);

  if (-s "${manifest}.new" != -s $manifest) {
    rename("${manifest}.new", "${manifest}") || die;
  }
}
