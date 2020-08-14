use v5.10;

my @files = glob( "bin/*" );

foreach my $file ( @files ) {
	my $data = do { local( @ARGV, $/ ) = $file; <> };
	
	my( $name ) = $data =~ m/
		=head1 \s+ NAME \s+ (.*?) \v
		/xi;

	$name //= $file;

	say "=item $name\n";
	}

use AnyEvent;
use AnyEvent::Fork::Remote;
 
my $rpc = AnyEvent::Fork::Remote
   ->new_execp ("ssh", "ssh", "othermachine", "perl")
   ->require ("MyModule")
   ->run ("MyModule::run", my $cv = AE::cv);
 
my $fh = $cv->recv;
