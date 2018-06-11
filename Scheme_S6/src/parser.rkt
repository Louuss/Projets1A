#lang racket

(provide (all-defined-out))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Functions to clean the original file;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;Fonction's aim : removes all the elements beginning with a '#' and normalizes the spaces of all the other elements.
;;Variables' type : list of strings
;;PRECOND : l is a list
;;POSTCOND : the function returns a list
;;Returnal's type : list of strings
;;Example :
;;'("# Any line starting with a '#' is a comment line.\t"
;;  "[] --> [Herb=1,Wheat=1] cost = 1"
;;  "[]    -->   [Sugarcane=1,Almond=1]         cost = 3")
;; becomes :
;;'(("[]" "-->" "[Herb=1,Wheat=1]" "cost" "=" "1")
;;  ("[]" "-->" "[Sugarcane=1,Almond=1]" "cost" "=" "3"))
(define (clean a)
  (cond [(empty? a) '()]
        [(string-prefix? (car a) "#" ) (clean (cdr a))]
        [ else (cons (string-split (car a)) (clean (cdr a)))]))

;;Fonction's aim : removes all the elements '[', ']', '=' '-->' 'cost' from each line.
;;Variables' type : list of strings
;;PRECOND : l is a list
;;POSTCOND : the function returns a list
;;Returnal's type : list of strings
;;Example :
;;'(("[]" "-->" "[Herb=1,Wheat=1]" "cost" "=" "1"))
;; becomes :
;;'(("" "Herb=1,Wheat=1" "1"))
(define (del-line a)
  (if (empty? a)
  '()
  (cons (del-c (car a)) (del-line (cdr a)) )))


(define (del-c a)
  (cond
    [(empty? a) '()]
    [(string-prefix? (car a) "-") (del-c (cdr a))]
    [(string-prefix? (car a) "=") (del-c (cdr a))]
    [(string=? (car a) "cost") (del-c (cdr a))]
    [else (cons (string-replace (string-replace (car a) "[" "") "]" "") (del-c (cdr a)))]))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Functions to create the resources list;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;Fonction's aim : deletes the last element of each line
;;Variables' type : list of strings
;;PRECOND : l is a list of strings
;;POSTCOND : the function returns a list of strings
;;Returnal's type : list of strings
;;Example :
;;'(("" "Herb=1,Wheat=1" "1")
;;  ("" "Sugarcane=1,Almond=1" "3"))
;;becomes
;;'(("" "Herb=1,Wheat=1")
;;  ("" "Sugarcane=1,Almond=1"))
(define (drop-the-cost liste)
  (drop-right liste 1))


;;Previous function applied to all the list.
(define (drop-the-cost-for-all liste)
  (map drop-the-cost liste))

;;Fonction's aim : Creates a big list with all the lists of lists used for the function.
;;Variables' type : liste is a list of lists.
;;PRECOND : liste is a list
;;POSTCOND : returns a list
;;Returnal's type : list
;;Example : '(("" "Herb=1,Wheat=1") ("" "Sugarcane=1,Almond=1"))
;;becomes '("" "Herb=1,Wheat=1" "" "Sugarcane=1,Almond=1")
(define (apply-append liste)
  (apply append liste))


;;Fonction's aim : create a big string with all the ressources from the list, separated by ",".
;;Variables' type : l : list of strings / res : string
;;PRECOND : l is a list and res a string
;;POSTCOND : the function returns a list
;;Returnal's type : list of strings
;;Example :
;;'("" "Herb=1,Wheat=1" "" "Sugarcane=1,Almond=1")
;; becomes :
;;",Herb=1,Wheat=1,,Sugarcane=1,Almond=1"
(define (list-of-ressources liste res)
  (if (empty? liste)
    res
    (list-of-ressources (cdr liste) (string-append (string-append res "," ) (car liste)))))


;;Fonction's aim : cut-off the name of a ressource.
;;Variables' type : string
;;PRECOND : elt is a string
;;POSTCOND : the function returns a list
;;Returnal's type : list
;;Example : "Herb=1,Wheat=1"
;;becomes '("Herb" "Wheat")
(define (get-names-once elt)
  (if
    (= 0 (string-length elt ))
    '()
    (cons (car (string-split (car (string-split elt ",")) "="))  (get-names-once(list-of-ressources (cdr (string-split elt ",")) "")))))


