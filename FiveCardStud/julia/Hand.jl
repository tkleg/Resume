include("Card.jl")

mutable struct Hand
	myCards::Array{Card,1}
	markedCards::Array{Bool,2}
	numEachCard::Array{Int,1}
	handRank::Int
	flushSuit::Int
	kickerSuit::Int
	kickerValue::Int
	pairHighSuit::Int
	valueOfTriple::Int
	fourKindVal::Int
	pairValue::Int
	twoPairValue::Int
	doubleCardVal::Int
end

function Hand()
	return Hand(Array{Card,1}(undef, 5), 
	Array{Bool,2}(undef, 4, 13),
	zeros(Int, 13),
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1 )
end

function aceLowStraightCheck(hand::Hand)
	if hand.myCards[1].value != 13
		return
	end
	if hand.myCards[2].value != 4
		return
	end
	if hand.myCards[3].value != 3
		return
	end
	if hand.myCards[4].value != 2
		return
	end
	if hand.myCards[5].value != 1
		return
	end
	holdAce = hand.myCards[1]
	for x in 1:4
		hand.myCards[x] = hand.myCards[x+1]
	end
	hand.myCards[5] = holdAce
end

function getNumEachCard(hand::Hand)
	for x in 1:5
		hand.numEachCard[hand.myCards[x].value] += 1
	end
end

function sortHands( hands::Array{Hand,1} )
	indexTracker = Array{Int,1}(undef, 6)
	for x in 1:6
		indexTracker[x] = x
	end
	anotherPassNeeded = true
	while anotherPassNeeded
		anotherPassNeeded = false
		for x in 1:5
			if losesTo( hands[x], hands[x+1] )
				anotherPassNeeded = true
				tempHand = hands[x]
				hands[x] = hands[x+1]
				hands[x+1] = tempHand

				tempIndex = indexTracker[x]
				indexTracker[x] = indexTracker[x+1]
				indexTracker[x+1] = tempIndex
			end
		end
	end
	return indexTracker
end

function losesTo( hand::Hand, hand2::Hand )
	if hand.handRank != hand2.handRank
		return hand.handRank < hand2.handRank
	elseif hand.handRank == HIGH_CARD
		for x in 1:5
			if hand.myCards[x].value != hand2.myCards[x].value
				return hand.myCards[x].value < hand2.myCards[x].value
			end
		end
		return suitRank(hand.myCards[1]) < suitRank(hand2.myCards[1])
	elseif hand.handRank == PAIR
		if hand.pairValue != hand2.pairValue
			return hand.pairValue < hand2.pairValue
		end
		for x in 1:5
			if hand.myCards[x].value != hand2.myCards[x].value
				return hand.myCards[x].value < hand2.myCards[x].value
			end
		end
#		firstIndex = 1
#		secondIndex = 1
#		while firstIndex != 6 && secondIndex != 6
#			while hand.myCards[firstIndex].value == hand.pairValue
#				firstIndex += 1
#			end
#			while hand2.myCards[secondIndex].value == hand2.pairValue
#				secondIndex += 1
#			end
#			if hand.myCards[firstIndex].value == hand2.myCards[secondIndex].value
#				return hand.myCards[firstIndex].value < hand2.myCards[secondIndex].value
#			end
#			firstIndex += 1
#			secondIndex += 1
#		end
		return hand.kickerSuit < hand2.kickerSuit
	elseif hand.handRank == TWO_PAIR
		if hand.twoPairValue != hand2.twoPairValue
			return hand.twoPairValue < hand2.twoPairValue
		elseif hand.pairValue != hand2.pairValue
			return hand.pairValue < hand2.pairValue
		elseif hand.kickerValue != hand2.kickerValue
			return hand.kickerValue < hand2.kickerValue
		end
		return hand.kickerSuit < hand2.kickerSuit
	elseif hand.handRank == THREE_OF_A_KIND
		return hand.valueOfTriple < hand2.valueOfTriple
	elseif hand.handRank == STRAIGHT
		if hand.myCards[1].value != hand2.myCards[1].value
			return hand.myCards[1].value < hand2.myCards[1].value
		end
		return suitRank( hand.myCards[1] ) < suitRank( hand2.myCards[1] )
	elseif hand.handRank == FLUSH
		for x in 1:5
			if hand.myCards[x].value != hand2.myCards[x].value
				return hand.myCards[x].value < hand2.myCards[x].value
			end
		end
		return hand.flushSuit < hand2.flushSuit
	elseif hand.handRank == FULL_HOUSE
		return hand.valueOfTriple < hand2.valueOfTriple
	elseif hand.handRank == FOUR_OF_A_KIND
		return hand.fourKindVal < hand2.fourKindVal
	elseif hand.handRank == STRAIGHT_FLUSH
		if hand.myCards[1].value != hand2.myCards[1].value
			return hand.myCards[1].value < hand2.myCards[1].value
		end
		return suitRank( hand.myCards[1] ) < suitRank( hand2.myCards[1] )
	elseif hand.handRank == ROYAL_FLUSH
		return hand.flushSuit < hand2.flushSuit
	end
