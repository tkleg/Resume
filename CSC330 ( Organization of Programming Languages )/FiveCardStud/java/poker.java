import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.io.File;
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.lang.String;

public class poker{

	public static final int HIGH_CARD = 0;
	public static final int PAIR = 1;
	public static final int TWO_PAIR = 2;
	public static final int THREE_OF_A_KIND = 3;
	public static final int STRAIGHT = 4;
	public static final int FLUSH = 5;
	public static final int FULL_HOUSE = 6;
	public static final int FOUR_OF_A_KIND = 7;
	public static final int STRAIGHT_FLUSH = 8;
	public static final int ROYAL_FLUSH = 9;
	public static final int VALID = -1;//used for Card.value for duplicateCard

	public static final String[] faces = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
        public static final String[] handRanks = {"High Card","Pair","Two Pair","Three of a Kind","Straight","Flush","Full House","Four of a Kind","Straight Flush","Royal Flush"};

	public static void main(String[] args) throws FileNotFoundException{
		Card[] cards = new Card[1];//initialized to satisfy compiler
		Hand[] hands;
		String fileName = "";
		String fullFile = "";
		boolean random = args.length == 0;
		if( random ){
			cards = getRandCards();
			hands = generateRandHands( cards );
		}else{
			fileName = "../handsets/"+args[0];//cur directory is the langauge directory
			fullFile = getFullFile(fileName);
			hands = getFileHands( fileName );//this method sets cards to have every card in the hand
		}
		Card duplicateCard = new Card( -1, 'z' );
		if( !random )//random card generation guarantees no duplicates
			duplicateCard = checkDuplicateCards( hands, cards );
		printDeckAndHands( hands, cards, random, duplicateCard.value != VALID, fileName, fullFile);
                if( duplicateCard.value != VALID ){
                        System.out.println("\n\n*** ERROR - DUPLICATED CARD FOUND IN DECK ***");
                        System.out.println("\n\n*** DUPLICATE: "+duplicateCard.toString() +" ***");
                        System.exit(0);
                }
		Hand[] originalHands = copyHands( hands );
		sortEach(hands);
		for( int x = 0; x < 6; x++ ){
			hands[x].markCards();
			hands[x].getNumEachCard();
			hands[x].gradeHand();
		}
		int[] indexTracker = Hand.sortHands(hands);
		printResults( hands, originalHands, indexTracker );
	}

	public static String getFullFile( String fileName ) throws FileNotFoundException{
		Scanner scan = new Scanner( new File( fileName ) );
		String fullFile = "";
		while( scan.hasNextLine() )
			fullFile += scan.nextLine() + "\n";
		return fullFile.substring(0,119);//file sive always is the same, this excludes the final linebreak
	}

	public static Hand[] getFileHands( String fileName ) throws FileNotFoundException{
		Scanner scan = new Scanner( new File( fileName ) );
		Hand[] hands = new Hand[6];
		for( int x = 0; x < 6; x++ ){
			String line = scan.nextLine();
			String[] rawCards= line.split(",");
			Hand hand = new Hand();
			for( int y = 0; y < 5; y++ ){
				String cardString = rawCards[y];
				Card card = new Card();//constructor call necessary for compiler
				if( cardString.charAt(0) == '1' )//true if the card is a 10
					card = new Card( 8, cardString.charAt(2) );
				else
					card = new Card( Card.getValue( cardString.charAt(1) ), cardString.charAt(2) );
				hand.myCards[y] = card;
			}
			hands[x] = hand;
		}
		return hands;
	}

