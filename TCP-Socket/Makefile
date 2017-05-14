CC		=	gcc 
RM		= rm -rf 

#LIBS = -lsocket -lnsl

PROGS = Pserver Sclient Aclient 

all: $(PROGS)

Pserver:  Pserver.o
	$(CC)  -o Pserver Pserver.c $(LIBS)
Sclient:  Sclient.o
	$(CC)  -o Sclient Sclient.c $(LIBS)
Aclient:  Aclient.o
	$(CC)  -o Aclient Aclient.c $(LIBS)
clean:;
	$(RM) $(PROGS) *.o core 
