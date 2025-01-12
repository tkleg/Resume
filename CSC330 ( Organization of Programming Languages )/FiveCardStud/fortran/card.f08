module Card_module
	implicit none
	private
	public :: Card, init_Card, init_Card_Vals, getValue
	public :: suitRank, toString
	character(len=*), parameter :: faces(0:12) = [ character(len=2) :: "2","3","4","5","6","7","8","9","10","J","Q","K","A"]
	type Card
	integer :: value
	character(len=1) :: suit

	contains
		procedure :: init_Card
		procedure :: init_Card_Vals
		procedure :: suitRank
		procedure :: toString
	end type Card

contains

	subroutine init_Card( this )
		class(Card) :: this
		this%value = -1
		this%suit = 'z'
	end subroutine init_Card

	subroutine init_Card_Vals( this,  newValue, newSuit )
		class(Card) :: this
		integer :: newValue
		character(len=1) :: newSuit
		this%value = newValue
		this%suit = newSuit
	end subroutine init_Card_Vals

	function suitRank( this ) result( suitR )
		class(Card) :: this
		integer :: suitR
		select case( this%suit )
			case( 'D' )
				suitR = 3
				return
			case( 'C' )
				suitR = 2
				return
			case( 'H' )
				suitR = 1
				return
			case( 'S' )
				suitR = 0
				return
			case default
				suitR = -1
				return
		end select
	end function suitRank

	function getValue( c ) result( val )
		character(len=1) :: c
		integer :: val
		if ((c .ge. '2') .and. (c .le. '9')) then
			val = ichar( c ) - ichar( '0' ) - 2
			return
		end if
		select case( c )
			case( 'J' )
				val = 10
				return
			case( 'Q' )
				val = 11
				return
			case( 'K' )
				val = 12
				return
			case( 'A' )
				val = 13
				return
			case default
				return
		end select
	end function getValue

	function toString( this ) result( string )
		class(Card) :: this
		character(len=:), allocatable :: string
		string = trim( faces( this%value ) ) // this%suit
	end function toString

end module Card_module
