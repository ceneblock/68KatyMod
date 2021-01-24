#
# (C) Tenable Network Security
#
# See the Nessus Scripts License for details
#
# Ref: http://www.securitytracker.com/alerts/2003/Mar/1006203.html
#

if(description)
{
 script_id(11624); 
 script_version ("$Revision: 1.3 $");
 
 name["english"] = "SHOUTcast Server logfiles XSS";
 script_name(english:name["english"]);
 
 desc["english"] = "
The remote host is running SHOUTcast server.

This software does not properly validate the data passed
by clients, and displays it 'as is' in its log file.

An attacker may use this flaw to perform a cross site scripting
attack against the administrators of the remote SHOUTcast server,
and steal the administrators cookies.

See also : http://www.securitytracker.com/alerts/2003/Mar/1006203.html
Risk factor : Medium";

 script_description(english:desc["english"]);
 
 summary["english"] = "SHOUTcast Server DoS detector vulnerability";
 script_summary(english:summary["english"]);
 
 script_category(ACT_GATHER_INFO);
 
 script_copyright(english:"This script is Copyright (C) 2003 Tenable Network Security");
 family["english"] = "General";
 script_family(english:family["english"]);

 script_dependencie("find_service.nes", "no404.nasl");
 script_require_ports("Services/www", 8000);
 exit(0);
}

#
# The script code starts here
#

include("http_func.inc");
include("misc_func.inc");

ports = add_port_in_list(list:get_kb_list("Services/www"), port:8000);
foreach port (ports)
{
 if (get_port_state(port))
 {
  banner = get_http_banner(port:port);
  if(!banner)exit(0);
  if ("SHOUTcast Distributed Network Audio Server" >< banner)
  {
   security_warning(port);
   exit(0);
  } 
 }
}
