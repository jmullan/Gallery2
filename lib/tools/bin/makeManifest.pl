#!/usr/local/bin/perl
#
# This script traverses the Gallery tree and creates a manifest file that
# contains a list of checksums for files in the distribution.  The installer
# verifies the integrity of the files before proceeding.
# The Debug module also uses this file to figure out whether or not it's
# safe to show you the contents of the file in stack traces.
#
use strict;
use File::Basename;
use Cwd;
use String::CRC32;

$| = 1;

chdir(dirname($0) . '/../../..');
my $basedir = cwd();

# Get a list of every file committed to CVS.
#
my @entries = ();
print STDERR "Finding all files...";
&parseCvs($basedir, \@entries);
print STDERR "\n";

# Strip base dir, sort
print STDERR "Sorting...";
map(s{$basedir/}{}, @entries);
@entries = sort @entries;
print STDERR "\n";

# Get list of .class, .inc, .php files in basedir/modules/layouts..
my @viewable = grep(m{^(install/.*|modules/.*|layouts/.*|[^/]*)\.(class|inc|php)$}, @entries);

# Split into sections
#
my %sections;
print STDERR "Separating into sections...";
foreach my $file (@entries) {
  if ($file =~ m{^((modules|layouts|themes)/.*?)/}) {
    push(@{$sections{"$1/MANIFEST"}}, $file);
  } else {
    push(@{$sections{'MANIFEST'}}, $file);
  }
}
print STDERR "\n";

# Now generate the checksum files
#
print STDERR "Generating checksums...";
foreach my $manifest (keys %sections) {
  my $out;
  open($out, ">$manifest") or die;
  print $out "# File crc32 crc32(crlf) size size(crlf) viewable\n";
  my @entries = @{$sections{$manifest}};
  foreach my $entry (@entries) {
    my ($file, $isBinary) = split(/ /, $entry);
    next if ($file =~ /MANIFEST$/);

    open(my $fd, "<$file");
    binmode($fd);
    my $data = join('', <$fd>);
    my $data_crlf;
    close($fd);

    my $size;
    my $size_crlf;
    if ($isBinary) {
      $data_crlf = $data;
      $size = (stat($file))[7];
      $size_crlf = (stat($file))[7];
    } else {
      if ($data =~ /\r/) {
	$data_crlf = $data;
	$data =~ s/\r//g;
      } else {
	($data_crlf = $data) =~ s/\n/\r\n/g;
      }
      $size = length($data);
      $size_crlf = length($data_crlf);
    }

    my $cksum = crc32($data);
    my $cksum_crlf = crc32($data_crlf);
    my $view = grep(m{^\Q$file\E$}, @viewable) ? 1 : 0;
    print $out "$file $cksum $cksum_crlf $size $size_crlf $view\n";
  }
  close $out;
  print STDERR ".";
}
print STDERR "\n";
printf(STDERR "Completed in %d seconds\n", time - $^T);

sub parseCvs {
  my $activeDir = shift;
  my $entries = shift;

  my $cvsDir = "$activeDir/CVS";
  die "missing $cvsDir" unless (-d $cvsDir);

  local *FD;
  open(FD, "<$cvsDir/Entries") or die;
  while (<FD>) {
    next if /^D$/;

    if (m|^D/([^/]*)/|) {
      my $target = "$activeDir/$1";
      if (-d $target) {
	&parseCvs($target, $entries);
      } if (-f $target) {
	die "$target not a dir" if (! -d $target);
      } else {
	# CVS doesn't always get rid of D/ entries when the dir is 
	# pruned.  Ignore.
      }
    } elsif (m|/([^/]*)/|) {
      next if m{/MANIFEST$};
      my $target = "$activeDir/$1";
      die "$target not a file" if (! -f $target);
      push(@$entries, sprintf("%s %d", $target, m/-kb/));
    } else {
      die "Can't parse: $_";
    }
  }
  close FD;
}
