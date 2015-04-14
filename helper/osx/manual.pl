#!/usr/bin/perl

# wrapper script for manual start hokuto.pl
# for game scene like kettoudenn.
use Term::ReadKey;
ReadMode 4; # Turn off controls keys
while (defined ($key = ReadKey(0))) {
	if ($key eq 'q')
	{
		ReadMode 0;
		exit;
	}
	#print "Get key $key\n";
	system("perl hokuto.pl $key");
}
ReadMode 0; # Reset tty mode before exiting
