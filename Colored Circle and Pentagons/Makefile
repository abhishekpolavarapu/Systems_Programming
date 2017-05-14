CC = gcc 
DEBUG = -O

CFLAGS = $(DEBUG) 

LIBS =  -lXm -lXt -lX11  -lm

TARGETS= ccp xdraw 

all: $(TARGETS)

ccp: ccp.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
xdraw: xdraw.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
 

clean:
	rm -f *.o *~* *.a  *pyo
	rm -f $(TARGETS)
