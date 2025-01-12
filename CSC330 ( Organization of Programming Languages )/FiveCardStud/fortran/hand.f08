module hand_module
	use card_module
	private
	public :: Hand, init_Hand, aceLowStraightCheck,	getNumEachCard, gradeHand, markKicker, markCards
	public :: losesTo, royalFlush, straightFlush, fourOfAKind, fullHouse, flush, straight, twoPair, pair, threeOfAKind, getHandRank	
	character(len=*), parameter :: faces(0:12) = [ character(len=2) :: "2","3","4","5","6","7","8","9","10","J","Q","K","A"]
	character(len=*), parameter :: handRanks(0:9) = [ character(len=20) :: "High Card", "Pair", "Two Pair", "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind", "Straight Flush", "Royal Flush"]
	integer, parameter :: HIGH_CARDV = 0
	integer, parameter :: PAIRV = 1
	integer, parameter :: TWO_PAIRV = 2
	integer, parameter :: THREE_OF_A_KINDV = 3
	integer, parameter :: STRAIGHTV = 4
	integer, parameter :: FLUSHV = 5
	integer, parameter :: FULL_HOUSEV = 6
	integer, parameter :: FOUR_OF_A_KINDV = 7
	integer, parameter :: STRAIGHT_FLUSHV = 8
	integer, parameter :: ROYAL_FLUSHV = 9
	integer, parameter :: VALIDV = -1
	type Hand
		
		type(Card), dimension(0:4) :: myCards
		logical, dimension(0:3,0:12) :: markedCards
		integer, dimension(0:12) :: numEachCard
		integer :: handRank, flushSuit, kickerSuit, kickerValue, pairHighSuit, valueOfTriple, fourKindVal, pairValue, twoPairValue, doubleCardVal
	
		contains
			procedure :: init_Hand
			procedure :: aceLowStraightCheck
			procedure :: getNumEachCard
			procedure :: gradeHand
			procedure :: markKicker
			procedure :: markCards
			procedure :: losesTo
			procedure :: royalFlush
			procedure :: straightFlush
			procedure :: fourOfAKind
			procedure :: fullHouse
			procedure :: flush
			procedure :: straight
			procedure :: threeOfAKind
			procedure :: twoPair
			procedure :: pair
			procedure :: getHandRank
	end type Hand

