#!/usr/local/bin/perl
#
use strict;
use File::Find;
use Cwd;

my @FILES;
my $basedir = cwd();
$basedir =~ s{/(lib|docs|layouts|modules|setup|templates|themes)/.*}{};
chdir($basedir);

foreach my $module (<$basedir/modules/*>) {
  next if ($module =~ /CVS$/);
  @FILES = ();

  system("mkdir -p $module/debug");
  find(\&viewableFiles, $module);

  if ($module =~ m|/core|) {
    push(@FILES, "init.php");
    push(@FILES, "main.php");
  }

  foreach my $file (@FILES) {
    system("cksum -o3 @FILES > $module/debug/viewableFiles.txt");
  }
}

sub viewableFiles {
  my $file = $File::Find::name;
  my $dir  = $File::Find::dir;
  $file =~ s|$basedir/||;
  if ($file =~ /(inc|class|php)$/) {
    push(@FILES, $file);
  }
}

