#!/usr/bin/perl

use Template;
my $tt = Template->new;
my $classname_u = " ";
my @classdata;	
my %data = ( classname => " ",
	     classname_upper => " ");

open (classList, "classlist.txt");

while ($record = <classList>) {
	chomp($record);
	$classname_u = uc($record);

	%data = ( classname => $record,
		  classname_upper => $classname_u);

	push(@classdata, $record);

	$tt->process('source.tmp', \%data, "../src/".$record."_ast.cpp")
      			|| die $tt->error;

	$tt->process('header.tmp', \%data, "../src/".$record."_ast.h")
      			|| die $tt->error;
}

%makefileData = ( classdata => \@classdata);

# Create the Makefile
	$tt->process('makefile.tmp', \%makefileData, "../Makefile")
      			|| die $tt->error;

# Create the Includes File
	$tt->process('include.tmp', \%makefileData, "../src/ast_include.h")
      			|| die $tt->error;

close(classList);
