program TroughDepth
    use bisectionMod

    implicit none

    interface
        function f( x ) result(y)
            real (kind=8), intent(in) :: x
            real (kind=8) :: y
        end function f
    end interface

    real (kind=8) :: result

    result = bisection(f, 0.0_8, 1.0_8, 1.0E-5_8, 10000000)

end program TroughDepth

function f( x ) result(y)
    implicit none
    real (kind=8), intent(in) :: x
    real (kind=8) :: y
    real (kind=8), parameter :: PI = 3.14159265358979323846264338327950288419716939937510_8
    y = 10.0_8 * ( PI / 2.0_8 - asin(1-x) - (1-x) * sqrt( - (x**2.0_8) + 2.0_8 * x) ) - 12.4_8
    return
end function f