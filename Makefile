INC_DIR="G:/DEV/gmp-6.2.1/gmp-6.2.1/include"
LIB_DIR="G:/DEV/gmp-6.2.1/gmp-6.2.1/lib"
LIBS=-lgmp -lgmpxx -lm
CFLAGS=-O2 -Wall -I$(INC_DIR)
LDFLAGS=-L$(LIB_DIR)
OBJS=bsgs-gmp.o
PROGS=bsgs-gmp

most: bsgs-gmp

all: $(PROGS)

bsgs-gmp: bsgs-gmp.o
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LIBS)
	rm -f $(OBJS)

clean:
	rm -f $(OBJS) $(PROGS)
