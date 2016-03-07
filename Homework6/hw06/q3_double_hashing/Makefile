CC:=gcc
CFLAGS:=-Wall -g -std=c99

targets = hash-table-lp
all: $(targets)

hash-table-lp: hash_table_lp.o student.h Makefile
	$(CC) $(CFLAGS) $(filter %.o,$^) -o $@

clean:
	@rm *.o *~ $(targets) -f
