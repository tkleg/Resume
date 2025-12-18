module bisectionMod
  implicit none
contains

  function bisection(f, a_in, b_in, tol, maxit) result(p)
    implicit none
    interface
      function func_interface(a) result(c)
        real (kind=8) :: c
        real (kind=8), intent(in) :: a
      end function func_interface
    end interface

    procedure(func_interface) :: f
    real (kind=8), intent(in) :: a_in, b_in, tol
    integer, intent(in) :: maxit

    real (kind=8) :: fa, fp, root, p, a, b
    integer :: iter

    a = a_in
    b = b_in
    
    iter = 1
    fa = f( a )
    do while ( iter < maxit )
        p = a + ( b - a ) / 2.0_8
        fp = f( p )
        if (fp == 0.0_8 .or. ( b - a ) / 2.0_8 < tol) then
            write(*,'(A,F18.16,A,I0,A)') "Root found at p = ", p, " after ", iter, " iterations."
            return
        end if
        iter = iter + 1
        if ( fp * fa > 0.0_8 ) then
            a = p
            fa = fp 
        else
            b = p
        end if
    end do
    if (iter == maxit) then
        write (*,*) "Maximum iterations reached without convergence."
    end if
  end function bisection

end module bisectionMod