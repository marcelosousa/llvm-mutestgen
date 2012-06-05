#!/usr/bin/perl -w

my $mbfile = $ARGV[0];

open FILE, "<", "stats.log" or die $!;

my $num = <FILE>;
print "Running Mutants\n";
for($count = 1; $count <= $num-1; $count++){ 
  print "Iteration $count\n";
  $ENV{MUNUM} = $count;
	system("./$mbfile");
}
print "Finished\n";
