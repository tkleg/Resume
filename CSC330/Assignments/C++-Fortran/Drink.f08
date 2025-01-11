module drink_module

    implicit none
    private
    public :: Drink, init_drink, init_drink_with_cost, vend, refill
    public :: profit, drinks_sold, get_drink_name, restock_amount

    type Drink
        character(len=:), allocatable :: drink_name
        integer :: available, consumed, use_default_cost, use_supplied_cost
        real (kind=4):: drink_cost, money_made
        real (kind=4) :: DEFAULT_COST
    contains
        procedure :: init_drink
        procedure :: init_drink_with_cost
        procedure :: vend
        procedure :: refill
        procedure :: profit
        procedure :: drinks_sold
        procedure :: get_drink_name
        procedure :: restock_amount
    end type Drink

contains

    subroutine init_drink ( this, brand_name )
            class(Drink) :: this        
            character(len=*) :: brand_name
            this%drink_name = brand_name
            this%DEFAULT_COST = 1.75
            this%available = 0
            this%consumed = 0
            this%money_made = 0.0
            this%drink_cost = this%DEFAULT_COST 
            this%use_default_cost = 1
            this%use_supplied_cost = 0
    end subroutine init_drink

    subroutine init_drink_with_cost ( this, brand_name, cost )
            class(Drink) :: this        
            character(len=*) :: brand_name
            real :: cost
            this%drink_name = brand_name
            this%available = 0
            this%consumed = 0
            this%money_made = 0.0
            this%drink_cost = cost
            this%use_default_cost = 0
            this%use_supplied_cost = 1
    end subroutine init_drink_with_cost

    subroutine vend ( this )
            class(Drink) :: this        
            if ( this%available > 0 ) then
                this%available = this%available - 1
                this%consumed = this%consumed + 1
                this%money_made = this%money_made + ( this%use_default_cost * this%DEFAULT_COST&
                       & + this%use_supplied_cost * this%drink_cost )
                print *, this%drink_name, " purchased."
            else
                print *, "************"
                print *, "* SOLD OUT *"
                print *, "************"
            end if
    end subroutine vend

    subroutine refill ( this )
            class(Drink) :: this        
            this%available = 10
    end subroutine refill

    function profit ( this ) result(profit_in_dollars)
            class(Drink) :: this        
            real (kind=4) :: profit_in_dollars 
            profit_in_dollars = this%money_made
    end function profit

    function drinks_sold ( this ) result(this_drink_sold)
            class(Drink) :: this        
            integer :: this_drink_sold
            this_drink_sold = this%consumed
    end function drinks_sold

    function get_drink_name ( this ) result(result_value)
            class(Drink) :: this        
            character(:), allocatable :: result_value
            character(len(this%drink_name)) :: tmp
            write(tmp,'(a)') this%drink_name
            result_value = trim(tmp)
    end function get_drink_name

    function restock_amount ( this ) result(restock_total)
            class(Drink) :: this        
            integer :: restock_total
            restock_total = 10 - this%available
    end function restock_amount

end module drink_module
