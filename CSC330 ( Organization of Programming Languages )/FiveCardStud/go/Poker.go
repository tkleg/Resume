package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"strings"
	"time"
)

const (
	HIGH_CARD = iota
	PAIR
	TWO_PAIR
	THREE_OF_A_KIND
	STRAIGHT
	FLUSH
	FULL_HOUSE
	FOUR_OF_A_KIND
	STRAIGHT_FLUSH
	ROYAL_FLUSH
)

var HAND_RANKS = []string{"High Card", "Pair", "Two Pair", "Three of a Kind", "Straight", "Flush", "Full House", "Four Of A Kind", "Straight Flush", "Royal Flush"}

func getFileHands(cards []Card) [6]Hand {
	var hands [6]Hand
	counter := 0
	for i := 0; i < 6; i++ {
		for j := 0; j < 5; j++ {
			hands[i].myCards[j] = cards[counter]
			counter++
		}
	}
	return hands
}

func getRandCards() []Card {
	rand.Seed(time.Now().UnixNano())
	var cards []Card
	suits := []rune{'H', 'D', 'S', 'C'}
	for x := 0; x < 4; x++ {
		for y := 0; y < 13; y++ {
			card := Card{y, suits[x]}
			cards = append(cards, card)
		}
	}
	for i := len(cards) - 1; i > 0; i-- {
		j := rand.Intn(i + 1)
		cards[i], cards[j] = cards[j], cards[i]
	}
	return cards
}

func getFullFile() string {
	file, _ := os.Open("../handsets/" + os.Args[1])
	//if err != nil{
	//	fmt.Errorf("Error opening file");
	//}
	scanner := bufio.NewScanner(file)
	var fullFile string = ""
	for scanner.Scan() {
		fullFile += scanner.Text() + "\n"
	}
	//line below removes the last new line char before returning
	return fullFile
}

func getFileCards(fullFile string) []Card {
	var cards []Card
	//var cardStrings [30]string
	lines := strings.Split(fullFile, "\n")
	//cuts the 7th ( empty ) line from a handset
	lines = lines[:len(lines)-1]
	for _, line := range lines {
		lineStrings := strings.Split(line, ",")
		for i := range lineStrings {
			lineStrings[i] = strings.TrimSpace(lineStrings[i])
			if len(lineStrings[i]) == 2 {
				card := Card{getValue(rune(lineStrings[i][0])), rune(lineStrings[i][1])}
				cards = append(cards, card)
			} else {
				card := Card{8, rune(lineStrings[i][2])}
				cards = append(cards, card)
			}
		}
	}
	return cards
}

type Card struct {
	value int
	suit  rune
}

/*
	func new(newValue int, newSuit rune) *Card{
	        return &Card{
	                value : newValue,
	                suit : newSuit,
	        }
	}
*/
func suitRank(suit rune) int {
	switch suit {
	case 'D':
		return 0
	case 'C':
		return 1
	case 'H':
		return 2
	case 'S':
		return 3
	default:
		return -1
	}
}

func getValue(face rune) int {
	switch face {
	case '2', '3', '4', '5', '6', '7', '8', '9':
		return (int(face) - int('0')) - 2
	case 'J':
		return 9
	case 'Q':
		return 10
	case 'K':
		return 11
	case 'A':
		return 12
	default:
		return -1
	}
}

func (card Card) toString() string {
	face := ""
	switch card.value {
	case 12:
		face = "A"
	case 11:
		face = "K"
	case 10:
		face = "Q"
	case 9:
		face = "J"
	case 8:
		face = "10"
	default:
		face = string(card.value + '0' + 2)
	}
	return face + string(card.suit)
}

type Hand struct {
	myCards       [5]Card
	markedCards   [4][13]bool
	numEachCard   [13]int
	handRank      int
	flushSuit     int
	kickerSuit    int
	kickerValue   int
	pairHighSuit  int
	valueOfTriple int
	fourKindVal   int
	pairValue     int
	twoPairValue  int
	doubleCardVal int
}

func getRandHands(cards []Card) [6]Hand {
	var hands [6]Hand
	curHand := 0
	iteration := 0
	for i := 0; i < 30; i++ {
		hands[curHand].myCards[iteration] = cards[i]
		curHand++
		if curHand == 6 {
			curHand = 0
			iteration++
		}
	}
	return hands
}

func printRawHands(hands [6]Hand) {
	for i := 0; i < 6; i++ {
		for j := 0; j < 5; j++ {
			fmt.Print(hands[i].myCards[j].toString() + " ")
		}
		fmt.Println()
	}
}

