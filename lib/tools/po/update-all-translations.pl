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
$OPTS{'VERBOSE'} = 0;
$OPTS{'MAKE_BINARY'} = 0;
$OPTS{'PATTERN'} = '';
$OPTS{'DRY_RUN'} = 0;
$OPTS{'REMOVE_OBSOLETE'} = 0;
chomp(my $MAKE = `(which gmake || which make) 2>/dev/null`);
die "Missing make" unless $MAKE;

GetOptions('make-binary!' => \$OPTS{'MAKE_BINARY'},
	   'pattern=s' => \$OPTS{'PATTERN'},
	   'dry-run!' => \$OPTS{'DRY_RUN'},
	   'verbose|v!' => \$OPTS{'VERBOSE'},
	   'remove-obsolete!' => \$OPTS{'REMOVE_OBSOLETE'});

my %PO_DIRS = ();
my %MO_FILES = ();
my @failures = ();

my $curdir = cwd();
my $basedir = cwd();
$basedir =~ s{(/.*)/(lib|docs|layouts|modules|setup|templates)/.*?$}{$1};

find(\&locatePoDir, $basedir);

my $TARGET = $OPTS{'REMOVE_OBSOLETE'} ? 'all-remove-obsolete' : 'all';
foreach my $poDir (keys(%PO_DIRS)) {
  (my $printableDir = $poDir) =~ s|$basedir.||;
  print STDERR "$printableDir: ";
  unless ($OPTS{'DRY_RUN'}) {
    if (-f "$poDir/GNUmakefile") {
      chdir $poDir;
      my_system("$MAKE $TARGET clean QUIET=1 2>&1")
	and print "FAIL!\n"
	  and push(@failures, $poDir);
    } else {
      print "Missing GNUmakefile!\n";
      push(@failures, $poDir);
    }
  }
}

if ($OPTS{'MAKE_BINARY'}) {
  # Make all .mo files binary in CVS.  We could make this smarter by reading
  # the CVS/Entries files
  #
  find(\&locateMoFile, $basedir);
  chdir $basedir;
  my_system("cvs admin -kb " . join(" ", keys(%MO_FILES)));
}

sub my_system {
  my $cmd = shift;
  if ($OPTS{'VERBOSE'}) {
    print STDERR "System: $cmd\n";
  }
  system($cmd);
}

if (@failures) {
  print "\n\n";
  print scalar(@failures) . " failures\n";
  foreach (@failures) {
    print "\t$_\n";
  }
  exit 1;
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
    if ($OPTS{'PATTERN'}) {
      next unless $dir =~ m/$OPTS{'PATTERN'}/;
    }
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
