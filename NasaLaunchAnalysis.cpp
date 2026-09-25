#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include "TimeCode.h"
using namespace std;

TimeCode parse_time(const string& line){
	
		
	stringstream ss(line);
	string before, after;
	
	getline(ss, before, ':');
	getline(ss, after);
	
	string hours = before.substr(before.length() - 2, 2);
	string mins = after.substr(0, 2);
	
	unsigned int h = static_cast<unsigned int>(stoul(hours));
    unsigned int m = static_cast<unsigned int>(stoul(mins));
    
	return TimeCode(h, m, 0);
}



int main(){
	ifstream file("Space_Corrected.csv");
	vector<TimeCode> time_container;
	string line;
	
	getline(file, line);
	
	while (getline(file, line)) {
		if (line.find(':') != string::npos){
			time_container.emplace_back(parse_time(line));
		}
		
	}
	
	TimeCode initial_sum(0, 0, 0);
	TimeCode total_sum = accumulate(time_container.begin(), time_container.end(), initial_sum);
	
	double num_items = static_cast<double>(time_container.size());
	TimeCode average = total_sum / num_items;
	
	cout << time_container.size() << " data points." << endl;
    cout << "AVERAGE: " << average.ToString() << endl;

    return 0;
	
}
