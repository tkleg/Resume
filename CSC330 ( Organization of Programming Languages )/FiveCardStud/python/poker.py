
import random
import sys

HIGH_CARD = 0
PAIR = 1
TWO_PAIR = 2
THREE_OF_A_KIND = 3
STRAIGHT = 4
FLUSH = 5
FULL_HOUSE = 6
FOUR_OF_A_KIND = 7
STRAIGHT_FLUSH = 8
ROYAL_FLUSH = 9
VALID = -1

faces = ["2","3","4","5","6","7","8","9","10","J","Q","K","A"]

handRanks = ["High Card","Pair","Two Pair","Three of a Kind","Straight","Flush","Full House","Four of a Kind","Straight Flush","Royal Flush"]

suits = ['H','D','S','C']

class Card:

	def __init__( self, value = 0, suit = '\0' ):
		self.value = value
		self.suit = suit

	def suitRank(self):
		val = self.suit
		if val == 'D':
			return 3
		if val == 'C':
			return 2
		if val == 'H':
			return 1
		if val == 'S':
			return 0
		return -1

	@staticmethod
	def getValue( c ):
		if (c >= '2') and ( c <= '9' ):
			return ( ord(c) - 2 )
		if c == 'J':
			return 9
		if c == 'Q':
			return 10
		if c == 'K':
			return 11
		if c == 'A':
			return 12
		return -1

	def toString(self):
		return faces[ self.value ] + self.suit

