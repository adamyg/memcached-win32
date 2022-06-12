#!/usr/bin/perl -w
# -*- mode: perl; -*-
# $Id: buildinfo.pl,v 1.4 2022/06/12 16:10:56 cvsuser Exp $
# buildinfo generation
#
# Copyright Adam Young 2018-2020
# All rights reserved.
#
# The applications are free software: you can redistribute it
# and/or modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, version 3.
#
# Redistributions of source code must retain the above copyright
# notice, and must be distributed with the license document above.
#
# Redistributions in binary form must reproduce the above copyright
# notice, and must include the license document above in
# the documentation and/or other materials provided with the
# distribution.
#
# The applications are distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# ==end==
#

use strict;
use warnings 'all';
use Getopt::Long;
use POSIX qw(strftime asctime);

my $makelib = './makelib.in';
my $output  = "buildinfo.h";
my $prefix  = "";

my $package = undef;
my $packagename = undef;
my $version = "0.0.1";

my $builddate = undef;
my $buildnumber = "1";
my $buildtype = undef;
my $buildtoolchain = undef;

my $bindir  = undef;
my $sbindir = undef;
my $libdir  = undef;
my $libexecdir = undef;
my $datadir = undef;

my $help    = 0;

Usage() if (0 == GetOptions(
		'makelib'       => \$makelib,
		'output=s'      => \$output,
		'prefix=s'      => \$prefix,
		'package:s'     => \$package,
		'name:s'        => \$packagename,
		'version=s'     => \$version,
		'date=i'        => \$builddate,
		'build=i'       => \$buildnumber,
		'toolchain=s'   => \$buildtoolchain,
		'type:s'        => \$buildtype,
		'bindir:s'      => \$bindir,
		'sbindir:s'     => \$sbindir,
		'libdir:s'      => \$libdir,
		'libexecdir:s'  => \$libexecdir,
		'datadir:s'     => \$datadir,
		'help'          => \$help)
			|| $help);

if (-f $makelib) {
	my (%env, %tokens);

	require './makeconfig.pm' or
		die "makeconfig.pm: couldn't load $@\n";

	my $config = MakeConfig->New();

	$config->LoadProfile($makelib);

	$package = $config->{PACKAGE}
		if (! $package && defined $config->{PACKAGE});

	$packagename = $config->{PACKAGE_NAME}
		if (! $packagename && defined $config->{PACKAGE_NAME});
}

die "buildinfo: PACKAGE not defined\n"
	if (! $package);

die "buildinfo: PACKAGE_NAME not defined\n"
	if (! $packagename);

$version = "0.0.1"
	if (! $version);

$builddate = strftime('%Y%m%d', localtime)
	if (! $builddate);

Generate();

sub
Generate	#()
{
	open(FILE, ">${output}") or
		die "cannot create <${output}> : $!\n";

	my ($version1, $version2, $version3) =
		split(/\./, $version);

	my $timestamp = asctime(localtime);

	$version2 = 0 if (! $version2);
	$version3 = 0 if (! $version3);

	print FILE <<"EOT";
// Auto-generated by Makefile ${timestamp}
#define ${prefix}PACKAGE "${package}"
#define ${prefix}PACKAGE_NAME "${packagename}"
#define ${prefix}VERSION "${version}"
#define ${prefix}VERSION_1 ${version1}
#define ${prefix}VERSION_2 ${version2}
#define ${prefix}VERSION_3 ${version3}
#define ${prefix}VERSION_4 ${buildnumber}
#define ${prefix}BUILD_DATE "${builddate}"
#define ${prefix}BUILD_NUMBER "${buildnumber}"
EOT

	print FILE "#define BUILD_TOOLCHAIN \"${buildtoolchain}\"\n"
		if ($buildtoolchain);

	if ($buildtype) {
		print FILE "#define BUILD_TYPE \"${buildtype}\"\n";

		die "buildinfo.pm: build type verb 'release' or 'debug' expected.\n"
			if ($buildtype !~ /release/ && $buildtype !~ /debug/);

		die "buildinfo.pm: build type verbs 'release' and 'debug' are mutually exclusive.\n"
			if ($buildtype =~ /release/ && $buildtype =~ /debug/);

		print FILE "#define BUILD_TYPE_RELEASE 1\n"
			if ($buildtype =~ /release/);
		print FILE "#define BUILD_TYPE_DEBUG 1\n"
			if ($buildtype =~ /debug/);
	}

	print FILE "#define ${prefix}BUILD_BINDIR \"${bindir}\"\n"
		if ($bindir);

	print FILE "#define ${prefix}BUILD_SBINDIR \"${sbindir}\"\n"
		if ($sbindir);

	print FILE "#define ${prefix}BUILD_LIBDIR \"${libdir}\"\n"
		if ($libdir);

	print FILE "#define ${prefix}BUILD_LIBEXECDIR \"${libexecdir}\"\n"
		if ($libexecdir);

	close(FILE);
}


sub
Usage		# ([message])
{
	print "\nbuildinfo.h @_\n\n" if (@_);
	print <<EOU;

Usage: perl buildinfo.pl [options]

Options:
    --output <file>         Output file.
    --prefix <prefix>       Identifier prefix (optional).
    --package <package>     Package label.
    --name <name>           Package name.
    --version <version>     Package version.
    --date <date>           Build date.
    --build <number>        Build number.
    --toolchain <desc>      Toolchain.

    --bindir <path>         bindir path.
    --sbindir <path>        sbindir path.
    --libdir <path>         libdir path.
    --libexecdir<path>      libexecdir path.
    --datadir <path>        datadir path.

    --help                  Help.

EOU
	exit 3;
}

1;

#end

