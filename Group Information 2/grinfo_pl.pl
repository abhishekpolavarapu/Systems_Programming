#!/usr/bin/perl
#Abhishek Polavarapu
#Assignment 2
#UIN:01028922

if(!$ARGV[0] | !$ARGV[1]){

print "Usage: grinfo.pl [-c <count>]
Examples:
        grinfo.pl       // Help
        grinfo.pl -c 10 // List groups of at least 10";

}
else
{
print "Retrieving data \n\n";

open (my $file1, '>', 'GP')or die "Unable to open,$!";
open (my $file2, '>', 'PW')or die "Unable to open,$!";
my $group = `getent group | awk -F: '{print ":"\$3":" "	\t" \$1}'`; 
my $password = `getent passwd | awk -F: '{print ":"\$4":" }'`;

print $file1 $group;
print $file2 $password;

open my $file1, 'PW' || die "Unable to open,$!\n";

chomp(@words = <$file1>);    
foreach $word (@words) {
    $count{$word}++
}
print "Count  \t\t GID	\t Name \n";
print "-----   \t ---  \t\t -----" ;
foreach $word (keys %count) {
	if($count{$word} >=$ARGV[1] & $word ne '::'){
	print "\n";
	my $search = ":";
	my $replace = " ";
	my $count_sum = $count{$word};
	print $count_sum;
	$word =~ s/$search/$replace/g;
	open (my $name, '>', 'RES')or die "Unable to open,$!";
	my $name = `getent group | grep $word |sed 's/:/ /g' | awk '{printf "	\t" \$1}'` ;

	print " \t\t",$word ;
	print $name;
    $x++;
	}

}
print "\n\n";
print "There are ( $x ) groups with at least ( $ARGV[1] ) members \n";
unlink 'GP' or warn "Cannot unlink file $file1: $!";
unlink 'PW' or warn "Cannot unlink file $file2: $!";
unlink 'RES'or warn "Cannot unlink file$name: $!";

}