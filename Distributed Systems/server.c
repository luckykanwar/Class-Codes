/ * Time server (concurrent mode).
 * Synchronization of clocks, following the centralized algorithm of Cristian. * /

#include <string.h>

// Files needed to handle sockets, addresses, etc.

#include <sys / socket.h>
#include <sys / types.h>
#include <time.h>
#include <netinet / in.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>

#include <stdlib.h>
#include <stdio.h>

#define TAMBUF 100

// Commands and responses defined in the protocol.

Char * commands [] =
{
"OPEN", // Login request.
"SYNC", // Start synchronization process.
"TERM" // Logout.
};

Int compares_commands (char * s1, char * s2);
// Compare two strings of exactly 4 characters, identifying the command.
Int parser_command (char * command);
// Identify the command in question.
Void clean_buffer (char * buffer, int start, int fin);
Void fetch (int s, struct sockaddr_in * info);

/ ************************************************* ************************************************** /

Int main ()
{
Int sock_list, sock_dialog; // connection and dialog sockets.
Struct sockaddr_in dir_serv, dir_cli;
Char buf [TAMBUF]; // buffer for read / write on socket.
Int port, length;

Length = sizeof (struct sockaddr);

System ( "clear");

Write (1, "ServerCristian> connect", 25);

Printf ( "\ n \ nPort (as of% d):", IPPORT_RESERVED + 1);

Scanf ( "% d", & port);

While (! (Port> IPPORT_RESERVED))
{
Printf ( "\ n \ nThe port% d is reserved, try again.", Port);
Printf ( "\ n \ nPort (as of% d):", IPPORT_RESERVED + 1);
Scanf ( "% d", & port);
}

// Create the listening socket ...

If ((sock_list = socket (PF_INET, SOCK_STREAM, 0)) <0)
{
Perror ( "\ nSingle socket");
Exit (1);
}

Dir_serv.sin_family = AF_INET;
Dir_serv.sin_port = htons (port);
Dir_serv.sin_addr.s_addr = htonl (INADDR_ANY); // Anyone can connect.

If (bind (struct sockadd *) & dir_serv, sizeof (dir_serv)) <0)
{
Perror ( "\ nBind");
Exit (1);
}

// We put the socket to the listening ...

If (listen (sock_count, 7) <0)
{
Perror ( "\ nListen");
Exit (1);
}

Signal (SIGCHLD, SIG_IGN); // avoid child zombies.

Printf ( "\ n \ nAPPLICATION: Synchronizing clocks following the centralized algorithm \ n");
Printf (from Cristian. \ N \ n ");
Printf ( "Time server, waiting for requests ... \ n");

do
{
// Block waiting for connection request.

Sock_dialog = accept (sock_list, (struct sockaddr *) & dir_cli, (int *) & length);

If (sock_dialog == - 1)
{
// Special treatment for interruptions of dead children.

If (errno == EINTR) continue;
Perror ( "\ nAccept");
Exit (1);
}

else
Switch (fork ())
{
Case -1:

Perror ( "\ nCrearing a child");
break;

Case 0:

Close (sock_counter);
Bring (sock_dialog, & dir_cli);
Close (sock_dialog);
Exit (0);

default:

Close (sock_dialog);
break;
}
} While (1);

Exit (0);
}

/ ************************************************* ************************************************** /

Int compares_commands (char * s1, char * s2)
// Compare two strings of exactly 4 characters, identifying the command.

{
Int i;
Int result = 1;

For (i = 0; i <4; i ++)
If (s1 [i]! = S2 [i])
Result = 0;

Return (result);
}

Int parser_command (char * command)
// Identify the command in question.

{
If ((compares commands (command, commands [0])) == 1) return (0); // OPEN
If ((compares commands (command, commands [1])) == 1) return (1); // SYNC
If ((compares commands (command, commands [2])) == 1) return (2); // TERM

Return (-1);
}

Void clear_buffer (char * buffer, int start, int end)
{
Int i;

For (i = start; i <= fin; i ++) buffer [i] = '';
}

Void fetch (int s, struct sockaddr_in * info)
{
Char * answer [] =
{
"OKEY", // You can carry a parameter indicating the time (t (mt)) of the time server, or carry nothing.
"FINN" // May be accompanied by a string explaining why the refusal has occurred.
};

// auxiliary variables.

Int k, lon, lon2;
Char buf [TAMBUF];

Struct timeval time server;
Struct tm * tmp;

// Wait for the OPEN command to be sent.

K = read (s, buf, TAMBUF);

If (k <0)
{
Perror ( "\ nReception OPEN command");
return;
}

Buf [k] = '\ 0';

If ((compares_commands (commands [0], buf)) == 0)
{
Perror ( "\ unknown command");
Sprintf (buf, "% s: OPEN command expected", response [1]);
Write (s, buf, strlen (buf));
}

// All right. We return OKEY and wait for them to send us a command, which from this moment
// can be: SYNC or TERM

Sprintf (buf, "% s: Open session", response [0]);
Write (s, buf, strlen (buf));
Printf ( "\ nIP =% ld Connected \ n", ntohl (info-> sin_addr.s_addr));

// We enter the command receive loop.

do
{
K = read (s, buf, TAMBUF);

If (k <0)
{
Perror ( "\ nReceiving a command");
return;
}

Buf [k] = '\ 0';

Switch (comma_command (buf))
{
Case 1: // SYNC

/ * Calculate server time * /

Gettimeofday (& server, NULL);

// the server sends you as reply:
// OK +
// seconds (value starts in & buf [10]) +
// microseconds (value starts in & buf [35])

Sprintf (buf, "% s: sec:% ld \ 0", response [0], hourserver.tv_sec);
Lon = strlen (buf);
Clean_buffer (buf, lon + 1.29);
Sprintf (& buf [30], "useg:% ld \ 0", hourserver.tv_usec);
Lon2 = strlen (& buf [30]);
Write (s, buf, 30 + lon2);

Tmp = (struct tm *) localtime (& (hourservidor.tv_sec));
Printf ( "\ nIP =% ld Synchronizing ... \ n", ntohl (info-> sin_addr.s_addr));
Printf ( "t (mt):% d hrs.% D mns.% D sgs.% Ld usgs. \ N", tmp-> tm_hour, tmp-> tm_min, tmp-> tm_sec, hoursserver.tv_usec);
break;

Case 2: // TERM

Sprintf (buf, "% s: Closing session ...", response [0]);
Write (s, buf, strlen (buf));
Close (s);
Printf ( "\ nIP =% ld Disconnected \ n", ntohl (info-> sin_addr.s_addr));
return;

Case 0: // OPEN

Sprintf (buf, "% s: Client protocol error", response [1]);
Write (s, buf, strlen (buf));
Close (s);
return;

default:

Sprintf (buf, "% s: Unknown command", response [1]);
Write (s, buf, strlen (buf));
Close (s);
return;
}
} While (1);
}

