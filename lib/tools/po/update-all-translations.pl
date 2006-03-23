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
	   'remove-obsolete!' => \$OPTS{'REMOVE_OBSOLETE'},
	   'po=s' => \$OPTS{'PO'},
	   'permissions!' => \$OPTS{'PERMISSIONS'},
	   'cvs-add!' => \$OPTS{'CVS_ADD'});

my %PO_DIRS = ();
my %MO_FILES = ();
my @failures = ();
my @warnings = ();

my $curdir = cwd();
my $basedir = cwd();
$basedir =~ s{(/.*)/(lib|docs|layouts|modules|setup|templates)/.*?$}{$1};

find(\&locatePoDir, $basedir);

if ($OPTS{'PERMISSIONS'}) {
  my $poParam = $OPTS{'PO'} ? "$OPTS{PO}.po" : '*.po';
  foreach my $poDir (keys(%PO_DIRS)) {
    chmod(0755, $poDir);
    chdir $poDir;
    &my_system("chmod 644 $poParam 2> /dev/null");
  }
  print STDERR "Updated permissions for $poParam in " . scalar(keys %PO_DIRS) . " directories.\n";
  exit;
}

if ($OPTS{'CVS_ADD'}) {
  my $poParam = $OPTS{'PO'} ? "$OPTS{PO}.po" : '*.po';
  foreach my $poDir (keys(%PO_DIRS)) {
    my %cvs = ();
    chdir $poDir;
    open(CVS, '<CVS/Entries') or die;
    while (<CVS>) {
      m|^/(.*?)/| and $cvs{$1} = 1;
    }
    close CVS;
    @_ = glob $poParam;
    chdir '..';
    foreach my $poFile (@_) {
      unless (exists $cvs{$poFile}) {
        $_ = 'locale/' . substr($poFile, 0, -3);
        system("cvs add po/$poFile" . (-d $_ ? " $_ $_/LC_MESSAGES" : ''));
        -d $_ and system("cvs add -kb $_/LC_MESSAGES/*.mo");
      }
    }
  }
  exit;
}

my $TARGET = $OPTS{'REMOVE_OBSOLETE'} ? 'all-remove-obsolete' : 'all';
foreach my $poDir (keys(%PO_DIRS)) {
  (my $printableDir = $poDir) =~ s|$basedir.||;
  print STDERR "$printableDir: ";
  unless ($OPTS{'DRY_RUN'}) {
    if (-f "$poDir/GNUmakefile") {
      chdir $poDir;
      my $poParam = '';
      if (!$OPTS{'PO'} || (-f "$OPTS{PO}.po" && ($poParam = 'PO=' . $OPTS{'PO'}))) {
	my_system("$MAKE $TARGET clean QUIET=1 NOCREATE=1 $poParam 2>&1")
	  and print "FAIL!\n"
	    and push(@failures, $poDir);
      } else {
	print "Missing $OPTS{PO}.po!\n";
	push(@warnings, $poDir);
      }
    } else {
      print "Missing GNUmakefile!\n";
      push(@warnings, $poDir);
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

if (@warnings) {
  print "\n\n";
  print scalar(@warnings) . " warnings\n";
  foreach (@warnings) {
    print "\t$_\n";
  }
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