func checkDuplicateCards(hands [6]Hand) Card {
	var cardsFound [4][13]bool
	for i := 0; i < 6; i++ {
		for j := 0; j < 5; j++ {
			sRank := suitRank(hands[i].myCards[j].suit)
			value := hands[i].myCards[j].value
			if cardsFound[sRank][value] {
				return hands[i].myCards[j]
			} else {
				cardsFound[sRank][value] = true
			}
		}
	}
	return Card{-1, 'z'}
}

func printDeckAndHands(hands [6]Hand, cards []Card, random bool, dupPresent bool, fullFile string) {
	fmt.Println("\n*** P O K E R  H A N D  A N A L Y Z E R ***\n")
	if random {
		fmt.Println("\n*** USING RANDOMIZED DECK OF CARDS ***\n\n*** Shuffled 52 card deck:")
		fmt.Print(cards[0].toString() + " ")
		for x := 1; x < 52; x++ {
			fmt.Print(cards[x].toString() + " ")
			if x%13 == 0 {
				fmt.Println()
			}
		}
		fmt.Println()
	} else {
		fmt.Print("\n*** USING TEST DECK ***\n\n*** File: ../handsets/" + os.Args[1] + "\n" + fullFile)

	}
	if dupPresent {
		return
	}
	fmt.Println("\n*** Here are the six hands...")
	for x := 0; x < 6; x++ {
		for y := 0; y < 5; y++ {
			fmt.Print(hands[x].myCards[y].toString() + " ")
		}
		fmt.Println()
	}
	if !random {
		return
	}
	fmt.Println("\n*** Here is what remains in the deck...")
	for x := 30; x < 52; x++ {
		fmt.Print(cards[x].toString() + " ")
	}
	fmt.Println()
}

func copyHands(hands [6]Hand) [6]Hand {
	var originalHands [6]Hand
	for x := 0; x < 6; x++ {
		for y := 0; y < 5; y++ {
			holdVal := hands[x].myCards[y].value
			holdSuit := hands[x].myCards[y].suit
			originalHands[x].myCards[y] = Card{holdVal, holdSuit}
		}
	}
	return originalHands
}

func sortEach(hands [6]Hand) [6]Hand {
	for x := 0; x < 6; x++ {
		anotherPassNeeded := true
		for anotherPassNeeded {
			anotherPassNeeded = false
			for y := 0; y < 4; y++ {
				if hands[x].myCards[y].value < hands[x].myCards[y+1].value {
					anotherPassNeeded = true
					temp := hands[x].myCards[y]
					hands[x].myCards[y] = hands[x].myCards[y+1]
					hands[x].myCards[y+1] = temp
				}
			}
		}
		hands[x] = aceLowStraight(hands[x])
	}
	return hands
}

func aceLowStraight(hand Hand) Hand {
	if hand.myCards[0].value != 12 {
		return hand
	} else if hand.myCards[1].value != 3 {
		return hand
	} else if hand.myCards[2].value != 2 {
		return hand
	} else if hand.myCards[3].value != 1 {
		return hand
	} else if hand.myCards[4].value != 0 {
		return hand
	}
	temp := hand.myCards[0]
	for x := 0; x < 4; x++ {
		hand.myCards[x] = hand.myCards[x+1]
	}
	hand.myCards[4] = temp
	return hand
}

func markCards(hand Hand) [4][13]bool {
	var markedCards [4][13]bool
	for x := 0; x < 5; x++ {
		sRank := suitRank(hand.myCards[x].suit)
		markedCards[sRank][hand.myCards[x].value] = true
	}
	return markedCards
}

func getNumEachCard(myCards [5]Card) [13]int {
	var numEachCard [13]int
	for x := 0; x < 5; x++ {
		numEachCard[myCards[x].value]++
	}
	return numEachCard
}

func (hand *Hand) royalFlush() bool {
	for x := 0; x < 4; x++ {
		for y := 8; y < 14; y++ {
			if y == 13 {
				hand.flushSuit = x
				return true
			}
			if !hand.markedCards[x][y] {
				break
			}
		}
	}
	return false
}

func (hand *Hand) straightFlush() bool {
	for x := 0; x < 4; x++ {
		curConsecutive := 0
		for y := 0; y < 13; y++ {
			if curConsecutive == 5 {
				hand.flushSuit = x
				return true
			} else if hand.markedCards[x][y] {
				curConsecutive++
			} else {
				curConsecutive = 0
			}
		}
	}
	if hand.myCards[4].value != 12 {
		return false
	}
	potentialSuit := hand.myCards[4].suit
	for x := 0; x < 4; x++ {
		if hand.myCards[x].value != (3-x) || potentialSuit != hand.myCards[x].suit {
			return false
		}
	}
	hand.flushSuit = suitRank(hand.myCards[0].suit)
	return true
}

func (hand *Hand) flush() bool {
	potentialSuit := hand.myCards[0].suit
	for x := 1; x < 5; x++ {
		if hand.myCards[x].suit != potentialSuit {
			return false
		}
	}
	hand.flushSuit = suitRank(hand.myCards[0].suit)
	return true
}

