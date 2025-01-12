#!/usr2/local/sbcl/bin/sbcl --script
(defclass person ()
  ((name
    :initarg :name
    :accessor name)
   (lisper
    :initform nil
    :accessor lisper)))

;; => #<STANDARD-CLASS PERSON>

(defvar p2 (make-instance 'person :name "me" ))
;;                                 ^^^^ initarg
;; => #<PERSON {1006234593}>

(name p2)
;;^^^ accessor
;; => "me"

(lisper p2)
;; => nil
;;    ^^ initform (slot unbound by default)

(setf (lisper p2) nil)


(defclass child (person)
  ())

(defclass child (person)
  ((can-walk-p
     :accessor can-walk-p
     :initform t)))
;; #<STANDARD-CLASS CHILD>

(can-walk-p (make-instance 'child))
;; T

(princ (name p2))
(terpri)
(princ (lisper p2))
(terpri)
(princ "slots")
(terpri)