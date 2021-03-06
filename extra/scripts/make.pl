#!/usr/bin/perl -w

use File::Basename;

# Compilers
my $cpath = $ARGV[0]; # "~/Documents/thesis/code";
 
# c File we want to mutate
my $cfile   = $ARGV[1];
my $cbfile  = basename($cfile, ".c");
my $cbcfile = $cbfile . ".bc";

# mutated version
my $cmbcfile = "mut" . $cbfile . ".bc";

# mutation library
my $ovcfile = $ARGV[2];
my $ovbfile  = basename($ovcfile, ".c");
my $ovbcfile = $ovbfile . ".bc";

# combined file
my $mbfile = $ARGV[3];
my $mbcfile = $mbfile . ".bc";
my $masfile = $mbfile . ".s";

# Compile to bc
print "Compiling mutation library\n";
system("$cpath/clang/bin/clang -c $ovcfile -pthread -emit-llvm -o $ovbcfile");

print "Compiling test case\n";
system("$cpath/clang/bin/clang -c $cfile -pthread -emit-llvm -o $cbcfile");

print "Generating instrumented bytecode\n";
system("$cpath/llvm/build/bin/opt -load $cpath/llvm/build/lib/LLVMMutation.dylib -mutation < $cbcfile > $cmbcfile");

print "Linking bytecode files\n";
system("$cpath/llvm/build/bin/llvm-link $ovbcfile $cmbcfile -o $mbcfile");

print "Generating Assembly\n";
system("$cpath/llvm/build/bin/llc $mbcfile -o $masfile");

print "Generating Executable\n";
system("$cpath/clang/bin/clang $masfile -o $mbfile");

print "Finished\n";