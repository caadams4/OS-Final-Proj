INCLUDE := -I ~/include
# Define Make rules as follows:
# A default rule to compile a .c file into a .o file
all: main
main: main.o hold_queues.o internal_events.o read_input.o system_status.o banker_algorithm.o cpu.o
	cc -o main main.o hold_queues.o internal_events.o read_input.o system_status.o banker_algorithm.o cpu.o
# A rule for "all" to build the entire project into a program
%.o: %.c prototypes.h
	cc -c $< -I ~/include

# A rule for "clean" to remove all .o files
clean: 
	rm -f *.o main

run:
	./main
