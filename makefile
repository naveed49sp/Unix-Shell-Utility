#this is a comment
myexe : functions_v1.o functions_v2.o functions_v3.o myshell.o
	gcc  functions_v1.o functions_v2.o functions_v3.o myshell.o -o myexe
functions_v1.o: functions_v1.c myshell.h
	gcc -c -I. functions_v1.c 
functions_v2.o: functions_v2.c myshell.h
	gcc -c -I. functions_v2.c 
functions_v3.o: functions_v3.c myshell.h
	gcc -c -I. functions_v3.c
myshell.o: myshell.c myshell.h
	gcc -c -I.  myshell.c 
clean:
	rm -f *.o tempin.txt tempout.txt outfile.txt
install: myexe
	@cp myexe /usr/bin
	@chmod a+x /usr/bin/myexe
	@chmod og-w /usr/bin/myexe
	@echo "myexe installed successfully in /usr/bin"
uninstall:
	@rm -f /usr/bin/myexe
	@echo "myexe successfully un-installed from /usr/bin"