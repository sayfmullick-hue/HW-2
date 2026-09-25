


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
	long long int elapsed = static_cast<long long int>(cur_time - dss.startTime);
	long long int total_seconds = static_cast<long long int>(dss.timeToDry->GetTimeCodeAsSeconds());
	
	long long int remain = total_seconds - elapsed;
	
	if (remain < 0) {
		return 0;
	}
	
	return remain;
}

// Returns a string telling the user how much time is left of the total time it will take the paint to dry
string drying_snap_shot_to_string(DryingSnapShot dss){
	long long int remain = get_time_remaining(dss);
	
	TimeCode remain_tc(0, 0, remain);
	
	return dss.name + " will take in total " + dss.timeToDry->ToString() + "\nTime Remaining: " + remain_tc.ToString();
	
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
	DryingSnapShot dss_done;
    dss_done.startTime = time(0) - 20; // Started 20 seconds ago
    TimeCode tc_done = TimeCode(0, 0, 5); // Only takes 5 seconds to dry
    dss_done.timeToDry = &tc_done;
    assert(get_time_remaining(dss_done) == 0);

	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	
	// Check radius of 0 results in 0
	double sa_zero = get_sphere_sa(0.0);
    assert (sa_zero == 0.0);
	
	// Check radius of 1 results in 4 * pi
	double sa_one = get_sphere_sa(1.0);
    assert (12.5663 < sa_one && sa_one < 12.5664);
    
	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;


	// add more tests here
	// Large surface area forcing TimeCode to roll over into hours and minutes
    TimeCode *tc3 = compute_time_code(3665.9); // 3665 total seconds
    assert(tc3->GetTimeCodeAsSeconds() == 3665);
    assert(tc3->GetHours() == 1);
    assert(tc3->GetMinutes() == 1);
    assert(tc3->GetSeconds() == 5);
    delete tc3;
    
    
    // Verify string formatting contains the expected components
    DryingSnapShot dss_str;
    dss_str.name = "Batch-X";
    dss_str.startTime = time(0);
    TimeCode tc_str = TimeCode(1, 30, 0); 
    dss_str.timeToDry = &tc_str;
    
    string output = drying_snap_shot_to_string(dss_str);
    cout << "\n" << output << "\n";
    assert(output.find("Batch-X") != string::npos);
    assert(output.find("will take in total 1:30:0") != string::npos);

	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	//tests();
	vector<DryingSnapShot> batches;
    string input;
    unsigned int batch_counter = 1;

    cout << "Welcome to the Paint Dry Timer!" << endl;

    while (true) {
        cout << "\nChoose an option: (A)dd, (V)iew, (Q)uit: ";
        cin >> input;

        if (input == "A" || input == "a") {
            double radius;
            cout << "Enter radius: ";
            cin >> radius;

            DryingSnapShot new_batch;
            new_batch.startTime = time(0);
            new_batch.name = "Batch-" + to_string(batch_counter);
            batch_counter++;

            double sa = get_sphere_sa(radius);
            new_batch.timeToDry = compute_time_code(sa);

            batches.push_back(new_batch);
            
            cout << new_batch.name << " added! It will take " << new_batch.timeToDry->ToString() << " to dry." << endl;
        } 
        else if (input == "V" || input == "v") {
            if (batches.empty()) {
                cout << "No batches are currently being tracked." << endl;
                continue;
            }

            // Create a temporary vector to keep only batches that are still drying
            vector<DryingSnapShot> active_batches;

            for (size_t i = 0; i < batches.size(); i++) {
                cout << drying_snap_shot_to_string(batches[i]) << endl;

                if (get_time_remaining(batches[i]) > 0) {
                    active_batches.push_back(batches[i]);
                } else {
                    // Free's the heap memory for objects that are finished
                    delete batches[i].timeToDry;
                }
            }
            
            // Overwrite the old vector with only the active ones
            batches = active_batches;
        }
        else if (input == "Q" || input == "q") {
            cout << "Exiting program. Cleaning up memory..." << endl;
            break;
        }
        else {
            cout << "Invalid option." << endl;
        }
    }

    // Ensure there are no memory leaks when quitting
    for (size_t i = 0; i < batches.size(); i++) {
        delete batches[i].timeToDry;
    }
	return 0;
}
