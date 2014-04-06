(defun mirror (l) (if (listp l) (if (null (cdr l)) (mirror (car l)) (list (mirror (cdr l)) (mirror (car l)))) l))
