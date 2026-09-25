


#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;




struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};


long long int get_time_remaining(DryingSnapShot dss){
	// Replace with your code
	time_t cur_time = time(0);
	long long int elapsed = static_cast<long long int>(current_time - dss.startTime);
	long long int total_seconds = statoc_cast<long long int>(dss.timeToDry->GetTimeCodeAsSeconds());
	
	long long int remain = total_seconds - elapsed;
	
	if (remaining < 0) {
		return 0;
	}
	
	return remain;
}


string drying_snap_shot_to_string(DryingSnapShot dss){
	long long int remain = get_time_remaining(dss);
	
	TimeCode remain_tc(0, 0, remain);
	
	return dss.name + " (Total time it will take: " + dss.timeToDry->ToString() + ")\nTime Remaining: " + remain_tc.ToString();
	
}


double get_sphere_sa(double rad){
	
	return 4.0 * M_PI * rad * rad;
}


TimeCode *compute_time_code(double surfaceArea){
	// replace with your code
	return new TimeCode(0, 0, static_cast<unsigned long long int>(surfaceArea));
}


void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	// add more tests here


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	// add more tests here


	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;


	// add more tests here


	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	// replace with your code
	//tests());
	return 0;
}
