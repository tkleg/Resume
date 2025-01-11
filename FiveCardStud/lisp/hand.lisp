;#!/usr2/local/sbcl/bin/sbcl --script


(load "card.lisp")

(defconstant HIGH_CARD 0)
(defconstant PAIR 1)
(defconstant TWO_PAIR 2)
(defconstant THREE_OF_A_KIND 3)
(defconstant STRAIGHT 4)
(defconstant FLUSH 5)
(defconstant FULL_HOUSE 6)
(defconstant FOUR_OF_A_KIND 7)
(defconstant STRAIGHT_FLUSH 8)
(defconstant ROYAL_FLUSH 9)

(defstruct Hand
    myCards
    markedCards
    numEachCard
    handRank
    flushSuit
    kickerSuit
    kickerValue
    pairHighSuit
    valueOfTriple
    fourKindVal
    pairValue
    twoPairValue
    doubleCardVal
)

(defun newHand ()
    (make-hand
        :myCards (list)
        :markedCards (make-array '(4 13) :initial-element nil)
        :numEachCard (make-array 13 :initial-element 0)
        :handRank 0
        :flushSuit 0
        :kickerSuit 0
        :kickerValue 0
        :pairHighSuit 0
        :valueOfTriple 0
        :fourKindVal 0
        :pairValue 0
        :twoPairValue 0
        :doubleCardVal 0
    )
)

(defun losesTo (hand1 hand2)
  (if (not (= (hand-handrank hand1) (hand-handrank hand2)))
    (return-from losesto (< (hand-handrank hand1) (hand-handrank hand2)))
  )
  (if (= HIGH_CARD (hand-handrank hand1))(progn
    (loop for x from 0 to 4 do
        (if (not (= (card-value (nth x (hand-mycards hand1))) (card-value (nth x (hand-mycards hand2)))))
            (return-from losesto (< (card-value (nth x (hand-mycards hand1))) (card-value (nth x (hand-mycards hand2)))))
        )
    )
    (return-from losesto (< (suitRank (card-suit (nth 0 (hand-mycards hand1)))) (suitRank (card-suit (nth 0 (hand-mycards hand2))))))
  ))
  (if (= PAIR (hand-handrank hand1))(progn
    (if (not (= (hand-pairvalue hand1) (hand-pairvalue hand2)))
        (return-from losesto (< (hand-pairvalue hand1) (hand-pairvalue hand2)))
    )
    (loop for x from 0 to 4 do
        (if (not (= (card-value (nth x (hand-mycards hand1))) (card-value (nth x (hand-mycards hand2)))))
            (return-from losesto (< (card-value (nth x (hand-mycards hand1))) (card-value (nth x (hand-mycards hand2)))))
        )
    )
    (return-from losesto (< (hand-kickersuit hand1) (hand-kickersuit hand2)))
  ))
  (if (= TWO_PAIR (hand-handrank hand1))(progn
    (if (not (= (hand-twopairvalue hand1) (hand-twopairvalue hand2)))
        (return-from losesto (< (hand-twopairvalue hand1) (hand-twopairvalue hand2)))
    )
    (if (not (= (hand-pairvalue hand1) (hand-pairvalue hand2)))
        (return-from losesto (< (hand-pairvalue hand1) (hand-pairvalue hand2)))
    )
    (if (not (= (hand-kickervalue hand1) (hand-kickervalue hand2)))
        (return-from losesto (< (hand-kickervalue hand1) (hand-kickervalue hand2)))
    )
    (return-from losesto (< (hand-kickersuit hand1) (hand-kickersuit hand2)))
  ))
  (if (= three_of_a_kind (hand-handrank hand1))
    (return-from losesto (< (hand-valueoftriple hand1) (hand-valueoftriple hand2)))
  )
  (if (= straight (hand-handrank hand1))(progn
    (if (not (= (card-value (nth 0 (hand-mycards hand1))) (card-value (nth 0 (hand-mycards hand2)))))
        (return-from losesto (< (card-value (nth 0 (hand-mycards hand1))) (card-value (nth 0 (hand-mycards hand2)))))
    )
    (return-from losesto (< (suitRank (card-suit (nth 0 (hand-mycards hand1)))) (suitRank (card-suit (nth 0 (hand-mycards hand2))))))
  ))
  (if (= flush (hand-handrank hand1))(progn
    (loop for x from 0 to 4 do
        (if (not (= (card-value (nth x (hand-mycards hand1))) (card-value (nth x (hand-mycards hand2)))))
            (return-from losesto (< (card-value (nth x (hand-mycards hand1))) (card-value (nth x (hand-mycards hand2)))))
        )
    )
    (return-from losesto (< (hand-flushsuit hand1) (hand-flushsuit hand2)))
  ))
  (if (= full_house (hand-handrank hand1))
    (return-from losesto (< (hand-valueoftriple hand1) (hand-valueoftriple hand2)))
  )
  (if (= four_of_a_kind (hand-handrank hand1))
    (return-from losesto (< (hand-fourkindval hand1) (hand-fourkindval hand2)))
  )
  (if (= straight_flush (hand-handrank hand1))(progn
    (if (not (= (card-value (nth 0 (hand-mycards hand1))) (card-value (nth 0 (hand-mycards hand2)))))
        (return-from losesto (< (card-value (nth 0 (hand-mycards hand1))) (card-value (nth 0 (hand-mycards hand2)))))
    )
    (return-from losesto (< (suitRank (card-suit (nth 0 (hand-mycards hand1)))) (suitRank (card-suit (nth 0 (hand-mycards hand2))))))
  ))
  (< (hand-flushsuit hand1) (hand-flushsuit hand2))
)

(defun pairFunc (hand)
(let ((suitHighCardNoPair -1) (valueHighCardNoPair -1))
    (loop for x from 0 to 12 do
        (if (= 2 (aref (hand-numeachcard hand) x))(progn
            (setf suithighcardnopair -1)
            (setf valuehighcardnopair -1)
            (loop for y from 0 to 4 do
                (if (and (= 1 (aref (hand-numeachcard hand) (card-value (nth y (hand-mycards hand) ) ) ) ) ( < valuehighcardnopair (card-value (nth y (hand-mycards hand)))))(progn
                    (setf valuehighcardnopair (card-value (nth y (hand-mycards hand)) ) )
                    (setf suithighcardnopair (suitRank (card-suit (nth y (hand-mycards hand)))))
                ))
            )
            (setf (hand-kickersuit hand) suithighcardnopair)
            (setf (hand-kickervalue hand) valuehighcardnopair)
            (setf (hand-pairvalue hand) x)
            (return-from pairfunc T)
        ))
    )
)
    (return-from pairfunc nil)
)

(defun markKicker (hand)
    (loop for x from 0 to 12 do
        (if (= 1 (aref (hand-numeachcard hand) x))
        (progn
            (loop for y from 0 to 4 do
                (if (= x (card-value (nth y (hand-mycards hand))))
                (progn
                    (setf (hand-kickersuit hand) (suitRank (card-suit (nth y (hand-mycards hand)))))
                    (setf (hand-kickervalue hand) (card-value (nth y (hand-mycards hand))))
                    (return-from markkicker)
                )
                )
            )
        )
        )
    )
)

(defun twoPair (hand)
(let ((pairFound nil) (temp 0))
    (loop for x from 0 to 12 do
        (if (> (aref (hand-numeachcard hand) x) 1)
            (progn
            (if pairfound
                (progn
                    (setf (hand-twopairvalue hand) x)
                    (markKicker hand)
                    (if (< (hand-twopairvalue hand) (hand-pairvalue hand))
                    (progn
                        (setf temp (hand-pairvalue hand))
                        (setf (hand-pairvalue hand) (hand-twopairvalue hand))
                        (setf (hand-twopairvalue hand) temp)
                    )
                    )
                    (return-from twoPair T)
                )
                (progn
                    (setf (hand-pairvalue hand) x)
                    (setf pairfound T)
                )
            )
            )
        )
    )
    nil
))

(defun threeOfAKind (hand)
    (loop for x from 0 to 12 do
        (if (= 3 (aref (hand-numeachcard hand) x))
            (return-from threeofakind T)
        )
    )
    nil
)

(defun straightFunc (hand) 
    (let ((curConsecutive 0))
        (loop for y from 0 to 12 do
            (if (= 5 curconsecutive)
                (return-from straightfunc T)
                (progn
                    (if (= 1 (aref (hand-numeachcard hand) y))
                        (incf curconsecutive)
                        (setf curconsecutive 0)
                    )
                )
            )
        )
    )
    (if (not (= 12 (card-value (nth 4 (hand-mycards hand)))))
        (return-from straightfunc nil)
    )
    (loop for x from 0 to 3 do
        (if (not (= (- 3 x) (card-value (nth x (hand-mycards hand)))))
            (return-from straightfunc nil)
        )
    )
    T
)

(defun flushFunc (hand)
    ;(format t "~A~%" (type-of (char (card-suit (nth 0 (hand-mycards hand))))))
    (let ((potentialSuit (card-suit (nth 0 (hand-mycards hand)))))
        (loop for x from 1 to 4 do
            (if (not (equal potentialsuit (card-suit (nth x (hand-mycards hand)))))
                (return-from flushfunc nil)
            )
        )
        (setf (hand-flushsuit hand) (suitRank potentialSuit))
        T
    )
)

(defun fullHouse (hand)
    (let ((tripleFound nil) (doubleFound nil))
        (loop for x from 0 to 12 do
            (if (= (aref (hand-numeachcard hand) x) 3)
                (progn
                    (setf (hand-valueoftriple hand) x)
                    (setf triplefound T)
                )
                (progn
                    (if (= 2 (aref (hand-numeachcard hand) x))
                        (progn
                            (setf (hand-doublecardval hand) x)
                            (setf doublefound T)
                        ))))
            (if (and triplefound doublefound) 
                (return-from fullhouse T)
            )
        )
        nil
    )
)
(defun fourOfAKind (hand) 
    (loop for x from 0 to 12 do
        (if (= 4 (aref (hand-numeachcard hand) x))
            (progn
                (setf (hand-fourkindval hand) x)
                (return-from fourofakind T)
            )
        )
    )
    nil
)
(defun straightFlush (hand) 
    (let ((curConsecutive 0) (potentialSuit #\z))
        (loop for x from 0 to 3 do
            (setf curconsecutive 0)
            (loop for y from 0 to 12 do
                (if (= curconsecutive 5)
                    (progn
                        (setf (hand-flushsuit hand) x)
                        (return-from straightFlush (not nil))
                    )
                )
                (if (aref (hand-markedcards hand) x y)
                    (incf curconsecutive)
                    (setf curconsecutive 0)
                )
            )
        )

        (if (not (= (card-value (nth 4 (hand-mycards hand))) 12))
            (return-from straightFlush nil)
        )
        (setf potentialsuit (string (card-suit (nth 4 (hand-mycards hand)))))
        (loop for x from 0 to 3 do
            (if (or (not (= (- 3 x) (card-value (nth x (hand-mycards hand))))) (not (= (char-code (char potentialsuit 0)) (char-code (card-suit (nth x (hand-mycards hand)))))))
                (return-from straightflush nil)
            )
        )
        (setf (hand-flushsuit hand) (suitRank (card-suit (nth 0 (hand-mycards hand))))) 

    (not nil))
)
(defun royalFLush (hand)
    (loop for x from 0 to 3 do
        (loop for y from 8 to 13 do
            (if (= y 13)
                (progn
                (setf (hand-flushsuit hand) x)
                (return-from royalFlush (not nil))
                )
            )
            (if (not (aref (hand-markedcards hand) x y) ) 
                (return)
            )
        )
    )
    nil)

(defun gradeHand (hand)
    (if (royalFlush hand)(progn
        (setf (hand-handrank hand) ROYAL_FLUSH)
        (return-from gradeHand)
    ))
    (if (straightFlush hand)(progn
        (setf (hand-handrank hand) STRAIGHT_FLUSH)
        (return-from gradeHand)
    ))
    (if (fourOfAKind hand)(progn
        (setf (hand-handrank hand) FOUR_OF_A_KIND)
        (return-from gradeHand)
    ))
    (if (fullHouse hand)(progn
        (setf (hand-handrank hand) FULL_HOUSE)
        (return-from gradeHand)
    ))
    (if (flushFunc hand)(progn
        (setf (hand-handrank hand) FLUSH)
        (return-from gradeHand)
    ))
    (if (straightFunc hand)(progn
        (setf (hand-handrank hand) STRAIGHT)
        (return-from gradeHand)
    ))
    (if (threeOfAKind hand)(progn
        (setf (hand-handrank hand) THREE_OF_A_KIND)
        (return-from gradeHand)
    ))
    (if (twoPair hand)(progn
        (setf (hand-handrank hand) TWO_PAIR)
        (return-from gradeHand)
    ))
    (if (pairFunc hand)(progn
        (setf (hand-handrank hand) PAIR)
        (return-from gradeHand)
    ))
    (setf (hand-handrank hand) HIGH_CARD)
)
;(defparameter faces (make-array 4 :initial-contents '(#\D #\C #\H #\S)))
;(defparameter faces '(#\D #\C #\H #\S))


;(defparameter hand1 (newHand))
;(loop for i from 0 to 4
;    do (setf (aref (hand-mycards hand1) i) (newCard i (aref faces (rem i 4))))
;    do (format t "toString: ~A~%" (toString (aref (hand-mycards hand1) i) ) )
;)
