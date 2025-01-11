

program loop

    character(len=20) :: Sstart, Send
    integer*8 :: start, end, temp, curNum
    integer*8 :: count
    logical :: anotherPassNeeded

    type CollatzPair
        integer*8 :: seqStart, length
    end type CollatzPair

    type(CollatzPair) :: newPair, tempPair, tempPair2
    type(CollatzPair), dimension(0:9) :: listj

    call get_command_argument(1, Sstart)
    call get_command_argument(2, Send)
    read(Sstart, *) start
    read(Send, *) end

    if( start > end ) then
        temp = start
        start = end
        end = temp
    end if

    do i = 0, 9
        listj(i) = newPair
    end do

    do i = start, end
        curNum = i
        count = 0
        do while (curNum /= 1)
            if ( mod(curNum, 2) == 0 ) then
                curNum = curNum / 2
            else
                curNum = curNum * 3 + 1
            end if
            count = count + 1
        end do 
        newPair%seqStart = i
        newPair%length = count
        do j = 0, 9
             if (newPair%seqStart == 1) then
                do k = 9, 1, -1
                    listj(k) = listj(k-1)
                end do
                listj(0) = newPair
            else if (newPair%length == listj(j)%length) then
                exit
            else if (newPair%length > listj(j)%length) then
                do k = 9, j + 1, -1
                    listj(k) = listj(k - 1)
                end do
                listj(j) = newPair
                exit
            end if
        end do
            
    end do

    write (*, '(A)') "Sorted based on sequence length"
    do i = 0, size(listj)-1
        if ( listj(i)%seqStart == 0 ) then
            exit
        end if
        write(*, '(I20,I20)') listj(i)%seqStart, listj(i)%length
        !print *, listj(i)%seqStart, listj(i)%length
        if (listj(i)%seqStart == 1 ) then
            exit
        end if
    end do


    anotherPassNeeded = .true.
    do while (anotherPassNeeded)
        anotherPassNeeded = .false.
        do i = 0, 8
            if ( listj(i)%seqStart == 0 .or. listj(i+1)%seqStart == 0) then
                exit
            end if
            if ( listj(i)%seqStart < listj(i+1)%seqStart ) then
                anotherPassNeeded = .true.
                tempPair = listj(i)
                listj(i) = listj(i+1)
                listj(i+1) = tempPair
            end if
        end do
    end do

write (*, '(A)') "Sorted based on integer size"
    do i = 0, size(listj)-1
        if ( listj(i)%seqStart == 0 ) then
            exit
        end if
        write(*, '(I20,I20)') listj(i)%seqStart, listj(i)%length
        !print *, listj(i)%seqStart, listj(i)%length
        if (listj(i)%seqStart == 1 ) then
            exit
        end if
    end do

end program