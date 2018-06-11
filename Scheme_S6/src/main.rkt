#lang racket
(require "./strat-basique.rkt")
(require "./parser.rkt")
(provide (all-defined-out))

;(define liste-usines (factorisation "../tst/fichier_entree.txt"))
(define liste-usines '((1 2 (1 0 0))))

(define (boucle strategie gold usines nbtour chaine-prod); return goldfinal
  (define-values (gold-tmp chaine-prod-tmp) (strategie gold usines chaine-prod nbtour))
  (if (= nbtour 0)
      gold
      (boucle strategie gold-tmp usines (- nbtour 1) chaine-prod-tmp)))


(define chaine-prod (l-init-strat (length (list-ref (car liste-usines) 2))))

(define (resultat strategie goldinit nbtour) ; strat function returns gold and factories after one turn
  (boucle strategie goldinit liste-usines nbtour chaine-prod)  )


(resultat strategie1 1 100)
