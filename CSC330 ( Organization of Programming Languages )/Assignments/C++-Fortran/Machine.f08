program machine

use drink_module

integer :: totalSold
real (kind=4) :: totalProfit
type(Drink), dimension(5) :: drinks

call drinks(1)%init_drink("Coke")
call drinks(2)%init_drink("Sprite")
call drinks(3)%init_drink("Doctor Pepper")
call drinks(4)%init_drink_with_cost("Guinness", 6.25)
call drinks(5)%init_drink_with_cost("Mellow Yellow", 5.50)

! Refill the drinks
do i = 1, 5
    call drinks(i)%refill()
enddo

! Purchase 8 Cokes
do i = 1, 8
    call drinks(1)%vend()
enddo

! Purchase 5 Sprites 
do i = 1, 5
    call drinks(2)%vend()
enddo

! Purchase 2 Doctor Peppers 
do i = 1, 2
    call drinks(3)%vend()
enddo

! Purchase 11 Guinness 
do i = 1, 11 
    call drinks(4)%vend()
enddo

! Purchase 7 Mellow Yellow
do i = 1, 7
    call drinks(5)%vend()
enddo

! Compute total drinks sold and total profit
totalProfit = 0
totalSold = 0
do i = 1, size(drinks)
    totalSold = totalSold + drinks(i)%drinks_sold()
    totalProfit = totalProfit + drinks(i)%profit()
enddo

print "(a,i3,a,f7.2)", "A total of ", totalSold, " drinks were sold for a profit of $",&
        & totalProfit

do i = 1, size(drinks)
    print "(i2, 1x, a, 1x, a)", drinks(i)%restock_amount(),&
            &drinks(i)%get_drink_name(), "needed to restock machine"  
enddo

end program machine
