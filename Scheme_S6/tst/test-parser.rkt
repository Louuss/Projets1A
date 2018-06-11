#lang racket
(require "../src/parser.rkt")


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;Tests de parser.rkt pour un exemple simple;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define path-to-file "./fichier_entree_pour_test.txt")
(define file-to-test (file->lines "./fichier_entree_pour_test.txt"))
(define file-parsed (file->lines "./fichier_entree.txt"))


(define (test-clean filepath result)
  (if (equal? (clean filepath) result)
      (display "Test clean .... pass \n")
      (display "Test clean .... don't pass\n")))

(define (test-del-line liste result)
  (if (equal? (del-line liste) result)
      (display "Test del-line .... pass \n")
      (display "Test del-line .... don't pass\n")))

(define (test-drop-the-cost-for-all liste result)
  (if (equal? (drop-the-cost-for-all liste) result)
      (display "Test drop-the-coast-for-all .... pass \n")
      (display "Test drop-the-coast-for-all .... don't pass\n")))

(define (test-apply-append liste result)
  (if (equal? (apply-append liste) result)
      (display "Test apply-append .... pass \n")
      (display "Test apply-append .... don't pass\n")))

(define (test-list-of-ressources liste result)
  (if (equal? (list-of-ressources liste "") result)
      (display "Test list-of-ressources .... pass \n")
      (display "Test list-of-ressources .... don't pass\n")))

(define (test-get-all-names liste result)
  (if (equal? (get-all-names liste) result)
      (display "Test get-all-names .... pass \n")
      (display "Test get-all-names .... don't pass\n")))

(define (test-swap-gold liste result)
  (if (equal? (swap-gold liste) result)
      (display "Test swap-gold .... pass \n")
      (display "Test swap-gold .... don't pass\n")))


(define (test-create-list liste result)
  (if (equal? (create-list liste) result)
      (display "Test create-list .... pass \n")
      (display "Test create-list .... don't pass\n")))


(define (test-empty-profit liste result)
  (if (equal? (empty-profit liste) result)
      (display "Test empty-profit .... pass \n")
      (display "Test empty-profit .... don't pass\n")))

(define (test-split-in-list liste result)
  (if (equal? (split-in-list liste) result)
      (display "Test split-in-list .... pass \n")
      (display "Test split-in-list .... don't pass\n")))

(define (test-insert-at x pos liste result)
  (if (equal? (insert-at x pos liste) result)
      (display "Test insert-at .... pass \n")
      (display "Test insert-at .... don't pass\n")))


(define (test-res-plus-one all-res liste liste-0 result)
  (if (equal? (res-plus-one all-res liste liste-0) result)
      (display "Test res-plus-one .... pass \n")
      (display "Test res-plus-one .... don't pass\n")))

(define (test-res-minus-one all-res liste liste-0 result)
  (if (equal? (res-minus-one all-res liste liste-0) result)
      (display "Test res-minus-one .... pass \n")
      (display "Test res-minus-one .... don't pass\n")))



(define (test-good-form-plus liste result)
  (if (equal? (good-form-plus liste) result)
      (display "Test good-form-plus .... pass \n")
      (display "Test good-form-plus .... don't pass\n")))

(define (test-good-form-minus liste result)
  (if (equal? (good-form-minus liste) result)
      (display "Test good-form-minus .... pass \n")
      (display "Test good-form-minus .... don't pass\n")))

(define (test-get-plus all-res liste list-of-0 result)
  (if (equal? (get-plus all-res liste list-of-0) result)
      (display "Test get-plus .... pass \n")
      (display "Test get-plus .... don't pass\n")))


(define (test-get-minus all-res liste list-of-0 result)
  (if (equal? (get-minus all-res liste list-of-0) result)
      (display "Test get-minus .... pass \n")
      (display "Test get-minus .... don't pass\n")))


(define (test-get-profit all-res liste list-of-0 result)
  (if (equal? (get-profit all-res liste list-of-0) result)
      (display "Test get-profit .... pass \n")
      (display "Test get-profit .... don't pass\n")))


(define (test-one-factory all-res liste list-of-0 usine_id result)
  (if (equal? (one-factory all-res liste list-of-0 usine_id) result)
      (display "Test one-factory .... pass \n")
      (display "Test one-factory .... don't pass\n")))


(define (test-create-factories all-res liste-parsed tot_fact result)
  (if (equal? (create-factories all-res liste-parsed tot_fact) result)
      (display "Test create-factories .... pass \n")
      (display "Test create-factories .... don't pass\n")))


