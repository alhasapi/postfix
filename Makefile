   
all: 
	gcc -o evaluator ./postfix_evaluator.c

clean:
	rm evaluator
