#!/usr/bin/perl
#
# Merge the creation date and charset from a def.po file with a ref.pot file
# so that msgmerge does not complain.
#
# This is a brutish hack.
#
use strict;

my $def_po = shift;
my $ref_pot = shift;

my @header;
my $saving = 0;
open(FD, "<$def_po") || die;
while (<FD>) {
  chomp;
  if (/^\"Project-Id-Version/) {
    $saving = 1;
  }

  if (/^\s*$/) {
    $saving = 0;
  }

  if ($saving) {
    push(@header, "$_\n");
  }
}
close(FD);

my @lines;
my $replacing = 0;
open(FD, "<$ref_pot") || die;
while (<FD>) {
  if (/^\"Project-Id-Version/) {
    push(@lines, @header);
    $replacing = 1;
  }

  if (/^\s*$/) {
    $replacing = 0;
  }

  unless ($replacing) {
    push(@lines, $_);
  }
}
close(FD);

print @lines;
