#
# (C) Tenable Network Security
#
# This plugin text was extracted from Mandrake Linux Security Advisory MDKSA-2004:090
#


if ( ! defined_func("bn_random") ) exit(0);
if(description)
{
 script_id(14679);
 script_version ("$Revision: 1.3 $");
 script_cve_id("CVE-2004-0797");
 
 name["english"] = "MDKSA-2004:090: zlib";
 
 script_name(english:name["english"]);
 
 desc["english"] = "
The remote host is missing the patch for the advisory MDKSA-2004:090 (zlib).


Due to a Debian bug report, a Denial of Service vulnerability was discovered in
the zlib compression library versions 1.2.x, in the inflate() and inflateBack()
functions. Older versions of zlib are not affected.
Once the updated packages have been installed, all programs linked against zlib
must be restarted for the new packages to take effect.


Solution : http://wwwnew.mandriva.com/security/advisories?name=MDKSA-2004:090
Risk factor : High";



 script_description(english:desc["english"]);
 
 summary["english"] = "Check for the version of the zlib package";
 script_summary(english:summary["english"]);
 
 script_category(ACT_GATHER_INFO);
 
 script_copyright(english:"This script is Copyright (C) 2004 Tenable Network Security");
 family["english"] = "Mandrake Local Security Checks";
 script_family(english:family["english"]);
 
 script_dependencies("ssh_get_info.nasl");
 script_require_keys("Host/Mandrake/rpm-list");
 exit(0);
}

include("rpm.inc");
if ( rpm_check( reference:"zlib1-1.2.1-2.1.100mdk", release:"MDK10.0", yank:"mdk") )
{
 security_hole(0);
 exit(0);
}
if ( rpm_check( reference:"zlib1-devel-1.2.1-2.1.100mdk", release:"MDK10.0", yank:"mdk") )
{
 security_hole(0);
 exit(0);
}
if (rpm_exists(rpm:"zlib-", release:"MDK10.0") )
{
 set_kb_item(name:"CVE-2004-0797", value:TRUE);
}
