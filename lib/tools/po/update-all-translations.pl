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
$OPTS{'REPORT_FILE'} = undef;

GetOptions('make-binary!' => \$OPTS{'MAKE_BINARY'},
	   'report:s' => \$OPTS{'REPORT_FILE'});

my %PO_DIRS = ();
my %MO_FILES = ();

my $curdir = cwd();
my $basedir = cwd();
$basedir =~ s{(/.*)/(lib|docs|layouts|modules|setup|templates)/.*?$}{$1};

find(\&locatePoDir, $basedir);

my %report;
foreach my $poDir (keys(%PO_DIRS)) {

  print STDERR "BUILDING IN >> $poDir <<\n";
  chdir $poDir;
  open(FD, "gmake -k install clean 2>&1 |") || die;

  while (<FD>) {
    if ($OPTS{'REPORT_FILE'}) {
      if (/Compiling locale (\w+):/) {
	my $locale = $1;
	chomp(my $line = <FD>);
	$report{$locale}{$poDir}{'translated'} = 0;
	$report{$locale}{$poDir}{'fuzzy'} = 0;
	$report{$locale}{$poDir}{'untranslated'} = 0;
	while ($line !~ /^  \.\.\. (\w+)/) {

	  # 112 translated messages, 93 fuzzy translations, 100 untranslated messages.
	  if ($line =~ /(\d+) translated messages/) {
	    $report{$locale}{$poDir}{'translated'} = $1;
	  }

	  if ($line =~ /(\d+) fuzzy translation/) {
	    $report{$locale}{$poDir}{'fuzzy'} = $1;
	  }

	  if ($line =~ /(\d+) untranslated messages/) {
	    $report{$locale}{$poDir}{'untranslated'} = $1;
	  }

	  push(@{$report{$locale}{$poDir}{'output'}}, $line);
	  $line = <FD>;
	}
	(my $status_raw = $line) =~ /^  \.\.\. (\w+)/;
	if ($status_raw =~ /fail/i) {
	  $report{$locale}{$poDir}{'status'} = 'fail';
	} elsif ($1 =~ /done/i) {
	  $report{$locale}{$poDir}{'status'} = 'success';
	} else {
	  $report{$locale}{$poDir}{'status'} = 'unknown';
	}
      }
    } else {
      print;
    }
  }
  close(FD);
}

if ($OPTS{'REPORT_FILE'}) {
  chdir $curdir;
  print STDERR "Writing file: $OPTS{REPORT_FILE}\n";
  my $fd = gensym;
  open($fd, ">$OPTS{REPORT_FILE}") || die;
  my $now = scalar(gmtime());
  out($fd, 0, "<report date=\"$now GMT\">");
  foreach my $locale (keys %report) {
    out($fd, 1, "<locale id=\"$locale\">");

    foreach my $poDir (keys %PO_DIRS) {
      (my $component = $poDir) =~ s/$basedir\///;
      out($fd, 2, "<component id=\"$component\">");
      if (exists($report{$locale}{$poDir})) {
	my $status = $report{$locale}{$poDir}{'status'};
	if ($status =~ /success/) {
	  out($fd, 3, "<status type=\"success\">$status</status>");
	} else {
	  out($fd, 3, "<status type=\"failure\">$status</status>");
	}
	out($fd, 3, "<translated>$report{$locale}{$poDir}{translated}</translated>");
	out($fd, 3, "<fuzzy>$report{$locale}{$poDir}{fuzzy}</fuzzy>");
	out($fd, 3, "<untranslated>$report{$locale}{$poDir}{untranslated}</untranslated>");

	out($fd, 3, "<output>");
	foreach my $line (@{$report{$locale}{$poDir}{'output'}}) {
	  out($fd, 4, "<line>");
	  out($fd, 5, $line);
	  out($fd, 4, "</line>");
	}
	out($fd, 3, "</output>");
      } else {
	out($fd, 3, "<status type=\"failure\">missing</status>");
      }
      out($fd, 2, "</component>");
    }
    out($fd, 1, "</locale>");
  }
  out($fd, 0, "</report>");
  close($fd);
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
