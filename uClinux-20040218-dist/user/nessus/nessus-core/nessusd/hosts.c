/* Nessus
 * Copyright (C) 1998 - 2003 Renaud Deraison
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2,
 * as published by the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * In addition, as a special exception, Renaud Deraison
 * gives permission to link the code of this program with any
 * version of the OpenSSL library which is distributed under a
 * license identical to that listed in the included COPYING.OpenSSL
 * file, and distribute linked combinations including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * this file, you may extend this exception to your version of the
 * file, but you are not obligated to do so.  If you do not wish to
 * do so, delete this exception statement from your version.
 *
 * $Id: hosts.c,v 1.21 2003/07/01 21:03:51 renaud Exp $
 */

#include <includes.h>
#include "utils.h"
#include "log.h"
#include "preferences.h"
#include "detached.h"
#include "save_kb.h"
#include "save_tests.h"
#include "hosts.h"
#include "ntp_11.h"

struct host {
	char * name;
	int soc;
	int psoc;
	pid_t pid;
	struct host * next;
	struct host * prev;
	};




static struct host * hosts = NULL;
static int    g_soc = -1;
static int    g_max_hosts = 15;



static void sigchld_handler(int sig)
{
 struct host * h = hosts;
 while (h != NULL)
 {
  if(h->pid != 0)
	 {
		 int e;
		 do { e = waitpid(h->pid, NULL, WNOHANG); }
		while( e < 0 && errno == EINTR);
	}
  h = h->next;
 }
}

/*-------------------------------------------------------------------------*/
static int forward(struct arglist * globals, int in, int out)
{
 fd_set rd;
 struct timeval tv;
 int e;
 struct arglist * preferences = globals ? arg_get_value(globals, "preferences"):NULL;
 char buf[8192];
 
 
again:
 tv.tv_sec = 0;
 tv.tv_usec = 1000;
 FD_ZERO(&rd);
 FD_SET(in, &rd);
 if((e = select(in + 1, &rd, NULL, NULL, &tv)) > 0)
 {
  int n;
  int m = 0, r;
  
  if(data_left(in) <= 0)
   return -1;
   
  n = recv_line(in, buf, sizeof(buf) - 1);
  if(n <= 0)
   return -1;
  
  if(preferences != NULL)
  {
  if(preferences_detached_scan(preferences) != 0)
		detached_copy_data(globals, estrdup(buf), n);
		
  if(preferences_save_session(preferences) != 0)
  		save_tests_write_data(globals, estrdup(buf));		
  }
  
  	
  while(out != -1 && (m != n))
  {
   r = nsend(out, buf + m, n - m, 0);
   if(r <= 0)
    return -1;
   else
    m += r;
  }

  /* Make sure the buffer was not full */
  if(buf[n - 1] != '\n')
    	goto again;
  
  /* Ack the reception */
  (void)send(in, ".", 1, 0);
 
  return 0;
 }
 else if(e < 0 && errno == EINTR)goto again;
 return -1;
}


static void forward_all(struct arglist * globals, int in, int out)
{ 
 while(forward(globals, in, out) == 0);
}
/*-------------------------------------------------------------------*/



static struct host * host_rm(struct arglist * globals, struct host * hosts, struct host * h)
{
 struct arglist * preferences = arg_get_value(globals, "preferences");
    
    
 if(h->pid != 0)waitpid(h->pid, NULL, WNOHANG);
 forward_all(globals, h->soc, g_soc);
 
 if( preferences_save_session(preferences) != 0 )
   	save_tests_host_done(globals, h->name);
	

	
 close(h->soc);
 if(h->psoc != 0)close(h->psoc);
 
 if( h->next != NULL )
  	h->next->prev = h->prev;

 if( h->prev != NULL )
 	h->prev->next = h->next;
 else
 	hosts = h->next;
	
	
 efree(&h->name);
 efree(&h);
 return hosts;
}

/*-----------------------------------------------------------------*/

static int hosts_num()
{
 struct host * h = hosts;
 int num;
 
 for(num = 0; h != NULL ; num++, h = h->next);
 
 return num;
}

static struct host * hosts_get(char * name)
{
 struct host * h = hosts;
 while ( h != NULL )
 {
  if(strcmp(h->name, name) == 0)
   return h;
  h = h->next;
 }
 return NULL;
}


