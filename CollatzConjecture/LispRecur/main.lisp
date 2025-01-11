#!/usr2/local/sbcl/bin/sbcl --script

;disables warnings
(declaim (sb-ext:muffle-conditions cl:warning))


(defstruct CPair
    seqStart
    len
)

(defun newCPair ( newStart newLen )
    (make-cpair :seqStart newstart :len newlen )
)

(defun CPairToString (pair)
    (format nil "~20,d ~20,d" (cpair-seqstart pair) (cpair-len pair))
)

(defun collatz (num count)
    (if (= num 1)
        count
        (progn
	    (incf count)
            (if (= (rem num 2) 0) 
                (collatz (/ num 2) count)
                (collatz (+ 1 (* 3 num)) count)
            )
        )
    )
)

(let (
    (start (parse-integer (second sb-ext:*posix-argv*)))
    (end (parse-integer (third sb-ext:*posix-argv*)))
    (listj (list))
    (newPair nil)
    (anotherPassNeeded T)
    (tempPair nil)
)

(if (> start end)
    (progn
        (let ((temp start))
            (setf start end)
            (setf end temp)
        )
    )
)

(loop for i from 0 to 9 do
    (push (newcpair 0 0) listj)
)
(setf listj (reverse listj))

(do ((i start (1+ i))) ((> i end))
    (setf newpair (newcpair i ( collatz i 0 )))
    (loop for i from 0 to 9 do
        (if (= 1 (cpair-seqstart newpair))
        (progn
            (setf listj (cons newpair listj) )
            (setf listj (butlast listj) )
            (return)
        )
        (progn
            (if (= (cpair-len newpair) (cpair-len (nth i listj)))
                (return)
                (progn
                (if  (< (cpair-len (nth i listj)) (cpair-len newpair))
                    (progn
                    (setf listj (append
                        (subseq listj 0 i)
                        (list newpair)
                        (subseq listj i)
                    ))
                    (setf listj (butlast listj) )
                    (return)
                    )
                )
                )
            )
        )
        )
    )
)

(format t "Sorted based on sequence length~%")
(loop for i in listj do
    (if (= 0 (cpair-seqstart i))
        (return)
    )
    (format t "~A~%" (cpairtostring i))
    (if (= 1 (cpair-seqstart i))
        (return)
    )
)

(loop while anotherpassneeded do 
    (setf anotherpassneeded nil)
    (loop for i from 0 to 8 do
        (if (< (cpair-seqstart (nth i listj)) (cpair-seqstart (nth (+ 1 i) listj)) )
            (progn
                (setf anotherpassneeded T)
                (setf temppair (nth i listj))
                (setf (nth i listj) (nth (+ 1 i) listj))
                (setf (nth (+ 1 i) listj) temppair)
            )
        )
    )
)

(format t "Sorted based on integer size~%")
(loop for i in listj do
    (if (= 0 (cpair-seqstart i))
        (return)
    )
    (format t "~A~%" (cpairtostring i))
    (if (= 1 (cpair-seqstart i))
        (return)
    )
)
)
