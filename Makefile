.PHONY: all clean

all:
	g++ console.cpp -c -o console.o
	g++ tty_control.cpp -c -o tty_control.o
	g++ main.cpp -c -o main.o
	g++ *.o -o console-sample

clean:
	$(RM) main *.o

