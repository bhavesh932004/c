all: mywhich test

mywhich: mywhich.c c_strtok.c
	cc -o mywhich c_strtok.c mywhich.c

test: test.c c_strtok.c
	cc -o test c_strtok.c test.c

clean:
	rm mywhich test
