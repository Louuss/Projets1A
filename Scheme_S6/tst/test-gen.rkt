#lang racket

(require "../src/gen.rkt")
(require "../src/parser.rkt")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Tests de gen.rkt;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define path-to-file "./fichier_entree_pour_test.txt")
(define file-to-test (file->lines "./fichier_entree_pour_test.txt"))
(define file-parsed (file->lines "./fichier_entree.txt"))

(define (test-rajout l x i result)
  (if (equal? (rajout l x i) result)
      (display "Test rajout .... pass \n")
    (display "Test rajout .... don't pass\n")))


(define (test-mult i x l result)
  (if (equal? (mult i x l) result)
      (display "Test mult .... pass \n")
    (display "Test mult .... don't pass\n")))


(define (test-search usines id_res result)
  (if (equal? (search usines id_res) result)
      (display "Test search .... pass \n")
    (display "Test search .... don't pass\n")))



(define (test-liste-indices-éléments-negatifs-gen liste result)
  (if (equal? (liste-indices-éléments-negatifs-gen liste) result)
      (display "Test liste-indices-éléments-negatifs-gen .... pass \n")
      (display "Test liste-indices-éléments-negatifs-gen .... don't pass\n")))


(define (test-res-to-usine usines-dispo paire result)
  (if (equal? (res-to-usine usines-dispo paire) result)
      (display "Test res-to-usine .... pass \n")
      (display "Test res-to-usine .... don't pass\n")))


(define (test-construction-chaine-gen usines-dispo result)
  (if (equal? (construction-chaine-gen usines-dispo) result)
      (display "Test construction-chaine-gen .... pass \n")
      (display "Test construction-chaine-gen .... don't pass\n")))


(define (test-l-init x result)
  (if (equal? (l-init x) result)
      (display "Test l-init .... pass \n")
      (display "Test l-init .... don't pass\n")))


(define (test-nb-factories liste result)
  (if (equal? (nb-factories liste) result)
      (display "Test nb-factories .... pass \n")
      (display "Test nb-factories .... don't pass\n")))


(define (test-ind-factory liste result)
  (if (equal? (ind-factory liste) result)
      (display "Test ind-factory .... pass \n")
      (display "Test ind-factory .... don't pass\n")))


(define (test-ressources-factory fact-avail liste result)
  (if (equal? (ressources-factory fact-avail liste) result)
      (display "Test ressources-factory .... pass \n")
      (display "Test ressources-factory .... don't pass\n")))


(define (test-viable chaine-prod list-res list-factories-available result)
  (if (equal? (viable chaine-prod list-res list-factories-available) result)
      (display "Test viable .... pass \n")
      (display "Test viable .... don't pass\n")))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Tests;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define list-of-factories (factorisation path-to-file))
(define big-list-of-factories (factorisation "./fichier_entree.txt"))

(test-rajout '(1 2 3 4) 3 2 '(1 5 3 4))
(test-mult 2 4 '(1 2 3 4 5) '(1 8 3 4 5))
(test-search '((1 1(1 1 -1 0 0)) (2 3 (2 0 0 1 0)) (3 2 (3 0 1 -1 0))) 4 2)
(test-liste-indices-éléments-negatifs-gen '(1 0 -4 0 -7 6 0 -8) '((3 4) (5 7) (8 8)))
(test-res-to-usine list-of-factories '(2 2) '(3 2))
(test-construction-chaine-gen big-list-of-factories '((6 1) (5 1) (4 3) (1 6)))
(test-l-init 3 '(0 0 0))
(test-nb-factories '((6 2) (5 2) (4 6) (1 12)) 2)
(test-ind-factory '((6 2) (5 2) (4 6) (1 12)) 6)
(test-ressources-factory big-list-of-factories '((3 2) (5 2) (4 1)) '(0 0 0 0 0 1 0 0 -2 -1))
(test-viable '((6 1) (5 1) (4 3) (1 6)) '(0 0 0 0 0 0 0 0 0 0) big-list-of-factories #t)
"All tests .... PASSED"



