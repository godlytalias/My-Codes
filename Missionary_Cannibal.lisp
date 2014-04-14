;Copyright (c) 2014 Godly T.Alias

;state - ((msnry cnbl) (msnry cnbl))

(defun no_misnry_left (state) (caar state)) ;no: of missionaries in left bank

(defun no_misnry_right (state) (caadr state))  ;no: of missionaries in right bank

(defun no_cnbl_left (state) (cadar state))  ;no: of cannibals in left bank

(defun no_cnbl_right (state) (cadadr state))  ;no: of cannibals in right bank

(defun not-possible (state) (cond
							((null state) t)
							((or (< (no_misnry_left state) 0) (> (no_misnry_left state) 3)) t)   
							((or (< (no_cnbl_left state) 0) (> (no_cnbl_left state) 3)) t) 
							((or (< (no_misnry_right state) 0) (> (no_misnry_right state) 3)) t)   
							((or (< (no_cnbl_right state) 0) (> (no_cnbl_right state) 3)) t) 
							((and (eq (+ (no_misnry_left state) (no_misnry_right state)) 3) (eq (+ (no_cnbl_left state) (no_cnbl_right state)) 3)) nil)
							))
							
(defun danger (state) (cond
						((and (> (no_misnry_left state) (no_cnbl_left state)) (> (no_cnbl_left state) 0)) t) 
						((and (> (no_misnry_right state) (no_cnbl_right state)) (> (no_cnbl_right state) 0)) t)
						(t nil)))
							
;removes the impossible states from the list of states
(defun possible (state) (cond
							((null state) NIL )
							((not-possible (car state)) (possible (cdr state)))
							((danger (car state)) (possible (cdr state)))
							(t (cons (car state) (possible (cdr state))))))
							
(defun goalp (state) (cond
						((not-possible state) nil)
						((and (and (= (no_misnry_left state) 3) (= (no_cnbl_left state) 3)) (and (= (no_misnry_right state) 0) (= (no_cnbl_right state) 0))) T)))
						
(defun msnry-msnry-left (state) (list (list (+ 2 (no_misnry_left state)) (no_cnbl_left state)) (list (- (no_misnry_right state) 2) (no_cnbl_right state))))

(defun msnry-msnry-right (state) (list (list (- (no_misnry_left state) 2) (no_cnbl_left state)) (list (+ 2 (no_misnry_right state)) (no_cnbl_right state))))

(defun msnry-cnbl-left (state) (list (list (+ 1 (no_misnry_left state)) (+ 1 (no_cnbl_left state))) (list (- (no_misnry_right state) 1) (- (no_cnbl_right state) 1))))

(defun msnry-cnbl-right (state) (list (list (- (no_misnry_left state) 1) (- (no_cnbl_left state) 1)) (list (+ 1 (no_misnry_right state)) (+ 1 (no_cnbl_right state)))))

(defun cnbl-cnbl-left (state) (list (list (no_misnry_left state) (+ 2 (no_cnbl_left state))) (list (no_misnry_right state) (- (no_cnbl_right state) 2))))

(defun cnbl-cnbl-right (state) (list (list (no_misnry_left state) (- (no_cnbl_left state) 2)) (list (no_misnry_right state) (+ 2 (no_cnbl_right state)))))

(defun msnry-left (state) (list (list (+ 1 (no_misnry_left state)) (no_cnbl_left state)) (list (- (no_misnry_right state) 1) (no_cnbl_right state))))

(defun msnry-right (state) (list (list (- (no_misnry_left state) 1) (no_cnbl_left state)) (list (+ (no_misnry_right state) 1) (no_cnbl_right state))))

(defun cnbl-left (state) (list (list (no_misnry_left state) (+ 1 (no_cnbl_left state))) (list (no_misnry_right state) (- (no_cnbl_right state) 1))))

(defun cnbl-right (state) (list (list (no_misnry_left state) (- (no_cnbl_left state) 1)) (list (no_misnry_right state) (+ 1 (no_cnbl_right state)))))

(defun child (state depth) (if (eq 0 (mod depth 2)) (possible (list (msnry-msnry-left state) (msnry-cnbl-left state)
													(cnbl-cnbl-left state) (msnry-left state)(cnbl-left state) ))
													(possible (list (msnry-msnry-right state) (msnry-cnbl-right state)
													(cnbl-cnbl-right state)  (msnry-right state) (cnbl-right state)))))
							
(defun solution (state depth) (setf *dep* depth) 
								(cond
								((not-possible state) nil)
								(t (dfs state 0))))
								
(defun dfs (state depth) (cond
							((null state) nil)
							((goalp state) state)
							((let ((goal-child (dfs-children (child state depth) (+ depth 1))))
								(and goal-child (cons state goal-child))))))
								
(defun dfs-children (state depth) (cond
									((null state) nil)
							        ((> depth *dep*) nil)
									((dfs (car state) depth))
									((dfs-children (cdr state) depth))))
