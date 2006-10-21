#!/usr/local/bin/perl
#
# This script traverses the Gallery tree and creates a manifest file that
# contains a list of checksums for files in the distribution.  The installer
# verifies the integrity of the files before proceeding.
#
use strict;
use File::Basename;
use Cwd;
use String::CRC32;
my $quiet = 0;
foreach my $i (0 .. $#ARGV) {
    if ('-q' eq $ARGV[$i]) {
	$quiet = 1;
    }
}
sub quietprint {
    if (!$quiet) {
	my $string = shift;
	print STDERR $string;
    }
}
$| = 1;

chdir(dirname($0) . '/../../..');
my $basedir = cwd();

# Get a list of every file committed to Subversion.
#
my @entries = ();
quietprint("Finding all files...");
&listSvn(\@entries);
quietprint("\n");

# Strip base dir, sort
quietprint("Sorting...");
@entries = sort @entries;
quietprint("\n");

# Split into sections
#
my %sections;
quietprint("Separating into sections...");
foreach my $file (@entries) {
  if ($file =~ m{^((modules|layouts|themes)/.*?)/}) {
    push(@{$sections{"$1/MANIFEST"}}, $file);
  } else {
    push(@{$sections{'MANIFEST'}}, $file);
  }
}
quietprint("\n");

# Now generate the checksum files
#
quietprint("Generating checksums...");
my $changed = 0;
my $total = 0;
foreach my $manifest (keys %sections) {
  my @old_lines = ();
  my $oldContent = '';
  my $oldRevision = '';
  if (open(FD, "<$manifest")) {
    @old_lines = <FD>;
    close(FD);
    $oldRevision = $1 if ($old_lines[0] =~ /Revision(: \d+\s*)\$/);
    $oldContent = join('', @old_lines);
  }
  open(my $out, ">$manifest.new") or die;
  print $out '# $Revision' . "$oldRevision\$\n";
  print $out "# File crc32 crc32(crlf) size size(crlf)  or  R File\n";
  my @entries = @{$sections{$manifest}};
  my %deleted;
  my %seen = {};
  foreach my $entry (@entries) {
    my ($file, $isBinary) = split(/\@\@/, $entry);
    next if ($file =~ /MANIFEST$/);

    if ($file =~ /deleted:(.*)/) {
      $deleted{$1}++;
    } else {
      $seen{$file}++;
      open(my $fd, "<$file");
      binmode($fd);
      my $data = join('', <$fd>);
      close($fd);

      my ($data_crlf, $size, $size_crlf);
      if ($isBinary) {
	$data_crlf = $data;
	$size = $size_crlf = (stat($file))[7];
      } else {
	if ($data =~ /\r/) {
	  ($data_crlf = $data) =~ s/\r//g;
	} else {
	  ($data_crlf = $data) =~ s/\n/\r\n/g;
	}
	$size = length($data);
	$size_crlf = length($data_crlf);
      }

      my $cksum = crc32($data);
      my $cksum_crlf = crc32($data_crlf);
      print $out "$file\t$cksum\t$cksum_crlf\t$size\t$size_crlf\n";
    }
  }
  if (@old_lines) {
    foreach (@old_lines) {
      next if /^\#/;
      if (/^R\t(.*)$/) {
	if ($seen{$1}) {
	  # Marked as deleted in the old manifest but back again!
	} else {
	  $deleted{$1}++;
	}
      } else {
	/^(\S+)\t/;
	unless ($seen{$1}) {
	  # We used to have it but we don't anymore
	  $deleted{$1}++;
	}
      }
    }

    print $out map("R\t$_\n", sort rSort keys %deleted);
  }
  close($out);

  $changed += replaceIfNecessary($oldContent, $manifest, "$manifest.new");
  $total++;

  quietprint(".");
}
quietprint("\n");
quietprint(sprintf("Completed in %d seconds\n", time - $^T));
quietprint(sprintf("Manifests changed: $changed (total: $total)\n"));

sub replaceIfNecessary {
  my ($oldContent, $oldFile, $newFile) = @_;

  open(FD, "<$newFile") || die;
  my $new = join("", <FD>);
  close(FD);

  if ($oldContent ne $new) {
    rename($newFile, $oldFile);
    return 1;
  } else {
    unlink($newFile);
    return 0;
  }
}

sub listSvn {
  my $entries = shift;
  my %binaryList = ();
  local *FD;
  open(FD, "svn propget --non-interactive -R svn:mime-type |") or die;
  while (<FD>) {
    split / - /;
    $binaryList{$_[0]} = 1;
  }
  close FD;
  open(FD, "svn status --non-interactive -v -q |") or die;
  while (<FD>) {
    die "\n$_" unless /^(.).....\s*\d+\s+\d+\s+\S+\s+(.*)$/;
    die "\n$2" unless (-e $2);
    next unless (-f $2);
    die "Check $1 status for $2" if ($1 ne ' ' and $1 ne 'D' and $1 ne 'M');
    quietprint("Warning: $2 is locally modified\n") if ($1 eq 'M');
    push(@$entries,
      sprintf("%s%s@@%d", ($1 eq 'D' ? 'deleted:' : ''), $2, exists($binaryList{$2})));
  }
  close FD;
}

sub rSort {
  return 1 if ("$a/" eq substr($b, 0, length($a) + 1));
  return -1 if ("$b/" eq substr($a, 0, length($b) + 1));
  return $a cmp $b;
}

