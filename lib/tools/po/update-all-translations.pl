#!/usr/bin/perl
#
# Update all translations and create a report.  This is a very crude hack
# and should really be cleaned up.
#
use strict;
use File::Basename;
use File::Find;
use Cwd;
use Data::Dumper;
use Getopt::Long;
use Symbol;

my %OPTS;
$OPTS{'MAKE_BINARY'} = 0;

GetOptions('make-binary!' => \$OPTS{'MAKE_BINARY'});

my %PO_DIRS = ();
my %MO_FILES = ();

my $curdir = cwd();
my $basedir = cwd();
$basedir =~ s{(/.*)/(lib|docs|layouts|modules|setup|templates)/.*?$}{$1};

find(\&locatePoDir, $basedir);

foreach my $poDir (keys(%PO_DIRS)) {

  print STDERR "BUILDING IN >> $poDir <<\n";
  chdir $poDir;
  system("gmake -k install clean 2>&1") and die;
}

if ($OPTS{'MAKE_BINARY'}) {
  # Make all .mo files binary in CVS.  We could make this smarter by reading
  # the CVS/Entries files
  #
  find(\&locateMoFile, $basedir);
  chdir $basedir;
  system("cvs admin -kb " . join(" ", keys(%MO_FILES)));
}

sub out {
  my ($file, $indent, $msg) = @_;
  print $file " " x ($indent * 4) . $msg . "\n";
}


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
