' This script is an example of MY-BASIC
' Copyright (c) 2011 - 2012 Tony's Toy. All rights reserved.
' For more information, see http://code.google.com/p/my-basic/
' mailto:hellotony521@gmail.com

PRINT "Input: "
INPUT ns$
n = VAL(ns$)

x = n * 2 - 1
a = 1 - 1 / 3
w = (x - 5) / 2 + 1
v = 100 / w

FOR y = 5 TO x STEP 2
	iy = (y - 1) / 4
	iy = FLOOR(iy)
	IF iy = (y - 1) / 4 THEN a = a + 1 / y ELSE a = a - 1 / y
	u = u + v
NEXT
a = a * 4

PRINT "PI = ", a