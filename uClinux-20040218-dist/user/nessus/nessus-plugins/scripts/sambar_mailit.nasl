#
# This script was written by Renaud Deraison <deraison@cvs.nessus.org>
#
# See the Nessus Scripts License for details
#

if(description)
{
 script_id(10417);
 script_version ("$Revision: 1.10 $");
 name["english"] = "Sambar /cgi-bin/mailit.pl installed ?";
 script_name(english:name["english"]);
 
 desc["english"] = "The Sambar webserver is running
and the 'mailit.pl' cgi is installed. This CGI takes
a POST request from any host and sends a mail to a supplied address. 


Solution : remove it from /cgi-bin.
Risk factor : Serious";


 script_description(english:desc["english"]);
 
 summary["english"] = "Checks for the presence of /cgi-bin/mailit";
 
 script_summary(english:summary["english"]);
 
 script_category(ACT_ATTACK);
 
 
 script_copyright(english:"This script is Copyright (C) 2000 Hendrik Scholz");
 family["english"] = "CGI abuses";
 family["francais"] = "Abus de CGI";
 script_family(english:family["english"], francais:family["francais"]);
 script_dependencie("find_service.nes", "no404.nasl", "http_version.nasl");
 script_require_ports("Services/www", 80);
 script_require_keys("www/sambar");
 exit(0);
}

#
# The script code starts here
#

cgi = "/cgi-bin/mailit.pl";
port = is_cgi_installed(cgi);
if(port)security_hole(port);
