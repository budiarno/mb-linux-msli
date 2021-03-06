# This script was automatically generated from 
#  http://www.gentoo.org/security/en/glsa/glsa-200503-34.xml
# It is released under the Nessus Script Licence.
# The messages are release under the Creative Commons - Attribution /
# Share Alike license. See http://creativecommons.org/licenses/by-sa/2.0/
#
# Avisory is copyright 2001-2005 Gentoo Foundation, Inc.
# GLSA2nasl Convertor is copyright 2004 Michel Arboi <mikhail@nessus.org>

if (! defined_func('bn_random')) exit(0);

if (description)
{
 script_id(17643);
 script_version("$Revision: 1.2 $");
 script_xref(name: "GLSA", value: "200503-34");
 script_cve_id("CVE-2003-0969");

 desc = 'The remote host is affected by the vulnerability described in GLSA-200503-34
(mpg321: Format string vulnerability)


    A routine security audit of the mpg321 package revealed a known
    security issue remained unpatched. The vulnerability is a result of
    mpg321 printing embedded ID3 data to the console in an unsafe manner.
  
Impact

    Successful exploitation would require a victim to play a specially
    crafted audio file using mpg321, potentially resulting in the execution
    of arbitrary code.
  
Workaround

    There is no known workaround at this time.
  
References:
    http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2003-0969


Solution: 
    All mpg321 users should upgrade to the latest version:
    # emerge --sync
    # emerge --ask --oneshot --verbose ">=media-sound/mpg321-0.2.10-r2"
  

Risk factor : Medium
';
 script_description(english: desc);
 script_copyright(english: "(C) 2005 Michel Arboi <mikhail@nessus.org>");
 script_name(english: "[GLSA-200503-34] mpg321: Format string vulnerability");
 script_category(ACT_GATHER_INFO);
 script_family(english: "Gentoo Local Security Checks");
 script_dependencies("ssh_get_info.nasl");
 script_require_keys('Host/Gentoo/qpkg-list');
 script_summary(english: 'mpg321: Format string vulnerability');
 exit(0);
}

include('qpkg.inc');
if (qpkg_check(package: "media-sound/mpg321", unaffected: make_list("ge 0.2.10-r2"), vulnerable: make_list("lt 0.2.10-r2")
)) { security_warning(0); exit(0); }