end

function fourOfAKind( hand::Hand )
	for x in 1:13
		if hand.numEachCard[x] == 4
			hand.fourKindVal = x
			return true
		end
	end
	return false
end

function fullHouse( hand::Hand )
	tripleFound = false
	doubleFound = false
	for x in 1:13
		if hand.numEachCard[x] == 3
			hand.valueOfTriple = x
			tripleFound = true
		elseif hand.numEachCard[x] == 2
			hand.doubleCardVal = x
			doubleFound = true
		end
		if tripleFound && doubleFound
			return true
		end
	end
	return false
end

function royalFlush( hand::Hand )
	for x in 1:4
		for y in 9:14
			if y == 14
				hand.flushSuit = x
				return true
			end
			if ! hand.markedCards[x,y]
				break
			end
		end
	end
	return false
end

function straightFlush( hand::Hand )
	for x in 1:4
		curConsecutive = 0
		for y in 1:13
			if curConsecutive == 5
				hand.flushSuit = x
				return true
			elseif hand.markedCards[x,y]
				curConsecutive += 1
			else
				curConsecutive = 0
			end
		end
	end
	if hand.myCards[5].value != 13
			return false
	end
	potentialSuit = hand.myCards[5].suit
	for x in 1:4
		if hand.myCards[x].value != (5-x) || hand.myCards[x].suit != potentialSuit
			return false
		end
	end
	hand.flushSuit = suitRank( hand.myCards[1] )
	return true
end

function flush( hand::Hand )
	potentialSuit = hand.myCards[1].suit
	for x in 2:5
		if hand.myCards[x].suit != potentialSuit
			return false
		end
	end
	hand.flushSuit = suitRank( hand.myCards[1] )
	return true
end

function straight( hand::Hand )
	curConsecutive = 0
	for y in 1:13
		if curConsecutive == 5
			return true
		elseif hand.numEachCard[y] == 1
			curConsecutive += 1
		else
			curConsecutive = 0
		end
	end
	if hand.myCards[5].value != 13
		return false
	end
	for x in 1:4
		if hand.myCards[x].value != (5-x)
			return false
		end
	end
	return true
end

function threeOfAKind( hand::Hand )
	for x in 1:13
		if hand.numEachCard[x] == 3
			hand.valueOfTriple = x
			return true
		end
	end
	return false
end

function twoPair( hand::Hand )
	pairFound = false
	for x in 1:13
		if hand.numEachCard[x] > 1
			if pairFound
				hand.twoPairValue = x
				markKicker( hand )
				if hand.twoPairValue < hand.pairValue
					temp = hand.pairValue
					hand.pairValue = hand.twoPairValue
					hand.twoPairValue = temp
				end
				return true
			else
				hand.pairValue = x
				pairFound = true
			end
		end
	end
	return false
end

function markKicker( hand::Hand )
	for x in 1:13
		if hand.numEachCard[x] == 1
			for y in 1:5
				if hand.myCards[y].value == x
					hand.kickerSuit = suitRank( hand.myCards[y] )
					hand.kickerValue = hand.myCards[y].value
					return
				end
			end
		end
	end
end

function pair( hand::Hand )
	for x in 1:13
		if hand.numEachCard[x] == 2
			suitHighCardNoPair = -1
			valueHighCardNoPair = -1
			for y in 1:5
				if hand.numEachCard[ hand.myCards[y].value ] == 1 && valueHighCardNoPair < hand.myCards[y].value
					valueHighCardNoPair = hand.myCards[y].value
					suitHighCardNoPair = suitRank( hand.myCards[y] )
				end
			end
			hand.kickerSuit = suitHighCardNoPair
			hand.kickerValue = valueHighCardNoPair
			hand.pairValue = x
			return true
		end
	end
	return false
end

function markCards( hand::Hand )
	for x in 1:5
		card = hand.myCards[x]
		hand.markedCards[ suitRank(card), card.value ] = true
	end
end

function gradeHand( hand::Hand )
	if royalFlush( hand )
		hand.handRank = ROYAL_FLUSH
	elseif straightFlush( hand )
		hand.handRank = STRAIGHT_FLUSH
	elseif fourOfAKind( hand )
		hand.handRank = FOUR_OF_A_KIND
	elseif fullHouse( hand )
		hand.handRank = FULL_HOUSE
	elseif flush( hand )
		hand.handRank = FLUSH
	elseif straight( hand )
		hand.handRank = STRAIGHT
	elseif threeOfAKind( hand )
		hand.handRank = THREE_OF_A_KIND
	elseif twoPair( hand )
		hand.handRank = TWO_PAIR
	elseif pair( hand )
		hand.handRank = PAIR
	else
		hand.handRank = HIGH_CARD
	end
end
