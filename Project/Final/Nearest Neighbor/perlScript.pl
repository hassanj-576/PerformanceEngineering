use strict;
use warnings;
use Carp;
use English qw(-no_match_vars);


my $files = 'model.csv';
if (-f $files) {
	unlink $files
		or croak "Cannot delete $files: $!";
}

my $OUTFILE;


my $txt=".txt";
open $OUTFILE, '>>', $files
	or croak "Cannot open $files: $OS_ERROR";



my $bucketWidth=50;
print { $OUTFILE } "Function,Total Number,N,Execution Time\n";
my $totalNumber;
my $N;
for($totalNumber=100;$totalNumber<=20000;$totalNumber=$totalNumber+100){
	
	my $outputFile = `python datagenerator.py $totalNumber$txt $totalNumber`;
	for($N=10;$N<1000;$N=$N+10){
		if($N<=$totalNumber){
			print { $OUTFILE } "EC2,$totalNumber,$N,";
			my $cmd = "./ec2 $totalNumber $totalNumber$txt $N";
			my @output = `$cmd`;
			chomp @output;

			foreach my $line (@output)
			{
					print { $OUTFILE } "$line"
							or croak "Cannot write to $files: $OS_ERROR";
			}
			print { $OUTFILE } "\n";
			
		}
	}
	for($N=10;$N<1000;$N=$N+10){
		if($N<=$totalNumber){
			print { $OUTFILE } "Main,$totalNumber,$N,";
			my $cmd2 = "./main $totalNumber $totalNumber$txt $N";
			my @output2 = `$cmd2`;
			chomp @output2;

			foreach my $line2 (@output2)
			{
					print { $OUTFILE } "$line2"
							or croak "Cannot write to $files: $OS_ERROR";
			}
			print { $OUTFILE } "\n";
		}
	}


	my $outputFile2 = `rm -rf $totalNumber$txt`;
}

