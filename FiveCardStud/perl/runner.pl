use lib '.';
use Card;
use CommonData;
use Hand;
use Poker;

my @hands;
my @cards;
my $fullFile;
my $random = scalar @ARGV == 0;
if( $random ){
	@cards = Poker->getRandCards();
	@hands = Poker->getRandHands(@cards);
}else{
	$fullFile = Poker->getFullFile();
	@cards = Poker->getFileCards();
	@hands = Poker->getFileHands(@cards);
}
$duplicateCard = Card->new( -1, 'z' );
if ( $random == 0 ){
	$duplicateCard = Poker->checkDuplicateCards( @hands );
}
my $dupPresent = $duplicateCard->{value} != -1;
my @originalHands = Poker->copyHands( @hands );
Poker->printDeckAndHands( @hands, \@cards );
if ( $dupPresent == 0 ){
	Poker->printDeckAndHands2(@hands);
	if( $random ){
		print "\n*** Here is what remains in the deck...\n";
		for my $i (30..51){
			print @cards[$i]->toString()." ";
		}
		print "\n";
	}
}
Poker->sortEach(@hands);
if( $duplicateCard->{value} != -1 ){
	print "*** ERROR - DUPLICATE CARD FOUND IN DECK ***\n";
	print "\n\n*** DUPLICATE: ".$duplicateCard->toString()." ***\n";
	exit 0;
}
for( my $i = 0; $i < 6; $i++ ){
	@hands[$i]->markCards();
	@hands[$i]->getNumEachCard();
	@hands[$i]->gradeHand(); 
}
@indexTracker = Poker->sortHands( @hands );
Poker->printResults( \@hands, \@originalHands, \@indexTracker );

1;
