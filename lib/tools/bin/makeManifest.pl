#!/usr/local/bin/perl
#
# This script traverses the Gallery tree and creates a manifest file that
# contains a list of checksums for files in the distribution.  The installer
# verifies the integrity of the files before proceeding.
# The Debug module also uses this file to figure out whether or not it's
# safe to show you the contents of the file in stack traces.
#
use strict;
use File::Basename;
use Cwd;

chdir(dirname($0) . '/../../..');
my $basedir = cwd();

# Get a list of every file committed to CVS.
#
my @files = ();
&parseCvs($basedir, \@files);

# Strip base dir, sort
map(s{$basedir/}{}, @files);
@files = sort @files;

# Get list of .class, .inc, .php files in basedir/modules/layouts..
my @viewable = grep(m{^(install/.*|modules/.*|layouts/.*|[^/]*)\.(class|inc|php)$}, @files);

# Now generate the checksum file
#
my $out;
open($out, ">lib/MANIFEST.txt") or die;
while (@files) {
  my @set = splice(@files, 0, 10);
  local *FD;
  open(FD, "cksum -o3 @set |") or die;
  while (<FD>) {
    my ($sum, $size, $file) = /^(\d+)\s+(\d+)\s+(.*)$/;
    my $view = grep(m{^\Q$file\E$}, @viewable) ? 1 : 0;
    print $out "$file $sum $size $view\n";
  }
  close FD;
}
close $out;

sub parseCvs {
  my $activeDir = shift;
  my $files = shift;

  my $cvsDir = "$activeDir/CVS";
  die "missing $cvsDir" unless (-d $cvsDir);

  local *FD;
  open(FD, "<$cvsDir/Entries") or die;
  while (<FD>) {
    next if /^D$/;

    if (m|^D/([^/]*)/|) {
      my $target = "$activeDir/$1";
      die "$target not a dir" if (! -d $target);
      &parseCvs($target, $files);
    } elsif (m|/([^/]*)/|) {
      next if m{lib/MANIFEST.txt};
      my $target = "$activeDir/$1";
      die "$target not a file" if (! -f $target);
      push(@$files, $target);
    } else {
      die "Can't parse: $_";
    }
  }
  close FD;
}
