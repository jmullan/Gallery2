#!/usr/local/bin/perl
#
# This script traverses the Gallery tree and creates a new directory
# called "debug" containing a single file called viewableFiles.txt inside
# every module and layout.  This new file contains a list of every
# PHP file in the module/layout and a checksum for the file.
#
# The Debug module uses this file to figure out whether or not it's
# safe to show you the contents of the file in stack traces.
#
use strict;
use File::Find;
use Cwd;
use Data::Dumper;

my @FILES;
my $basedir = cwd();
$basedir =~ s{/(lib|docs|layouts|modules|setup|templates|themes)/.*}{};
chdir($basedir);

# Get a list of every non-binary file committed to CVS.
#
my @files = ();
&parseCvs($basedir, \@files);

# Strip base dir
map(s{$basedir/}{}, @files);

# Keep everything at the basedir, modules, layouts.  Ditch the rest
@files = grep(m{^(modules/.*|layouts/.*|[^/]*)$}, @files);

# Keep .class, .inc, .php files
@files = grep(m{\.(class|inc|php)$}, @files);

# Separate it out into modules/layouts
#
my %sections;
foreach my $file (@files) {
  if ($file =~ m{^modules/(.*?)/}) {
    push (@{$sections{'modules'}{$1}}, $file);
  } elsif ($file =~ m{^layouts/(.*?)/}) {
    push (@{$sections{'layouts'}{$1}}, $file);
  } else {
    push (@{$sections{'modules'}{'core'}}, $file);
  }
}

# Now generate the checksum file for each section
#
foreach my $section (keys %sections) {
  foreach my $component (keys %{$sections{$section}}) {
    print STDERR "$section/$component...";
    my @files = sort @{$sections{$section}{$component}};
    mkdir("$section/$component/debug");
    system("cksum -o3 @files > $section/$component/debug/viewableFiles.txt");
    print STDERR "\n";
  }
}

sub parseCvs {
  my $activeDir = shift;
  my $files = shift;

  my $cvsDir = "$activeDir/CVS";
  die "missing $cvsDir" unless (-d $cvsDir);

  local *FD;
  open(FD, "<$cvsDir/Entries") || die;
  while (<FD>) {
    next if /^D$/;

    if (m|^D/([^/]*)/|) {
      my $target = "$activeDir/$1";
      die "$target not a dir" if (! -d $target);
      &parseCvs($target, $files);
    } elsif (m|/([^/]*)/|) {
      next if (m|/-kb/$|);
      next if (/viewableFiles.txt/);
      my $target = "$activeDir/$1";
      die "$target not a file" if (! -f $target);
      die if (! -f $target);
      push(@$files, $target);
    } else {
      die "Can't parse: $_";
    }
  }
}
