#!/usr/bin/perl
#
use strict;
use File::Basename;
use File::Find;
use Cwd;

my %PO_DIRS = ();
my %MO_FILES = ();

my $basedir = cwd();
$basedir =~ s{/(lib|docs|layouts|modules|setup|templates|themes)/.*}{};

find(\&locatePoDir, $basedir);

foreach my $poDir (keys(%PO_DIRS)) {
  chdir $poDir;
  system("gmake install clean");
}

# Make all .mo files binary in CVS.  We could make this smarter by reading
# the CVS/Entries files
#
find(\&locateMoFile, $basedir);
chdir $basedir;
system("cvs admin -kb " . join(" ", keys(%MO_FILES)));

sub locatePoDir {
  my $file = $File::Find::name;
  my $dir  = $File::Find::dir;
  if (basename($dir) eq 'po') {
    next if ($dir =~ m|lib/tools|);
    $PO_DIRS{$dir}++;
  }
}

sub locateMoFile {
  my $file = $File::Find::name;
  my $dir  = $File::Find::dir;
  if ($file =~ /\.mo$/) {
    $file =~ s|$basedir/||;
    $MO_FILES{$file}++;
  }
}
