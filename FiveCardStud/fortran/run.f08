program run
use Card_module
use hand_module
use poker_module 
implicit none
	type(Card), dimension(0:51) :: cards
	integer :: i, j, k, val
	type(Hand), dimension(0:5) :: hands, originalHands
	integer, dimension(0:5) :: indexTracker
	character(len=*), parameter :: faces(0:12) = [ character(len=2) :: "2","3","4","5","6","7","8","9","10","J","Q","K","A"]
	
	call getRandCards( cards )
	call getRandHands( hands, cards )
	originalHands = copyHands( hands )
	call sortEach(hands)
	call printDeckAndHands( hands, cards )
	do i = 0, 5
		call hands(i)%markCards()
		call hands(i)%getNumEachCard()
		call hands(i)%gradeHand()
	end do
	indexTracker = sortHands( hands )
	call printResults( hands, originalHands, indexTracker )

end program run

