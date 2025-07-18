; valid4.as - מאקרו נפרש פעמיים עם פקודות רגילות

mcro m1
inc r1
dec r2
mcroend

MAIN:   mov #5, r1
        m1
        add r1, r2
        m1
        stop

