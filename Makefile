CFLAGS = -Wall -Wextra -Wfloat-equal -pedantic -ansi -Werror
INCS = bst.h s_hash.h

all: testbst spl spl_hash testbst_d spl_d spl_hash_d

testbst:  bst.c testbst.c $(INCS)
	$(CC) bst.c testbst.c -o testbst -O3 $(CFLAGS)

spl : spl.c bst.c  $(INCS)
	$(CC) bst.c spl.c -o spl -O3 $(CFLAGS)

spl_hash : spl_hash.c s_hash.c  $(INCS)
	$(CC) s_hash.c spl_hash.c -o spl_hash -O3 $(CFLAGS)

testbst_d:  bst.c testbst.c $(INCS)
	$(CC) bst.c testbst.c -o testbst_d -g -O $(CFLAGS)

spl_d : spl.c bst.c  $(INCS)
	$(CC) bst.c spl.c -o spl_d -g -O $(CFLAGS)

spl_hash_d : spl_hash.c s_hash.c  $(INCS)
	$(CC) s_hash.c spl_hash.c -o spl_hash_d -g -O $(CFLAGS)

run: all
	./testbst
	time ./spl eng_370k_shuffle.txt heart_darkness.txt
	time ./spl_hash eng_370k_shuffle.txt heart_darkness.txt


memchk: testbst_d spl_d spl_hash_d
	valgrind --error-exitcode=1 --quiet --leak-check=full ./testbst_d
	valgrind --error-exitcode=1 --quiet --leak-check=full ./spl_d eng_370k_shuffle.txt heart_darkness.txt
	valgrind --error-exitcode=1 --quiet --leak-check=full --show-leak-kinds=all ./spl_hash eng_370k_shuffle.txt heart_darkness.txt

clean:
	rm -f testbst testbst_d spl spl_d
