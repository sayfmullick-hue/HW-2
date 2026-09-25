# found this trick online
# didnt do it for the compiler since we haven't had a reason to use anything other than g++ yet
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# default target to build all executables
all: timecode_tests nasa_analysis paint_dry

# compile the shared TimeCode class into an object file 
TimeCode.o: TimeCode.cpp TimeCode.h
	g++ $(CXXFLAGS) -c TimeCode.cpp

# build the TimeCode tests executable
timecode_tests: TimeCodeTests.cpp TimeCode.o
	g++ $(CXXFLAGS) TimeCodeTests.cpp TimeCode.o -o timecode_tests

# build the NasaLaunchAnalysis executable
nasa_analysis: NasaLaunchAnalysis.cpp TimeCode.o
	g++ $(CXXFLAGS) NasaLaunchAnalysis.cpp TimeCode.o -o nasa_analysis

# build the PaintDryTimer executable
paint_dry: PaintDryTimer.cpp TimeCode.o
	g++ $(CXXFLAGS) PaintDryTimer.cpp TimeCode.o -o paint_dry

# clean up files
clean:
	rm -f *.o timecode_tests nasa_analysis paint_dry
