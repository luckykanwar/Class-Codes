// Client for clock synchronization using the Cristian algorithm, using the sockets interface directly.

#include <sys / socket.h>
#include <sys / types.h>
#include <netinet / in.h>
#include <errno.h>
#include <netdb.h> // to use gethostbyname
#include <stdio.h>
#include <sys / timeb.h>
#include <time.h>

#define TAMBUF 100

Char nom_serv [80]; // name of the server machine
Char * commands [] = { "OPEN", "SYNC", "TERM"}; // commands to communicate with the server
Char * answers [] = { "OKEY", "FINN"}; // server responses

Struct timeval Dmin;

Int comp_rests (char * s1, char * s2);
// Compare two strings of exactly 4 characters
Int parser_responses (char * response);
// Identify the command in question
Int compute_deviation_absolute (long * sgs, long * usgs);
// Returns 1 if the local clock is ahead.
// -1 if the local clock was delayed.
// 0 if the local clock is set.
Int minorDmin (struct timeval * newD);
// Returns 1 if the time D passed as an argument is less than the one at least so far.
// 0 e. or. C.
Void synchronize (int s);
Void end (int s);

Int main ()
{
Int sock, k, port, i;
  Struct sockaddr_in server;
  Struct hostent * hp, * gethostbyname ();

  Char buf [TAMBUF];
Char option [50];

System ( "clear");

Printf ( "APPLICATION: Synchronizing clocks following the centralized algorithm \ n");
Printf (from Cristian. \ N \ n ");

 // request server name.

  Printf ( "Enter the name of the local network server \ n (Example: acpt00.gi.ehu.es / localhost):");
Scanf ( "% s", serv_name);

Printf ( "\ n \ nPort (as of% d):", IPPORT_RESERVED + 1);
Scanf ( "% d", & port);

While (port <= IPPORT_RESERVED)
{
Printf ( "\ n \ nThe port% d is reserved. Try again. \ N", port);
Printf ( "\ nPort (as of% d):", IPPORT_RESERVED + 1);
Scanf ( "% d", & port);
}

  // Open the socket to establish the connection.

  Sock = socket (PF_INET, SOCK_STREAM, 0);
  If (sock <0)
{
Perror ( "Can not create socket");
Exit (1);
  }

  Server.sin_family = AF_INET;
  Server.sin_port = htons (port);

  // Remove the DNS information from the server.

  Hp = gethostbyname (serv_name);
  If (hp == NULL)
  {
Perror ( "gethostbyname");
Close (sock);
Exit (1);
  }

  Memcpy (& server.sin_addr, hp-> h_addr, hp-> h_length);

  If (connect (sock, (struct sockaddr *) & server, sizeof server) <0)
{
Perror ( "connect");
Close (sock);
Exit (1);
  }

  // Start the application protocol with the OPEN command.

  Printf ( "\ n \ nConnecting to port% d of the machine,% s ... \ n", port, server_name);
  Sprintf (buf, "% s", commands [0]);
  Write (sock, buf, strlen (buf));

  // if we are here, we must receive the confirmation OKEY.

  If ((k == read (sock, buf, TAMBUF)) <0)
  {
Perror ( "read");
Close (sock);
Exit (1);
  }

  Switch (response_parser (buf))
  {
  Case 0: // correct login
Printf ( "\ nStart session set ... \ n");
break;

  Case 1: // login failed.
Printf ( "\ nFirst session failed ... \ n");
Close (sock);
Exit (1);

  Default: // we do not know what happened ...
Printf ( "\ nProtocol error ... Abandonment. \ N");
Close (sock);
Exit (1);
  }

// Initialize Dmin with a sufficiently large value.

Dmin.tv_sec = 1000; //for example. (1000 sgs.)
Dmin.tv_usec = 1000000;

  While (1)
  {
Printf ( "\ n --------------------------------------");
Printf ( "\ n Choose the option you want:");
Printf ( "\ n 1.- Synchronize the clock");
Printf ( "\ n 2.- Exit");
Printf ( "\ n -------------------------------------- \ n \ n");
Scanf ( "% s", option);

Switch (option [0])
{
Case '1': synchronize (sock); break;
Case '2': finish (sock); break;
               Default: printf ( "\ nNot known, please try again. \ N"); break;
}
  }
}

Int compare_rests (char * s1, char * s2)
// Compare two strings of exactly 4 characters
{
Int i;
Int result = 1;
For (i = 0; i <4; i ++)
If (s1 [i]! = S2 [i]) result = 0;
Return (result);
}

Int parser_responses (char * response)
// Identify the command in question
{
If ((compares answers (answer, answers [0])) == 1) return (0); // OKEY
If ((compares answers (answer, answers [1])) == 1) return (1); // FINN
Return (-1);
}

Int calculate_deviation_absolute (long * sgs, long * usgs)
// Returns 1 if the local clock is ahead.
// -1 if the local clock was delayed.
// 0 if the local clock is set.
{
If (* sgs> 0)
{
Printf ( "advanced.");
If (* usgs <0)
{
* Usgs = (* usgs) + 1000000;
* Sgs--;
}
Return (1);
}
Else if (* sgs == 0)
{
If (* usgs> 0)
{
Printf ( "advanced.");
Return (1);
}
Else if (* usgs == 0)
{
Printf ( "set.");
Return (0);
}
else
{
Printf ( "delayed.");
* Usgs = (* usgs) * (-1);
Return (-1);
}
}
else
{
* Sgs = (* sgs) * (-1);
Printf ( "delayed.");
If (* usgs> 0)
{
* Usgs = (* usgs) * (-1) + 1000000;
* Sgs = (* sgs) -1;
}
Else if (* usgs <0) * usgs = (* usgs) * (-1);
Return (-1);
}
}

Int minorDmin (struct timeval * newD)
// Returns 1 if the time D passed as an argument is less than the one at least so far.
// 0 e. or. C.
{
If (newD-> tv_sec <Dmin.tv_sec) return (1);
Else if (newD-> tv_sec> Dmin.tv_sec) return (0);
else
{
If (newD-> tv_usec <Dmin.tv_usec) return (1);
Else return (0);
}
}

Void sync (int s)
{
  Char buf [TAMBUF];
Int k, advanced;

Struct timeval t0, t1, D, deviation, absolute deviation, tmt, t, fit;
Struct tm * tmp, * tmp2, * tmp3;

System ( "clear");

// We note the current time just before the time request to the server.

Gettimeofday (& t0, NULL);

// We send the SYNC command to start the synchronization.

Sprintf (buf, "% s", commands [1]);
If (write (s, buf, strlen (buf)) <strlen (buf))
{
Perror ( "Failed to send SYNC command Abandon ..");
Close;
Exit (0);
}

// We receive the time provided by the server.

If ((k = read (s, buf, TAMBUF)) <0)
{
Perror ( "Reading the time received by the server.");
Exit (1);
}

// We note the current time after receiving the server time.

Gettimeofday (& t1, NULL);

// Calculation of D. D = t1-t0

D.tv_sec = t1.tv_sec-t0.tv_sec;
D.tv_usec = t1.tv_usec-t0.tv_usec;

// I have subtracted on one side seconds and on the other side microseconds. The difference (t1-t0) may not be real.
// t1> t0

If (D.tv_usec <0)
{
D.tv_usec = D.tv_usec + 1000000;
D.tv_sec--;
}

Printf ( "Attempt D equal to,% ld sgs and% ld usgs. \ N", D.tv_sec, D.tv_usec);

// Manipulate the time of the received server.

Tmt.tv_sec = atol (& buf [10]); // seconds and microseconds of t (mt).
Tmt.tv_usec = atol (& buf [35]);
Tmp = (struct tm *) localtime (& (tmt.tv_sec));

T.tv_sec = t1.tv_sec- (D.tv_sec / 2);
T.tv_usec = t1.tv_usec- (D.tv_usec / 2);

// I have subtracted on one side seconds and on the other side microseconds. The difference may not be real.

If (t.tv_usec <0)
{
T.tv_usec = t.tv_usec + 1000000;
t.tv_sec--;
}

Tmp2 = (struct tm *) localtime (& (t.tv_sec));

Printf ( "\ n t:% d hrs.% D mns.% D sgs.% Ld usgs.", Tmp2-> tm_hour, tmp2-> tm_min, tmp2-> tm_sec, t.tv_usec);
\ N ", tmp-> tm_hour, tmp-> tm_min, tmp-> tm_sec, tmt \ n", "msgstr" "msgstr" "msgstr" "msgstr" "msgid" .tv_usec);

// We calculate the time difference between our clock and the server, and adjust it.

// The current deviation of the local clock will be given by: deviation = t-t (mt)

Printf ( "\ n Then you would have the clock");

Deviationabsoluta.tv_sec = t.tv_sec-tmt.tv_sec;
Deviationabsoluta.tv_usec = t.tv_usec-tmt.tv_usec;

// I have subtracted on one side seconds and on the other side microseconds.

Forward = calculate_absolute_deviation (& deviationabsolute.tv_sec, & deviationabsolute.tv_usec);

// advance takes value: 1 if the local clock is ahead.
// -1 if the local clock is delayed.
// 0 if the local clock is set.


Tmp3 = (struct tm *) localtime (& (deviationabsoluta.tv_sec));
\ N \ n ", tmp3 -> tm_hour - 1, tmp3 -> tm_min, tmp3 -> tmp3 -> tmp3 -> tmp3 -> printf (" > Tm_sec, deviationabsoluta.tv_usec);

