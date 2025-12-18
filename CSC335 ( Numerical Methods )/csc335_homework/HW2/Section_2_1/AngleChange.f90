program AngleChange
    use bisectionMod
    implicit none

    interface
        function f( x ) result(y)
            real (kind=8) :: y
            real (kind=8), intent(in) :: x
        end function f
    end interface

    real (kind=8) :: root

    root = bisection(f, -1.0_8, 0.0_8, 1.0E-10_8, 1000000000)

end program AngleChange

function f(x) result(y)
    implicit none
    real(kind=8), intent(in) :: x
    real(kind=8) :: y
    real(kind=8), parameter :: E = 2.718281828459045_8
    y = -(32.17_8 / (2.0_8 * x**2_8)) * ((E**x - E**(-x)) / 2.0_8 - sin(x)) - 1.7_8
end function f