using Random
include("Hand.jl")

function getFullFile()
	f = open("../handsets/"*ARGS[1],"r")
	return read(f, String)
end

function getFileCards()
	f = open("../handsets/"*ARGS[1],"r")
	allhands = read(f, String)
	close(f)
	rawCards = split(allhands, [',','\n'], keepempty=false)
	
	#convert cards to an OffsetArray and changes them to Strings
	#strip removes the space before every card that is not a 10
	stringCards = Array{String,1}(undef,30)
	cards = Array{Card,1}(undef,30)
	for x in 1:30
		cardString = ""*strip(rawCards[x])
		#only untrue if the card has a 10 value
		if length( cardString ) == 2
			cards[x] = Card( getValue(cardString[1]),  cardString[2] )
		else
			cards[x] = Card( 9, cardString[3] )
		end
	end

	return cards	
end

function getFileHands( cards::Array{Card,1} )
	hands = Array{Hand,1}(undef, 6)
	counter = 1
	for x in 1:6
		hands[x] = Hand()
		for y in 1:5
			hands[x].myCards[y] = cards[ counter ]
			counter += 1
		end
	end
	return hands
end

#function indexOfFace( face::Char )
#	for x in 0:12
#		if string(face) == FACES[x]
#			return x
#		end
#	end
#end

function printDeckAndHands( hands::Array{Hand,1}, cards::Array{Card,1}, random::Bool, duplicateCard::Bool, fileName::String, fullFile::String )
	println("\n*** P O K E R  H A N D  A N A L Y Z E R ***\n")
	if random
		println("\n*** USING RANDOMIZED DECK OF CARDS ***\n\n*** Shuffled 52 card deck:")
		print( toString( cards[1] )*" " )
		for x in 2:52
			if !random && x % 5 == 0
				print(" ")
			end
			print( toString( cards[x] )*" " )
			if x % 13 == 0
				println()
			end
		end
		println()
	else
		println("\n*** USING TEST DECK ***\n\n*** File: "*fileName*"\n"*fullFile)
	end
	if duplicateCard
		return
	end
	println("*** Here are the six hands...")
	for x in 1:6
		for y in 1:5
			print( toString( hands[x].myCards[y] )*" " )
		end
		println()
	end
	if !random
		return
	end
	println("\n*** Here is what remains in the deck...")
	for x in 31:52
		print( toString( cards[x] )*" " )
	end
	println()
end

function printResults( hands::Array{Hand,1}, originalHands::Array{Hand,1}, indexTracker::Array{Int,1} )
	println("\n --- WINNING HAND ORDER ---")
	for x in 1:6
		origIndexToPrint = indexTracker[x]
		print( " "*toString( originalHands[origIndexToPrint].myCards[1] ) )
		for y in 2:5
			handHelp = originalHands[origIndexToPrint]
			cardString = toString( handHelp.myCards[y] )
			#below is statement handles cases where first two cards are 10s
			if y == 3 && handHelp.myCards[2].value == 9 && originalHands[origIndexToPrint].myCards[1].value == 9
				cardString = " "*cardString
			elseif originalHands[origIndexToPrint].myCards[1].value == 9 && y == 2 && length( cardString ) == 2
				cardString = " "*cardString
			elseif length( cardString ) == 2
				cardString = "  "*cardString
			else
				cardString = " "*cardString
			end
			print(cardString)
		end
		println( " - "*HAND_RANKS[hands[x].handRank] )
	end
end

function copyHands( hands::Array{Hand,1} )
	originalHands = Array{Hand,1}(undef, 6)
	for x in 1:6
		originalHands[x] = Hand()
		for y in 1:5
			originalHands[x].myCards[y] = Card( hands[x].myCards[y].value, hands[x].myCards[y].suit )
		end
	end
	return originalHands
end

function getRandCards()
	cards = Array{Card,1}(undef, 52)
	#cards = Array{Card}(undef,52)
	suits = ['H','D','S','C']
	counter = 1
	for x in 1:4
		for y in 1:13
			cards[ counter ] = Card( y, suits[x] )
			counter += 1
		end
	end

	return shuffle( cards )
end

function getRandomHands( cards::Array{Card,1} )
	hands = Array{Hand,1}(undef, 6)
	curHand = 1
	iteration = 1
	for x in 1:6
		hands[x] = Hand()
	end
	for x in 1:30
		hands[curHand].myCards[iteration] = cards[x]
		curHand += 1
		if curHand == 7
			curHand = 1
			iteration += 1
		end
	end
	return hands
end

function sortEach( hands::Array{Hand,1} )
	for a in 1:6
		anotherPassNeeded = true
		while anotherPassNeeded
			anotherPassNeeded = false
			for x in 1:4
				if hands[a].myCards[x].value < hands[a].myCards[x+1].value
					temp = hands[a].myCards[x]
					hands[a].myCards[x] = hands[a].myCards[x+1]
					hands[a].myCards[x+1] = temp
					anotherPassNeeded = true
				end
			end
		end
		aceLowStraightCheck( hands[a] )
	end
end

function quickPrint( hand::Hand )
	println("======")
        for card in hand.myCards
                print( toString(card)*" ")
        end
	println("\n"*HAND_RANKS[hand.handRank])
        println("======")
end

function checkDuplicateCards( hands::Array{Hand,1}, cards::Array{Card,1} )
	cardsFound = Array{Bool,2}(undef, 4, 13 )
	for x in 1:6
		for y in 1:5
			sRank = suitRank( hands[x].myCards[y] )
			value = hands[x].myCards[y].value
			if cardsFound[ sRank, value ]
				return hands[x].myCards[y]
			else
				cardsFound[ sRank, value ] = true
			end
		end
	end
	return Card( VALID, 'z' )
end

random = length(ARGS) == 0

cards = nothing
hands = nothing
fileName = ""
fullFile = ""
if random
	cards = getRandCards()
	hands = getRandomHands(cards)
else
	fileName = "../handsets/"*ARGS[1]
	fullFile = getFullFile()
	cards = getFileCards()
	hands = getFileHands( cards )
end
duplicateCard = Card( -1, 'z' )
if !random
	duplicateCard = checkDuplicateCards(hands, cards)
end
#println("*****"*toString(duplicateCard)*"***")
printDeckAndHands( hands, cards, random, duplicateCard.value != -1, fileName, fullFile )
if duplicateCard.value != -1
	println("*** ERROR - DUPLICATE CARD FOUND IN DECK ***")
	println("\n\n*** DUPLICATE: "*toString(duplicateCard)*" ***")
	exit(0)
end
originalHands = copyHands( hands )
sortEach( hands )
for hand in hands
	markCards( hand )
	getNumEachCard( hand )
	gradeHand( hand )
end
#for x in 1:6
#	for y in 1:5
#		print( toString(hands[x].myCards[y])*" ")
#	end
#	println()
#end
indexTracker = sortHands(hands)

printResults(hands, originalHands, indexTracker)
