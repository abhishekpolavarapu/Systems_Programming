#include "def.h"
void exit (int);

#define SA struct sockaddr
#define MAXLINE 1024

#define MAXHOSTNAME 80
#define URGENT 1
#define NORMAL 0
void reusePort (int sock);
void PIPEhandle (int sig);
void CHLDhandle (int sig);
void QUIThandle (int sig);
void INThandle (int sig);
void USR1handle (int sig);
void USR2handle (int sig);

int PANsd, AUDsd, psd, sd;
struct sockaddr_in PANserver;
struct sockaddr_in AUDserver;
struct hostent *hp, *gethostbyname ();
struct servent *sp;
struct sockaddr_in from;
int fromlen;
int length;
char ThisHost[80];
int childpid;
char buf[512];
int MODE = URGENT;
char *byby="The Panel is Over\n";

int i;
int myindex;
char *clientName ;
char *clientIP ;
int clientPort ;

#define MAXPAN 10
#define MAXAUD 10

void shmInit();
void MemAttach();
void PANServ();
void AUDServ();
void PANHand();
void RefreshLists();
int PANpid, AUDpid, PANHandpid;
int PANgetfd ();
int AUDgetfd ();


int  PANsegment_id1,  PANsegment_id2,  PANsegment_id3;
int  AUDsegment_id1,  AUDsegment_id2,  AUDsegment_id3;
int  MSGsegment;
int  PIPEflagSegment;

int *PANconnfd;
struct sockaddr_in *PANList;

struct user_name {
    char    logname[10];
};

char *MSGbuffer;
int  *PIPEflag;

struct user_name *PANname;
struct user_name *AUDname;

int *AUDconnfd;
struct sockaddr_in *AUDList;
char username[MAXLINE];



main (argc, argv)
int argc;
char *argv[];
{

    if (argc != 2) {
        printf (" Usage: Pserver <port> \n");
        exit (0);
    }

    signal (SIGPIPE, PIPEhandle);
    signal (SIGCHLD, CHLDhandle);
    signal (SIGQUIT, QUIThandle);
    signal (SIGINT, INThandle);
    signal (SIGUSR1, USR1handle);
    shmInit();


    PANserver.sin_family = AF_INET;
    PANserver.sin_addr.s_addr = htonl (INADDR_ANY);
    PANserver.sin_port = htons (atoi (argv[1]));

    AUDserver.sin_family = AF_INET;
    AUDserver.sin_addr.s_addr = htonl (INADDR_ANY);
    AUDserver.sin_port = htons (atoi (argv[1]) +1);

    PANsd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    reusePort (PANsd);

    if (bind (PANsd, (SA *) & PANserver, sizeof (PANserver)) < 0)
    {
        close (PANsd);
        perror ("binding name to stream socket");
        exit (-1);
    }

    length = sizeof (PANserver);
    if (getsockname (PANsd, (SA *) & PANserver, &length))
    {
        perror ("getting socket name");
        exit (0);
    }

    listen (PANsd, 4);

    AUDsd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    reusePort (AUDsd);

    if (bind (AUDsd, (SA *) & AUDserver, sizeof (AUDserver)) < 0)
    {
        close (AUDsd);
        perror ("binding name to stream socket");
        exit (-1);
    }

    length = sizeof (AUDserver);
    if (getsockname (AUDsd, (SA *) & AUDserver, &length))
    {
        perror ("getting socket name");
        exit (0);
    }

    listen (AUDsd, 4);

    AUDpid = fork ();
	PANpid = fork ();
    if (AUDpid == 0)
    {
        //MemAttach();
        signal (SIGINT, SIG_IGN);
        signal (SIGQUIT, SIG_IGN);
        signal (SIGUSR2, USR2handle);
        AUDServ ();
    }
	if (PANpid == 0)
    {
        //MemAttach();
        signal (SIGINT, SIG_IGN);
        signal (SIGQUIT, SIG_IGN);
        signal (SIGUSR2, USR2handle);
        PANServ ();
    }

    printf ("Forked SPEAKERS Server, PANpid = %d\n", PANpid);
	printf ("Forked AUDIENCE Server, AUDpid = %d\n", AUDpid);

    printf ("Started SPEAKERS Server,  Port = (%d)\n", ntohs (PANserver.sin_port));
	printf ("Started AUDIENCE Server,  Port = (%d)\n", ntohs (AUDserver.sin_port));
    PANServ ();
}

