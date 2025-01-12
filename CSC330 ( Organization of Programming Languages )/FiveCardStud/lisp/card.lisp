;#!/usr2/local/sbcl/bin/sbcl --script

(defstruct Card
    value
    suit
)

(defun newCard ( value suit )
    (make-card :value value :suit suit))

(defun defaultCard ()
  (make-card :value -1 :suit #\z))

(defun getValue (char)
    (case char
        (#\2 0)
        (#\3 1)
        (#\4 2)
        (#\5 3)
        (#\6 4)
        (#\7 5)
        (#\8 6)
        (#\9 7)
        (#\J 9)
        (#\Q 10)
        (#\K 11)
        (#\A 12)
        (otherwise -1)
    )
)

(defun suitRank (suit)
    ;(format t "~A~%" char)
    ;(let ((ch (char (symbol-name c))))
    (case suit
        ('D 0)
        (#\D 0)
        ('C 1)
        (#\C 1)
        ('H 2)
        (#\H 2)
        ('S 3)
        (#\S 3)
        (otherwise -1)
    )
)


(defun toString (card)
  (let ((face (case (card-value card)
                 (12 "A")
                 (11 "K")
                 (10 "Q")
                 (9 "J")
                 (8 "10")
                 (otherwise (format nil "~A" (+ (card-value card) 2)))))
         (suit (string (card-suit card))))
    (concatenate 'string face suit)))

;(defparameter my-card (make-card :value 10 :suit #\H))

;(format t "Card Value: ~A~%" (card-value my-card))
;(format t "Card Suit: ~A~%" (card-suit my-card))
;(format t "Suit Value: ~A~%" (getValue (card-suit my-card)))
;(format t "toString: ~A~%" ( toString my-card ) )

;(defparameter cards ( make-array 13 :initial-element (defaultCard)))
;(defparameter faces (make-array 4 :initial-contents '(#\D #\C #\H #\S)))

;(loop for i from 0 to 12
;    do (setf (aref cards i) (newCard i (aref faces (rem i 4)))))

;(loop for i from 0 to 12
;    do(format t "toString: ~A~%" ( toString (aref cards i) )))