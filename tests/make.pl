#!/usr/bin/perl -w

use File::Basename;

# c File we want to mutate
my $cfile   = $ARGV[0];
my $cbfile  = basename($cfile, ".c");
my $cbcfile = $cbfile . ".bc";

# mutated version
my $cmbcfile = "mut" . $cbfile . ".bc";

# mutation library
my $ovcfile = $ARGV[1];
my $ovbfile  = basename($ovcfile, ".c");
my $ovbcfile = $ovbfile . ".bc";

# combined file
my $mbfile = $ARGV[2];
my $mbcfile = $mbfile . ".bc";
my $masfile = $mbfile . ".s";

# Compile to bc
print "Compiling mutation library\n";
system("~/Documents/thesis/code/clang+llvm-3.1-x86_64-apple-darwin11/bin/clang -c $ovcfile -pthread -emit-llvm -o $ovbcfile");

print "Compiling test case\n";
system("~/Documents/thesis/code/clang+llvm-3.1-x86_64-apple-darwin11/bin/clang -c $cfile -pthread -emit-llvm -o $cbcfile");

print "Generating instrumented bytecode\n";
system("~/Documents/thesis/code/llvm/build/bin/opt -load ~/Documents/thesis/code/llvm/build/lib/LLVMMutation.dylib -mutation < $cbcfile > $cmbcfile");

print "Linking bytecode files\n";
system("~/Documents/thesis/code/llvm/build/bin/llvm-link $ovbcfile $cmbcfile -o $mbcfile");

print "Generating Assembly\n";
system("~/Documents/thesis/code/llvm/build/bin/llc $mbcfile -o $masfile");

print "Generating Executable\n";
system("~/Documents/thesis/code/clang+llvm-3.1-x86_64-apple-darwin11/bin/clang $masfile -o $mbfile");

print "Finished\n";