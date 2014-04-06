(defun mirror (l) (if (listp l) (if (eq (length (cdr l)) 0) (mirror (car l)) (list (mirror (cdr l)) (mirror (car l)))) l))
