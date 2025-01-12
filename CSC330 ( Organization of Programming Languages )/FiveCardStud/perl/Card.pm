package Card;

use lib '.';
use CommonData;

my $suit;
my $value;

sub new {
	my $class = shift;
	my $newValue = shift;
	my $newSuit = shift; 
	my $self = bless {
		value => $newValue,
		suit => $newSuit
	}, $class;

	return $self;
}

sub suitRank{
	my( $class, $c ) = @_;
	my $d = "D";
	my $C = "C";
	my $H = "H";
	my $S = "S";
	if( $c eq $d ){
		return 0;
	} elsif ( $c eq $C ){
		return 1;
	} elsif ( $c eq $H ){
		return 2;
	} elsif ( $c eq $S ){
		return 3;
	} else {
		return -1;
	}

}

sub getValue{
	my ($class, $c) = @_;
	if ( $c >= "2" && $c <= "9" ){
		return ($c - 2);
	} elsif ( $c eq "10" ){
                return 8;
	} elsif ( $c eq "J" ) {
		return 9;
	} elsif ( $c eq "Q" ) {
		return 10;
	} elsif ( $c eq "K" ) {
		return 11;
	} elsif ( $c eq "A" ) {
		return 12;
	} else {
		return -1;
	}
}

sub toString{
	my $self = shift;
	return $CommonData::FACES[$self->{value}] . $self->{suit};
}

1
