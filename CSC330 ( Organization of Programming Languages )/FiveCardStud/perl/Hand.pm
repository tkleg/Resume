package Hand;

use lib '.';
use CommonData;
use Card;


my $HIGH_CARD = 0;
my $PAIR = 1;
my $TWO_PAIR = 2;
my $THREE_OF_A_KIND = 3;
my $STRAIGHT = 4;
my $FLUSH = 5;
my $FULL_HOUSE = 6;
my $FOUR_OF_A_KIND = 7;
my $STRAIGHT_FLUSH = 8;
my $ROYAL_FLUSH = 9;
my $VALID = -1;

my @myCards;
my $markedCards;
my $numEachCard;
my $handRank;
my $flushSuit;
my $kickerSuit;
my $kickerVaklue;
my $pairHighSuit;
my $valueOfTriple;
my $fmyKindVal;
my $pairValue;
my $twoPairValue;
my $doubleCardVal;

sub new {
	my $class = shift;
	my $self = bless {
		markedCards => [ map { [ (0) x 13 ] } (0..3) ],
		numEachCard => [(0) x 13],
	}, $class;
	push @myCards, Card->new(-1,'\0');	
	return $self;
}

sub getNumEachCard {
	my $self = shift;
	for( my $i = 0; $i < 13; $i++ ){
		$self->{numEachCard}[$i] = 0;
	}
	for( my $i = 0; $i < 5; $i++ ){
		$self->{numEachCard}[ $self->{myCards}[$i]->{value} ]++;
	} 
}

sub markCards{
	my $self = shift;
	for( my $i = 0; $i < 4; $i++ ){
		for( my $j = 0; $j < 13; $j++ ){
			$self->{markedCards}[$i][$j] = 0;
		}
	}
	for( my $i = 0; $i < 5; $i++ ){
		$self->{markedCards}[ Card->suitRank($self->{myCards}[$i]->{suit}) ][ $self->{myCards}[$i]->{value} ] = 1; 
	}
}

sub sortHand{
	my $self = shift;
	my $anotherPassNeeded = 1;
	while( $anotherPassNeeded ){
		$anotherPassNeeded = 0;
		for( my $j = 0; $j < 4; $j++ ){
			if( $self->{myCards}[$j]->{value} < $self->{myCards}[$j + 1]->{value} ){
				$temp = $self->{myCards}[$j];
				$self->{myCards}[$j] = $self->{myCards}[$j + 1];
				$self->{myCards}[$j + 1] = $temp;
				$anotherPassNeeded = 1;
			}
		}
	}
	$self->aceLowStraightCheck();		
}

sub aceLowStraightCheck{
	my $self = shift;
	if( $self->{myCards}[0]->{value} != 12 ){
		return;
	} elsif( $self->{myCards}[1]->{value} != 3 ){
		return;
	} elsif( $self->{myCards}[2]->{value} != 2 ){
		return;
	} elsif( $self->{myCards}[3]->{value} != 1 ){
		return;
	} elsif( $self->{myCards}[4]->{value} != 0 ){
		return;	
	}

	my $holdAce = $self->{myCards}[0];
	for( my $i = 0; $i < 4; $i++ ){
		$self->{myCards}[$i] = $self->{myCards}[$i + 1];
	}
	$self->{myCards}[4] = $holdAce;
}

sub fourOfAKind{
	my $self = shift;
	for( my $i = 0; $i < 12; $i++ ){
		if( $self->{numEachCard}[$i] == 4 ){
			$self->{fourKindVal} = $i;
			return 1;
		}
	}
	return 0;
}

sub fullHouse{
	my $self = shift;
	$tripleFound = 0;
	$doubleFound = 0;
	for( my $i = 0; $i < 13; $i++ ){
		if( $self->{numEachCard}[$i] == 3 ){
			$self->{valueOfTriple} = $i;
			$tripleFound = 1;
		} elsif ( $self->{numEachCard}[$i] == 2 ){
			$self->{doubleCardVal} = $i;
			$doubleFound = 1;
		}
		if( $tripleFound && $doubleFound ){
			return 1;
		}
	}
	return 0;
}

sub royalFlush{
	my $self = shift;
	for( my $i = 0; $i < 4; $i++ ){
		my $counter = 0;
		for( my $j = 8; $j < 13; $j++ ){
			if( $self->{markedCards}[$i][$j] == 1 ){
				$counter++;	
			}
		}
		if( $counter == 5 ){
			$self->{flushSuit} = $i;
			return 1;
		}
	}
	return 0;
}

