#lang racket
(require "./parser.rkt")
(require "./gen.rkt")

(define (l-init1 x)
  (if (= 0 x )
    '()
    (cons 1 (l-init1 (sub1 x)))))

(define (l-init123 i j)
  (if (> i j)
    '()
    (cons i (l-init123 (+ 1 i) j ))))
;(l-init1 4)
;(l-init123 1 6)


;----------------------------------------------------------------
;
;                      MISE EN PLACE
;
;----------------------------------------------------------------


(define liste-usines '((1 1 (1 -1 0)) (2 1 (0 2 0)) (3 2 (1 0 -1)) (4 2 (0 0 3))))
(define surplusvide '(0 0 0))
"liste-usines" liste-usines

(define (liste-indices-éléments-negatifs-gen l)
  (liste-indices-éléments-negatifs l 1))

(define (liste-indices-éléments-negatifs l compteur)
  (if (null? l)
      '()
      (if (< (car l) 0)
          (cons (list compteur (- 0 (car l)))  (liste-indices-éléments-negatifs (cdr l) (+ 1 compteur)))
          (liste-indices-éléments-negatifs (cdr l) (+ 1 compteur)))))

;"liste-indices-éléments-negatifs-gen '(1 0 -4 8 -7 6 4 -8)" (liste-indices-éléments-negatifs-gen '(1 0 -4 8 -7 6 4 -8))


(define (indices-gold-factories liste-usines)
  (if (null? liste-usines)
      '()
      (if (< 0 (car (list-ref (car liste-usines) 2)))
          (cons (list-ref (car liste-usines) 0) (indices-gold-factories (cdr liste-usines)))
          (indices-gold-factories (cdr liste-usines)) )))
;"(indices-gold-factories liste-usines)"(indices-gold-factories liste-usines)

(define (enlever-surplus ressources surplus)
  (if (null? ressources)
      '()
      (cons (list (caar ressources) (max 0 (- (cadar ressources) (list-ref surplus (sub1 (caar ressources)))))) (enlever-surplus (cdr ressources) surplus))))
  
(define (construction-chaine-gen usines-dispo indice-gold surplus)
  (construction-chaine usines-dispo (list (list indice-gold 1)) 1 surplus))

(define (construction-chaine usines-dispo chaine indice-dernier-ajout surplus)
  (if (> indice-dernier-ajout (length chaine))
      chaine
      (construction-chaine usines-dispo (append chaine
                       (map (lambda (x) (res-to-usine usines-dispo (mult 2 (list-ref (list-ref chaine (- indice-dernier-ajout 1)) 1) x) ))
         (enlever-surplus (liste-indices-éléments-negatifs-gen (list-ref (list-ref usines-dispo (- (car (list-ref chaine (- indice-dernier-ajout 1))) 1)) 2)) surplus )))    
                           (+ indice-dernier-ajout 1) surplus )  ))

;"(construction-chaine-gen liste-usines 1)"(construction-chaine-gen liste-usines 1 surplusvide)

(define (chain-cost chain liste-usines)
  (if (null? chain)
      0
      (+ (chain-cost (cdr chain) liste-usines) (* (cadar chain)(cadr (list-ref liste-usines (sub1 (caar chain))))))))
      
;"(chain-cost (construction-chaine-gen liste-usines 1) liste-usines)"(chain-cost (construction-chaine-gen liste-usines 1 surplusvide) liste-usines)

(define (surplus chain liste-usines)
  (if (= 1 (length chain))
     (map (lambda(x) (* (cadar chain) x)) (list-ref (list-ref liste-usines (sub1 (caar chain))) (sub1 3)))
     (map + (map (lambda(x) (* (cadar chain) x)) (list-ref (list-ref liste-usines (sub1 (caar chain))) (sub1 3))) (surplus (cdr chain) liste-usines))  ))

;"(surplus (construction-chaine-gen liste-usines 1) liste-usines)" (surplus (construction-chaine-gen liste-usines 1 surplusvide) liste-usines)
;(and (= 0 (apply + (cdr surplus)))
(define (liste-states indice-gold liste-usines surpluss end)
  (if  (= end 1)
      '()
      (let([chain (construction-chaine-gen liste-usines indice-gold surpluss)])
           (let ([surplus-aux (map + surpluss (surplus chain liste-usines))])
      (if (= 0 (apply + (cdr surplus-aux)))
          (cons chain (liste-states indice-gold liste-usines surplus-aux 1))
          (cons chain (liste-states indice-gold liste-usines surplus-aux 0))
    )))))

(define (liste-states-gen indice-gold liste-usines)
  (liste-states indice-gold liste-usines (l-init (length (list-ref (car liste-usines) 2))) 0))
;"(liste-states-gen 1 liste-usines)"(liste-states-gen 1 liste-usines)

(define (states  liste-usines)
  (map (lambda(x) (liste-states-gen x liste-usines)) (indices-gold-factories liste-usines)))

;"(states liste-usines)"(states liste-usines)
                                                      
;"test"(construction-chaine-gen liste-usines 1 '(2 0 1))
;(surplus (construction-chaine-gen liste-usines 1 '(1 1 0)) liste-usines)

(define (state-to-price states)
  (list (car (surplus (car states) liste-usines)) (map (lambda(x) (chain-cost x liste-usines)) states))) 

;"(state-to-price (car (states liste-usines)))"(state-to-price (car (states liste-usines)))  

(define (states-for-auto liste-usines)
  (map state-to-price (states liste-usines)))

"(states-for-auto liste-usines)"(states-for-auto liste-usines)

;----------------------------------------------------------------
;
;                      AUTOMATE
;
;----------------------------------------------------------------

(define teststates (states-for-auto liste-usines))
(define etat1 '(0 10 (2 3) 0))

(define (price actual-state network state-list)
  (list-ref (cadr (list-ref state-list (- network 1) )) (- (list-ref (caddr actual-state) (- network 1)) 1)))

;"(price etat1 2 teststates)"(price etat1 2 teststates)

;(define state-list '((9 (4 2)) (6 (5 1))))
;(define actual-state '(8 5 (2 1) 0))
;(price actual-state 2 state-list)

(define (up-chain-state actual-state bought state-list)
  (let ([cmax (length (cadr (list-ref state-list (sub1 bought))))])
  (if (= (list-ref (list-ref actual-state 2) (sub1 bought)) cmax)
      (list (list-ref actual-state 0) (list-ref actual-state 1)  (rajout (list-ref actual-state 2) (- 0 (- cmax 1)) bought )      (list-ref actual-state 3))
      (list (list-ref actual-state 0) (list-ref actual-state 1)  (rajout (list-ref actual-state 2) 1 bought )      (list-ref actual-state 3)))))

;"(up-chain-state etat1 1 teststates)"(up-chain-state etat1 1 teststates)

(define (next-state actual-state bought state-list nb-of-turns)
  (if (< (car actual-state) (price actual-state bought state-list))
      (if (= 0 (list-ref actual-state 1))
          (rajout actual-state nb-of-turns 4)
          (next-state (rajout (rajout actual-state (cadr actual-state) 1) 1 4) bought state-list nb-of-turns))
      (up-chain-state (rajout (rajout actual-state (- 0 (price actual-state bought state-list)) 1) (car (list-ref state-list (sub1 bought))) 2) bought state-list)
))

;"(next-state etat1 2 teststates 10)"(next-state etat1 2 teststates 10)
(define (wait-to-the-end state nb-of-turns)
  (+ (list-ref state 0) (* (list-ref state 1) (- nb-of-turns (list-ref state 3)) )))

;"(wait-to-the-end etat1 1)"(wait-to-the-end etat1 1)


(define (automate liste-states actual-state nb-of-turns)
  (if (<= nb-of-turns (list-ref actual-state 3))
      0
      (apply max (cons (wait-to-the-end actual-state nb-of-turns) (map (lambda(x) (automate liste-states (next-state actual-state x liste-states nb-of-turns) nb-of-turns)) (l-init123 1 (length liste-states)))))))



(define (autogen liste-usines goldinit nb-of-turns)
  (let([liste-states (states-for-auto liste-usines)])
  (automate liste-states (list goldinit 0  (l-init1 (length liste-states)) 0) nb-of-turns)))

(autogen liste-usines 20 3)