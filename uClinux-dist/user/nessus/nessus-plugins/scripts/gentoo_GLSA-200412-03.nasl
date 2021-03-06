# This script was automatically generated from 
#  http://www.gentoo.org/security/en/glsa/glsa-200412-03.xml
# It is released under the Nessus Script Licence.
# The messages are release under the Creative Commons - Attribution /
# Share Alike license. See http://creativecommons.org/licenses/by-sa/2.0/
#
# Avisory is copyright 2001-2005 Gentoo Foundation, Inc.
# GLSA2nasl Convertor is copyright 2004 Michel Arboi <mikhail@nessus.org>

if (! defined_func('bn_random')) exit(0);

if (description)
{
 script_id(15913);
 script_version("$Revision: 1.3 $");
 script_xref(name: "GLSA", value: "200412-03");
 script_cve_id("CVE-2004-1026");

 desc = 'The remote host is affected by the vulnerability described in GLSA-200412-03
(imlib: Buffer overflows in image decoding)


    Pavel Kankovsky discovered that several overflows found in the
    libXpm library (see GLSA 200409-34) also applied to imlib. He also
    fixed a number of other potential flaws.
  
Impact

    A remote attacker could entice a user to view a carefully-crafted
    image file, which would potentially lead to execution of arbitrary code
    with the rights of the user viewing the image. This affects any program
    that makes use of the imlib library.
  
Workaround

    There is no known workaround at this time.
  
References:
    http://www.gentoo.org/security/en/glsa/glsa-200409-34.xml
    http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2004-1026


Solution: 
    All imlib users should upgrade to the latest version:
    # emerge --sync
    # emerge --ask --oneshot --verbose ">=media-libs/imlib-1.9.14-r3"
  

Risk factor : Medium
';
 script_description(english: desc);
 script_copyright(english: "(C) 2005 Michel Arboi <mikhail@nessus.org>");
 script_name(english: "[GLSA-200412-03] imlib: Buffer overflows in image decoding");
 script_category(ACT_GATHER_INFO);
 script_family(english: "Gentoo Local Security Checks");
 script_dependencies("ssh_get_info.nasl");
 script_require_keys('Host/Gentoo/qpkg-list');
 script_summary(english: 'imlib: Buffer overflows in image decoding');
 exit(0);
}

include('qpkg.inc');
if (qpkg_check(package: "media-libs/imlib", unaffected: make_list("ge 1.9.14-r3"), vulnerable: make_list("le 1.9.14-r2")
)) { security_warning(0); exit(0); }
