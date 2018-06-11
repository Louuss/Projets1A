#lang racket

(require "./gen.rkt")
(require "./parser.rkt")
(provide (all-defined-out))

(define filepath "../tst/fichier_entree.txt")
;(define list-usines (factorisation "../tst/fichier_entree.txt"))
;;strategie1


(define (l-init-strat nbusines)
  (l-init nbusines))



;;Fonction's aim : produce the gold
;;Variables' type : stock : number (stock of ressources) / gold : number (number of gold in our possession)
;;usines : list (of factories) / chaine-prod : a list (the production network)
;;PRECOND : length(stock) = length(list of ressources) , length(usines)!= 0
;;POSTCOND : returns a number
;;Returnal's type : number 
;;Example : (produce1 '(0 0 0 0 0 0 0 0 0 0) 3 list-usines (construction-chaine-gen list-usines)) returns 4
(define (produce1 stock gold usines chaine-prod)
  (+ gold (car chaine-prod)))


;;Fonction's aim : add 1 to the number of factories wanted 
;;Variables' type : gold : number (of gold we have before the run) / usines : list (of factories) / chaine-prod : list (production network) / nbtour : number (of runs to do)
;;PRECOND : gold is a number , chaine-prod and usines non empty lists
;;POSTCOND : returns 4 elements : a number, two lists and an other number 
;;Returnal's type : 4 elements (the gold number, the list of factories, the list of the production network, the number of runs to still do)
;;Example : (ajout1 3 list-usines (construction-chaine-gen list-usines) 1)
;;returns
;;2
;;'((1 1 (0 0 0 0 0 0 0 0 1 1))
;;  (2 3 (0 0 0 0 0 0 1 1 0 0))
;;  (3 2 (0 0 0 0 0 1 0 0 -2 -1))
;;  (4 3 (0 0 0 0 1 0 0 0 -2 0))
;;  (5 4 (0 0 0 1 -3 0 0 0 0 0))
;;  (6 2 (5 0 0 -1 0 0 0 0 0 0))
;;  (7 1 (0 0 1 0 0 0 0 -1 0 0))
;;  (8 3 (0 1 -1 0 0 0 -2 0 0 0))
;;  (9 10 (10 -1 0 0 0 0 0 0 0 0)))
;;'((6 2) (5 1) (4 3) (1 6))
;;1
(define (ajout1 gold usines chaine-prod)
  (if (> gold 0)
      (values (sub1 gold) usines (rajout chaine-prod 1 1))
      (values gold usines chaine-prod)))


;;Fonction's aim : applies a basic strategy
;;Variables' type : produce : function / add-fact : function / gold : number (number of gold we have) / usines : list (liste of factories from the parser)
;;/ chaine-prod : list (of the production network) / nbtour : number (number of iterations)
;;PRECOND : 
;;POSTCOND : 
;;Returnal's type : number (of gold after the turns).
;;Example : (strategie produce1 ajout1 3 list-usines (construction-chaine-gen list-usines) 1)
;;returns 2 and '((6 2) (5 1) (4 3) (1 6))
(define (strategie produce add-fact gold usines chaine-prod nbtour )
                                                       ;ajout return golds and factories after buying factories following the strat
  (let* ((nb-ressources (length (create-list filepath))) ; stock = ressources during the turn
         (stock (l-init nb-ressources)))
    (define-values (goldtmp usinestmp chaine-prodtmp) (add-fact gold usines chaine-prod))
    (values (produce1 1 goldtmp usines chaine-prodtmp)chaine-prodtmp )))


;;Fonction's aim : applies the function strategie once to the 1irst strategie : buy the same factory each run
;;Variables' type : gold : number (number of gold we have) / usines : list (liste of factories from the parser)
;;/ chaine-prod : list (of the production network) / nbtour : number (number of iterations)
;;PRECOND : nbtour >=1 , length(usines) != 0 , gold != 0
;;POSTCOND : returns (produce stock goldtmp usinestmp chaine-prodtmp) chaine-prodtmp
;;Returnal's type : number (of gold after the turns).
(define (strategie1 gold usines chaine-prod nbtour)
  (strategie produce1 ajout1 gold usines chaine-prod nbtour))

;(strategie1 3 list-usines (construction-chaine-gen list-usines) 1)

;((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((;
;((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((;
;((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((;
;((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((;

;((((((((((((((((((((((((((((((((((((((((((((
