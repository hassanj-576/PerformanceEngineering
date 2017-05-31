use strict;
use warnings;
use Carp;
use English qw(-no_match_vars);


my $files = 'output.csv';
if (-f $files) {
	unlink $files
		or croak "Cannot delete $files: $!";
}

my $OUTFILE;


my $txt=".txt"
open $OUTFILE, '>>', $files
	or croak "Cannot open $files: $OS_ERROR";
my @fileNames = ("dataLarge1.csv","dataLarge2.csv","dataLarge3.csv","dataLarge4.csv");
#my @fileNames = ("dataLarge1.csv");

my $bucketWidth=50;
print { $OUTFILE } "Function,Total Number,N,Execution Time\n";

for($totalNumber=100;$totalNumber<=500;$totalNumber=$totalNumber+100){
	my outputFile= 'python datagenerator.py $totalNumber$txt $totalNumber'
	for($N=10;$N<15;$N=$N+1){
			
			print { $OUTFILE } "EC2,$totalNumber,$N,";
			my $cmd = "./ec2 $totalNumber $totalNumber$txt $N";
			my @output = `$cmd`;
			chomp @output;

			foreach my $line (@output)
			{
					print { $OUTFILE } "$line,"
							or croak "Cannot write to $files: $OS_ERROR";
			}
			print { $OUTFILE } "\n"
	}
	my outputFile= 'rm -rf $totalNumber$txt'
}

my $hostname = 'cwi.nl';
my $this_day = 'date';
my $email = "hassan.jalil576\@gmail.com";
my $to = "$email";
my $from = "h.jalil\@$hostname";
my $subject = "JOB COMPLETE - $this_day";
my $message = "The Job Running on Stones02 is complete...";
open(MAIL, "|/usr/sbin/sendmail -t");
print MAIL "To: $to\n";
print MAIL "From: $from\n";
print MAIL "Subject: $subject\n\n";
print MAIL $message;
close(MAIL);
