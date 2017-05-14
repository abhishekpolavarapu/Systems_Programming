
Pserver  -   Panel server 

Sclient   -   Speaker client

Aclient   -   Audience client

Sclient:
 
·         Connects to the  Pserver   at  (<host>  <port>)

·         Sends its user login.

·         If accepted by the Pserver:

          Receives  data from the Pserver and displays it to stdout.

          Reads data from stdin and sends  it to  the Pserver.

          Exits when the user types CTRL-D.
 
Aclient:
 
·         Connects to   to  the Pserver   at  (<host>  <port>+1)

·         Sends its user login.

·         If accepted by the Pserver:

          Receives data  from   the Pserver and displays it to stdout.
 
          Upon Permission from the Pserver,  reads data from stdin and sends it to the Pserver.
 
          Exits when the user types CTRL-C.
 
 Pserver:
 
·        Creates two server sockets at <port>  &  <port>+1

·        When an Sclient connects to <port>:

          If approved by the Pserver  manager:
     
          Accepts it and saves its information ( host, port & login ) in speakers list.

          Forks a new process to:

              Reads data from its client.
              Sends the received data to it all clients, speakers & audience.
·       When an Aclient connects to <port>+1 :

          If approved by the Pserver manager:
          
          Accepts it and saves its information in an audience list.
          
          CTRL-Z (TSTP)  Permits  the Aclients (current and future)  to send messages exactly  like the Sclients.
          
     CTRL-C     (INT)    Displays  the  contents of both the current  speakers & audience lists.
     
     CTRL-\    (QUIT)     Exits after sending “The Panel is Over” to all Sclients and Aclients.


To run server:

type ./Pserver 10369

To run clients:

type: ./Sclient localhost 10369

type: ./Aclient localhost 10369 
