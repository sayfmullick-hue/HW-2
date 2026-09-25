# HW-2
This repository was used for my HW 2 assignment in CPS 222.

This HW focused on creating a time-tracking class (TimeCode), processing CSV data, 
and heap management.

TimeCode Class: A class that stores data in seconds and presents it in hours,
minutes, seconds. Supports arithmetic, comparison operators, and component
rollover.

NasaLaunchAnalysis.cpp : Parses through a CSV file containing launch times and
calculates the average launch time.

PaintDryTimer.cpp : An interactive application that tracks in real time how long
paint batches based on a certain radius take to dry. Allows you to check their
progress or quit whenever. It takes extra care to clean the heap after use.

TimeCodeTests.cpp : This was used to test that arithmetic, comparison operators,
rollover logic, and exception handling of the TimeCode class work.

Compiler: May need slight modification in the makefile but any c++17 compiler 
should work.

Valgrind was the memory debugger.