Printf ( "The value of D obtained in this attempt, \ n");

If (minorDmin (& D) == 0)
{
Printf ( "IS NOT LESS than the minimum obtained so far. \ N");
\ N \ n ", Dmin.tv_sec, Dmin.tv_usec); printf (" Minimo D:% ld sgs and% ld usgs. \ N \ n \ nIf you choose NOT to adjust.
}
else
{
Printf ( "IF IT IS LESS than the minimum obtained so far. \ N");
Dmin.tv_sec = D.tv_sec;
Dmin.tv_usec = D.tv_usec;
Printf ( "New minimum D:% ld sgs and% ld usgs. \ N \ n \ n", Dmin.tv_sec, Dmin.tv_usec);

Gettimeofday (& set, NULL);

If (advance == 1) // subtract difference
{
Ajust.tv_usec = adjustment.tv_usec-deviationabsoluta.tv_usec;

If (set.tv_usec <0)
{
Setting.tv_usec = setting.tv_usec + 1000000;
setting.tv_sec--;
}
Ajust.tv_sec = adjustment.tv_sec-deviationabsoluta.tv_sec;

If ((settimeofday (& setting, NULL)) <0) perror ( "Setting clock ...");
else
{
Tmp3 = (struct tm *) localtime (& (set.tv_sec));
Printf ( "Synchronized clock:% d hrs.% D mns.% D sgs.% Ld usgs. \ N", tmp3-> tm_hour, tmp3-> tm_min, tmp3-> tm_sec, setting.tv_usec);
}
}
Else if (advance == - 1) // add difference
{
Ajust.tv_usec = adjustment.tv_usec + deviationabsoluta.tv_usec;

If (setting.tv_usec> = 1000000)
{
Setting.tv_usec = setting.tv_usec - 1000000;
Setting.tv_sec ++;
}
Ajust.tv_sec = adjustment.tv_sec + deviationabsoluta.tv_sec;

If ((settimeofday (& setting, NULL)) <0) perror ( "Setting clock ...");
else
{
Tmp3 = (struct tm *) localtime (& (set.tv_sec));
Printf ( "Synchronized clock:% d hrs.% D mns.% D sgs.% Ld usgs. \ N", tmp3-> tm_hour, tmp3-> tm_min, tmp3-> tm_sec, setting.tv_usec);
}
}
Else // is left as it is
{
Tmp3 = (struct tm *) localtime (& (set.tv_sec));
Printf ( "Synchronized clock:% d hrs.% D mns.% D sgs.% Ld usgs. \ N", tmp3-> tm_hour, tmp3-> tm_min, tmp3-> tm_sec, setting.tv_usec);
}
}
}

Void end (int s)
{
Char buf [TAMBUF];
Int k;

// We send the TERM command

Sprintf (buf, "% s", commands [2]);

If (write (s, buf, strlen (buf)) <strlen (buf))
{
Perror ( "Failed to send TERM command, Abandon ..");
Close (s);
Exit (0);
}

// We look forward to receiving the OKEY chain.

If ((k = read (s, buf, 4)) <0)
{
Perror ( "Reading response to TERM command");
Exit (1);
}

// We checked that we have read an OKEY.

Switch (response_parser (buf))
{
Case 0: // OK, we closed the connection.
Close (s);
Exit (0);
Case 1: // Something is wrong.
Printf ( "Rejected TERM command \ n");
Close (s);
return;
Default: // We do not know what happened ...
Close (s);
Exit (1);
}
}

