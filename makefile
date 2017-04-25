all: mycat mycp myls mycd pwd


mycat.o: mycat.c
	gcc mycat.c -o mycat.o

mycp.o: mycp.c
	gcc mycp.c -o mycp.o

myls.o: myls.c
	gcc myls.c -o myls.o

mycd.o: mycd.c
	gcc mycd.c -o mycd.o

pwd.o: pwd.c
	gcc pwd.c -o pwd.o



mycat: mycat.o
	gcc mycat.o -o mycat

mycp: mycp.o
	gcc mycp.o -o mycp

myls: myls.o
	gcc myls.o -o myls

mycd: mycd.o
	gcc mycd.o -o mycd

pwd: pwd.o
	gcc pwd.o -o pwd