(define (test-factorisation filepath result)
  (if (equal? (factorisation filepath) result)
      (display "Test factorisation .... pass \n")
      (display "Test factorisation .... don't pass\n")))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Tests;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define test1 (clean file-to-test))
(define test2 (del-line test1))
(define test3 (drop-the-cost-for-all test2))
(define test4 (apply-append test3))
(define test5 (apply-append (get-all-names test4)))
(define ressources (create-list "./fichier_entree_pour_test.txt"))
(define liste-of-0 (empty-profit ressources))
(define test6 '("Herb=1" "Wheat=1" "Sugarcane=1" "Almond=1" "Herb=1" "Wheat=2" "Beer=1"))

(test-clean file-to-test '(("[]" "-->" "[Herb=1,Wheat=1]" "cost" "=" "1")
                           ("[]" "-->" "[Sugarcane=1,Almond=1]" "cost" "=" "3")
                           ("[Herb=1,Wheat=2]" "-->" "[Beer=1]" "cost" "=" "2")))
(test-del-line test1 '(("" "Herb=1,Wheat=1" "1") ("" "Sugarcane=1,Almond=1" "3") ("Herb=1,Wheat=2" "Beer=1" "2")))
(test-drop-the-cost-for-all test2 '(("" "Herb=1,Wheat=1") ("" "Sugarcane=1,Almond=1") ("Herb=1,Wheat=2" "Beer=1")))
(test-apply-append test3 '("" "Herb=1,Wheat=1" "" "Sugarcane=1,Almond=1" "Herb=1,Wheat=2" "Beer=1"))
(test-list-of-ressources test4 ",,Herb=1,Wheat=1,,Sugarcane=1,Almond=1,Herb=1,Wheat=2,Beer=1")
(test-get-all-names test4 '(("Herb" "Wheat") ("Sugarcane" "Almond") ("Herb" "Wheat") ("Beer")))
(test-swap-gold test5 '("Gold" "Beer" "Wheat" "Herb" "Almond" "Sugarcane" "Wheat" "Herb"))
(test-create-list path-to-file '("Gold" "Beer" "Almond" "Sugarcane" "Wheat" "Herb"))

(test-empty-profit ressources '(0 0 0 0 0 0))
(test-split-in-list test6 '(("Herb" "1") ("Wheat" "1") ("Sugarcane" "1") ("Almond" "1") ("Herb" "1") ("Wheat" "2") ("Beer" "1")))
(test-insert-at 2 4 '(0 0 0 0 0 0 0) '(0 0 0 0 2 0 0))
(test-res-plus-one ressources '("Herb" "1" "Wheat" "2") liste-of-0 '(0 0 0 0 2 1))
(test-res-minus-one ressources '("Herb" "1" "Wheat" "1") liste-of-0 '(0 0 0 0 -1 -1))
(test-good-form-plus test4 '("Herb" "1" "Wheat" "1"))
(test-good-form-minus test4 '())
(test-get-plus ressources '("Herb=1,Wheat=2" "Beer=1") liste-of-0 '(0 1 0 0 0 0))
(test-get-minus ressources '("Herb=1,Wheat=2" "Beer=1") liste-of-0 '(0 0 0 0 -2 -1))
(test-get-profit ressources '("Herb=1,Wheat=2" "Beer=1") liste-of-0 '(0 1 0 0 -2 -1))
(test-one-factory ressources '("Herb=1,Wheat=2" "Beer=1" "2") liste-of-0 2 '(2 2 (0 1 0 0 -2 -1)))
(test-create-factories ressources test2 3 '((3 1 (0 0 0 0 1 1)) (4 3 (0 0 1 1 0 0)) (5 2 (0 1 0 0 -2 -1))))
(test-factorisation path-to-file '((1 1 (0 0 0 0 1 1)) (2 3 (0 0 1 1 0 0)) (3 2 (0 1 0 0 -2 -1))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;Tests globaux pour des fichiers à parser longs;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(test-create-list "./fichier_entree.txt" '("Gold" "Marzipan" "Sugar" "Bread" "Flour" "Beer" "Almond" "Sugarcane" "Wheat" "Herb"))
(test-create-list "./fichier_entree_gold_identique.txt" '("Gold"))
(test-factorisation "./fichier_entree_que_commentaires.txt"  '())
(test-factorisation "./fichier_entree_gold_identique.txt"  '((1 1 (2)) (2 1 (2)) (3 1 (2))) )
"All tests .... PASSED"