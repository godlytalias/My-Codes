;Copyright (c) 2014 Godly T.Alias

;returns all the cell states in column n
(defun col (n i) (cond 
			((> n 7) nil)
			((= i 7) (list (list n i)))
			(t (cons (list n i) (col n (+ i 1))))))
				
;y axis component				
(defun row-cordinate (state) (cond
				((null state) nil)
				(t (cadr state))))

;x axis component							
(defun col-cordinate (state) (cond
				((null state) nil)
				(t (car state))))

;returns the cells in column next to state cell
(defun next-col (state) (cond
				((null state) (col 0 0))
				(t (col (+ 1 (col-cordinate (car state))) 0))))

;check whether the state1 and state2 cells are conflicting
(defun possible (state1 state2) (cond
				((or (null state1) (null state2)) nil)
				((eq (row-cordinate state1) (row-cordinate state2)) nil)
				((eq (col-cordinate state1) (col-cordinate state2)) nil)
				((eq (abs (- (row-cordinate state1) (col-cordinate state1))) (abs (- (row-cordinate state2) (col-cordinate state2)))) nil)
				(t T)))

;check the possibility of the cell with co-ordinates new-co with all the cell in list state								
(defun check (state new-co) (cond
				((null state) T)
				((and (possible (car state) new-co) (check (cdr state) new-co)))))

;gets the next possible columns						
(defun get-possible-next (state next-col-states) (cond
				((null next-col-states) nil)
				((check state (car next-col-states)) (cons (car next-col-states) (get-possible-next state (cdr next-col-states))))
				(t (get-possible-next state (cdr next-col-states)))))

;gets the next possible columns								
(defun possible-next-col (state) (cond
				((null state) (next-col state))
				(t (get-possible-next state (next-col state)))))

;make dfs in given node									
(defun dfs-node (solution state depth) (cond
				((eq depth 7) (list state))
				((let ((goal-route (dfs solution (possible-next-col solution) (+ depth 1))))
					(and goal-route (cons state goal-route))))))

;recurses on each node of the branch								
(defun dfs (solution state depth) (cond
				((null state) nil)
				((dfs-node (cons (car state) solution) (car state) depth))
				((dfs solution (cdr state) depth))))
						
;gives the solution MAIN FUNCTION						
(defun get-solution () (dfs '() (possible-next-col '()) 0))
