; Verification Conditions — JavaSubset compiler
; z3 fichero.smt2

(push 1)
; [absValue] correctitud
(declare-fun x () Int)
(assert (not (=> true (and (=> (< (- 5) 0) (>= (- (- 5)) 0)) (=> (not (< (- 5) 0)) (>= (- 5) 0))))))
(check-sat)

(pop 1)

(push 1)
; [wrongMethod] correctitud
(declare-fun x () Int)
(assert (not (=> true (> 5 10))))
(check-sat)

(pop 1)

(push 1)
; [sumLoop] correctitud
(declare-fun i () Int)
(declare-fun s () Int)
(assert (not (=> true (and (>= 0 0) (>= 1 1)))))
(check-sat)

(pop 1)

(push 1)
; [sumLoop] invariant iniciacion
(declare-fun i () Int)
(declare-fun s () Int)
(assert (not (=> true (and (>= 0 0) (>= 1 1)))))
(check-sat)

(pop 1)

(push 1)
; [sumLoop] invariant preservacion
(declare-fun i () Int)
(declare-fun s () Int)
(assert (not (=> (and (and (>= s 0) (>= i 1)) (<= i 5)) (and (>= (+ s i) 0) (>= (+ i 1) 1)))))
(check-sat)

(pop 1)

(push 1)
; [sumLoop] invariant uso
(declare-fun i () Int)
(declare-fun s () Int)
(assert (not (=> (and (and (>= s 0) (>= i 1)) (not (<= i 5))) (>= s 0))))
(check-sat)

(pop 1)

(push 1)
; [sumLoop] terminacion (variante >= 0)
(declare-fun i () Int)
(declare-fun s () Int)
(assert (not (=> (and (and (>= s 0) (>= i 1)) (<= i 5)) (>= (- 6 i) 0))))
(check-sat)

(pop 1)

(exit)
