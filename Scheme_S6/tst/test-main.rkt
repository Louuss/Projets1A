#lang racket
;;(require rackunit)
(require "../src/main.rkt")

(define ressources
  '( "blé" "pain" "or"))

;chaque élément est de la forme (id cout gain)
(define liste-usines '((1 2 (1 0 -2)) (2 1 (0 -2 1)) (3 1 (0 2 0))))


;;Testing the function which searches the usine producing a special ressources into the usines'list
(define (test--search)
  (println "Test search")
  (check-eq? (= (search '((1 2 (1 0 -2)) (2 1 (0 -2 1)) (3 1 (0 2 0))) 2) 3) #t
             "Can't find a factory because there is no factory"))



(test--search)