int hosts_init(int soc, int max_hosts)
{
 g_soc = soc;
 g_max_hosts = max_hosts;
 signal(SIGCHLD, sigchld_handler);
 return 0;
}

int hosts_new(struct arglist * globals, char * name)
{
 struct host * h;
 int soc[2];
 
 while(hosts_num() >= g_max_hosts)
 {
  if(hosts_read(globals) < 0)
   return -1;
 }
 
 
 if(socketpair(AF_UNIX, SOCK_STREAM, 0, soc) < 0)
  return -1;
  
 h = emalloc(sizeof(struct host)); 
 h->name = estrdup(name);
 h->pid  = 0;
 h->soc  = soc[1];
 h->psoc = soc[0];
 if(hosts != NULL)
  hosts->prev = h;
 h->next = hosts;
 h->prev = NULL;
 hosts = h;
 return soc[0];
}


int hosts_set_pid(char * name, pid_t pid)
{
 struct host * h = hosts_get(name);
 if(h == NULL)
  {
  fprintf(stderr, "host_set_pid() failed!\n");
  return -1;
  }
 
 h->pid = pid;
 close(h->psoc); /* Close the socket used by our son */
 h->psoc = 0;
 return 0;
}

/*-----------------------------------------------------------------*/
int hosts_stop_host(struct arglist * globals, char * name)
{
 struct host * h = hosts_get(name);
 if( h == NULL ) 
  return -1;
 
 shutdown(h->soc, 2);
 kill(h->pid, SIGTERM);
 waitpid(h->pid, NULL, 0);
 hosts = host_rm(globals, hosts, h);
 return 0;
}

void hosts_stop_all()
{
 
 while(hosts != NULL)
 {
  hosts_stop_host(NULL, hosts->name);
 }
}
/*-----------------------------------------------------------------*/







static int hosts_read_data(struct arglist * globals)
{
 fd_set rd;
 struct timeval tv;
 int max = -1;
 struct host * h = hosts;
 int e;
 int ret = 0;
 
	
 
 waitpid(-1, NULL, WNOHANG);

 if( h == NULL )
  return 0;
  
 FD_ZERO(&rd);
 while(h != NULL)
 {
  if(kill(h->pid, 0) < 0) /* Process is dead */
  { 
   hosts = host_rm(globals, hosts, h);
   h = hosts;
  }
  else
  {
   FD_SET(h->soc, &rd);
   if(h->soc > max)
    max = h->soc;
   h = h->next;
  }
 }
 
 
 for(;;)
 {
  tv.tv_sec = 0;
  tv.tv_usec = 10000;
  e = select(max + 1, &rd, NULL, NULL, &tv);
  
  if(e < 0 && errno == EINTR)continue;
  else break;
 }
 
 if(e <= 0)
  return -1;
 
 h = hosts;
 while(h != NULL)
 {
  if(FD_ISSET(h->soc, &rd) != 0)
   {
   if((data_left(h->soc) != 0) &&
      (forward(globals, h->soc, g_soc) == 0))
      	ret ++;
   }
  h = h->next;
 }
 
 return ret;
}


static int hosts_read_client(struct arglist * globals)
{
 char buf[4096];
 struct timeval tv;
 int e;
 fd_set rd;
 int rsoc;
 int n;

 if(g_soc == -1 )
    return 0;


 rsoc = nessus_get_socket_from_connection(g_soc);
 if(rsoc == -1)
    return -1;




 
 FD_ZERO(&rd);
 FD_SET(rsoc, &rd);

 for(;;)
 {
 tv.tv_sec = 0;
 tv.tv_usec = 1000;
 e = select(rsoc + 1, &rd, NULL, NULL, &tv);
 if(e < 0 && errno == EINTR)continue;
 else break;
 }
 
 if(e > 0 && FD_ISSET(rsoc, &rd) != 0)
 {
 int f;
 n = recv_line(g_soc, buf, sizeof(buf) - 1);
 if(n <= 0)
  return -1;
 
 f = ntp_11_parse_input(globals, buf);
 if( f == NTP_STOP_WHOLE_TEST )
  return -1;
 }
 
 return 0;
}


int hosts_read(struct arglist * globals)
{
 
 if(hosts_read_client(globals) < 0)
  {
  hosts_stop_all();
  log_write("Client abruptly closed the communication");
  return -1;
  }
  
  
 if( hosts == NULL )
  return -1; 
 
  
 hosts_read_data(globals);
 return 0;
}




