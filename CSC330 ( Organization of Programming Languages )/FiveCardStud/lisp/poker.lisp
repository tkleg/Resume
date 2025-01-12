;#!/usr2/local/sbcl/bin/sbcl --script

;( load "card.lisp" )
;( load "hand.lisp" )

(defparameter faces (make-array 4 :initial-contents '(#\D #\C #\H #\S)))
(defparameter handRanks '("High Card" "Pair" "Two Pair" "Three of a Kind" "Straight" "Flush" "Full House" "Four Of A Kind" "Straight Flush" "Royal Flush"))


(defun printResults (hands originalHands indextracker)
(let ((origIndexToPrint 0) (handHelp 0) (cardString 0))
  (format t " --- WINNING HAND ORDER ---~%")
  (loop for x from 0 to 5 do
    (setf origindextoprint (nth x indextracker))
    (format t " ~A" (toString (nth 0 (hand-mycards (nth origindextoprint originalhands)))))
    (loop for y from 1 to 4 do
      (setf handhelp (nth origindextoprint originalhands))
      (setf cardstring (toString (nth y (hand-mycards handhelp))))
      (if (and (= y 2) (= 8 (card-value (nth 0 (hand-mycards handhelp)))) (= 8 (card-value (nth 0 (hand-mycards handhelp)))))
        (setf cardstring (concatenate 'string " " cardstring))
      (progn
      (if (and (= 8 (card-value (nth 1 (hand-mycards handhelp)))) (= y 1) (= (length cardstring) 2))
        (setf cardstring (concatenate 'string " " cardstring))
      (progn
      (if (= 2 (length cardstring))
        (setf cardstring (concatenate 'string "  " cardstring))
        (setf cardstring (concatenate 'string " " cardstring))
      )
      ))
      ))
      (format t "~A" cardstring)
    )
    (format t " - ~A~%" (nth (hand-handrank (nth x hands)) handranks))
  )
))

(defun sortHands (hands) 
(let ((indexTracker (list)) (anotherPassNeeded T) (tempHand (newHand)) (tempIndex 0))
  (loop for x from 0 to 5 do
    (push x indextracker)
  )
  (setf indextracker (reverse indextracker))
  (loop while anotherpassneeded do
    (setf anotherpassneeded nil)
    (loop for x from 0 to 4 do
      (if (losesTo (nth x hands) (nth (+ x 1) hands))(progn
        (setf anotherpassneeded T)
        (setf temphand (nth x hands))
        (setf (nth x hands) (nth (+ x 1) hands))
        (setf (nth (+ x 1) hands) temphand)

        (setf tempindex (nth x indextracker))
        (setf (nth x indextracker) (nth (+ x 1) indextracker))
        (setf (nth (+ x 1) indextracker) tempindex)
      ))
    )
  )
  indextracker
))

(defun getNumEachCard (hand)
  (loop for x from 0 to 4 do 
    (incf (aref (hand-numeachcard hand) (card-value (nth x (hand-mycards hand))) ) )
  )
)

(defun markCards (hand)
  (let ((sRank -1))
    (loop for x from 0 to 4 do
      (setf sRank (suitRank (card-suit (nth x (hand-mycards hand) ) ) ) )
      (setf (aref (hand-markedcards hand) sRank  (card-value (nth x (hand-mycards hand) ) ) ) (not nil) )
    )
  )

)

(defun aceLowStraightCheck (handCards)
  (if (not (= (card-value (nth 0 handCards)) 12))
    (return-from aceLowStraightCheck)
  )
  (if (not (= (card-value (nth 1 handCards)) 3))
    (return-from aceLowStraightCheck)
  )
  (if (not (= (card-value (nth 2 handCards)) 2))
    (return-from aceLowStraightCheck)
  )
  (if (not (= (card-value (nth 3 handCards)) 1))
    (return-from aceLowStraightCheck)
  )
  (if (not (= (card-value (nth 4 handCards)) 0))
    (return-from aceLowStraightCheck)
  )
  (defvar temp (nth 0 handCards))
  (loop for x from 0 to 3 do 
    (setf (nth x handCards) (nth (+ x 1) handCards) )
  )
  (setf (nth 4 handCards) temp )
)

(defun sortEach (hands)
  (let (
    (anotherPassNeeded nil)
    (temp (defaultCard)))
    (loop for x from 0 to 5 do 
      (setf anotherPassNeeded (not nil) )
      (loop while anotherPassNeeded do 
        (setf anotherPassNeeded nil)
        (loop for y from 0 to 3 do 
          (if (< (card-value (nth y (hand-mycards (nth x hands)))) (card-value (nth (+ y 1) (hand-mycards (nth x hands))))) 
          (progn
            (setf anotherPassNeeded (not nil))
            (setf temp (nth y (hand-mycards (nth x hands))))
            (setf (nth y (hand-mycards (nth x hands)) ) (nth (+ y 1 ) (hand-mycards (nth x hands))) )
            (setf (nth (+ y 1 ) (hand-mycards (nth x hands))) temp)
        ))
        )
      )
      (aceLowStraightCheck (hand-mycards (nth x hands)))
    )
  )
)

(defun copyHands (hands)
  (let ((originalHands (list))
  (holdVal 0)
  (holdSuit #\z))
  (loop for i from 0 to 5
    do 
    (push (newHand) originalHands)
  )
  (loop for x from 0 to 5 do 
    (loop for y from 0 to 4 do 
      (setf holdVal (card-value (nth y (hand-mycards (nth x hands ) ) ) ) )
      (setf holdSuit (card-suit (nth y (hand-mycards (nth x hands ) ) ) ) )
      (push (newCard holdVal holdSuit) (hand-mycards (nth x originalHands)) )
    )
    (setf (hand-mycards (nth x originalHands)) (reverse (hand-mycards (nth x originalHands))) )
  )
  originalHands)
)

(defun printDeckAndHands (hands cards random dupPresent fullFile)
  (format t "~%~A~%~%" "*** P O K E R  H A N D  A N A L Y Z E R ***" )
  (if random
    (progn
    (format t "~%~A~%~%~A~%" "*** USING RANDOMIZED DECK OF CARDS ***" "*** Shuffled 52 card deck:")
    (format t "~A " (toString (nth 0 cards) ) )
    (loop for x from 1 to 51 do
      (format t "~A " (toString (nth x cards) ) )
      (if (= (rem x 13) 0)
        (terpri)
      )
    )
    (terpri)
    )
    (format t "~%~A~%~%~A~A~%~A" "*** USING TEST DECK ***" "*** File: ../handsets/" (second sb-ext:*posix-argv*) fullFile)
  )
  (if dupPresent
    (return-from printDeckAndHands)
  )
  (format t "~%~A~%" "*** Here are the six hands...")
  (loop for x from 0 to 5 do
    (loop for y from 0 to 4 do 
      (format t "~A " (toString (nth y (hand-mycards (nth x hands)))))
    )
    (terpri)
  )
  (if (not random)
    (return-from printDeckAndHands)
  )
  (format t "~%~A~%" "*** Here is what remains in the deck...")
  (loop for x from 30 to 51 do 
    (format t "~A " (toString (nth x cards) ) )
  )
  (terpri)
)

(defun getFullFile (filename)
  (with-open-file (stream (format nil "../handsets/~A" filename ))
    (let ((content ""))
      (loop for line = (read-line stream nil)
           while line
           do (setf content (format nil "~A~A~%" content line)))
      content)))

(defun checkDuplicateCards (hands)
  (let (
      (cardsFound (make-array '(4 13) :initial-element nil ) )
      (sRank 0)
      (value 0))
      (loop for i from 0 to 5 do
        (loop for j from 0 to 4 do
          (setf sRank (suitRank (card-suit (nth j (hand-mycards (nth i hands)) ) ) ) )
          (setf value (card-value (nth j (hand-mycards (nth i hands)) ) ) )
          (if( aref cardsFound sRank value )
            (return-from checkDuplicateCards (nth j (hand-mycards (nth i hands)) ))
            (setf (aref cardsFound sRank value) t)
          )
        )
      )
      (newCard -1 #\z)
  )
)

(defun getFileHands (cards)
    (let (
        (hands (list))
        (curHand 0)
        (iteration 0)
        (hand nil)
        (temp (defaultCard))
        )
        (loop for i from 0 to 5 do
          (setf hand (newHand) ) 
          (push hand hands)
        )
        (loop for i from 0 to 29
            do
             (setf temp (nth i cards))
            (push (nth i cards) (hand-mycards (nth (floor i 5) hands)))
        )
        (loop for i from 0 to 5 do
          (setf (hand-mycards (nth i hands)) (reverse (hand-mycards (nth i hands)) ) )
        )
        hands)
)

(defun comma-split (string)
  (loop for start = 0 then (1+ finish)
        for finish = (position #\, string :start start)
        collecting (subseq string start finish)
        until (null finish)))

(defun read-file ( filename )(
  with-open-file (stream (format nil "../handsets/~A" filename ) )
  ;;; Use this variable to store the sting you read in for parsing
  (let ((cards (list))
  (card 0))
  (defvar line "")
  (defvar trimmedString "" )
  ;;; Now start reading each line 
  (loop for i from 0 to 5 do
    ( setf line ( read-line stream) )
    ( loop for j from 0 to 4 do
      ( if ( string-equal ( subseq ( nth j (comma-split line)) 0 2) "10" )
        (progn 
          (setf trimmedString (string-trim '(#\Space) (nth j (comma-split line)) ) )
          (setf card (newCard 8 ( char trimmedString 2 ) ) )
          ;(append cards (cards card))
          (push card cards )
        )
        (progn
          (setf trimmedString (string-trim '(#\Space) (nth j (comma-split line)) ) )
          (setf card (newCard (getValue (char trimmedString 0)) (char trimmedString 1) ) )
          (push card cards )
          ;(append cards (cards card))
        )
      )
    )
  )
  
  (reverse cards))))

(defun getRandHands (cards)
    (let (
        (randHands (list))
        (curHand 0)
        (iteration 0)
        (hand nil)
        (temp (defaultCard))
        )
        (loop for i from 0 to 5
          do (push (newHand) randHands)
        )
        (loop for i from 0 to 29
            do
             (setf temp (nth i cards))
            ;(setf (nth iteration (hand-mycards (nth curHand randHands)) ) (nth i cards))
            (push (nth i cards) (hand-mycards (nth curHand randHands)))
            (incf curHand)
            (if ( = curHand 6 )
                (setf curHand 0)
                (incf iteration))
        )
        randHands)
)

(defun getRandCards ()
  (let ((cards (list))
        (suits '(H D S C)))
    (dotimes (x 4)
      (dotimes (y 13)
        (let ((card (newCard y (nth x suits))))
          (push card cards))))
    (setf cards (shuffle cards) )
    cards))
    
(defun shuffle (cards)
  (let ((n (length cards))
    ( j 0 )
  )
    ;sets the random seed based on the time
    (setf *random-state* (make-random-state t))
    (loop for i from 51 downto 1
      do (setf j (random i))
      (rotatef (nth i cards) (nth j cards))
    )cards))

(defun printCards (cards)
(let ((counter 0))
(dolist ( card  cards)
  (format t ".~A." (toString card))
  (incf counter)
  (if (= (rem counter 5) 0)
    (terpri)
  )
)
))

(defun printHands (hands)
(dolist ( hand1 hands )
    (dolist (card (hand-mycards hand1))
        (format t "~A " (toString card))
        (princ " ")
    )
    (format t "~A ~A " (nth (hand-handRank hand1) handRanks) (hand-flushsuit hand1))
    (format t "~A ~A ~A " (hand-fourkindval hand1) (hand-valueoftriple hand1) (hand-doublecardval hand1))
    (format t "~A " (hand-pairvalue hand1))
    (terpri)
)
)

;(defparameter printcards (shuffle (getRandCards)))
;(setf printcards (shuffle printcards))
;(printCards (getRandCards))
