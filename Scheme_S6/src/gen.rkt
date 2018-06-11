#lang racket
;;Generique
(require "./parser.rkt")
(provide (all-defined-out))


(define ressources (create-list "../tst/fichier_entree.txt"))

;;Fonction's aim : add 1 to an element placed i of a list l
;;Variables' type : l : list / x : a number / i : a number
;;PRECOND : i <= length(l)
;;POSTCOND : returns a list
;;Returnal's type : list
;;Example :(rajout '(1 2 3 4) 3 2) returns '(1 5 3 4)
(define (rajout l x i)
  (if (null? l)
      '()
      (if (= 1 i)
          (cons (+ (car l) x) (cdr l))
          (cons (car l) (rajout (cdr l) x (- i 1))))))


;;Fonction's aim : multiplies a special element of the list
;;Variables' type : i : number (place of the number considered) / x : number (multiplicator) / l :list
;;PRECOND : i <= length(l)
;;POSTCOND : returns a list
;;Returnal's type : list
;;Example : (mult 2 3 '(1 2 3 4 5))
;;returns '(1 6 3 4 5)
(define (mult i x l)
  (if (null? l)
      '()
      (if (= 1 i)
          (cons (* (car l) x) (cdr l))
          (cons (car l) (mult (- i 1) x (cdr l))))))



;;searches the usine in usines that can produce res
;;arguments: list of usines, id res
;;returns: pair of id usine we are looking for and id of the entry (ressource needed for the usine)
;;exemple: (search '((1 1 -1 0 0) (2 0 0 1 0) (3 0 1 -1 0)) 1) ------> '(1 2)
;;Fonction's aim : searches the id into the list of factories, of the first factorie that can produce res
;;Variables' type : usines : list (list of factories) / id_res : number (id of the ressource searched)
;;PRECOND : id_res <= length(list of ressources of the factories)
;;POSTCOND : number returned <= length(usines)
;;Returnal's type : a number
;;Example : (search '((0 1(1 1 -1 0 0)) (1 3 (2 0 0 1 0)) (2 2 (3 0 1 -1 0))) 4)
;;returns 1
(define (search usines id_res)
  (if (null? usines)
      (raise "error")
      (if (> (list-ref (list-ref (car usines) 2) (- id_res 1)) 0)
          (car (car usines))
          (search (cdr usines) id_res))))


;;Fonction's aim : Gives the id and the value of the negative elements of the factory ressources. 
;;Variables' type : l : list (of ressources used for the factory) / compteur : number (to know where we are in the list)
;;PRECOND : compteur <= length(l)
;;POSTCOND : compteur <= length(l)
;;Returnal's type : a list of lists (of length 2) 
;;Example : (liste-indices-éléments-negatifs-gen '(1 0 -4 8 -7 6 4 -8))
;;returns '((3 4) (5 7) (8 8))
(define (liste-indices-éléments-negatifs l compteur)
  (if (null? l)
      '()
      (if (< (car l) 0)
          (cons (list compteur (- 0 (car l)))  (liste-indices-éléments-negatifs (cdr l) (+ 1 compteur)))
          (liste-indices-éléments-negatifs (cdr l) (+ 1 compteur)))))

(define (liste-indices-éléments-negatifs-gen l)
  (liste-indices-éléments-negatifs l 1))


;;Fonction's aim : Searches the first factory which can create the ressource wanted and calculates how many factory of this kind we need
;;Variables' type : usines-dispo : list (of all usines initialised by the parser) / paire : list (composed of the id of the ressource wanted and the quantity needed)
;;PRECOND : (firt element of paire) <= length(list of ressources)
;;POSTCOND : length(list returned) <= 2
;;Returnal's type : list
;;Example : (res-to-usine liste-usines '(2 2)) returns '(8 2)
(define (res-to-usine usines-dispo paire)
  (list (search usines-dispo (car paire)) (ceiling (/ (list-ref paire 1) (list-ref (car (cdr (cdr (list-ref usines-dispo (- (search usines-dispo (car paire)) 1))))) (- (car paire) 1 )))))) 


;;Fonction's aim : Find the first path to create gold.
;;Variables' type : usines-dispo : list (of all usines initialised by the parser)
;;PRECOND : usines-dispo is a list
;;POSTCOND : returns a list
;;Returnal's type : list
;;Example : (construction-chaine liste-usines (list (list (search liste-usines 1) 1)) 1 ) returns '((6 1) (5 1) (4 3) (1 6))
(define (construction-chaine usines-dispo chaine indice-dernier-ajout)
  (if (> indice-dernier-ajout (length chaine))
      chaine
      (construction-chaine usines-dispo (append chaine
                       (map (lambda (x) (res-to-usine usines-dispo (mult 2 (list-ref (list-ref chaine (- indice-dernier-ajout 1)) 1) x) ))
         (liste-indices-éléments-negatifs-gen (list-ref (list-ref usines-dispo (- (car (list-ref chaine (- indice-dernier-ajout 1))) 1)) 2))))     
                           (+ indice-dernier-ajout 1)  )  ))


(define (construction-chaine-gen usines-dispo )
  (construction-chaine usines-dispo (list (list (search usines-dispo 1) 1)) 1   ))


;;Fonction's aim : creates a list of x 0.
;;Variables' type : x: number
;;PRECOND : x is a number
;;POSTCOND : returns a list of length x
;;Returnal's type : list
;;Example : (l-init 3)
;;returns '(0 0 0)
(define (l-init x)
  (if (= 0 x )
    '()
    (cons 0 (l-init (sub1 x)))))



;;Fonction's aim : returns the quantity of the first factory nedded in the production network
;;Variables' type : L : liste (production network)
;;PRECOND : L is a non empty list
;;POSTCOND : returns a number
;;Returnal's type : number
;;Example : (nb-factories '((3 2) (5 2) (4 1))) returns 2
(define (nb-factories L)
  (cadar L))



;;Fonction's aim : returns the id of the first factory
;;Variables' type : L : liste (production network)
;;PRECOND : L is a non empty list
;;POSTCOND : returns a number
;;Returnal's type : number
;;Example : (ind-factory '((3 2) (5 2) (4 1))) returns 3
(define (ind-factory L)
  (caar L))


;;returns a list of the ressources needed and created by a factory

;;Fonction's aim : returns a list of the ressources needed and created by the first factory
;;Variables' type : fact-avail : list (of usines given by the parser) / L : list (of a production network)
;;PRECOND : length(L) <= length(fact-avail) and list is non empty
;;POSTCOND : returns a list and length(list returned) = length(list of ressources given by the parser)
;;Returnal's type : list
;;Example : (ressources-factory liste-usines '((3 2) (5 2) (4 1))) returns '(0 0 0 0 0 1 0 0 -2 -1)
(define (ressources-factory fact-avail L)
  (caddr (list-ref fact-avail (- (ind-factory L) 1))))


;;Fonction's aim : determines if the metwork is viable (#t) or not (#f)
;;Variables' type : chaine-prod : list (production network) / list-res : list (of 0) / list-factories-available : list (list of factories given by the parser)
;;PRECOND : length(list-res) = length(list of ressrouces given by the parser)
;;POSTCOND : returns a boolean
;;Returnal's type : boolean 
;;Example : (viable '((6 1) (5 1) (4 3) (1 6)) '(0 0 0 0 0 0 0 0 0 0) big-list-of-factories) returns #t
(define (viable chaine-prod list-res list-factories-available )
  (if (null? chaine-prod)
      (andmap (lambda (x) (> x -1)) list-res)
      (viable (cdr chaine-prod) (map + (map (lambda (x) (* x (nb-factories chaine-prod))) (ressources-factory list-factories-available chaine-prod)) list-res) list-factories-available )))
