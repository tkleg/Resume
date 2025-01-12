package Poker;

use lib '.';
use CommonData;
use Card;
use Hand;
use List::Util qw(shuffle);

sub sortHands{
	my ( $class, @hands ) = @_;
	my @indexTracker = (0..5);
	my $anotherPassNeeded = 1;
	while( $anotherPassNeeded ){
		$anotherPassNeeded = 0;
		for( my $i = 0; $i < 5; $i++ ){
			if( @hands[$i]->losesTo(@hands[$i+1]) ){
				$anotherPassNeeded = 1;
				$tempHand = @hands[$i];
				@hands[$i] = @hands[$i+1];
				@hands[$i+1] = $tempHand;

				$tempIndex = @indexTracker[$i];
				@indexTracker[$i] = @indexTracker[$i+1];
				@indexTracker[$i+1] = $tempIndex;								
			}
		}
	}
	return @indexTracker;
}

sub printResults{
	my( $class, $handsRef, $originalHandsRef, $indexTrackerRef ) = @_;
	my @hands = @$handsRef;
	my @originalHands = @$originalHandsRef;
	my @indexTracker = @$indexTrackerRef;
	print "\n --- WINNING HAND ORDER ---\n";
	
	for my $i (0..5){
		my $origIndexToPrint = @indexTracker[$i];
		print " ".@originalHands[$origIndexToPrint]->{myCards}[0]->toString();
		for( my $j = 1; $j < 5; $j++ ){
			my $handHelp = @originalHands[$origIndexToPrint];
			my $cardString = $handHelp->{myCards}[$j]->toString();
			if( $j == 3 && $handHelp->{myCards}[1]->{value} == 8 && $handHelp->{myCards}[0]->{value} == 8 ){
				$cardString = " ".$cardString;
			} elsif ( $handHelp->{myCards}[0]->{value} == 8 && $j == 1 && length( $cardString ) == 2 ){
				$cardString = " ".$cardString;
			} elsif( length( $cardString ) == 2 ){
				$cardString = "  ".$cardString;
			} else {
				$cardString = " ".$cardString;
			}
			print $cardString;
		}
		print " - ".$CommonData::HAND_RANKS[@hands[$origIndexToPrint]->{handRank}]."\n";
	}
}

sub sortEach{
	my ($class, @hands ) = @_;
	for my $i ( 0 .. 5 ){
		$anotherPassNeeded = 1;
		while ( $anotherPassNeeded ){
			$anotherPassNeeded = 0;
			for my $j ( 0 .. 3 ){
				if( @hands[$i]->{myCards}[$j]->{value} < @hands[$i]->{myCards}[$j+1]->{value} ){
					$anotherPassNeeded = 1;
					$temp = @hands[$i]->{myCards}[$j];
					@hands[$i]->{myCards}[$j] = @hands[$i]->{myCards}[$j+1];
					@hands[$i]->{myCards}[$j+1] = $temp;
				}
			}
		}
		@hands[$i]->aceLowStraightCheck();
	}
	return @hands;
}

sub copyHands{
	my ( $class, @hands ) = @_;
	for my $i ( 0 .. 5 ){
		@originalHands[$i] = Hand->new();
		for my $j ( 0 .. 4 ){
			@originalHands[$i]->{myCards}[$j] = Card->new(@hands[$i]->{myCards}[$j]->{value}, @hands[$i]->{myCards}[$j]->{suit} );
		}
	}
	return @originalHands;
}
sub printDeckAndHands{
	my ( $class, @hands, $cards ) = @_;
	my $random = scalar @ARGV == 0;
	my $fullFile = Poker->getFullFile();
	@cards = shuffle(@cards);
	print "\n*** P O K E R  H A N D  A N A L Y Z E R ***\n\n";
	if( $random ){
		print "\n*** USING RANDOMIZED DECK OF CARDS ***\n\n*** Shuffled 52 card deck:\n";
		print @cards[0]->toString()." ";
		for my $i ( 1 .. 51 ){
			if( $random == 0 && $i % 5 == 0 ){
				print " ";
			}
			print @cards[$i]->toString()." ";
			if( $i % 13 == 0 ){
				print "\n";
			}
		}
		print "\n";
	} else {
		print "\n*** USING TEST DECK ***\n\n*** File: "."../handsets/".@ARGV[0]."\n".$fullFile."\n";
	}
}