class Hand:

	def __init__(self):
		self.handRank = -1
		self.flushSuit = -1
		self.kickerSuit = -1
		self.kickerValue = -1
		self.pairHighSuit = -1
		self.valueOfTriple = -1
		self.fourKindVal = -1
		self.pairValue = -1
		self.twoPairValue = -1
		self.doubleCardVal = -1
		self.myCards = [Card() for _ in range(5)]
		self.markedCards = [[ False for _ in range(13) ] for _ in range(4)]
		self.numEachCard = [0 for _ in range(13)]

	def aceLowStraightCheck(self):
		if self.myCards[0].value != 12:
			return
		#this loop checks if the cards are not 5, 4, 3, 2
		for x in range(1,5):
			if self.myCards[x].value != (4-x):
				return

		holdAce = self.myCards[0]
		for x in range(4):
			self.myCards[x] = self.myCards[x+1]
		self.myCards[4] = holdAce

	def getNumEachCard(self):
		for x in range(5):
			self.numEachCard[ self.myCards[x].value ] += 1

	@staticmethod
	def sortHands(hands):
		indexTracker = [ x for x in range(6) ]
		anotherPassNeeded = True
		while anotherPassNeeded:
			anotherPassNeeded = False
			for x in range(5):
				if hands[x].losesTo( hands[x+1] ):
					anotherPassNeeded = True
					tempHand = hands[x]
					hands[x] = hands[x+1]
					hands[x+1] = tempHand

					tempIndex = indexTracker[x]
					indexTracker[x] = indexTracker[x+1]
					indexTracker[x+1] = tempIndex
		return indexTracker

	def losesTo(self, hand2 ):
		if self.handRank != hand2.handRank:
			return self.handRank < hand2.handRank
		if self.handRank == HIGH_CARD:
			for x in range(5):
				if self.myCards[x].value != hand2.myCards[x].value:
					return self.myCards[x].value < hand2.myCards[x].value
			return this.myCards[0].suitRank() < hand2.myCards[0].suitRank()
		elif self.handRank == PAIR:
			if self.pairValue != hand2.pairValue:
				return self.pairValue < hand2.pairValue
			firstIndex = 0
			secondIndex = 0
			while (firstIndex != 5) and (secondIndex != 5):
				while self.myCards[firstIndex].value == self.pairValue:
					firstIndex += 1
				while hand2.myCards[secondIndex].value == hand2.pairValue:
					secondIndex += 1
				if self.myCards[firstIndex].value != hand2.myCards[secondIndex].value:
					return self.myCards[firstIndex].value < hand2.myCards[secondIndex].value
				firstIndex += 1
				secondIndex += 1
			return self.kickerSuit < hand2.kickerSuit
		elif self.handRank == TWO_PAIR:
			if self.twoPairValue != hand2.twoPairValue:
				return self.twoPairValue < hand2.twoPairValue
			if self.pairValue != hand2.pairValue:
				return self.pairValue < hand2.pairValue
			if self.kickerValue != hand2.kickerValue:
				return self.kickerValue < hand2.kickerValue
			return self.kickerSuit < hand2.kickerSuit
		elif self.handRank == THREE_OF_A_KIND:
			return self.valueOfTriple < hand2.valueOfTriple
		elif self.handRank == STRAIGHT:
			if self.myCards[0].value != hand2.myCards[0].value:
				return self.myCards[0].value < hand2.myCards[0].value
			return self.myCards[0].suitRank() < hand2.myCards[0].suitRank()
		elif self.handRank == FLUSH:
			for x in range(5):
				if self.myCards[x].value != hand2.myCards[x].value:
					return self.myCards[x].value < hand2.myCards[x].value
			return self.flushSuit < hand2.flushSuit
		elif self.handRank == FULL_HOUSE:
			return self.valueOfTriple < hand2.valueOfTriple
		elif self.handRank == FOUR_OF_A_KIND:
			if self.fourKindVal != hand2.fourKindVal:
				return self.fourKindVal < hand2.fourKindVal
			for x in range(5):
				if self.myCards[x].value != hand2.myCards[x]:
					return self.myCards[x].value < hand2.myCards[x].value
			for x in range(5):
				if self.myCards[x].suitRank() != hand2.myCards[x].suitRank():
					return self.myCards[x].suitRank() < hand2.myCards[x].suitRank()
		elif self.handRank == STRAIGHT_FLUSH:
			if self.myCards[0].value != hand2.myCards[0].value:
				return self.myCards[0].value < hand2.myCards[0].value
			return self.myCards[0].suitRank() < hand2.myCards[0].suitRank()
		elif self.handRank == ROYAL_FLUSH:
			return self.flushSuit < hand2.flushSuit
		return True

	def gradeHand(self):
		if self.royalFlush():
			self.handRank = ROYAL_FLUSH
		elif self.straightFlush():
			self.handRank = STRAIGHT_FLUSH
		elif self.fourOfAKind():
			self.handRank = FOUR_OF_A_KIND
		elif self.fullHouse():
			self.handRank = FULL_HOUSE
		elif self.flush():
			self.handRank = FLUSH
		elif self.straight():
			self.handRank = STRAIGHT
		elif self.threeOfAKind():
			self.handRank = THREE_OF_A_KIND
		elif self.twoPair():
			self.handRank = TWO_PAIR
		elif self.pair():
			self.handRank = PAIR
		else:
			self.handRank = HIGH_CARD

	def royalFlush(self):
		for x in range(4):
			for y in range(8,14):
				if y == 13:
					self.flushSuit = x
					return True
				#the code below is meant to get around some syntax errors
				if not self.markedCards[x][y]:
					break
		return False

	def straightFlush(self):
		return self.straight() and self.flush()

	def fourOfAKind(self):
		for x in range(13):
			if self.numEachCard[x] == 4:
				self.fourKindVal = x
				return True
		return False

	def fullHouse(self):
		tripleFound = False
		doubleFound = False
		for x in range(13):
			if self.numEachCard[x] == 3:
				self.valueOfTriple = x
				tripleFound = True
			elif self.numEachCard[x] == 2:
				doubleFound = True
				doubleCardVal = x
			if tripleFound and doubleFound:
				return True
		return False

	def flush(self):
		potentialSuit = self.myCards[0].suit
		for card in self.myCards:
			if card.suit != potentialSuit:
				return False
		return True

	def straight(self):
		curConsecutive = 0
		for x in range(13):
			if curConsecutive == 5:
				return True
			if self.numEachCard[x] == 1:
				curConsecutive += 1
			else:
				curConsecutive = 0
		if self.myCards[4].value != 12:
			return False
		for x in range(4):
			if self.myCards[x].value != (3-x):
				return False
		return True

	def threeOfAKind(self):
		for x in range(13):
			if self.numEachCard[x] == 3:
				self.valueOfTriple = x
				return True
		return False

	def twoPair(self):
		pairFound = False
		for x in range(13):
			if self.numEachCard[x] > 1:
				if pairFound:
					self.twoPairValue = x
					self.markKicker()
					if self.twoPairValue < self.pairValue:
						temp = self.pairValue
						self.pairValue = self.twoPairValue
						self.twoPairValue = temp
					return True
				else:
					self.pairValue = x
					pairFound = True
		return False

	def markKicker(self):
		for x in range(13):
			if self.numEachCard[x] == 1:
				for y in range(5):
					if self.myCards[y].value == x:
						self.kickerSuit == self.myCards[y].suit
						self.kickerValue = self.myCards[y].value
						return

	def pair(self):
		for x in range(13):
			if self.numEachCard[x] > 1:
				suitHighCardNoPair = -1
				valueHighCardNoPair = -1
				for y in range(5):
					if (self.numEachCard[self.myCards[y].value] == 1) and ( valueHighCardNoPair < self.myCards[y].value ):
						valueHighCardNoPair = self.myCards[y].value
						suitHighCardNoPair = self.myCards[y].suitRank()
				self.kickerSuit = suitHighCardNoPair
				self.kickerValue = valueHighCardNoPair
				self.pairValue = x
				return True
		return False

	def markCards(self):
		for x in range(5):
			card = self.myCards[x]
			self.markedCards[ card.suitRank() ][ card.value ] = True

