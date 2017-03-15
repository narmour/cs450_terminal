# Makefile for pipe test

all: pipes.x pipe_demo.x

# $@ is make shorthand for the thing on the left side of the colon
#   (pipes.x in this case)
# $^ stands for everything on the right side of the colon (the .o files)
pipes.x: main.o parsetools.o parse_cmd.o exec_cmd.o
	gcc -ggdb -o  $@ $^

pipe_demo.x: pipe_demo.o
	gcc -o $@ $^

# $< is the first item after the colon (main.c here)
main.o: main.c parsetools.h constants.h parse_cmd.h
	gcc -ggdb -c -o $@ $<

parsetools.o: parsetools.c constants.h
	gcc -c -o $@ $<

pipe_demo.o: pipe_demo.c
	gcc -c -o $@ $<

parse_cmd.o: parse_cmd.c
	gcc -ggdb -c -o $@ $<

exec_cmd.o: exec_cmd.c
	gcc -ggdb -c -o $@ $<

clean:
	rm -f *.x *.o *~

