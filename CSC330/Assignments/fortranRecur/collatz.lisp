#!/usr2/local/sbcl/bin/sbcl --script
 
;;; Loops based factorial function
(defun factorial (n)
  "Calculates N!"
  (loop for result = 1 then (* result i)
        for i from 2 to n
        finally (return result)))
 
;;; Recursive factorial function
(defun rfactorial (n)
  (if (/= n 1)
    ( * n ( rfactorial (- n 1)))
    ( eval n)))
 
;;; Main Program
(write ( factorial 100))
(terpri)
(write (rfactorial 10000000000000000000000000))
(terpri)