void
INThandle (int sig)
{
    signal (SIGINT, INThandle);
    RefreshLists();
    usleep(100);
    RefreshLists();
    usleep(100);

    //printf("INThandle\n");
    printf("\n\n");

    printf("\nSTATUS:\n");
    printf("-------\n");
    printf("\nSPEAKER:\n");
    for (i = 0; i < MAXPAN; i++)
        if (PANconnfd[i] != -1) {
            printf("(%s:%d) [%s]\n",
                   inet_ntoa(PANList[i].sin_addr), ntohs(PANList[i].sin_port), PANname[i].logname);
        }

    printf("\nAUDIENCE:\n");
    for (i = 0; i < MAXPAN; i++)
        if (AUDconnfd[i] != -1) {
            printf("(%s:%d) [%s]\n",
                   inet_ntoa(AUDList[i].sin_addr), ntohs(AUDList[i].sin_port), AUDname[i].logname);
        }
    printf("--------------------------------------------------\n\n");

}

void
QUIThandle (int sig)
{
    signal (SIGQUIT, QUIThandle);
    //printf("QUIThandle\n");
    sprintf(MSGbuffer,"%s", byby);
    kill (AUDpid, SIGUSR2);
	kill (PANpid, SIGUSR2);
    kill (getpid(), SIGUSR1);
    sleep(2);
    system("pkill -9 Pserver");
    exit(0);
}

void shmInit()
{

    PANsegment_id1 = shmget (IPC_PRIVATE, MAXPAN * sizeof (int), S_IRUSR | S_IWUSR);
    PANsegment_id2 = shmget (IPC_PRIVATE, MAXPAN * sizeof (struct sockaddr_in), S_IRUSR | S_IWUSR);
    PANsegment_id3 = shmget (IPC_PRIVATE, MAXPAN * sizeof (struct user_name), S_IRUSR | S_IWUSR);

    AUDsegment_id1 = shmget (IPC_PRIVATE, MAXAUD * sizeof (int), S_IRUSR | S_IWUSR);
    AUDsegment_id2 = shmget (IPC_PRIVATE, MAXAUD * sizeof (struct sockaddr_in), S_IRUSR | S_IWUSR);
    AUDsegment_id3 = shmget (IPC_PRIVATE, MAXAUD * sizeof (struct user_name), S_IRUSR | S_IWUSR);

    MSGsegment = shmget (IPC_PRIVATE, MAXLINE*sizeof(char), S_IRUSR | S_IWUSR);
    PIPEflagSegment = shmget (IPC_PRIVATE, sizeof(int), S_IRUSR | S_IWUSR);

    PANconnfd = (int *) shmat (PANsegment_id1, NULL, 0);
    for (i = 0; i < MAXPAN; i++)
        PANconnfd[i] = -1;
    PANList = (struct sockaddr_in *) shmat (PANsegment_id2, NULL, 0);
    PANname = (struct user_name *) shmat (PANsegment_id3, NULL, 0);

    AUDconnfd = (int *) shmat (AUDsegment_id1, NULL, 0);
    for (i = 0; i < MAXAUD; i++)
        AUDconnfd[i] = -1;
    AUDList = (struct sockaddr_in *) shmat (AUDsegment_id2, NULL, 0);
    AUDname = (struct user_name *) shmat (AUDsegment_id3, NULL, 0);
    MSGbuffer = (char *) shmat (MSGsegment, NULL, 0);
    PIPEflag = (int *) shmat (PIPEflagSegment, NULL, 0);

}

void MemAttach() {
    PANconnfd = (int *) shmat (PANsegment_id1, NULL, 0);
    PANList = (struct sockaddr_in *) shmat (PANsegment_id2, NULL, 0);
    PANname = (struct user_name *) shmat (PANsegment_id3, NULL, 0);

    AUDconnfd = (int *) shmat (AUDsegment_id1, NULL, 0);
    AUDList = (struct sockaddr_in *) shmat (AUDsegment_id2, NULL, 0);
    AUDname = (struct user_name *) shmat (AUDsegment_id3, NULL, 0);
}

void PANServ() {

    int index;
    int psd;
    int rc;

    for(;;) {
        index = PANgetfd();

        fromlen = sizeof(from);
        if (  (PANconnfd[index]   = accept(PANsd, (SA *)&from, &fromlen)) == -1) {
            if (errno == EINTR) continue;
        }

        if( (rc=recv(PANconnfd[index] , username, sizeof(username), 0)) < 0)
            perror("receiving username  message");

        fromlen = sizeof (PANList[index]);
        getpeername(PANconnfd[index] ,(SA *)&PANList[index],&fromlen);
        sprintf(PANname[index].logname,"%s", username);

        printf("\nNew SPEAKER  Client: (%s:%d) [%s]\n",
               inet_ntoa(PANList[index].sin_addr), ntohs(PANList[index].sin_port), PANname[index].logname);

        PANHandpid = fork ();
        if (PANHandpid == 0) {
//            MemAttach();
            signal (SIGINT, SIG_IGN);
            signal (SIGQUIT, SIG_IGN);
            PANHand (index);
        }
        printf ("Forked SPEAKER Handler, PID =  %d \n", PANHandpid);

    }
}