class poker:

	@staticmethod
	def printDeckAndHands( hands, card, rand, duplicateCard, fileName, fullFile ):
		print("\n*** P O K E R  H A N D  A N A L Y Z E R ***\n")
		if rand:
			print("*** USING RANDOMIZED DECK OF CARDS ***\n\n*** Shuffled 52 card deck:")
			print( cards[0].toString(), end = " " )
			for x in range(1,52):
				if  ( not rand )  and ( x % 5 == 0 ):
					print(" ", end = "")
				print( cards[x].toString(), end = " " )
				if x % 13 == 0:
					print()
		else:
			print("*** USING TEST DECK ***\n\n*** File: ", fileName, "\n", fullFile, end = "" )
		if duplicateCard:
			return
		print("\n\n*** Here are the six hands...")
		for x in range(6):
			for y in range(5):
				print( hands[x].myCards[y].toString(), end = " " )
			print()
		if not rand:
			return
		print("\n*** Here is what remains in the deck...")
		for x in range(30,52):
			print( cards[x].toString(), end = " " )

	@staticmethod
	def printResults( hands, originalHands, indexTracker ):
		print("\n\n --- WINNING HAND ORDER ---")
		for x in range(6):
			origIndexToPrint = indexTracker[x]
			print(" ", originalHands[origIndexToPrint].myCards[0].toString(), end = "" )
			for y in range(1, 5):
				cardString = originalHands[origIndexToPrint].myCards[y].toString()
				if originalHands[origIndexToPrint].myCards[0].value == 8 and y == 1 and len(cardString) == 2:
					cardString = " " + cardString
				elif len(cardString) == 2:
					cardString = "  " + cardString
				else:
					cardString = " " + cardString
				print( cardString, end = "" )
			print( " - ", handRanks[hands[x].handRank] )

	@staticmethod
	def copyHands( hands ):
		originalHands = [Hand() for _ in range(6)]
		for x in range(6):
			for y in range(5):
				originalHands[x].myCards[y] = hands[x].myCards[y]
		return originalHands

	@staticmethod
	def getRandCards():
		cards = [Card() for _ in range(52)]
		counter = 0
		for x in range(4):
			for y in range(13):
				cards[ counter ] = Card( y, suits[x] )
				counter += 1
		random.shuffle( cards )
		return cards

	@staticmethod
	def generateRandHands( cards ):
		hands = [Hand() for _ in range(6)]
		curHand = 0
		iteration = 0
		for x in range(30):
			hands[curHand].myCards[iteration] = cards[x]
			curHand += 1
			if curHand == 6:
				curHand = 0
				iteration += 1
		return hands

	@staticmethod
	def sortEach( hands ):
		for a in range(6):
			anotherPassNeeded = True
			while anotherPassNeeded:
				anotherPassNeeded = False
				for x in range(4):
					if hands[a].myCards[x].value < hands[a].myCards[x+1].value:
						temp = hands[a].myCards[x]
						hands[a].myCards[x] = hands[a].myCards[x+1]
						hands[a].myCards[x+1] = temp
						anotherPassNeeded = True
			hands[a].aceLowStraightCheck()

	@staticmethod
	def checkDuplicateCards( hands, cards ):
		cardsFound = [ [False for _ in range(13)] for _ in range(4)]
		for x in range(6):
			for y in range(5):
				suitRank = hands[x].myCards[y].suitRank()
				value = hands[x].myCards[y].value
				if cardsFound[ suitRank ][ value ]:
					return Card( value, hands[x].myCards[y].suit )
				else:
					cardsFound[ suitRank ][ value ] = True
		return Card( VALID, 'z' )




def getFullFile( fileName ):
	with open(fileName, "r") as file:
		return file.read()[1:]
#[1:] remoes additinal space at the front

def getFileHands( fileName, hands ):
	file = open( fileName, "r" )
	for x in range(6):
		line = file.readline()
		rawCards = line.split(",")
		hand = Hand()
		for y in range(5):
			cardString = rawCards[y]
			card = Card()
			if cardString[0] == '1':
				card.value = 8
				card.suit = cardString[2]
			else:
				card.value = faces.index( cardString[1] )
				card.suit = cardString[2]
			hand.myCards[y] = card
		hands[x] = hand
	return hands



cards = [Card()]
hands = [Hand() for _ in range(6)]
fileName = ""
fullFile = ""
rand = len( sys.argv ) == 1
if rand:
        cards = poker.getRandCards()
        hands = poker.generateRandHands( cards )
else:
        fileName = "../handsets/"+ sys.argv[1]
        fullFile = getFullFile( fileName )
        getFileHands( fileName, hands )
duplicateCard = Card( VALID, 'z' )
if not rand:
	card = poker.checkDuplicateCards(hands, cards)
	if card.value != VALID:
		duplicateCard.value = card.value
		duplicateCard.suit = card.suit
poker.printDeckAndHands( hands, cards, rand, duplicateCard.value != VALID, fileName, fullFile )
if duplicateCard.value != VALID:
        print("\n\n*** ERROR - DUPLICATED CARD FOUND IN DECK ***")
        print("\n\n*** DUPLICATE: ",duplicateCard.toString()," ***")
        sys.exit()
originalHands = poker.copyHands( hands )
poker.sortEach( hands )
for x in range(6):
        hands[x].markCards()
        hands[x].getNumEachCard()
        hands[x].gradeHand()
indexTracker = Hand.sortHands( hands )
#for a in range(6):
#	for x in range(4):
#			for y in range(13):
#				if hands[a].markedCards[x][y]:
#					print("(",faces[y],suits[x],")", end = " ")
#			print()
poker.printResults( hands, originalHands, indexTracker )
