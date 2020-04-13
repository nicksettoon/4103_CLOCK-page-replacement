#Name: Nicklaus Settoon
#Project: PA-2 (Page Replacement Algorithm)
#File: makefile
#Instructor: Feng Chen
#Class: cs4103-sp20
#LogonID: cs410361

clock: main.o
	gcc -g main.o -o clock

main.o: main.c
	gcc -c main.c

clean: 
	rm *.o clock

submit:
	make clean
	rm .*
	rm *.pdf
	rm *.code-workspace