sub straightFlush{
	my $self = shift;
	for( my $i = 0; $i < 4; $i++ ){
		$curConsecutive = 0;
		for( my $j = 0; $j < 13; $j++ ){
			if( $curConsecutive == 5 ){
				$self->{flushSuit} = $i;
				return 1;
			} elsif( $self->{markedCards}[$i][$j] ){
				$curConsecutive++;
			} else{
				$curConsecutive = 0;
			}

		}
	}
	if( $self->{myCards}[4]->{value} != 12 ){
		return 0;
	}
	$potentialSuit = $self->{myCards}[4]->{suit};
	for( my $i = 0; $i < 4; $i++ ){
		if( $self->{myCards}[$i]->{value} != (3-$i) || $self->{myCards}[$i]->{suit} ne $potentialSuit ){
			return 0;
		}
	}
	$self->{flushSuit} = Card->suitRank( $self->{myCards}[0]->{suit} );
	return 1;
}

sub flush{
	my $self = shift;
	$potentialSuit = $self->{myCards}[0]->{suit};
	for( my $i = 1; $i < 5; $i++ ){
		if( $self->{myCards}[$i]->{suit} ne $potentialSuit ){
			return 0;
		}
	}
	$self->{flushSuit} = Card->suitRank( $potentialSuit );
	return 1;
}

sub straight{
	$self = shift;
	$curConsecutive = 0;
	for( my $i = 0; $i < 13; $i++ ){
		if( $curConsecutive == 5 ){
			return 1;
		} elsif( $self->{numEachCard}[$i] == 1 ){
			$curConsecutive++;
		} else {
			$curConsecutive = 0;
		}
	}

	if( $self->{myCards}[4]->{value} != 12 ){
		return 0;
	}
	for( my $i = 0; $i < 4; $i++ ){
		if( $self->{myCards}[$i]->{value} != (3-$i) ){
			return 0;
		}
	}
	return 1;
}

sub threeOfAKind{
	my $self = shift;
	for( my $i = 0; $i < 13; $i++ ){
		if( $self->{numEachCard}[$i] == 3 ){
			$self->{valueOfTriple} = $i;
			return 1;
		}
	}
	return 0;
}

sub twoPair{
	my $self = shift;
	my $pairFound = 0;
	for( my $i = 0; $i < 13; $i++ ){
		if( $self->{numEachCard}[$i] > 1 ){
			if( $pairFound  ){
				$self->{twoPairValue} = $i;
				$self->markKicker();
				if( $self->{twoPairValue} < $self->{pairValue} ){
					$temp = $self->{pairValue};
					$self->{pairValue} = $self->{twoPairValue};
					$self->{twoPairValue} = $temp;
				}
				return 1;
			} else {
				$self->{pairValue} = $i;
				$pairFound = 1;
			}
		}
	}
	return 0;
}

sub markKicker{
	my $self = shift;
	for( my $i = 0; $i < 13; $i++ ){
		if( $self->{numEachCard}[$i] == 1 ){
			for( my $j = 0; $j < 5; $j++ ){
				if( $self->{myCards}[$j]->{value} == $i ){
					$self->{kickerSuit} = Card->suitRank( $self->{myCards}[$j]->{suit} );
					$self->{kickerValue} = $self->{myCards}[$j]->{value};
					return;
				}
			}
		}
	}
}

sub pair{
	my $self = shift;
	for( my $i = 0; $i < 13; $i++ ){
		if( $self->{numEachCard}[$i] == 2 ){
			$suitHighCardNoPair = -1;
			$valueHighCardNoPair = -1;
			for( my $j = 0; $j < 5; $j++ ){
				if( $self->{numEachCard}[ $self->{myCards}[$j]->{value} ] == 1 && $valueHighCardNoPair < $self->{myCards}[$j]->{value} ){
					$valueHighCardNoPair = $self->{myCards}[$j]->{value};
					$suitHighCardNoPair = Card->suitRank( $self->{myCards}[$j]->{suit} );
				}
			}
			$self->{kickerSuit} = $suitHighCardNoPair;
			$self->{kickerValue} = $valueHighCardNoPair;
			$self->{pairValue} = $i;
			return 1;
		}
	}
	return 0;
}