func (hand *Hand) straight() bool {
	curConsecutive := 0
	for y := 0; y < 13; y++ {
		if curConsecutive == 5 {
			return true
		} else if hand.numEachCard[y] == 1 {
			curConsecutive++
		} else {
			curConsecutive = 0
		}
	}
	if hand.myCards[4].value != 12 {
		return false
	}
	for x := 0; x < 4; x++ {
		if hand.myCards[x].value != (3 - x) {
			return false
		}
	}
	return true
}

func (hand *Hand) threeOfAKind() bool {
	for x := 0; x < 13; x++ {
		if hand.numEachCard[x] == 3 {
			hand.valueOfTriple = x
			return true
		}
	}
	return false
}

func (hand *Hand) twoPair() bool {
	pairFound := false
	for x := 0; x < 13; x++ {
		if hand.numEachCard[x] > 1 {
			if pairFound {
				hand.twoPairValue = x
				hand.markKicker()
				if hand.twoPairValue < hand.pairValue {
					temp := hand.pairValue
					hand.pairValue = hand.twoPairValue
					hand.twoPairValue = temp
				}
				return true
			} else {
				hand.pairValue = x
				pairFound = true
			}
		}
	}
	return false
}

func (hand *Hand) markKicker() {
	for x := 0; x < 13; x++ {
		if hand.numEachCard[x] == 1 {
			for y := 0; y < 5; y++ {
				if hand.myCards[y].value == x {
					hand.kickerSuit = suitRank(hand.myCards[y].suit)
					hand.kickerValue = hand.myCards[y].value
					return
				}
			}
		}
	}
}

func (hand *Hand) fourOfAKind() bool {
	for x := 0; x < 13; x++ {
		if hand.numEachCard[x] == 4 {
			hand.fourKindVal = x
			return true
		}
	}
	return false
}

func (hand *Hand) fullHouse() bool {
	tripleFound := false
	doubleFound := false
	for x := 0; x < 13; x++ {
		if hand.numEachCard[x] == 3 {
			hand.valueOfTriple = x
			tripleFound = true
		} else if hand.numEachCard[x] == 2 {
			hand.doubleCardVal = x
			doubleFound = true
		}
		if doubleFound && tripleFound {
			return true
		}
	}
	return false
}

func (hand *Hand) pair() bool {
	for x := 0; x < 13; x++ {
		if hand.numEachCard[x] == 2 {
			suitHighCardNoPair := -1
			valueHighCardNoPair := -1
			for y := 0; y < 5; y++ {
				if hand.numEachCard[hand.myCards[y].value] == 1 && valueHighCardNoPair < hand.myCards[y].value {
					valueHighCardNoPair = hand.myCards[y].value
					suitHighCardNoPair = suitRank(hand.myCards[y].suit)
				}
			}
			hand.kickerSuit = suitHighCardNoPair
			hand.kickerValue = valueHighCardNoPair
			hand.pairValue = x
			return true
		}
	}
	return false
}

func (hand *Hand) gradeHand() {
	if hand.royalFlush() {
		hand.handRank = ROYAL_FLUSH
	} else if hand.straightFlush() {
		hand.handRank = STRAIGHT_FLUSH
	} else if hand.fourOfAKind() {
		hand.handRank = FOUR_OF_A_KIND
	} else if hand.fullHouse() {
		hand.handRank = FULL_HOUSE
	} else if hand.flush() {
		hand.handRank = FLUSH
	} else if hand.straight() {
		hand.handRank = STRAIGHT
	} else if hand.threeOfAKind() {
		hand.handRank = THREE_OF_A_KIND
	} else if hand.twoPair() {
		hand.handRank = TWO_PAIR
	} else if hand.pair() {
		hand.handRank = PAIR
	} else {
		hand.handRank = HIGH_CARD
	}
}

func sortHands(hands *[6]Hand) [6]int {
	var indexTracker [6]int
	for x := 0; x < 6; x++ {
		indexTracker[x] = x
	}
	anotherPassNeeded := true
	for anotherPassNeeded {
		anotherPassNeeded = false
		for x := 0; x < 5; x++ {
			if hands[x].losesTo(hands[x+1]) {
				anotherPassNeeded = true
				tempHand := hands[x]
				hands[x] = hands[x+1]
				hands[x+1] = tempHand

				tempIndex := indexTracker[x]
				indexTracker[x] = indexTracker[x+1]
				indexTracker[x+1] = tempIndex
			}
		}
	}
	return indexTracker
}