void AUDServ() {
    int index;
    int psd;
    int rc;

    for(;;) {
        fromlen = sizeof(from);
        if (  (psd  = accept(AUDsd, (SA *)&from, &fromlen)) == -1) {
            if (errno == EINTR) continue;
        }
        if( (rc=recv(psd, username, sizeof(username), 0)) < 0)
            perror("receiving username  message");
        printf("\nNew AUDIENCE  Client: (%s:%d) [%s]\n",
               inet_ntoa(from.sin_addr), ntohs(from.sin_port), username);
        index = AUDgetfd();
        AUDconnfd[index] = psd;
        fromlen = sizeof (AUDList[index]);
        getpeername(psd,(SA *)&AUDList[index],&fromlen);
        sprintf(AUDname[index].logname,"%s", username);
    }
}

int PANgetfd ()
{
    int i;

    for (i = 0; i < MAXPAN; i++) {
        if (PANconnfd[i] == -1) return (i);
    }
    if (i == MAXPAN) {
        printf ("MaxPAN out fds\n");
        exit (-1);
    }
}

int AUDgetfd ()
{
    int i;

    for (i = 0; i < MAXAUD; i++) {
        if (AUDconnfd[i] == -1) return (i);
    }
    if (i == MAXAUD) {
        printf ("MaxAUD out fds\n");
        exit (-1);
    }
}

void PANHand(int index) {

    int rc;
    char buf[512];
    int i;


    for (;;) {
        if ((rc = recv (PANconnfd[index], buf, sizeof (buf), 0)) < 0)
        {
            PANconnfd[i] = -1;;
            //perror ("receiving stream  message");
            exit (-1);
        }
        if (rc > 0)
        {
            buf[rc] = '\0';
            sprintf(MSGbuffer,"%s", buf);
            kill (getppid(), SIGUSR1);
            kill (AUDpid, SIGUSR2);
			kill (PANpid, SIGUSR2);
        }

    }
}

void RefreshLists() {
//printf("Refreshing\n");
    sprintf(MSGbuffer,"%s", " \b");
    kill (getpid(), SIGUSR1);
    kill (AUDpid, SIGUSR2);
	kill (PANpid, SIGUSR2);
}

void USR1handle(int sig)
{
    signal (SIGUSR1, USR1handle);
//printf("USR1 handling\n");

    *PIPEflag = 0;
    for (i = 0; i < MAXPAN; i++) {
        if (PANconnfd[i] != -1) {
            if (send (PANconnfd[i], MSGbuffer, strlen(MSGbuffer), 0) < 0) {
                if (*PIPEflag == 1) printf("SPEAKER: %d disconnected\n", i);
                PANconnfd[i] = -1;
                // perror ("sending");
                // printf ("  PAN Client %d  Disconnected..", i);
            }
        }
    }

}
void USR2handle(int sig)
{
    signal (SIGUSR2, USR2handle);
//printf("USR2 handling\n");

    *PIPEflag = 0;
    for (i = 0; i < MAXAUD; i++) {
        if (AUDconnfd[i] != -1) {
            if (send (AUDconnfd[i], MSGbuffer, strlen(MSGbuffer), 0) < 0) {
                if (*PIPEflag == 1) printf("Audience: %d disconnected\n", i);
                AUDconnfd[i] = -1;
                //perror ("sending");
                //printf ("  AUD Client %d  Disconnected..", i);
            }
        }
    }
}

void
reusePort (int s)
{
    int one = 1;

    if (setsockopt (s, SOL_SOCKET, SO_REUSEADDR, (char *) &one, sizeof (one)) ==
            -1)
    {
        printf ("error in setsockopt,SO_REUSEPORT \n");
        exit (-1);
    }
}

void
PIPEhandle (int sig)
{
    signal (SIGPIPE, PIPEhandle);
    *PIPEflag = 1;
}
void
CHLDhandle (int sig)
{
    int cpid;
    signal (SIGCHLD, CHLDhandle);
    cpid=wait(NULL);
    //printf("PAN PID =  %d Terminated\n", cpid);
}

