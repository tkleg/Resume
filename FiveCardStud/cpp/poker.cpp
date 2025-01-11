#include<fstream>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;

const int HIGH_CARD = 0;
const int PAIR = 1;
const int TWO_PAIR = 2;
const int THREE_OF_A_KIND = 3;
const int STRAIGHT = 4;
const int FLUSH = 5;
const int FULL_HOUSE = 6;
const int FOUR_OF_A_KIND = 7;
const int STRAIGHT_FLUSH = 8;
const int ROYAL_FLUSH = 9;
const int VALID = -1;//used for Card.value for duplicateCard

const string faces[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
const string handRanks[] = {"High Card","Pair","Two Pair","Three of a Kind","Straight","Flush","Full House","Four of a Kind","Straight Flush","Royal Flush"};

class Card{
public:
	int value;
	char suit;
	Card( int value, char suit ) : value(value), suit(suit){}
	Card(){}

	int suitRank(){
		switch( suit ){
			case 'D':
				return 3;
			case 'C':
				return 2;
			case 'H':
				return 1;
			case 'S':
				return 0;
		}
		return -1;
	}
	static int getValue( char c ){
		if( c >= '2' && c <= '9' )
			return ( c - '0' ) - 2;
		switch( c ){
			case 'J': return 9;
			case 'Q': return 10;
			case 'K': return 11;
			case 'A': return 12;
		}
		return -1;
	}
	string toString(){
		return faces[value]+suit;
	}
};

class Hand{
	public:
	Card myCards[5];
	bool markedCards[4][13];
	int numEachCard[13];
	int handRank = -1;
	int flushSuit = -1;//suit of the flush
	int kickerSuit = -1;//suit of the kicker card in a two pair
	int kickerValue = -1;
	int pairHighSuit = -1;//suit of the highest value card not in the pair
	int valueOfTriple = -1;//value of the card appearing 3 times in a full house or three of a kind
	int fourKindVal = -1;
	int pairValue = -1;
	int twoPairValue = -1;
	int doubleCardVal = -1;//for full house

	Hand(){}

	void aceLowStraightCheck(){//if an ace low straight is present, the hand is shifted to put the ace in the last spot and 5 at the first
		if( myCards[0].value != 12 )
			return;
		if( myCards[1].value != 3 )
			return;
		if( myCards[2].value != 2 )
			return;
		if( myCards[3].value != 1 )
			return;
		if( myCards[4].value != 0 )
			return;
		Card holdAce = myCards[0];
		for( int x = 0; x < 3; x++ )
			myCards[x] = myCards[x+1];
		myCards[4] = holdAce;
	}
	void getNumEachCard(){
		for( int x = 0; x < 52; x++ )
			numEachCard[x] = 0;
		for( int x =0; x < 5; x++ )
			numEachCard[myCards[x].value]++;
	}

	static void sortHands( Hand hands[], int indexTracker[] ){
		for( int x = 0; x < 6; x++ )
			indexTracker[x] = x;
		bool anotherPassNeeded = true;
		while( anotherPassNeeded ){
			anotherPassNeeded = false;
			for( int x =0; x < 5; x++ )
				if( hands[x].losesTo( hands[x+1] ) ){
					anotherPassNeeded = true;
					Hand tempHand = hands[x];
					hands[x] = hands[x+1];
					hands[x+1] = tempHand;

					int tempIndex = indexTracker[x];
					indexTracker[x] = indexTracker[x+1];
					indexTracker[x+1] = tempIndex;
				}
		}
	}

	bool losesTo( Hand hand2 ){
		if( handRank != hand2.handRank )
			return handRank < hand2.handRank;
		if( handRank == HIGH_CARD ){
			for( int x = 0; x < 5; x++ )
				if( myCards[x].value != hand2.myCards[x].value )
					return myCards[x].value < hand2.myCards[x].value;
			return myCards[0].suitRank() < hand2.myCards[0].suitRank();
		}
		if( handRank == PAIR ){
			if( pairValue != hand2.pairValue )
				return pairValue < hand2.pairValue;
			int firstIndex = 0;
			int secondIndex = 0;
			while( firstIndex != 5 && secondIndex != 5 ){
				while( myCards[firstIndex].value == pairValue )
					firstIndex++;
				while( hand2.myCards[secondIndex].value == hand2.pairValue )
                                               secondIndex++;
				if( myCards[firstIndex].value != hand2.myCards[secondIndex].value )
					return myCards[firstIndex].value < hand2.myCards[secondIndex].value;
				firstIndex++;
				secondIndex++;
			}
			return kickerSuit < hand2.kickerSuit;
		}
		if( handRank == TWO_PAIR ){
			if( twoPairValue != hand2.twoPairValue )
				return twoPairValue < hand2.twoPairValue;
			if( pairValue != hand2.pairValue )
				return pairValue < hand2.pairValue;
			if( kickerValue != hand2.kickerValue )
				return kickerValue < hand2.kickerValue;
			return kickerSuit < hand2.kickerSuit;
		}
		if( handRank == THREE_OF_A_KIND ){
			if( valueOfTriple != hand2.valueOfTriple )
				return valueOfTriple < hand2.valueOfTriple;
			for( int x = 0 ; x < 5; x++ )
				if( myCards[x].value != hand2.myCards[x].value )
					return myCards[x].value < hand2.myCards[x].value;
			return myCards[0].suitRank() < hand2.myCards[0].suitRank();
		}
		if(handRank == STRAIGHT ){
			if( myCards[0].value != hand2.myCards[0].value )
				return myCards[0].value < hand2.myCards[0].value;
			return myCards[0].suitRank() < hand2.myCards[0].suitRank();
		}
		if( handRank == FLUSH ){
			for( int x = 0; x < 5; x++ )
				if( myCards[x].value != hand2.myCards[x].value )
					return myCards[x].value < hand2.myCards[x].value;
			return flushSuit < hand2.flushSuit;
		}
		if( handRank == FULL_HOUSE ){
			if( valueOfTriple != hand2.valueOfTriple )
				return valueOfTriple < hand2.valueOfTriple;
			if( doubleCardVal != hand2.doubleCardVal )
				return doubleCardVal < hand2.doubleCardVal;
			for( int x = 0; x < 5; x++ )
				if( myCards[x].suitRank() != hand2.myCards[x].suitRank() )
					return myCards[x].suitRank() < hand2.myCards[x].suitRank();
		}
		if( handRank == FOUR_OF_A_KIND ){
			if( fourKindVal != hand2.fourKindVal )
				return fourKindVal < hand2.fourKindVal;
			for( int x = 0; x < 5; x++ )
				if( myCards[x].value != hand2.myCards[x].value )
					return myCards[x].value < hand2.myCards[x].value;
			for( int x = 0; x < 5; x++ )//the if statement here is guaranteed to trigger once
				if( myCards[x].suitRank() != hand2.myCards[x].suitRank() )
					return myCards[x].suitRank() < hand2.myCards[x].suitRank();
		}
		if( handRank == STRAIGHT_FLUSH ){
			if( myCards[0].value != hand2.myCards[0].value )
				return myCards[0].value < hand2.myCards[0].value;
			return myCards[0].suitRank() < hand2.myCards[0].suitRank();
		}
		if( handRank == ROYAL_FLUSH )
			return flushSuit < hand2.flushSuit;
		return true; //unreachable but neccessary for compiler
	}

	void gradeHand(){
		if( royalFlush() ){
			handRank = ROYAL_FLUSH;
			return;
		}else if( straightFlush() ){
			handRank = STRAIGHT_FLUSH;
			return;
		}else if( fourOfAKind() ){
			handRank = FOUR_OF_A_KIND;
			return;
		}else if( fullHouse() ){
			handRank = FULL_HOUSE;
			return;
		}else if( flush() ){
			handRank = FLUSH;
			return;
		}else if( straight() ){
			handRank = STRAIGHT;
			return;
		}else if( threeOfAKind() ){
			handRank = THREE_OF_A_KIND;
			return;
		}else if( twoPair() ){
			handRank = TWO_PAIR;
			return;
		}else if( pair() ){
			handRank = PAIR;
			return;
		}
		handRank = HIGH_CARD;
	}

	bool royalFlush(){
		for( int x = 0; x < 4; x++ )
			for(int y = 8; y < 14; y++){//indexes in markedCards which can represent a card in the flush
				if( y == 13 ){//reachable only if a royal flush appears
					flushSuit = x;
					return true;
				}
				if( ! markedCards[x][y] )
					break;
			}
		return false;
	}

	bool straightFlush(){
		for( int x = 0; x < 4; x++ ){//does not handle ace low straight flushes
			int curConsecutive = 0;
			for( int y = 0; y < 13; y++ ){
				if( curConsecutive == 5 ){
					flushSuit = x;
					return true;
				}
				if( markedCards[x][y] ){
					curConsecutive++;
				}else
					curConsecutive = 0;
			}
		}
		if( myCards[4].value != 12 )//fifth card is an ace
			return false;
		char potentialSuit = myCards[0].suit;
		if( myCards[3].value != 0 || myCards[3].suit != potentialSuit )//fourth card is a 2
			return false;
		if( myCards[2].value != 1 || myCards[2].suit != potentialSuit )//third card is a 3
			return false;
		if( myCards[1].value != 2 || myCards[1].suit != potentialSuit )//second card is a 4
			return false;
		if( myCards[0].value != 3 || myCards[0].suit != potentialSuit )//first card is a 5
			return false;
		flushSuit = myCards[0].suitRank();
		return true;
	}

	bool fourOfAKind(){
		for( int x = 0; x < 13; x++ )
			if( numEachCard[x] == 4 ){
				fourKindVal = x;
				return true;
			}
		return false;
	}

	bool fullHouse(){
		bool tripleFound = false;
		bool doubleFound = false;
		for( int x = 0; x < 13; x++ ){
			if( numEachCard[x] == 3 ){
				valueOfTriple = x;
				tripleFound = true;
			}else if( numEachCard[x] == 2 ){
				doubleFound = true;
				doubleCardVal = x;
			}
			if( tripleFound && doubleFound )
				return true;
		}
		return false;
	}

	bool flush(){
		for( int x = 0; x < 4; x++ ){
			int suitCount = 0;
			for( int y = 0; y < 13; y++ ){
				if( suitCount == 5 ){
					flushSuit = x;
					return true;
				}
				if( markedCards[x][y] )
					suitCount++;
			}
		}
		return false;
	}

	bool straight(){
                int curConsecutive = 0;
                for( int y = 0; y < 13; y++ ){//
                        if( curConsecutive == 5 )
                                return true;
                        if( numEachCard[y] >=1 ){
                               	curConsecutive++;
			}else
                        	curConsecutive = 0;
         	}
		if( myCards[4].value != 12 )//fifth card is an ace
                        return false;
                if( myCards[3].value != 0 )//fourth card is a 2
                        return false;
                if( myCards[2].value != 1 )//third card is a 3
                        return false;
                if( myCards[1].value != 2 )//second card is a 4
                        return false;
                if( myCards[0].value != 3 )//first card is a 5
                        return false;
                return true;
	}

	bool threeOfAKind(){
                for( int x = 0 ; x < 13; x++ )
			if( numEachCard[x] == 3 ){
				valueOfTriple = x;
				return true;
			}
		return false;

	}

	bool twoPair(){
		bool pairFound = false;
		for( int x = 0; x < 13; x++ )
			if( numEachCard[x] > 1 ){
				if( pairFound ){
					twoPairValue = x;
					markKicker();
					if( twoPairValue < pairValue ){//makes sure the higher value is in twoPairValue
						int temp = pairValue;
						pairValue = twoPairValue;
						twoPairValue = temp;
					}
					return true;
				}else{
					pairValue = x;
					pairFound = true;
				}
			}
		return false;
	}

	void markKicker(){
		for( int x = 0; x < 13; x++ )
			if( numEachCard[x] == 1 )//only triggered when the card is the odd card out of two pairs
				for( int y = 0; y < 5; y++ )
					if( myCards[y].value == x ){
						kickerSuit = myCards[y].suitRank();
						kickerValue = myCards[y].value;
						return;
					}
	}

	bool pair(){
		for( int x = 0; x < 13; x++ ){
			if( numEachCard[x] > 1 ){//true if pair is found
				int suitHighCardNoPair = -1;
				int valueHighCardNoPair = -1;
				for( int y = 0; y < 5; y++ )//finds max value card not part of the pair
					if( (numEachCard[ myCards[y].value ] == 1) && valueHighCardNoPair < myCards[y].value ){
						valueHighCardNoPair = myCards[y].value;
						suitHighCardNoPair = myCards[y].suitRank();
					}
				kickerSuit = suitHighCardNoPair;
				kickerValue = valueHighCardNoPair;
				pairValue = x;
				return true;
			}
		}
		return false;
	}

	void markCards(){
		for( int x =0; x < 4; x++ )
			for( int y = 0; y < 13; y++ )
				markedCards[x][y] = false;
                for( int x = 0; x < 5; x++ ){
                        Card card = myCards[x];
                        markedCards[card.suitRank()][card.value] = true;
                }
	}

};

class poker{
public:
	static string getFullFile( string fileName ){
		ifstream scan(fileName);
		string fullFile = "";
		string line = "";
		while( getline( scan, line ) )
			fullFile += line+'\n';
		fullFile = fullFile.substr(0, 119);
		scan.close();
		return fullFile;
	}

	static void printRawHands( Hand hands[] ){
		cout << "\n\n";
		for( int x = 0; x < 6; x++ ){
			Hand curHand = hands[x];
			cout << "Hand " << (x+1) << ": ";
			for( int y = 0; y < 5; y++ ){
				Card curCard = curHand.myCards[y];
				cout << "(" << curCard.value << ", " << curCard.suit << "), ";
			}
			cout << endl;
		}
		cout << "\n\n";
	}

	static void getFileHands( string fileName, Hand hands[] ){
		ifstream scan(fileName);
		string line;
		int index = 0;
		while( getline( scan, line ) ){
		//for( int x = 0; x < 6; x++ ){
		//	getline( scan, line );
			string rawCards[5];
			Hand hand;
			for( int y= 0; y < 5; y++ )//fill rawCards with strings
				rawCards[y] = line.substr(y*4,3);
			for( int y = 0; y < 5; y++ ){
				string cardString = rawCards[y];
				Card card(-1,'z');
				if( cardString[0] == '1' ){
					card.value = 8;
 					card.suit = cardString[2];
				}else{
					card.value = Card::getValue( cardString[1] );
					card.suit = cardString[2];
				}
				hand.myCards[y] = card;
			}
			hands[index++] = hand;
		}
		scan.close();
	}

	static void printDeckAndHands( Hand hands[], Card cards[], bool random, bool duplicateCard, string fileName, string fullFile ){
		cout << "*** P O K E R  H A N D  A N A L Y Z E R ***\n" << endl;
		if( random ){
			cout << "*** USING RANDOMIZED DECK OF CARDS ***\n\n*** Shuffled 52 card deck:" << endl;
			cout << cards[0].toString() << " ";
			for( int x = 1; x < 52; x++ ){
                               	if( !random && x % 5 == 0 )
                                       	cout << " ";
                               	cout << cards[x].toString() << " ";
				if( x % 13 == 0 )
                                       	cout << endl;
			}
		}else
			cout << "*** USING TEST DECK ***\n\n*** File: " << fileName << endl << fullFile;
		if( duplicateCard )
			return;
		cout << "\n\n*** Here are the six hands..." << endl;
		for( int a = 0; a < 6; a++){
			for( int y = 0; y < 5; y++ )
				cout << hands[a].myCards[y].toString() << " ";
			cout << endl;
		}
		if( !random )
			return;
		cout << "\n*** Here is what remains in the deck..." << endl;
		for( int x = 30; x < 52; x++ )
			cout << cards[x].toString() << " ";
		cout << endl;
	}
	static void printResults( Hand hands[], Hand originalHands[], int indexTracker[] ){
		cout << "\n --- WINNING HAND ORDER ---" << endl;
		for( int x = 0 ; x < 6 ; x++ ){
			int origIndexToPrint = indexTracker[x];
			cout << " " << originalHands[origIndexToPrint].myCards[0].toString();
			for( int y = 1; y < 5; y++ ){
				string cardString = originalHands[origIndexToPrint].myCards[y].toString();
				if( originalHands[origIndexToPrint].myCards[0].value == 8 && y == 1 && cardString.length() == 2 )
					cardString = " " + cardString;
				else if( cardString.length() == 2 )
					cardString = "  " + cardString;
				else
					cardString = " " + cardString;
				cout << cardString;
			}
		cout << " - " << handRanks[hands[x].handRank] << endl;
		}
	}

	static void copyHands( Hand hands[], Hand originalHands[] ){
		for( int x = 0; x < 6; x++ ){
			//Hand newHand();
			//originalHands[x] = newHand;
			for( int y = 0; y < 5; y++ ){
				Card newCard( hands[x].myCards[y].value, hands[x].myCards[y].suit);
				originalHands[x].myCards[y] = newCard;
			}
		}
	}
	static void getRandCards( Card cards[] ){
		char suits[] = {'H','D','S','C'};
		int counter = 0;
		for( int x = 0; x < 4; x++ )
			for( int y = 0; y < 13; y++ ){
				Card newCard( y, suits[x]);
				cards[ counter++ ] = newCard;
			}
		shuffle( cards );
	}

	static void shuffle( Card cards[] ){
		srand( time(0) );//seeds the RNG
		for( int y = 0; y < 3; y++ ){//runs a lot of times because the randomness is not great
			for( int x = 51; x > 0; x-- ){
				int index = rand() % (x+1);
				Card temp = cards[index];
				cards[index] = cards[x];
				cards[x] = temp;
			}
		}
	}

	static void generateRandHands( Card cards[], Hand hands[] ){
		int curHand = 0;
		int iteration = 0;
		for( int x = 0; x < 6; x++ ){
			Hand newHand;
			hands[x] = newHand;
		}
		for( int x = 0 ; x < 30; x++ ){
			hands[curHand].myCards[iteration] = cards[x];
			curHand++;
			if( curHand == 6 ){
				curHand = 0;
				iteration++;
			}
		}
	}

	static void sortEach( Hand hands[] ){
		for( int a = 0; a < 6; a++ ){
			bool anotherPassNeeded = true;
			while( anotherPassNeeded ){
				anotherPassNeeded = false;
				for( int x = 0; x < 4; x++ ){
					if( hands[a].myCards[x].value < hands[a].myCards[x+1].value ){
						Card temp = hands[a].myCards[x];
						hands[a].myCards[x] = hands[a].myCards[x+1];
						hands[a].myCards[x+1] = temp;
						anotherPassNeeded = true;
					}
				}
			}
			hands[a].aceLowStraightCheck();
		}
	}

	static Card checkDuplicateCards( Hand hands[], Card cards[] ){
		bool cardsFound[4][13];
		for( int x = 0 ; x < 4; x++ )
			for( int y = 0; y < 13; y++ )
				cardsFound[x][y] = false;
		for( int x = 0; x < 6; x++ )
			for( int y = 0; y < 5; y++ ){
				int suitRank = hands[x].myCards[y].suitRank();
				int value = hands[x].myCards[y].value;
				if( cardsFound[ suitRank][ value ] )
					return hands[x].myCards[y];
				else
					cardsFound[ suitRank][ value ] = true;
			}
		Card validCard(VALID, 'z');
		return validCard;
	}

};

int main( int argc, char* argv[] ){
	cout << endl;
	Card cards[52];
	Hand hands[6];
	string fileName = "";
	string fullFile = "";
	bool random = argc == 1;
	if( random ){
		poker::getRandCards(cards);
		poker::generateRandHands( cards, hands );
	}else{
		string temp = argv[1];
		fileName = "../handsets/"+temp;//cur directory is the langauge directory
		fullFile = poker::getFullFile(fileName);
		poker::getFileHands( fileName, hands );//this method sets cards to have every card in the hand
	}
	Card duplicateCard( VALID, 'z' );
	if( argc == 2 )
		duplicateCard = poker::checkDuplicateCards( hands, cards );
	poker::printDeckAndHands(hands, cards, random, duplicateCard.value != VALID, fileName, fullFile);
	if( duplicateCard.value != VALID ){
		cout << "\n\n*** ERROR - DUPLICATED CARD FOUND IN DECK ***" << endl;
		cout << "\n\n*** DUPLICATE: " << duplicateCard.toString() << " ***" << endl;
		exit(0);
	}
	Hand originalHands[6];
	poker::copyHands( hands, originalHands );
	poker::sortEach( hands );
	for( int x =0; x < 6; x++ ){
		hands[x].markCards();
		Hand fixSegFault;
		if( x != 5 )
			fixSegFault = hands[x+1];//for some reason this call to NumEachCard sometimes likes to change the values of all the cards in this hand to 0 and all the suitranks to -1
		hands[x].getNumEachCard();
		if( x != 5 )
			hands[x+1] = fixSegFault;
		hands[x].gradeHand();
	}
	int indexTracker[6];
	Hand::sortHands( hands, indexTracker );
	poker::printResults( hands, originalHands, indexTracker );
	return 0;
}
