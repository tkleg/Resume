module poker_module
use hand_module
use card_module
implicit none
contains

        subroutine printCards( hands )
                type(Hand), dimension(0:5) :: hands
		integer :: i, j
                         do i = 0, 5
                                write(*, '(A5,I1,A2)', advance='no') "Hand ", i , ": "
                                do j = 0, 4
                                        write(*, '(A3,A2)', advance='no') hands(i)%myCards(j)%toString(), ", "
                                end do
                                print *, ""
                        end do
        end subroutine printCards

	function copyHands( hands ) result( newHands )
		type(Hand), dimension(0:5) :: hands, newHands
		integer :: i, j, value
		character(len=1) :: suit
		do i = 0, 5
			call newHands(i)%init_Hand()
			do j = 0, 4
				value = hands(i)%myCards(j)%value
				suit = hands(i)%myCards(j)%suit
				call newHands(i)%myCards(j)%init_Card_Vals( value, suit )
			end do
		end do
	end function copyHands

	subroutine getRandCards(cards)
		type(card), dimension(0:51) :: cards
		type(card) :: tempCard
		character(len=1), parameter :: suits(0:3) = [ character(len=1) :: 'H','D','S','C' ]
		integer :: index, i, j
		real :: randNum
		index = 0
		do i = 0, 3
			do j = 0, 12
				call cards(index)%init_Card_Vals( j, suits(i) )
				index = index + 1
			end do
		end do
		
		do i = 0, 3
			do j = 51, 1, -1
				call random_number(randNum)
				index = int( randNum * 52 )
				tempCard = cards(index)
				cards(index) = cards(j)
				cards(j) = tempCard
			end do
		end do

	end subroutine getRandCards
	
	subroutine getRandHands( hands, cards )
		type(Hand), dimension(0:5) :: hands
		type(card), dimension(0:51) :: cards
		integer :: curHand, iteration, i, j
		curHand = 0
		iteration = 0
		do i = 0, 5
			call hands(i)%init_Hand()
		end do
		do j = 0, 29
			hands(curHand)%myCards(iteration)%value = cards(j)%value
			hands(curHand)%myCards(iteration)%suit = cards(j)%suit
			curHand = curHand + 1
			if ( curHand == 6 ) then
				curHand = 0
				iteration = iteration + 1
			end if
		end do
	end subroutine getRandHands

	subroutine sortEach( hands )
		type(hand), dimension(0:5) :: hands
		logical :: anotherPassNeeded
		integer :: i, j
		type(card) :: tempCard
		do i = 0, 5
			anotherPassNeeded = .true.
			do while ( anotherPassNeeded )
				anotherPassNeeded = .false.
				do j = 0, 3
					if ( hands(i)%myCards(j)%value < hands(i)%myCards(j+1)%value ) then
						tempCard = hands(i)%myCards(j)
						hands(i)%myCards(j) = hands(i)%myCards(j+1)
						hands(i)%myCards(j+1) = tempCard
						anotherPassNeeded = .true.
					end if
				end do
			end do
			call hands(i)%aceLowStraightCheck()
		end do
	end subroutine sortEach
	
	function checkDuplicateCards( hands ) result( c )
		type(card) :: c
		type(hand), dimension(0:5) :: hands
		logical, dimension(0:3, 0:12) :: cardsFound
		integer :: i, j, suitRank, value
		do i = 0, 3
			do j = 0, 4
				cardsFound(i,j) = .false.
			end do
		end do
		do i = 0, 5
			do j = 0, 4
				suitRank = hands(i)%myCards(j)%suitRank()
				value = hands(i)%myCards(j)%value
				if ( cardsFound( suitRank, value ) ) then
					call c%init_Card()
					c = hands(i)%myCards(j)
					return
				else
					cardsFound( suitRank, value ) = .true.
				end if
			end do
		end do
		call c%init_Card_Vals(-1,'z')
	end function checkDuplicateCards

	subroutine printDeckAndHands( hands, cards )
		type(hand), dimension(0:5) :: hands
		type(card), dimension(0:51) :: cards
		integer :: i, j
		print *, ""
		print *, "*** P O K E R  H A N D  A N A L Y Z E R ***"
		print *, ""
		print *, ""
		print *, "*** USING RANDOMIZED DECK OF CARDS ***"
		print *, ""
		print *, ""
		print *, "*** Shuffled 52 card deck:"
		print *, ""
		do i = 1, 51
			if (   mod(i, 5) == 0  ) then
				write(*, '(A1)', advance='no') " "
			end if
			write(*, '(A3A1)', advance='no') cards(i)%toString(), " "
			if( mod(i, 13) == 0 ) then
				print *, ""
			end if
		end do
		print *, ""
		print *, ""
		print *, "*** Here are the six hands..."
		do i = 0, 5
			do j = 0, 4
				write(*, '(A3A1)', advance='no') hands(i)%myCards(j)%toString(), " "
			end do
			print *, ""
		end do
		print *, ""
		print *, "*** Here is what remains in the deck..."
		do i = 30, 51
			write(*, '(A3A1)', advance='no') cards(i)%toString(), " "
		end do
		print *, ""
	end subroutine printDeckAndHands

	subroutine printResults( hands, originalHands, indexTracker )
		integer :: i, j, origIndexToPrint
		character(len=:), allocatable :: cardString
		type(hand), dimension(0:5) :: hands, originalHands
		integer, dimension(0:5) :: indexTracker
		character(len=*), parameter :: handRanks(0:9) = [ character(len=20) :: "High Card", "Pair", "Two Pair", "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind", "Straight Flush", "Royal Flush"]
		print *, ""
		print *, "--- WINNING HAND ORDER ---"
		do i = 0, 5
			origIndexToPrint = indexTracker(i)
			write(*, '(A1A3)', advance='no') " ", originalHands(origIndexToPrint)%myCards(0)%toString()
			do j = 1, 4
				cardString = originalHands(origIndexToPrint)%myCards(j)%toString()
				if ( originalHands(origIndexToPrint)%myCards(j)%value == 8 .and. j == 1 .and. len(cardString) == 2 ) then
					cardString = " " // cardString
				else if ( len(cardString) == 2 ) then
					cardString = "  " // cardString
				else
					cardString = " " // cardString
				end if
				write(*, '(A4)', advance='no') cardString
			end do
			write(*, '(A3A20)') " - ", handRanks( hands(i)%handRank )
		end do
	end subroutine printResults

	function sortHands ( hands ) result( indexTracker )
                type(Hand), dimension(0:5) :: hands
                type(Hand) :: tempHand
                integer, dimension(0:5) :: indexTracker
                integer :: i, tempIndex
                logical :: anotherPassNeeded
!                allocate( hands(0:4) )
                do i = 0, 5
                        indexTracker(i) = i
                end do
                anotherPassNeeded = .true.
                do while( anotherPassNeeded )
                        anotherPassNeeded = .false.
                        do i = 0, 4
                                if ( hands(i)%losesTo( hands(i+1) ) ) then
                                        anotherPassNeeded = .true.

                                        tempHand = hands(i)
                                        hands(i) = hands(i+1)
                                        hands(i+1) = tempHand

                                        tempIndex = indexTracker(i)
                                        indexTracker(i) = indexTracker(i+1)
                                        indexTracker(i+1) = tempIndex
                                end if
                        end do
                end do

        end function sortHands

end module poker_module
