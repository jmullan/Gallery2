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
# way that Gallery embeds internationalized text, so let's tack on our
# own copyrights.
#
# Copyright 2002-2003 Bharat Mediratta <bharat@menalto.com>
#
# $Id$
#
use FileHandle;
use File::Basename;
use File::Find;

use strict;

my %strings;

my $exts = '(class|php|inc|tpl)';

foreach my $moduleDir (@ARGV) {
  find(\&extract, $moduleDir);
}

print join("\n" => sort keys %strings), "\n";

sub extract {
  my $file = $File::Find::name;
  my $dir  = $File::Find::dir;
  my $fd   = new FileHandle;

  if ($file =~ /\.$exts$/) {
    open($fd, basename($file));
    my $data = join('' => <$fd>);

    # grab phrases of this format: translate(".....")
    while ($data =~ /translate\("(.*?[^\\])"\)/sg) {
      my $text = $1;
      $strings{qq{gettext("$text")}}++;
    }

    # grab phrases of this format: translate(array('one' => '...', 'many' => '...'))
    while ($data =~ /translate\(.*?array\('one'\s*=>\s*'(.*?)'.*?'many'\s*=>\s*'(.*?)'.*?\).*?\)/sg) {
      my ($one, $many) = ($1, $2);
      $one =~ s/\"/\\\"/sg;	# escape double-quotes
      $many =~ s/\"/\\\"/sg;	# escape double-quotes
      $strings{qq{ngettext("$one", "$many")}}++;
    }

    # grab phrases of this format: translate('.....')
    while ($data =~ /translate\('(.*?[^\\])'\)/sg) {
      my $text = $1;
      $text =~ s/\"/\\\"/sg;	# escape double-quotes
      $strings{qq{gettext("$text")}}++;
    }

    # grab phrases of this format: i18n(".....")
    while ($data =~ /i18n\("(.*?[^\\])"\)/sg) {
      my $text = $1;
      $strings{qq{gettext("$text")}}++;
    }

    # grab phrases of this format: i18n('.....')
    while ($data =~ /i18n\('(.*?[^\\])'\)/sg) {
      my $text = $1;
      $text =~ s/\"/\\\"/sg;	# escape double-quotes
      $strings{qq{gettext("$text")}}++;
    }

    # grab phrases of this format {g->text ..... }
    while ($data =~ /(\{\s*g->text\s+.*?[^\\]\})/sg) {
      my $string = $1;
      my $text;
      my $one;
      my $many;

      # text=.....
      if ($string =~ /text="(.*?[^\\])"/s) {
	$text = $1;
      }
      elsif ($string =~ /text='(.*?)'/s) {
	$text = $1;
	$text =~ s/\"/\\\"/sg;	# escape double-quotes
      }

      # one = .....
      if ($string =~ /\s+one="(.*?[^\\])"/s) {
	$one = $1;
      }
      elsif ($string =~ /\s+one='(.*?)'/s) {
	$one = $1;
	$one =~ s/\"/\\\"/sg;	# escape double-quotes
      }

      # many = .....
      if ($string =~ /\s+many="(.*?[^\\])"/s) {
	$many = $1;
      }
      elsif ($string =~ /\s+many='(.*?)'/s) {
	$many = $1;
	$many =~ s/\"/\\\"/sg;	# escape double-quotes
      }

      # pick gettext() or ngettext()
      if ($text) {
	$string = qq{gettext("$text")};
      }
      elsif ($one and $many) {
	$string = qq{ngettext("$one", "$many")};
      }
      else {
	# parse error
	$text =~ s/\n/\n>/sg;
	print STDERR "extract.pl parse error: $file:\n";
	print STDERR "> $text\n";
	exit;
      }

      $string =~ s/\\\}/\}/sg;	# unescape right-curly-braces
      $strings{qq{$string}}++;
    }

    close($fd);
  }
}
