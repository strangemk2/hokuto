#!/usr/bin/perl -w

use strict;
use Win32::GuiTest qw(FindWindowLike SetForegroundWindow SendKeys);
use Term::ReadKey;

ReadMode 4;

while (1)
{
	my $ch = getc();
	if ($ch eq 'q')
	{
		ReadMode 0;
		exit;
	}
	# Find a specific Window
	my @windows = FindWindowLike(0, qr/^–k“l/, qr/^Chrome/);
	die "more than one windows" if (@windows != 1);
	#SetForegroundWindow($windows[0]);

	my $window = $windows[0];
	my $ds = new Win32::GuiTest::DibSect;
	$ds->CopyWindow($window);
	$ds->SaveAs("C:\\work\\eas_migration\\hokuto\\bla.bmp");

	my $text = `C:\\work\\eas_migration\\hokuto\\hoku1 C:\\work\\eas_migration\\hokuto\\bla.bmp 1`;

	my $num_flag = 0;
	my $inteligence_flag = 1;
	#if ($ch eq '.' || $ch eq 'o')
	#{
	#	substr($text, -1, 1, $ch);
	#}
	my $interval = undef;
	if ($ch eq ',')
	{
		$text = ".$text";
		$interval = 80;
	}
	elsif (ord($ch) > 48 && 57 >= ord($ch))
	{
		$num_flag = 1;
		$text = substr($text, 0, length($text) - $ch);
	}
	elsif ($ch eq '.')
	{
		$inteligence_flag = 0;
	}

	if ($inteligence_flag)
	{
		my $last = substr($text, -1);
		if ($last eq ',')
		{
			substr($text, -1, 1, '.');
		}
		elsif ($last eq 'c')
		{
			substr($text, -1, 1, 'o');
		}
		elsif ($last eq 'h')
		{
			substr($text, -1, 1, 'n');
		}
	}
	print $text . "\n";

	SetForegroundWindow($windows[0]);
	SendKeys($text, $interval); # Alt Print Screen

	if (!$num_flag)
	{
		@windows = FindWindowLike(0, qr/^Adminis.*•„/);
		die "more than one windows" if (@windows != 1);
		SetForegroundWindow($windows[0]);
	}
}

#for (@windows) {
#    SetForegroundWindow($_);
#    SendKeys('%{PRTSCR}'); # Alt Print Screen
#}
