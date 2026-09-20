#include <iostream>
#include <assert.h>
#include <stdexcept>

#include "TimeCode.h"

void TestComponentsToSeconds();
void TestDefaultConstructor();
void TestComponentConstructor();
void TestGetComponents();
void TestArithmetic();
void TestSubtract();
void TestSetMinutes();

int main () {
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestArithmetic();
	TestSubtract();
	TestSetMinutes();
	
	std::cout << "\nPASSED ALL TESTS!!!\n" << std::endl;
	return 1;
}

// tests the static conversion of components into total seconds
void TestComponentsToSeconds(){
	std::cout << "\nTesting ComponentsToSeconds\n" << std::endl;
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);
	std::cout << "PASSED!" << std::endl;
}

// tests initializing with no arguments
void TestDefaultConstructor(){
	std::cout << "\nTesting Default Constructor\n" << std::endl;
	TimeCode tc;
	assert(tc.ToString() == "0:0:0");
	std::cout << "PASSED!" << std::endl;
}

// tests roll-over logic to make sure the time is correctly converted
void TestComponentConstructor(){
	std::cout << "\nTesting Component Constructor\n" << std::endl;
	TimeCode tc = TimeCode(0, 0, 0);
	assert(tc.ToString() == "0:0:0");
	
	TimeCode tc3 = TimeCode(3, 71, 3801);
	assert(tc3.ToString() == "5:14:21");
	std::cout << "PASSED!" << std::endl;
}

void TestGetComponents(){
	std::cout << "\nTesting GetComponents\n" << std::endl;
	unsigned int h, m, s;
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	std::cout << "PASSED!" << std::endl;
}

// tests arithmetic operators and multiplication error handling
void TestArithmetic(){
	std::cout << "\nTesting Arithmetic Operators\n" << std::endl;
	TimeCode tc1(1, 0, 0);
	TimeCode tc2(0, 30, 0);
	
	TimeCode sum = tc1 + tc2;
	assert(sum.ToString() == "1:30:0");
	
	TimeCode prod = tc1 * 2.0;
	assert(prod.ToString() == "2:0:0");
	
	try {
		TimeCode badProd = tc1 * -1.5;
		assert(false);
	}
	catch(const std::invalid_argument& e){
		// success
	}
	
	std::cout << "PASSED!" << std::endl;
}

// tests subtraction and checks for negative argument exception
void TestSubtract(){
	std::cout << "\nTesting Subtract\n" << std::endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		assert(false);
	}
	catch(const std::invalid_argument& e){
		// success
	}
	std::cout << "PASSED!" << std::endl;
}

// tests setting minutes and rejecting values outside bounds
void TestSetMinutes(){
	std::cout << "\nTesting SetMinutes\n" << std::endl;
	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); 
	assert(tc.ToString() == "8:15:9");

	try {
		tc.SetMinutes(80);  
		assert(false);
	}
	catch (const std::invalid_argument &e){
		// success
	}
	assert(tc.ToString() == "8:15:9");
	std::cout << "PASSED!" << std::endl;
}
