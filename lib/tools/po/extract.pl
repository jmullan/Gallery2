#!/usr/local/bin/perl
#
# Perl script to extract strings from all the files and print
# to stdout for use with xgettext.
#
# This script is based on the one provided with the Horde project
# http://www.horde.org/.  As such, it inherits the license from the
# original version.  You can find that license here:
#
# http://cvs.horde.org/co.php/horde/COPYING?r=2.1
#
# I'm not exactly sure what the license restrictions are in this case,
# but I want to give full credit to the original authors:
#
# Copyright 2000-2002 Joris Braakman <jbraakman@yahoo.com>
# Copyright 2001-2002 Chuck Hagenbuch <chuck@horde.org>
# Copyright 2001-2002 Jan Schneider <jan@horde.org>
#
# We've modified the script somewhat to make it work cleanly with the
# way that Gallery embeds internationalized text.
#
# $Id$
#
use FileHandle;
use File::Basename;
use File::Find;
use Cwd;

use strict;

my %strings;
my $exts = '(php|inc|tpl)';

foreach my $moduleDir (@ARGV) {
  find(\&extract, $moduleDir);
}

print join("\n", sort keys %strings), "\n";

sub extract
{
  my $file = $File::Find::name;
  my $dir  = $File::Find::dir;
  my $fd   = new FileHandle;

  if ($file =~ /\.$exts$/) {
    open($fd, basename($file));
    my $data = join('', <$fd>);
    my $text;
    while ($data =~ s/translate\([\"\'](.*?)[\"\']\)//s) {
      $text = $1;
      #$text =~ s/\s+/ /g;
      $strings{"_(\"$text\")"}++;
    }

    while ($data =~ s/({galleryText.*?)(one|many|text)=[\"\'](.*?)[\"\']/$1/s) {
      $text = $3;
      #$text =~ s/\s+/ /g;
      $strings{"_(\"$text\")"}++;
    }
    close($fd);
  }
}
