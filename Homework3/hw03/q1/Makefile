CC:=gcc
CFLAGS:=-Wall -g -std=c99

targets = rpn-calc
all:$(targets)

rpn-calc: rpn_calc.o stack.o array.o stack.h array.h Makefile
	$(CC) $(CFLAGS) $(filter %.o,$^) -o $@

clean:
	@rm *.o *~ $(targets) -f