contains

	function getHandRank(this) result( string )
		class(Hand) :: this
		character(len=20) :: string
		string = handRanks(this%handRank)
	end function getHandRank

	subroutine init_Hand ( this )
		class(Hand) :: this
		this%handRank = -1
		this%flushSuit = -1
		this%kickerSuit = -1
		this%kickerValue = -1
		this%pairHighSuit = -1
		this%valueOfTriple = -1
		this%fourKindVal = -1
		this%pairValue = -1
		this%twoPairValue = -1
		this%doubleCardVal = -1
	end subroutine init_Hand

	
	subroutine aceLowStraightCheck ( this )
		class(Hand) :: this
		integer :: i
		type(Card) :: tempCard
		if ( this%myCards(0)%value /= 12 ) then
			return
		end if
		do i = 1, 4
			if ( this%myCards(i)%value /= (4-i) ) then
				return
			end if
		end do
		tempCard = this%myCards(0)
		do i = 0, 3
			this%myCards(i) = this%myCards(i+1)
		end do
		this%myCards(4) = tempCard
	end subroutine aceLowStraightCheck

	subroutine getNumEachCard ( this )
		class(Hand) :: this
		integer :: i
		do i = 0, 12
			this%numEachCard(i) = 0
		end do
		do i = 0, 4
			this%numEachCard( this%myCards(i)%value ) = this%numEachCard( this%myCards(i)%value ) + 1
		end do
	end subroutine getNumEachCArd		

	function losesTo ( this, hand2 ) result( loses )
		class(Hand) :: this, hand2
		logical :: loses
		integer:: i, firstIndex, secondIndex
		if (this%handRank .ne. hand2%handRank) then
			loses = this%handRank .lt. hand2%handRank
			return
		end if
		select case( this%handRank )
			case( HIGH_CARDV )
				do i = 0, 4
					if ( this%myCards(i)%value /= hand2%myCards(i)%value ) then
						loses = this%myCards(i)%value .lt. hand2%myCards(i)%value
						return
					end if
				end do
				loses = this%myCards(0)%suitRank() .lt. hand2%myCards(0)%suitRank()
				return
			case( PAIRV )
				if ( this%pairValue /= hand2%pairValue ) then
					loses = this%pairValue .lt. hand2%pairValue
					return
				end if
				firstIndex = 0
				secondIndex = 0
				do while ( ( firstIndex /= 5 ) .and. ( secondIndex /= 5 ) )
					do while ( this%myCards(firstIndex)%value == this%pairValue)
						firstIndex = firstIndex + 1
					end do
					do while ( hand2%myCards(secondIndex)%value == hand2%pairValue )
						secondIndex = secondIndex + 1
					end do
					if ( this%myCards(firstIndex)%value /= hand2%myCards(secondIndex)%value ) then
						loses = this%myCards(firstIndex)%value < hand2%myCards(secondIndex)%value
						return
					end if
					firstIndex = firstIndex + 1
					secondIndex = secondIndex + 1
				end do
				loses = this%kickerSuit < hand2%kickerSuit
			case( TWO_PAIRV )
				if ( this%twoPairValue /= hand2%twoPairValue ) then
					loses = this%twoPairValue < hand2%twoPairValue
					return
				end if
				if ( this%pairValue /= hand2%pairValue ) then
					loses = this%pairValue < hand2%pairValue
					return
				end if
				if ( this%kickerValue /= hand2%kickerValue ) then
					loses = this%kickerValue < hand2%kickerValue
					return
				end if
				loses = this%kickerSuit < hand2%kickerSuit
				return
			case( THREE_OF_A_KINDV )
				if ( this%valueOfTriple /= hand2%valueOfTriple ) then
					loses = this%valueOfTriple < hand2%valueOfTriple
					return
				end if
				do i = 0, 4
					if ( this%myCards(i)%value /= hand2%myCards(i)%value ) then
						loses = this%myCards(i)%value < hand2%myCards(i)%value
						return
					end if
				end do
				loses = this%myCards(0)%suitRank() < hand2%myCards(0)%suitRank()
				return
			case( STRAIGHTV )
				if ( this%myCards(0)%value /= hand2%myCards(0)%value ) then
					loses = this%myCards(0)%value < hand2%myCards(0)%value
					return
				end if
				loses = this%myCards(0)%suitRank() < hand2%myCards(0)%suitRank()
				return
			case( FLUSHV )
				do i = 0, 4
					if ( this%myCards(i)%value /= hand2%myCards(i)%value ) then
						loses = this%myCards(i)%value < hand2%myCards(i)%value
						return
					end if
				end do
				loses = this%flushSuit < hand2%flushSuit
				return
			case( FULL_HOUSEV )
				if ( this%valueOfTriple /= hand2%valueOfTriple ) then
					loses = this%valueOfTriple < hand2%valueOfTriple
					return
				end if
				if ( this%doubleCardVal /= hand2%doubleCardVal ) then
					loses = this%doubleCardVal < hand2%doubleCardVal
					return
				end if
				do i = 0, 4
					if ( this%myCards(i)%suitRank() /= hand2%myCards(i)%suitRank() ) then
						loses = this%myCards(i)%suitRank() < hand2%myCards(i)%suitRank()
						return
					end if
				end do
			case( FOUR_OF_A_KINDV )
				if ( this%fourKindVal /= hand2%fourKindVal ) then
					loses = this%fourKindVal < hand2%fourKindVal
					return
				end if
				do i = 0, 4
				if ( this%myCards(i)%value /= hand2%myCards(i)%value ) then
						loses = this%myCards(i)%value < hand2%myCards(i)%value
						return
					end if
				end do
				do i = 0, 4
					if ( this%myCards(i)%suitRank() /= hand2%myCards(i)%suitRank() ) then
						loses = this%myCards(i)%suitRank() < hand2%myCards(i)%suitRank()
						return
					end if
				end do
			case( STRAIGHT_FLUSHV )
				if ( this%myCards(0)%value /= hand2%myCards(0)%value ) then
					loses = this%myCards(0)%value < hand2%myCards(0)%value
					return
				end if
				loses = this%myCards(0)%suitRank() < hand2%myCards(0)%suitRank() 
				return
			case( ROYAL_FLUSHV )
				loses = this%flushSuit < hand2%flushSuit
				return
		end select
		loses = .true.
	end function losesTo

	subroutine gradeHand (this)
		class(Hand) :: this
		if( this%royalFlush() ) then
			this%handRank = ROYAL_FLUSHV
			return
		else if ( this%straightFlush() ) then
			this%handRank = STRAIGHT_FLUSHV
			return
		else if ( this%fourOfAKind() ) then
			this%handRank = FOUR_OF_A_KINDV
			return
		else if ( this%fullHouse() ) then
			this%handRank = FULL_HOUSEV
			return
		else if ( this%flush() ) then
			this%handRank = FLUSHV
			return
		else if ( this%straight() ) then
			this%handRank = STRAIGHTV
			return
		else if ( this%threeOfAKind() ) then
			this%handRank = THREE_OF_A_KINDV
			return
		else if ( this%twoPair() ) then
			this%handRank = TWO_PAIRV
			return
		else if ( this%pair() ) then
			this%handRank = PAIRV
			return
		end if
		this%handRank = HIGH_CARDV
	end subroutine gradeHand

	function royalFlush ( this ) result( b )
		class(Hand) :: this
		integer :: i, j
		logical :: b
		do i = 0, 3
			do j = 8, 13
				if ( j == 13 ) then
					this%flushSuit = i
					b = .true.
					return
				end if
				if ( .not. this%markedCards(i,j) ) then
					exit
				end if
			end do
		end do
		b = .false.
		return
	end function royalFlush

	function straightFlush ( this ) result( b )
		class(Hand) :: this
		logical :: b
		b = this%flush() .and. this%straight()
	end function straightFlush

	function fourOfAKind ( this ) result( b )
		class(Hand) :: this
		logical :: b
		integer :: i
		do i = 0, 12
			if ( this%numEachCard(i) == 4 ) then
				this%fourKindVal = i
				b = .true.
				return
			end if
		end do
		b = .false.
	end function fourOfAKind

	function fullHouse ( this ) result( b )
		class(Hand) :: this
		logical :: b, tripleFound, doubleFound
		integer :: i
		tripleFound = .false.
		doubleFound = .false.
		do i = 0, 12
			if (this%numEachCard(i) == 3) then
				this%valueOfTriple = x
				tripleFound = .true.
			else if (this%numEachCard(i) == 2) then
				doubleFound = .true.
				this%doubleCardVal = i
			end if
			if (tripleFound .and. doubleFound) then
				b = .true.
				return
			end if
		end do
		b = .false.
	end function fullHouse

	function flush ( this ) result( b )
		class(Hand) :: this
		logical :: b
		integer :: i, j, suitCount
		character(len=1) :: potentialSuit

		potentialSuit = this%myCards(0)%suit
		do i = 1, 4
			if (this%myCards(i)%suit /= potentialSuit) then
				b = .false.
				return
			end if
		end do
		this%flushSuit = this%myCards(0)%suitRank()
		b = .true.
	end function flush

	function straight ( this ) result( b )
		class(Hand) :: this
		logical :: b
		integer :: curConsecutive, i
		curConsecutive = 0
		do i = 0, 12
			if ( curConsecutive == 5 ) then
				b = .true.
				return
		end if
			if ( this%numEachCard(i) >= 1 ) then
				curConsecutive = cuConsecutive + 1
			else
				curConsecutive = 0
			end if
		end do
		if ( this%myCards(4)%value /= 12 ) then
			b = .false.
			return
		end if
		do i = 0, 3
			if ( this%myCards(3-i)%value /= i ) then
				b = .false.
				return
			end if
		end do
		b = .true.
	end function straight

	function threeOfAKind ( this ) result( b )
		class(Hand) :: this
		logical :: b 
		integer :: i
		do i = 0, 12
			if ( this%numEachCArd(i) == 3 ) then
				this%valueOfTriple = i
				b = .true.
				return
			end if
		end do
		b = .false.
	end function threeOfAKind

	function twoPair ( this ) result( b )
		class(Hand) :: this
		logical :: b, pairFound
		integer :: i, temp
		pairFound = .false.
		do i = 0, 12
			if ( this%numEachCard(i) > 1 ) then
				if ( pairFound ) then
					this%twoPairValue = i
					call	this%markKicker()
					if ( this%twoPairValue < this%pairValue ) then
						temp = this%pairValue
						this%pairValue = this%twoPairValue
						this%twoPairValue = temp
					end if
					b = .true.
					return
				else
					this%pairValue = i
					pairFound = .true.
				end if
			end if
		end do
		b = .false.
	end function twoPair

	subroutine markKicker ( this )
		class(Hand) :: this
		integer :: i, j
		do i = 0, 12
			if ( this%numEachCard(i) == 1 ) then
				do j = 0, 4
					if ( this%myCards(j)%value == i ) then
						this%kickerSuit = this%myCards(j)%suitRank()
						this%kickerValue = this%myCards(j)%value
						return
					end if
				end do
			end if
		end do
	end subroutine markKicker

	function pair ( this ) result( b )
		class(Hand) :: this
		logical :: b
		integer :: i, suitHighCardNoPair, valueHighCardNoPair, j
		do i = 0, 12
			if ( this%numEachCard(i) > 1 ) then
				suitHighCardNoPair = -1
				valueHighCardNoPair = -1
				do j = 0, 4
					if ( this%numEachCard( this%myCards(j)%value ) == 1 .and. valueHighCardNoPair < this%myCards(i)%value ) then
						valueHighCardNoPair = this%myCards(j)%value
						suitHighCardNoPair = this%myCards(j)%suitRank()
					end if
				end do
				this%kickerSuit = suitHighCardNoPair
				this%kickerValue = valueHighCardNoPair
				this%pairValue = i
				b = .true.
				return
			end if
		end do
		b = .false.
	end function pair
		
	subroutine markCards (this)
		class(Hand) :: this
		integer :: i, j
		do i = 0, 3
			do j = 0, 12
				this%markedCards(i,j) = .false.
			end do
		end do	
		do i = 0, 4
			this%markedCards(this%myCards(i)%suitRank(),this%myCards(i)%value) = .true.
		end do
	end subroutine markCards

end module hand_module