sub printDeckAndHands2{
	my( $class, @hands ) = @_;
        print "\n*** Here are the six hands...\n";
	for( my $i = 0; $i < 6; $i++ ){
                for (my $j = 0; $j < 5; $j++ ){
                        print @hands[$i]->{myCards}[$j]->toString()." ";
                }
                print "\n";
        }
        if( $random == 0 ){
                return;
        }
        print "\n*** Here is what remains in the deck...\n";
        for my $i (30..51){
                print @cards[$i]->toString()." ";
        }
        print "\n";
}
sub printHandsRaw{
	my ( $class, @hands ) = @_;
	for( my $i = 0; $i < 6; $i++ ){
        	for( my $j = 0; $j < 5; $j++ ){
        	        print " ".@hands[$i]->{myCards}[$j]->toString();
        	}
        print " ".$CommonData::HAND_RANKS[@hands[$i]->{handRank}]."\n";
	
	}
	print "\n";
}


sub checkDuplicateCards{
	my ( $class, @hands ) = @_;
	
	my @cardsFound = (0)x52 ;
	for( my $i = 0; $i < 6; $i++ ){
		for( my $j = 0; $j < 5; $j++ ){
			$sRank = Card->suitRank( @hands[$i]->{myCards}[$j]->{suit} );
			$value = @hands[$i]->{myCards}[$j]->{value};
			if( $cardsFound[$sRank*13 + $value] == 1 ){
				return @hands[$i]->{myCards}[$j];
			} else {
				$cardsFound[$sRank * 13 + $value] = 1;
				
			}
		}
	}

	return Card->new( -1, 'z' );
}	

sub getFullFile{
	my $class = shift;
	my $fullFile = "";
	open( my $fh, '<', "../handsets/".@ARGV[0]) or die $!;
	while( my $line = <$fh> ){
		$fullFile = $fullFile . $line;
	}
	close $fh;
	return $fullFile;
}

sub getFileCards{
	my $class = shift;
	$fullFile = Poker->getFullFile();
	@lines = split('\n', $fullFile);
	@cardsS;
	foreach my $line (@lines){
		my @rawCards = split(',', $line );
		foreach my $rawCard (@rawCards){
			if( substr($rawCard, 0, 1) == " " ){
				$rawCard = substr($rawCard,1,3);
			}
			push( @cardsS, $rawCard );
		}
	}

	my @cards;
	for( my $i = 0; $i < 30; $i++ ){
		if( length( @cardsS[$i] ) == 3 ){
			push( @cards, Card->new(8, substr(@cardsS[$i],-1,1) ) );
		}else {
			$newVal = Card->getValue( substr(@cardsS[$i],0,1) );
			push( @cards, Card->new($newVal, substr(@cardsS[$i],-1,1) ) );
		}
		
	}
	
	return @cards;	
}

sub getFileHands{
	my ($class, @cards ) = @_;
	@hands;
	for( my $i = 0; $i < 6; $i++ ){
		push( @hands, Hand->new() );
	}
	$index = 0;
	for( my $i = 0; $i < 6; $i++ ){
		for( my $j = 0; $j < 5; $j++ ){
			@hands[$i]->{myCards}[$j] = @cards[$counter];
			$counter++;
		}	
	}
	return @hands;
}

sub getRandCards{
	my $class = shift;
	@cards;
	@suits = ('H','D','S','C');
	for( my $i = 0; $i < 4; $i++ ){
		for( my $j = 0; $j < 13; $j++ ){
			push(@cards, Card->new($j, @suits[$i]) );
		}
	}
	return shuffle( shuffle( shuffle( @cards ) ) );
}

sub getRandHands{
	my ($class, @cards ) = @_;
	@hands;
	for( my $i = 0; $i < 6; $i++ ){
		push( @hands, Hand->new() );
	}
	$curHand = 0;
	$iteration = 0;
	for( my $i = 0; $i < 30; $i++ ){
		@hands[$curHand]->{myCards}[$iteration] = @cards[$i];
		$curHand++;
		if( $curHand == 6 ){
			$curHand = 0;
			$iteration++;
		}
	}
	return @hands;
}

1;
