#!/usr2/local/sbcl/bin/sbcl --script

;disables warnings
(declaim (sb-ext:muffle-conditions cl:warning))

( load "card.lisp" )
( load "hand.lisp" )
( load "poker.lisp" )

(defun displayNumEachCard (nums)
    (loop for x from 0 to 12 do 
        (format t "~A "(aref nums x ))
    )
    (terpri)
)
(defun displayMarks (marks)
    (let ((mark 0))
        (terpri)
        (loop for x from 0 to 3 do
            (loop for y from 0 to 12 do 
                (if (aref marks x y) 
                    (setf mark 1)
                    (setf mark 0)    
                )
                (format t "~A " mark)
            ) 
            (terpri)
        )
    
    )
)
;(eval-when (:compile-toplevel :load-toplevel :execute)
;  (declaim (optimize (safety 0) (debug 0) (compilation-speed 0))))

;(printCards (getRandCards))
;(printHands (getRandHands(getRandCards)))
;(printCards (getFileCards))
(let (
    (cards (list))
    (hands (list))
    (random 0)
    (fullFile "")
    (duplicateCard (defaultCard))
    (dupPresent (not nil))
    (originalHands (list))
    (indexTracker (list)))

(if ( not (= (length sb-ext:*posix-argv*)  1) )
    ( setf random nil )
    ( setf random (not nil) )
)

(if (not random)
    (progn
        (setf fullFile (getFullFile (second sb-ext:*posix-argv*)) )
        (setf cards (read-file (second sb-ext:*posix-argv*)))    
        (setf hands (getFileHands cards) )
    )
    (progn
        (setf cards (getRandCards))
        (setf hands (getRandHands cards) )
    )
)

(if (not random)
    (setf duplicateCard (checkDuplicateCards hands))
)
(if (= (card-value duplicateCard) -1)
    (setf dupPresent nil)
)
(printDeckAndHands hands cards random dupPresent fullFile )
(if dupPresent 
    (progn
        (format t "~%~A~%" "*** ERROR - DUPLICATE CARD FOUND IN DECK ***")
        (format t "~%~%*** DUPLICATE: ~A ***~%" (toString duplicateCard))
        (sb-ext:exit)
    )
)
(setf originalHands (copyHands hands) )
(sortEach hands)
(terpri)
;(printHands hands)

 ;(format t "~A ~A~%" (type-of #\S) (type-of (card-suit (nth 0 cards))))
(loop for x from 0 to 5 do 
    (markCards (nth x hands))
    (getNumEachCard (nth x hands))
    (gradeHand (nth x hands))
    ;(displayNumEachCard (hand-numeachcard (nth x hands)))
    ;(displayMarks (hand-markedcards (nth x hands)))
)

(setf indextracker (sortHands hands))
(printResults hands originalhands indextracker)
#|(printHands hands)
(dolist ( index indextracker)
    (format t "~A " index)
)|#
)