	public static void printDeckAndHands( Hand[] hands, Card[] cards, boolean random, boolean duplicateCard, String fileName, String fullFile ){
		System.out.println("\n*** P O K E R  H A N D  A N A L Y Z E R ***\n");
		if( random ){
			System.out.println("*** USING RANDOMIZED DECK OF CARDS ***\n\n*** Shuffled 52 card deck:");
			System.out.print( cards[0].toString()+" ");//necessary cause the loop will print a line after the first card elsewise
                        for( int x = 1; x < 52; x++ ){
                                if( !random && x % 5 == 0 )
                                        System.out.print(" ");
                                System.out.print( cards[x].toString()+" ");
                                if( x % 13 == 0 )
                                        System.out.println();
                        }
		}else{
			System.out.print("*** USING TEST DECK ***\n\n*** File: "+fileName+"\n"+fullFile);//last space is to indent the first card properly
		}
		if( duplicateCard )//below in this method only runs for valid decks
			return;
		System.out.println("\n\n*** Here are the six hands...");
		for( int x = 0; x < 6; x++){
			for( int y = 0; y < 5; y++ )
				System.out.print(hands[x].myCards[y].toString()+" ");
			System.out.println();
		}
		if( !random )//rest of method is for random decks only
			return;
		System.out.println("\n*** Here is what remains in the deck...");
		for( int x = 30; x < 52; x++ )//card at index 25 is the first card that wont be part of any hand
			System.out.print(cards[x].toString()+" ");
		System.out.println();
	}

	public static void printResults( Hand[] hands, Hand[] originalHands, int[] indexTracker ){
		System.out.println("\n --- WINNING HAND ORDER ---");
		for( int x = 0 ; x < 6 ; x++ ){
			int origIndexToPrint = indexTracker[x];//lets us print unsorted hands once assigned grades after being sorted
			System.out.print( " "+originalHands[origIndexToPrint].myCards[0].toString() );
			for( int y = 1; y < 5; y++ ){
				String cardString = originalHands[origIndexToPrint].myCards[y].toString();
				if( originalHands[origIndexToPrint].myCards[0].value == 8 && y == 1 && cardString.length() == 2 )//fixes hand being printing off center when first card is a 10
					cardString = " " + cardString;
				else if( cardString.length() == 2 )
					cardString = "  " + cardString;
				else
					cardString = " " + cardString;
				System.out.print(cardString);
			}
			System.out.println( " - "+handRanks[hands[x].handRank] );
		}
	}

	public static Hand[] copyHands( Hand[] hands ){
		Hand[] originalHands = new Hand[6];
		for( int x = 0; x < 6; x++ ){
			originalHands[x] = new Hand();
			for( int y = 0; y < 5 ; y++ )
				originalHands[x].myCards[y] = new Card(hands[x].myCards[y].value, hands[x].myCards[y].suit);
		}
		return originalHands;
	}

	public static void printHandsDiagnostic( Hand[] hands, String[] faces, String[] handRanks ){//gives more info about each hand, not used in program at final use, but used in development
		for( int y = 0; y < 6; y++ ){
                        System.out.print( "Hand " + (y+1) + "= { ");
                        for( int x = 0; x < 5; x++ )
				System.out.print( faces[hands[y].myCards[x].value] + hands[y].myCards[x].suit+", ");
			System.out.println(handRanks[hands[y].handRank]+":"+hands[y].flushSuit+":"+hands[y].kickerSuit+":"+hands[y].pairHighSuit+"}");
		}
	}

	public static Card[] getRandCards(){
		Card[] cards = new Card[52];
		char[] suits = {'H','D','S','C'};
		int counter = 0;
                for( int x = 0; x < 4; x++ )//one iteration per suit
                        for( int y = 0; y < 13; y++ )//2 through Ace
                                cards[ counter++ ] = new Card(y, suits[x]);
                List<Card> cardList = Arrays.asList( cards );
                Collections.shuffle( cardList );
                cardList.toArray( cards );
		return cards;
	}

	public static Hand[] generateRandHands(Card[] cards){
		Hand[] hands = new Hand[6];
		int curHand = 0;//used to rotate which hand a card is assigned to
		int iteration = 0;//used to go to the next spot in the card[] for a hand after an index is filled for every hand
		for( int x = 0; x < 6; x++ )
			hands[x] = new Hand();
                for( int x = 0; x < 30; x++ ){
			hands[curHand].myCards[iteration] = cards[x];
			curHand++;
			if( curHand == 6 ){//one rotation of dealing done if true
				curHand = 0;
				iteration++;
			}
		}
		return hands;
	}

