#!/usr/bin/perl
#
use strict;
use File::Basename;
use File::Find;
use Cwd;

my %PO_DIRS = ();

my $basedir = cwd();
$basedir =~ s{/(lib|docs|layouts|modules|setup|templates|themes)/.*}{};

find(\&locatePoDir, $basedir);

foreach my $poDir (keys(%PO_DIRS)) {
  chdir $poDir;
  system("gmake install clean");
}

sub locatePoDir {
  my $file = $File::Find::name;
  my $dir  = $File::Find::dir;
  if (basename($dir) eq 'po') {
    next if ($dir =~ m|lib/tools|);
    $PO_DIRS{$dir}++;
  }
}
