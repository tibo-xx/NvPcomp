#!/usr/bin/perl

use Template;
my $tt = Template->new;
my $classname_u = " ";
my @classdata;	
my %data = ( classname => " ",
	     classname_upper => " ");

open (classList, "expression_children.txt");

while ($record = <classList>) {
	chomp($record);
	$classname_u = uc($record);

	%data = ( classname => $record,
		  classname_upper => $classname_u);

	push(@classdata, $record);

	$tt->process('expression_source.tmp', \%data, "../src/".$record."_astNode.cpp")
      			|| die $tt->error;

	$tt->process('expression_header.tmp', \%data, "../src/".$record."_astNode.h")
      			|| die $tt->error;
}

close(classList);
