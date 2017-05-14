JVC =  javac
JVCFLAGS =
.SUFFIXES : .class .java
.java.class :
	$(JVC) $(JVCFLAGS) $<

PRG=Pserver.class Pclient.class 
all:    $(PRG)
	@chmod 755 ${PRG}

Pserver: \
	 Pserver.class
Pserver.class: Pserver.java

Pclient: \
         Pclient.class
Pclient.class: Pclient.java
clean:
	rm *.class 