;;Fonction's aim : create a list of all the ressources of the initial file.
;;Variables' type : list
;;PRECOND : liste is a list of strings
;;POSTCOND : the function returns a list of strings
;;Returnal's type : list of strings
;;Example :
;;'(""
;;  "Herb=1,Wheat=1"
;;  ""
;;  "Sugarcane=1,Almond=1")
;;becomes
;;'(("Herb" "Wheat")
;;  ("Sugarcane" "Almond"))
(define (get-all-names liste)
  (cond
    [(empty? liste) '()]
    [(string=? "" (car liste)) (get-all-names (cdr liste))]
    [else (cons (get-names-once (car liste)) (get-all-names (cdr liste)))]))


;;Fonction's aim : the same as (swap-gold-r list result) but (swap-gold lis) is recursive terminal
(define (swap-gold lis )
  (swap-gold-r lis '() ))


;;Fonction's aim : puts the 'Gold' ressource at the beginning of the list
;;Variables' type : l : list of string / result : list
;;PRECOND : l is a list of string and result an empty list.
;;POSTCOND : list is empty and result a list
;;Returnal's type : list
;;Example :
;;'("Herb" "Wheat" "Sugarcane" "Almond" "Beer" "Flour" "Bread" "Gold" "Sugar" "Marzipan")
;;becomes:
;;'("Gold" "Marzipan" "Sugar" "Bread" "Flour" "Beer" "Almond" "Sugarcane" "Wheat" "Herb")
(define (swap-gold-r list result)
  (cond
    [(empty? list) (cons "Gold" result)]
    [(string=? "Gold" (car list)) (swap-gold-r (cdr list) result)]
    [else (swap-gold-r (cdr list) (cons (car list) result))]))

;;Fonction's aim : generates the ressources list.
;;Variables' type : filepath = a path to a file.
;;PRECOND : filepath is valid/exists.
;;POSTCOND : returns a list
;;Returnal's type : list of strings
;;Example : (create-list "../tst/fichier_entree.txt")
;;returns
;; '("Gold" "Marzipan" "Sugar" "Bread" "Flour" "Beer" "Almond" "Sugarcane" "Wheat" "Herb")
(define (create-list filepath)
( swap-gold (remove-duplicates(apply-append (get-all-names (apply-append (drop-the-cost-for-all (del-line (clean (file->lines filepath))))))))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Functions to create the factories's list;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;Calls the next function to use it with an argument.
(define (empty-profit list)
  (empty-profit-r '() (length list)))

;;Fonction's aim : creates a list composed of 0.
;;Variables' type : res is a list / cpt a number
;;PRECOND : cpt = length(list of ressources generated by "create-list file")
;;POSTCOND : the list is only composed of 0
;;Returnal's type : list
;;Example : (empty-profit-r '() 10)
;;returns '(0 0 0 0 0 0 0 0 0 0)
(define (empty-profit-r res cpt)
  (if (= cpt 0)
  res
  (empty-profit-r  (cons 0 res) (sub1 cpt))))


;;Fonction's aim : Split a list of strings into a list of lists, removing the "=" symbol.
;;Variables' type : list is a list
;;PRECOND : list is a list
;;POSTCOND : returnsa list.
;;Returnal's type : list of lists.
;;Example :'("Herb=1" "Wheat=1")
;;becomes '(("Herb" "1") ("Wheat" "1"))
(define (split-in-list list)
  (if (empty? list)
    '()
    (cons (string-split( car list) "=") (split-in-list (cdr list)))))

;;Fonction's aim : goes to a special place of the list (pos) to change the number into an other (x)
;;Variables' type : x a number / pos is a number / list a list.
;;PRECOND : pos <= length(list)
;;POSTCOND : list has the same length as the beggining of the function.
;;Returnal's type : list
;;Example : (insert-at 4 2 '(0 0 0 0 0 0 0 0))
;;returns '(0 0 4 0 0 0 0 0)
(define (insert-at x pos list)
  (cond
    [(empty? list) '() ]
    [(= 0 pos) (cons x (insert-at x (sub1 pos) (cdr list))) ]
    [else (cons (car list) (insert-at x (sub1 pos) (cdr list)))]))


;;Fonction's aim : increments the ressources with their cost (positive cost if the ressource is created).
;;Variables' type : all-res is a list of strings (ressources) / liste a list of strings / result a list of numbers
;;PRECOND : all-res and result have the same length
;;POSTCOND : all-res and result have the same length
;;Returnal's type : a list
;;Example : (res-plus-one '("Gold" "Marzipan" "Sugar" "Bread" "Flour" "Beer" "Almond" "Sugarcane" "Wheat" "Herb") '("Herb" "1" "Wheat" "1") '(0 0 0 0 0 0 0 0 0 0))
;;becomes '(0 0 0 0 0 0 0 0 1 1)
(define (res-plus-one all-res liste result)
  (cond
    [(empty? liste) result]
    [else (res-plus-one all-res (cddr liste) (insert-at (string->number (cadr liste)) (index-of all-res (car liste)) result ) )]))



;;Fonction's aim : increments the ressources with their cost (negative cost if the ressources is needed to create another)
;;Variables' type : all-res is a list of strings (ressources) / liste a list of strings / result a list of numbers
;;PRECOND : all-res and result have the same length
;;POSTCOND : all-res and result have the same length
;;Returnal's type : a list
;;Example : (res-plus-one '("Gold" "Marzipan" "Sugar" "Bread" "Flour" "Beer" "Almond" "Sugarcane" "Wheat" "Herb") '("Herb" "1" "Wheat" "1") '(0 0 0 0 0 0 0 0 0 0))
;;becomes '(0 0 0 0 0 0 0 0 -1 -1)
(define (res-minus-one all-res liste result)
  (cond
    [(empty? liste) result]
    [else (res-minus-one all-res (cddr liste) (insert-at (-(string->number (cadr liste))) (index-of all-res (car liste)) result ) )]))



;;Fonction's aim : makes the list in an appropriate shape.
;;Variables' type : list is a list of strings.
;;PRECOND : list is a list of strings.
;;POSTCOND : returns a list of strings.
;;Returnal's type : list of string.
;;Example : (good-form-plus '("" "Herb=1,Wheat=1") )
;;becomes '("Herb" "1" "Wheat" "1")
(define (good-form-plus list )
  (apply-append (split-in-list (string-split (cadr list) ","))))


;;Fonction's aim : turns the list to an appropriate shape.
;;Variables' type : list is a list of strings.
;;PRECOND : list is a list of strings.
;;POSTCOND : returns a list of strings.
;;Returnal's type : list of string.
;;Example : (good-form-minus  '("Herb=12" "Herb=1,Wheat=1"))
;;becomes '("Herb" "12")
(define (good-form-minus list )
  (apply-append (split-in-list (string-split (car list) ","))))


;;Fonction's aim : gets all the "profits" (what is obtained) and put their costs (positive) into the list.
;;Variables' type : all-res is a list of strings (of ressources) / liste is a list of strings / result is a list of 0
;;PRECOND : length( list of ressources ) = length( list of 0 )
;;POSTCOND : length( list of ressources ) = length( list )
;;Returnal's type : list
;;Example : (get-plus '("Gold" "Marzipan" "Sugar" "Bread" "Flour" "Beer" "Almond" "Sugarcane" "Wheat" "Herb") '("" "Herb=1,Wheat=1") '(0 0 0 0 0 0 0 0 0 0))
;;becomes '(0 0 0 0 0 0 0 0 1 1)
(define (get-plus all-res liste result )
  (res-plus-one all-res (good-form-plus liste) result))


;;Fonction's aim : gets all the ressources needed and put their costs(negative) into the list.
;;Variables' type : all-res is a list of strings (of ressources) / liste is a list of strings / result is a list of 0
;;PRECOND : length( list of ressources ) = length( list of 0 )
;;POSTCOND : length( list of ressources ) = length( list )
;;Returnal's type : list
;;Example : (get-plus '("Gold" "Marzipan" "Sugar" "Bread" "Flour" "Beer" "Almond" "Sugarcane" "Wheat" "Herb") '("Herb=12" "Herb=1,Wheat=1") '(0 0 0 0 0 0 0 0 0 0))
;;becomes '(0 0 0 0 0 0 0 0 0 -12)
(define (get-minus all-res liste result )
  (res-minus-one all-res (good-form-minus liste) result))


;;Fonction's aim : creates the list with the ressources needed AND the ressources created. (a combinaison of get-plus and get-minus)
;;Variables' type : all-res is a list of strings (of ressources) / liste is a list of strings / result is a list of 0
;;PRECOND : length( list of ressources ) = length( list of 0 )
;;POSTCOND : length( list of ressources ) = length( list )
;;Returnal's type : list
;;Example : (get-profit '("Gold" "Marzipan" "Sugar" "Bread" "Flour" "Beer" "Almond" "Sugarcane" "Wheat" "Herb") '("Gold=12" "Herb=1,Wheat=1") '(0 0 0 0 0 0 0 0 0 0))
;;becomes '(-12 0 0 0 0 0 0 0 1 1)
(define (get-profit all-res liste result )
  (get-minus all-res liste (get-plus all-res liste result)))


;;Fonction's aim : Creates only one factory from the parsed file.
;;Variables' type : liste-res a list of strings / liste-parsed a liste of strings / empt-prof a list of 0 / number a number
;;PRECOND : length(liste-res) = length(empt-prof) et length(liste-res) > length(liste-parsed)
;;POSTCOND : length(liste-res) = length(empt-prof)
;;Returnal's type : a list of lists
;;Example : (one-factory  '("Gold" "Marzipan" "Sugar" "Bread" "Flour" "Beer" "Almond" "Sugarcane" "Wheat" "Herb") '("" "Herb=1,Wheat=1" "1") '(0 0 0 0 0 0 0 0 0 0) 0)
;;becomes '(0 1 (0 0 0 0 0 0 0 0 1 1))
(define (one-factory liste-res liste-parsed empt-prof number)
  (cons number (cons (string->number (third liste-parsed)) (cons (get-profit liste-res liste-parsed empt-prof) '() ))))



;;Fonction's aim : creates the list of all the factories possible.
;;Variables' type : liste-res a list of strings / liste-parsed a liste of strings / number a number
;;PRECOND : length(liste-res) > length(liste-parsed)
;;POSTCOND : returns a list of lists.
;;Returnal's type : list of lists
;;Example : (create-factories '("Gold" "Marzipan" "Sugar" "Bread" "Flour" "Beer" "Almond" "Sugarcane" "Wheat" "Herb") (del-line (clean (file->lines filepath))) (length (del-line (clean (file->lines filepath)))) )
;;returns
;;'((8 1 (0 0 0 0 0 0 0 0 1 1))
;;  (9 3 (0 0 0 0 0 0 1 1 0 0))
;;  (10 2 (0 0 0 0 0 1 0 0 -2 -1))
;;  (11 3 (0 0 0 0 1 0 0 0 -2 0))
;;  (12 4 (0 0 0 1 -3 0 0 0 0 0))
;;  (13 2 (5 0 0 -1 0 0 0 0 0 0))
;;  (14 1 (0 0 1 0 0 0 0 -1 0 0))
;;  (15 3 (0 1 -1 0 0 0 -2 0 0 0)))
(define (create-factories liste-res liste-parsed  nb )
  (cond
    [(empty? liste-parsed) '()]
    [else (cons (one-factory liste-res (car liste-parsed) (empty-profit liste-res) nb ) (create-factories liste-res (cdr liste-parsed) (add1 nb) ))]))


;;Fonction's aim : Calls create-factories to create all the usines from the file to parse.
;;Variables' type : filepath is a path to reach the file to parse.
;;PRECOND : filepath is a valid/existant/ path. The file is non empty.
;;POSTCOND : returns a list
;;Returnal's type : list
;;Example : (factorisation "../tst/fichier_entree.txt")
;;returns
;;'((0 1 (0 0 0 0 0 0 0 0 1 1))
;;  (1 3 (0 0 0 0 0 0 1 1 0 0))
;;  (2 2 (0 0 0 0 0 1 0 0 -2 -1))
;;  (3 3 (0 0 0 0 1 0 0 0 -2 0))
;;  (4 4 (0 0 0 1 -3 0 0 0 0 0))
;;  (5 2 (5 0 0 -1 0 0 0 0 0 0))
;;  (6 1 (0 0 1 0 0 0 0 -1 0 0))
;;  (7 3 (0 1 -1 0 0 0 -2 0 0 0)))
(define (factorisation filepath)
  (create-factories
    (create-list filepath );; liste ressource
    (del-line (clean (file->lines filepath)))
    1
    ))