	public static void sortEach( Hand[] hands ){
		for( int a = 0; a < 6; a++ ){
			boolean anotherPassNeeded = true;
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

	public static Card checkDuplicateCards( Hand[] hands, Card[] cards ){
		boolean[][] cardsFound = new boolean[4][13];
		for( int x = 0 ; x < 6; x++ )
			for( int y = 0; y < 5; y++ ){
				int suitRank = hands[x].myCards[y].suitRank();
				int value = hands[x].myCards[y].value;
				if( cardsFound[ suitRank ][ value ] )
					return hands[x].myCards[y];
				else
					cardsFound[ suitRank ][ value ] = true;

			}
		return new Card(VALID, 'z');//signals no duplicate found
	}

}

class Card{
	int value;
	char suit;

	public Card(){}

	public Card( int value, char suit ){
		this.value = value;
		this.suit = suit;
	}


	public int suitRank(){
		switch( this.suit ){
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

	public static int getValue( char c ){
		if( c >= '2' && c <= '9' )
			return  Integer.parseInt(""+c ) - 2;
		switch(c){
			case 'J': return 9;
			case 'Q': return 10;
			case 'K': return 11;
			case 'A': return 12;
		}
		return -1;//unreachable but necessary for compiler
	}

	public String toString(){
		return poker.faces[value]+suit;
	}

}

class Hand{
	public Card[] myCards = new Card[5];
	public boolean[][] markedCards;
	public int[] numEachCard;
	public int handRank = -1;
	public int flushSuit = -1;//suit of the flush
	public int kickerSuit = -1;//suit of the kicker card in a two pair
	public int kickerValue = -1;
	public int pairHighSuit = -1;//suit of the highest value card not in the pair
	public int valueOfTriple = -1;//value of the card appearing 3 times in a full house or three of a kind
	public int fourKindVal = -1;
	public int pairValue = -1;
	public int twoPairValue = -1;
	public int doubleCardVal = -1;//for full house
	public Hand(){}

	public void aceLowStraightCheck(){
                if( myCards[0].value != 12 )//is the 1st card an ace
                        return;
                if( myCards[1].value != 3 )//is the 2nd card a 5
                        return;
                if( myCards[2].value != 2 )//is the 3rd card a 4
                        return;
                if( myCards[3].value != 1 )//is the 4th card a 3
                        return;
                if( myCards[4].value != 0 )//is the 5th card a 2
                        return;

                //reachable if an ace-low straight is present. puts the ace at the end
                Card holdAce = myCards[0];
                for( int x= 0; x < 4; x++ )
                        myCards[x] = myCards[x+1];
                myCards[4] = holdAce;
        }

	public void getNumEachCard(){
		numEachCard = new int[13];
                	for( int x = 0 ; x < 5; x++ )
                        	numEachCard[myCards[x].value]++;
	}

	public static int[] sortHands( Hand[] hands ){
		int[] indexTracker = new int[6];
		for( int x = 0; x < 6; x++ )
			indexTracker[x] = x;
		boolean anotherPassNeeded = true;
		while( anotherPassNeeded ){
			anotherPassNeeded = false;
			for( int x = 0 ; x < 5; x++ )//iterating through each hand except the last
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
		return indexTracker;
	}

	public boolean losesTo( Hand hand2 ){
		//win by better handRank
		if( this.handRank != hand2.handRank )
			return this.handRank < hand2.handRank;
		switch( this.handRank ){
			case poker.HIGH_CARD:
				for( int x = 0; x < 5; x++ )
					if( this.myCards[x].value != hand2.myCards[x].value )
						return this.myCards[x].value < hand2.myCards[x].value;
				return this.myCards[0].suitRank() < hand2.myCards[0].suitRank();
			case poker.PAIR:
				if( this.pairValue != hand2.pairValue )
					return this.pairValue < hand2.pairValue;
				int firstIndex = 0;
				int secondIndex = 0;
				while( firstIndex != 5 && secondIndex != 5 ){
					while( this.myCards[firstIndex].value == this.pairValue )
						firstIndex++;
					while( hand2.myCards[secondIndex].value == hand2.pairValue )
                                                secondIndex++;
					if( this.myCards[firstIndex].value != hand2.myCards[secondIndex].value )
						return this.myCards[firstIndex].value < hand2.myCards[secondIndex].value;
					firstIndex++;
					secondIndex++;
				}
				return this.kickerSuit < hand2.kickerSuit;
			case poker.TWO_PAIR:
				if( this.twoPairValue != hand2.twoPairValue )
					return this.twoPairValue < hand2.twoPairValue;
				if( this.pairValue != hand2.pairValue )
					return this.pairValue < hand2.pairValue;
				if( this.kickerValue != hand2.kickerValue )
					return this.kickerValue < hand2.kickerValue;
				return this.kickerSuit < hand2.kickerSuit;
			case poker.THREE_OF_A_KIND:
				if( this.valueOfTriple != hand2.valueOfTriple )
					return this.valueOfTriple < hand2.valueOfTriple;
				for( int x = 0 ; x < 5; x++ )
					if( this.myCards[x].value != hand2.myCards[x].value )
						return this.myCards[x].value < hand2.myCards[x].value;
				return this.myCards[0].suitRank() < hand2.myCards[0].suitRank();
			case poker.STRAIGHT:
				if( this.myCards[0].value != hand2.myCards[0].value )
					return this.myCards[0].value < hand2.myCards[0].value;
				return this.myCards[0].suitRank() < hand2.myCards[0].suitRank();
			case poker.FLUSH:
				for( int x = 0; x < 5; x++ )
					if( this.myCards[x].value != hand2.myCards[x].value )
						return this.myCards[x].value < hand2.myCards[x].value;
				return this.flushSuit < hand2.flushSuit;
			case poker.FULL_HOUSE:
				if( this.valueOfTriple != hand2.valueOfTriple )
					return this.valueOfTriple < hand2.valueOfTriple;
				if( this.doubleCardVal != hand2.doubleCardVal )
					return this.doubleCardVal < hand2.doubleCardVal;
				for( int x = 0; x < 5; x++ )
					if( this.myCards[x].suitRank() != hand2.myCards[x].suitRank() )
						return this.myCards[x].suitRank() < hand2.myCards[x].suitRank();
			case poker.FOUR_OF_A_KIND:
				if( this.fourKindVal != hand2.fourKindVal )
					return this.fourKindVal < hand2.fourKindVal;
				for( int x = 0; x < 5; x++ )
					if( this.myCards[x].value != hand2.myCards[x].value )
						return this.myCards[x].value < hand2.myCards[x].value;
				for( int x = 0; x < 5; x++ )//the if statement here is guaranteed to trigger once
					if( this.myCards[x].suitRank() != hand2.myCards[x].suitRank() )
						return this.myCards[x].suitRank() < hand2.myCards[x].suitRank();
			case poker.STRAIGHT_FLUSH:
				if( this.myCards[0].value != hand2.myCards[0].value )
					return this.myCards[0].value < hand2.myCards[0].value;
				return this.myCards[0].suitRank() < hand2.myCards[0].suitRank();
			case poker.ROYAL_FLUSH:
				return this.flushSuit < hand2.flushSuit;
		}
		/*for( int x = 0 ; x < 5; x++ ){
			if( this.myCards[x].value > hand2.myCards[x].value )
				return false;
			if( this.myCards[x].value < hand2.myCards[x].value )
				return true;
		}
		switch(this.handRank){
			case poker.ROYAL_FLUSH:
				return this.flushSuit < hand2.flushSuit;
			case poker.STRAIGHT_FLUSH:
				return this.flushSuit < hand2.flushSuit;
			case poker.FOUR_OF_A_KIND:
				return this.fourKindVal < hand2.fourKindVal;
			case poker.FULL_HOUSE:
				return this.valueOfTriple < hand2.valueOfTriple;
			case poker.FLUSH:
				return this.flushSuit < hand2.flushSuit;
			case poker.STRAIGHT:
				return this.myCards[0].suitRank() < hand2.myCards[0].suitRank();
			case poker.THREE_OF_A_KIND:
				return this.valueOfTriple < hand2.valueOfTriple;
			case poker.TWO_PAIR:
				return this.kickerSuit < hand2.kickerSuit;
			case poker.PAIR: 
				return this.pairHighSuit < hand2.pairHighSuit;
			case poker.HIGH_CARD:
				return this.myCards[0].suitRank() < hand2.myCards[0].suitRank();
		}*/
		return true;//unreachable but neccessary for compiler
	}

	public void gradeHand(){
		if( royalFlush() ){
			handRank = poker.ROYAL_FLUSH;
			return;
		}else if( straightFlush() ){
			handRank = poker.STRAIGHT_FLUSH;
			return;
		}else if( fourOfAKind() ){
			handRank = poker.FOUR_OF_A_KIND;
			return;
		}else if( fullHouse() ){
			handRank = poker.FULL_HOUSE;
			return;
		}else if( flush() ){
			handRank = poker.FLUSH;
			return;
		}else if( straight() ){
			handRank = poker.STRAIGHT;
			return;
		}else if( threeOfAKind() ){
			handRank = poker.THREE_OF_A_KIND;
			return;
		}else if( twoPair() ){
			handRank = poker.TWO_PAIR;
			return;
		}else if( pair() ){
			handRank = poker.PAIR;
			return;
		}
		handRank = poker.HIGH_CARD;
	}

	public boolean royalFlush(){
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

	public boolean straightFlush(){
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
		if( myCards[3].value != 0 || myCards[3].suit != potentialSuit )//fourth card is a 5
			return false;
		if( myCards[2].value != 1 || myCards[2].suit != potentialSuit )//third card is a 4
			return false;
		if( myCards[1].value != 2 || myCards[1].suit != potentialSuit )//second card is a 2
			return false;
		if( myCards[0].value != 3 || myCards[0].suit != potentialSuit )//first card is a 5
			return false;
		flushSuit = myCards[0].suitRank();
		return true;
	}

	public boolean fourOfAKind(){
		for( int x = 0; x < 13; x++ )
			if( numEachCard[x] == 4 ){
				fourKindVal = x;
				return true;
			}
		return false;
	}

	public boolean fullHouse(){
		boolean tripleFound = false;
		boolean doubleFound = false;
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

	public boolean flush(){
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
	public boolean straight(){
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
                if( myCards[3].value != 0 )//fourth card is a 5
                        return false;
                if( myCards[2].value != 1 )//third card is a 4
                        return false;
                if( myCards[1].value != 2 )//second card is a 2
                        return false;
                if( myCards[0].value != 3 )//first card is a 5
                        return false;
                return true;

	}

	public boolean threeOfAKind(){
                for( int x = 0 ; x < 13; x++ )
			if( numEachCard[x] == 3 ){
				valueOfTriple = x;
				return true;
			}
		return false;

	}

	public boolean twoPair(){
		boolean pairFound = false;
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

	public void markKicker(){
		for( int x = 0; x < 13; x++ )
			if( numEachCard[x] == 1 )//only triggered when the card is the odd card out of two pairs
				for( int y = 0; y < 5; y++ )
					if( myCards[y].value == x ){
						kickerSuit = myCards[y].suitRank();
						kickerValue = myCards[y].value;
						return;
					}
	}

	public boolean pair(){
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

	public void markCards(){
		markedCards = new boolean[4][13];
                for( int x = 0; x < 5; x++ ){
                        Card card = this.myCards[x];
                        markedCards[card.suitRank()][card.value] = true;
                }

	}

}
