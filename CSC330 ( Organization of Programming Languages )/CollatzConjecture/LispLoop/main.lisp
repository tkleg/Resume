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

(defun collatz (num)
(let ((count 0))
    (loop while (not (= 1 num)) do
        (if (= 0 (rem num 2))
            (setf num (/ num 2))
            (setf num (+ 1 (* 3 num)))
        )
        (incf count)
    )
count)
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
"""
(format t "~A~%" start)
(format t "~A~%" end)
(format t "~A~%" (type-of start))
(format t "~A~%" (type-of end))
"""
(loop for i from 0 to 9 do
    (push (newcpair 0 0) listj)
)
(setf listj (reverse listj))
"""(loop for i from 0 to 9 do
    (format t "~A~%" (cpairtostring (nth i listj)))
)"""
(do ((i start (1+ i))) ((> i end))
    ;(format t "~A ~A~%" i (collatz i))
    (setf newpair (newcpair i ( collatz i )))
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