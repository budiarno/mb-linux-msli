# This script was automatically generated from the dsa-683
# Debian Security Advisory
# It is released under the Nessus Script Licence.
# Advisory is copyright 1997-2004 Software in the Public Interest, Inc.
# See http://www.debian.org/license
# DSA2nasl Convertor is copyright 2004 Michel Arboi

if (! defined_func('bn_random')) exit(0);

desc = '
Several buffer overflows have been discovered in PL/PgSQL as part of
the PostgreSQL engine which could lead to the execution of arbitrary
code.
For the stable distribution (woody) these problems have been fixed in
version 7.2.1-2woody8.
For the unstable distribution (sid) these problems have been fixed in
version 7.4.7-2.
We recommend that you upgrade your postgresql packages.


Solution : http://www.debian.org/security/2005/dsa-683
Risk factor : High';

if (description) {
 script_id(16465);
 script_version("$Revision: 1.4 $");
 script_xref(name: "DSA", value: "683");
 script_cve_id("CVE-2005-0245", "CVE-2005-0247");

 script_description(english: desc);
 script_copyright(english: "This script is (C) 2005 Michel Arboi <mikhail@nessus.org>");
 script_name(english: "[DSA683] DSA-683-1 postgresql");
 script_category(ACT_GATHER_INFO);
 script_family(english: "Debian Local Security Checks");
 script_dependencies("ssh_get_info.nasl");
 script_require_keys("Host/Debian/dpkg-l");
 script_summary(english: "DSA-683-1 postgresql");
 exit(0);
}

include("debian_package.inc");

w = 0;
if (deb_check(prefix: 'libecpg3', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package libecpg3 is vulnerable in Debian 3.0.\nUpgrade to libecpg3_7.2.1-2woody8\n');
}
if (deb_check(prefix: 'libpgperl', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package libpgperl is vulnerable in Debian 3.0.\nUpgrade to libpgperl_7.2.1-2woody8\n');
}
if (deb_check(prefix: 'libpgsql2', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package libpgsql2 is vulnerable in Debian 3.0.\nUpgrade to libpgsql2_7.2.1-2woody8\n');
}
if (deb_check(prefix: 'libpgtcl', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package libpgtcl is vulnerable in Debian 3.0.\nUpgrade to libpgtcl_7.2.1-2woody8\n');
}
if (deb_check(prefix: 'odbc-postgresql', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package odbc-postgresql is vulnerable in Debian 3.0.\nUpgrade to odbc-postgresql_7.2.1-2woody8\n');
}
if (deb_check(prefix: 'pgaccess', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package pgaccess is vulnerable in Debian 3.0.\nUpgrade to pgaccess_7.2.1-2woody8\n');
}
if (deb_check(prefix: 'postgresql', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package postgresql is vulnerable in Debian 3.0.\nUpgrade to postgresql_7.2.1-2woody8\n');
}
if (deb_check(prefix: 'postgresql-client', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package postgresql-client is vulnerable in Debian 3.0.\nUpgrade to postgresql-client_7.2.1-2woody8\n');
}
if (deb_check(prefix: 'postgresql-contrib', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package postgresql-contrib is vulnerable in Debian 3.0.\nUpgrade to postgresql-contrib_7.2.1-2woody8\n');
}
if (deb_check(prefix: 'postgresql-dev', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package postgresql-dev is vulnerable in Debian 3.0.\nUpgrade to postgresql-dev_7.2.1-2woody8\n');
}
if (deb_check(prefix: 'postgresql-doc', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package postgresql-doc is vulnerable in Debian 3.0.\nUpgrade to postgresql-doc_7.2.1-2woody8\n');
}
if (deb_check(prefix: 'python-pygresql', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package python-pygresql is vulnerable in Debian 3.0.\nUpgrade to python-pygresql_7.2.1-2woody8\n');
}
if (deb_check(prefix: 'postgresql', release: '3.1', reference: '7.4.7-2')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package postgresql is vulnerable in Debian 3.1.\nUpgrade to postgresql_7.4.7-2\n');
}
if (deb_check(prefix: 'postgresql', release: '3.0', reference: '7.2.1-2woody8')) {
 w ++;
 if (report_verbosity > 0) desc = strcat(desc, '\nThe package postgresql is vulnerable in Debian woody.\nUpgrade to postgresql_7.2.1-2woody8\n');
}
if (w) { security_hole(port: 0, data: desc); }
