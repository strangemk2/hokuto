#!/usr/bin/perl

# automatic script for matching
# for game scene like shitoudenn.
unlink foreach (glob("/Volumes/RAMDisk/.a*"));

system("osascript -e '\ntell application \"Chrome\"\nactivate\nend tell\n'");

my $sig_int = 0;

while (1)
{
	sleep 1;

	system("screencapture -x /Volumes/RAMDisk/a.png");
	exit 0 if ($? & 127);

	my $kana = `./hoku1 /Volumes/RAMDisk/a.png font/`;
	$kana =~ s/[%&!?].*//;
	next unless (length($kana));
	
	my $back_flag = 1;
	my $inteligence_flag = 1;
	my $speed = 150;
	if ($ARGV[0] eq ".")
	{
		#substr ($kana, -1, 1, $ARGV[0]);
		$speed = 30;
		$inteligence_flag = 0;
	}
	if ($ARGV[0] eq ",")
	{
		$kana = ",$kana";
	}
	elsif ($ARGV[0] <= 9 && $ARGV[0] > 0)
	{
		$kana = substr($kana, 0, (length($kana) - $ARGV[0]));
		$back_flag = 0;
	}
	elsif ($ARGV[0] eq "/")
	{
		$speed = 30;
	}

	if ($inteligence_flag)
	{
		my $last_char = substr($kana, -1);
		if ($last_char eq ',')
		{
			substr($kana, -1, 1, ".");
		}
		elsif ($last_char eq 'c')
		{
			substr($kana, -1, 1, "o");
		}
		elsif ($last_char eq 'h')
		{
			substr($kana, -1, 1, "n");
		}
	}
	print "$kana\n";

#system("osascript -e '\ntell application \"Chrome\"\nactivate\nend tell\ntell application \"System Events\"\nkeystroke \"$kana\"\nend tell\n'\n");
#$kana = "abc!!!???";

	open (my $fp, ">/Volumes/RAMDisk/a.osa");
	print $fp "tell application \"Chrome\"\n";
	print $fp "activate\n";
	print $fp "end tell\n";
	print $fp "tell application \"System Events\"\n";
	for (my $i = 0; $i != length($kana); ++$i)
	{
		my $ch = substr($kana, $i, 1);
		#if ($ch eq "!")
		#{
		#	print $fp "key code 18 using shift down\n"
		#}
		#elsif ($ch eq "?")
		#{
		#	print $fp "key code 44 using shift down\n"
		#}
		#else
		{
			print $fp "keystroke \"$ch\"\n";
		}
		my $millisecond = int(rand($speed)) + 10;
		my $mmm = sprintf("%03d", $millisecond);
		print $fp "delay 0.${mmm}\n";
	}
	print $fp "end tell";
	close ($fp);
	system("osascript /Volumes/RAMDisk/a.osa");
}

system("osascript -e '\ntell application \"Terminal\"\nactivate\nend tell\n'") if ($back_flag);
