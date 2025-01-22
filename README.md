# Projeto Final Teoria dos Grafos


## Arestas da camada inner core

- ic1.1 -> ag2, ag3, ag4, ag8, ic1.2, ic1.4, ic2.1
- ic1.2 -> ag1, ag9, ag12, ic1.1, ic1.3, ic2.2
- ic1.3 -> ag15, ag22, ag23, ag24, ic1.4, ic1.2, ic2.3
- ic1.4 -> ag20, ag26, ag27, ag28, ic1.1, ic1.3, ic2.4
- ic2.1 -> ag5, ag6, ag10, ic1.1, ic2.2, ic2.4
- ic2.2 -> ag11, ag13, ag16, ic1.2, ic2.1, ic2.3
- ic2.3 -> ag14, ag19, ag25, ic1.3, ic2.2, ic2.4
- ic2.4 -> ag7, ag20, ag21, ic1.4, ic2.1, ic2.3

## Arestas da camada de agregação

- ag1 -> ac1, ac4, ac13, ag2, ic1.2
- ag2 -> ac14, ac15, ag1, ic1.1
- ag3 -> ic1.1
- ag4 -> ac10, ac15, ag5, ic1.1
- ag5 -> ac12, ag4, ic2.1
- ag6 -> ac16, ag7, ic2.1
- ag7 -> ac3, ag6, ic2.4
- ag8 -> ac17, ag9, ic1.1
- ag9 -> ac18, ag8, ic1.2
- ag10 -> ac19, ag11, ic2.1
- ag11 -> ac20, ag10, ic2.2
- ag12 -> ac21, ag15, ic1.2
- ag13 -> ac23, ag14, ic2.2
- ag14 -> ac24, ag13, ic2.3
- ag15 -> ac22, ag12, ic1.3
- ag16 -> ag17, ic2.2
- ag17 -> ac25, ag16
- ag18 -> ag19, ic1.3
- ag19 -> ac43, ag18, ic2.3
- ag20 -> ac54, ag21, ic1.4
- ag21 -> ac57, ag20, ic2.4
- ag22 -> ac40, ag25, ic1.3
- ag23 -> ac26, ac33, ag26, ic1.3
- ag24 -> ac29, ag27, ic1.3
- ag25 -> ac44, ag22, ic2.3
- ag26 -> ac28, ag23, ic1.4
- ag27 -> ac32, ag24, ic1.4 
- ag28 -> ac49, ag29, ic1.4
- ag29 -> ac48, ac53, ag28, ic2.4

## Arestas da camada de acesso

- ac1 -> ac2, ag1
- ac2 -> ac1, ac3
- ac3 -> ac2, ag7
- ac4 -> ag1, ac5
- ac5 -> ac4, ac6
- ac6 -> ac5, ac16
- ac7 -> ac8, ac13
- ac8 -> ac7, ac9
- ac9 -> ac8, ac14
- ac10 -> ac11, ag4
- ac11 -> ac10, ac12
- ac12 -> ac11, ag5
- ac13 -> ac7, ag1
- ac14 -> ac9, ag2
- ac15 -> ag2, ag4
- ac16 -> ac6, ag4, ag6
- ac17 -> ac18, ag8
- ac18 -> ac17, ag9
- ac19 -> ac20, ag10
- ac20 -> ac19, ag11
- ac21 -> ac22, ag12
- ac22 -> ac21, ag15
- ac23 -> ac24, ag13
- ac24 -> ac23, ag14
- ac25 -> ag17
- ac26 -> ac27, ag23
- ac27 -> ac26, ac28
- ac28 -> ac27, ag26
- ac29 -> ac30, ag24
- ac30 -> ac29, ac31
- ac31 -> ac30, ac32
- ac32 -> ac31, ag27
- ac33 -> ac34, ag23
- ac34 -> ac33, ac35
- ac35 -> ac34, ac36
- ac36 -> ac35, ac37
- ac37 -> ac36, ac38
- ac38 -> ac37, ac39
- ac39 -> ac38, ag25
- ac40 -> ac41, ag22
- ac41 -. ac40, ac42
- ac42 -> ac41, ac43
- ac43 -> ac42, ag19
- ac44 -> ac45, ag25
- ac45 -> ac44, ac46
- ac46 -> ac45, ac47
- ac47 -> ac46, ac48
- ac48 -> ac47, ag29
- ac49 -> ac50, ag28
- ac50 -> ac49, ac51
- ac51 -> ac50, ac52
- ac52 -> ac51, ac53
- ac53 -> ac52, ag29
- ac54 -> ac55, ag20
- ac55 -> ac54, ac56
- ac56 -> ac55, ac57
- ac57 -> ac56, ag21