sub gradeHand{
	my $self = shift;
	if( $self->royalFlush() ){
		$self->{handRank} = $ROYAL_FLUSH;
	} elsif( $self->straightFlush() ){
		$self->{handRank} = $STRAIGHT_FLUSH;
	} elsif( $self->fourOfAKind() ){
		$self->{handRank} = $FOUR_OF_A_KIND;
	} elsif( $self->fullHouse() ){
		$self->{handRank} = $FULL_HOUSE;
	} elsif( $self->flush() ){
		$self->{handRank} = $FLUSH;
	} elsif( $self->straight() ){
		$self->{handRank} = $STRAIGHT;
	} elsif( $self->threeOfAKind() ){
		$self->{handRank} = $THREE_OF_A_KIND;
	} elsif( $self->twoPair() ){
		$self->{handRank} = $TWO_PAIR;
	} elsif( $self->pair() ){
		$self->{handRank} = $PAIR;
	} else {
		$self->{handRank} = $HIGH_CARD;
	}
}

sub losesTo{
	my( $self, $hand2 ) = @_;
	if( $self->{handRank} != $hand2->{handRank} ){
		return $self->{handRank} < $hand2->{handRank};
	} elsif( $self->{handRank} == $HIGH_CARD ){
		for( my $i = 0; $i < 5; $i++ ){
			if( $self->{myCards}[$i]->{value} != $hand2->{myCards}[$i]->{value} ){
				return $self->{myCards}[$i]->{value} < $hand2->{myCards}[$i]->{value};
			}
		}
		return Card->suitRank($self->{myCards}[0]->{suit}) < Card->suitRank($hand2->{myCards}[0]->{suit});
	} elsif( $self->{handRank} == $PAIR ){
		if( $self->{pairValue} != $hand2->{pairValue} ){
			return $self->{pairValue} < $hand2->{pairValue};
		}
		for( my $i = 0; $i < 5; $i++ ){
			if( $self->{myCards}[$i]->{value} != $hand2->{myCards}[$i]->{value} ){
				return $self->{myCards}[$i]->{value} < $hand2->{myCards}[$i]->{value};
			}
		}
		return $self->{kickerSuit} < $hand2->{kickerSuit};
	} elsif( $self->{handRank} == $TWO_PAIR ){
		if( $self->{twoPairValue} != $hand2->{twoPairValue} ){
			return $self->{twoPairValue} < $hand2->{twoPairValue};
		} elsif( $self->{pairValue} != $hand2->{pairValue} ){
			return $self->{pairValue} < $hand2->{pairValue};
		} elsif( $self->{kickerSuit} != $hand2->{kickerSuit} ){
			return $self->{kickerSuit} < $hand2->{kickerSuit};
		}
	} elsif( $self->{handRank} == $THREE_OF_A_KIND ){
		return $self->{valueOfTriple} < $hand2->{valueOfTriple};
	} elsif( $self->{handRank} == $STRAIGHT ){
		if( $self->{myCards}[0]->{value} != $hand2->{myCards}[0]->{value} ){
			return $self->{myCards}[0]->{value} < $hand2->{myCards}[0]->{value};
		}
		return Card->suitRank( $self->{myCards}[0]->{suit} ) < Card->suitRank( $hand2->{myCards}[0]->{suit} );
	} elsif( $self->{handRank} == $FLUSH ){
		for( my $i = 0; $i < 5; $i++ ){
			if( $self->{myCards}[$i]->{value} != $hand2->{myCards}[$i]->{value} ){
				return $self->{myCards}[$i]->{value} < $hand2->{myCards}[$i]->{value};
			}
		}
		return $self->{flushSuit} < $hand2->{flushSuit};
	} elsif( $self->{handRank} == $FULL_HOUSE ){
		return $self->{valueOfTriple} < $hand2->{valueOfTriple};
	} elsif( $self->{handRank} == $FOUR_OF_A_KIND ){
		return $self->{fourKindVal} < $hand2->{fourKindVal};
	} elsif( $self->{handRank} == $STRAIGHT_FLUSH ){
		if( $self->{myCards}[0]->{value} != $hand2->{myCards}[0]->{value} ){
			return $self->{myCards}[0]->{value} < $hand2->{myCards}[0]->{value};
		}
		return Card->suitRank( $self->{myCards}[0]->{suit} ) < Card->suitRank( $hand2->{myCards}[0]->{suit} );
	} elsif( $self->{handRank} == $ROYAL_FLUSH ){
		return $self->{flushSuit} < $hand2->{flushSuit};
	}

}

sub addCard{
	my ( $self, $newCard ) = @_;
	push @{ $self->{myCards} }, $newCard;
}

sub getMyCards{
	my $self = shift;
	return $self->{myCards};
}

1;