func (this Hand) losesTo(hand2 Hand) bool {
	if this.handRank != hand2.handRank {
		return this.handRank < hand2.handRank
	} else if this.handRank == HIGH_CARD {
		for x := 0; x < 5; x++ {
			if this.myCards[x].value != hand2.myCards[x].value {
				return this.myCards[x].value < hand2.myCards[x].value
			}
		}
		return suitRank(this.myCards[0].suit) < suitRank(hand2.myCards[0].suit)
	} else if this.handRank == PAIR {
		if this.pairValue != hand2.pairValue {
			return this.pairValue < hand2.pairValue
		}
		for x := 0; x < 5; x++ {
			if this.myCards[x].value != hand2.myCards[x].value {
				return this.myCards[x].value < hand2.myCards[x].value
			}
		}
		return this.kickerSuit < hand2.kickerSuit
	} else if this.handRank == TWO_PAIR {
		if this.twoPairValue != hand2.twoPairValue {
			return this.twoPairValue < hand2.twoPairValue
		} else if this.pairValue != hand2.pairValue {
			return this.pairValue < hand2.pairValue
		} else if this.kickerValue != hand2.kickerValue {
			return this.kickerValue < hand2.kickerValue
		} else {
			return this.kickerSuit < hand2.kickerSuit
		}
	} else if this.handRank == THREE_OF_A_KIND {
		return this.valueOfTriple < hand2.valueOfTriple
	} else if this.handRank == STRAIGHT {
		if this.myCards[0].value != hand2.myCards[0].value {
			return this.myCards[0].value < hand2.myCards[0].value
		}
		return suitRank(this.myCards[0].suit) < suitRank(hand2.myCards[0].suit)
	} else if this.handRank == FLUSH {
		for x := 0; x < 5; x++ {
			if this.myCards[x].value != hand2.myCards[x].value {
				return this.myCards[x].value < hand2.myCards[x].value
			}
		}
		return this.flushSuit < hand2.flushSuit
	} else if this.handRank == FULL_HOUSE {
		return this.valueOfTriple < hand2.valueOfTriple
	} else if this.handRank == FOUR_OF_A_KIND {
		return this.fourKindVal < hand2.fourKindVal
	} else if this.handRank == STRAIGHT_FLUSH {
		if this.myCards[0].value != hand2.myCards[0].value {
			return this.myCards[0].value < hand2.myCards[0].value
		}
		return suitRank(this.myCards[0].suit) < suitRank(hand2.myCards[0].suit)
	} else {
		return this.flushSuit < hand2.flushSuit
	}
}

func printResults(hands [6]Hand, originalHands [6]Hand, indexTracker [6]int) {
	fmt.Println("\n --- WINNING HAND ORDER ---")
	for x := 0; x < 6; x++ {
		origIndexToPrint := indexTracker[x]
		fmt.Print(" " + originalHands[origIndexToPrint].myCards[0].toString())
		for y := 1; y < 5; y++ {
			handHelp := originalHands[origIndexToPrint]
			cardString := handHelp.myCards[y].toString()
			if y == 2 && handHelp.myCards[1].value == 8 && handHelp.myCards[0].value == 8 {
				cardString = " " + cardString
			} else if handHelp.myCards[0].value == 8 && y == 1 && len(cardString) == 2 {
				cardString = " " + cardString
			} else if len(cardString) == 2 {
				cardString = "  " + cardString
			} else {
				cardString = " " + cardString
			}
			fmt.Print(cardString)
		}
		fmt.Println(" - " + HAND_RANKS[hands[x].handRank])
	}
}

func main() {
	var cards []Card
	var hands [6]Hand
	var random bool = len(os.Args) == 1
	//	fmt.Println(len(os.Args))
	var fullFile string = ""
	if !random {
		fullFile = getFullFile()
		cards = getFileCards(fullFile)
		hands = getFileHands(cards)
	} else {
		cards = getRandCards()
		hands = getRandHands(cards)
	}

	var duplicateCard Card = Card{-1, 'z'}
	if !random {
		duplicateCard = checkDuplicateCards(hands)
	}
	var dupPresent bool = duplicateCard.value != -1
	printDeckAndHands(hands, cards, random, dupPresent, fullFile)
	if dupPresent {
		fmt.Println("\n*** ERROR - DUPLICATE CARD FOUND IN DECK ***")
		fmt.Println("\n\n*** DUPLICATE: " + duplicateCard.toString() + " ***")
		os.Exit(0)
	}

	var originalHands [6]Hand = copyHands(hands)
	hands = sortEach(hands)
	for x := 0; x < 6; x++ {
		hands[x].markedCards = markCards(hands[x])
		hands[x].numEachCard = getNumEachCard(hands[x].myCards)
		hands[x].gradeHand()
	}

	indexTracker := sortHands(&hands)

	printResults(hands, originalHands, indexTracker)
	/*for x := 0; x < 6; x++ {
		fmt.Print("\n" + strconv.Itoa(hands[x].handRank))
	}*/
}
