;Copyright (c) 2014 Godly T.Alias

;returns the quantity in first jug
(defun get-first-jug (state) (car state))

;returns the quantity in second jug
(defun get-second-jug (state) (cadr state))

;returns the state of two jugs
(defun get-state (f s) (list f s))

;checks whether a given state is a goal
; GOAL IS TO GET 4 IN SECOND JUG
(defun is-goal (state)
    (eq (get-second-jug state) 4))

;returns all possible states that can be derived
;from a given state
(defun child-states (state)
    (remove-null
	(list
	    (fill-first-jug state)
	    (fill-second-jug state)
	    (pour-first-second state)
	    (pour-second-first state)
	    (empty-first-jug state)
	    (empty-second-jug state))))

;remove the null states
(defun remove-null (x)
    (cond
	((null x) nil)
	((null (car x)) (remove-null (cdr x)))
	((cons (car x) (remove-null (cdr x))))))

;return the state when the first jug is filled (first jug can hold 3)
(defun fill-first-jug (state)
    (cond
	((< (get-first-jug state) 3) (get-state 3 (get-second-jug state))))))

;returns the state when the second jug is filled (second jug can hold 5)
(defun fill-second-jug (state)
    (cond
	((< (get-second-jug state) 5) (get-state (get-first-jug state) 5))))

;returns the state when quantity in first
;is poured to second jug
(defun pour-first-second (state)
    (let (   (f (get-first-jug state))
	     (s (get-second-jug state)))
	(cond
	    ((zerop f) nil)		; first jug is empty
	    ((= s 5) nil)		; Second jug is full
	    ((<= (+ f s) 5)	
		(get-state 0 (+ f s)))
	    (t				; pour to first from second
		(get-state (- (+ f s) 5) 5)))))

;returns the state when second jug is poured to first
(defun pour-second-first (state)
    (let (   (f (get-first-jug state))
	     (s (get-second-jug state)))
	(cond
	    ((zerop s) nil)		; second jug is empty
	    ((= f 3) nil)		; second jug is full	    
	    ((<= (+ f s) 3)	
		(get-state (+ f s) 0))	    
	    (t				;pour to second from first
		(get-state 3 (- (+ f s) 3))))))

;returns the state when first jug is emptied
(defun empty-first-jug (state)
    (cond
	((> (get-first-jug state) 0) (get-state 0 (get-second-jug state)))))

;returns the state when second jug is emptied
(defun empty-second-jug (state)
    (cond
	((> (get-second-jug state) 0) (get-state (get-first-jug state) 0))))
	
	
	;;;MAIN FUNCTION
(defun dfs (start-state depth lmt)
    (setf *node* 0)
    (setf *limit* lmt)
    (dfs-node start-state depth)
)


;dfs-node expands a node and calls dfs-children to recurse on it
(defun dfs-node (state depth)
    (setf *node* (+ 1 *node*))
    (cond
	((is-goal state) (list state))
	((zerop depth) nil)
	((> *node* *limit*) nil)
	((let ((goal-child (dfs-children (child-states state) (- depth 1))))
		 (and goal-child (cons state goal-child)))) ;for back-tracking if the branch don't have a goal state
	))

;dfs-children expands each node recursively and give it
;to dfs-node to process
(defun dfs-children (states depth)
    (cond
	((null states) nil)
	((dfs-node (car states) depth))
	((dfs-children (cdr states) depth))))
	
(print "ENTER YOUR INPUT AS")
(print "(dfs start_state depth limit)")
