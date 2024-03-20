CC=     gcc
LD=     ld
CFLAGS= -g -W -Wall -Werror -std=c99 -O0 -fopenmp
TARGET= multi_mutex
SRC=    multi_mutex.c testlib.c main.c
OBJ=    $(SRC:.c=.o)

multi_mutex: $(OBJ)
	$(CC) -pthread -fopenmp -o $@ $(OBJ)

.PHONY: $(TARGET)-solution.o
$(TARGET)-sol: $(subst $(TARGET),$(TARGET)-solution,$(OBJ))
	$(CC) -pthread -fopenmp -o $@ $^

$(TARGET)-solution.o:
	@test -f $(TARGET)-solution.c \
	|| { echo "Please download solution." >&2; false; }
	$(CC) $(CFLAGS) -c $(TARGET)-solution.c

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(TARGET) $(TARGET)-sol *.o

showsrc:
	@echo multi_mutex.c

zip:
	cd ..; ./makezip.py
