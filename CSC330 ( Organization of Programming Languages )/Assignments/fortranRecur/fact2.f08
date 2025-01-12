
program fact2

integer*8 :: val, i

do i = 1, 21
   call fact(i, val)
   print *, i, val
enddo

end program fact2


recursive subroutine fact( i, val )

integer*8 :: i, val

if ( i /= 1 ) then
   call fact(i-1,val)
   val = val*i
else
   val = 1
   return
endif

end subroutine fact
