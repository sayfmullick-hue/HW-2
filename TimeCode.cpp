#include <iostream>
#include <string>
#include <stdexcept>
#include "TimeCode.h"

TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec) {
	t = ComponentsToSeconds(hr, min, sec);
}

TimeCode::TimeCode(const TimeCode& tc) {
	t = tc.t;
}

// takes the components and calculates total seconds using static casting to prevent overflow
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec) {
	return (static_cast<unsigned long long int>(hr) * 3600) + 
	       (static_cast<unsigned long long int>(min) * 60) + 
	       sec;
}

// extracts hours, minutes, and seconds from the total seconds 't'
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
	hr = t / 3600;
	min = (t % 3600) / 60;
	sec = t % 60;
}

// changes only the hours component without roll-over
void TimeCode::SetHours(unsigned int hours) {
	unsigned int h, m, s;
	GetComponents(h, m, s);
	t = ComponentsToSeconds(hours, m, s);
}

// changes only the minutes component and throws an error if the state is invalid
void TimeCode::SetMinutes(unsigned int minutes){
	if (minutes >= 60){
		throw std::invalid_argument("Negative arguments not allowed: " + std::to_string(minutes));
	}
	unsigned int h, m, s;
	GetComponents(h, m, s);
	t = ComponentsToSeconds(h, minutes, s);
}

// changes only the seconds component and throws an error if the state is invalid
void TimeCode::SetSeconds(unsigned int seconds){
	if (seconds >= 60){
		throw std::invalid_argument("Negative arguments not allowed: " + std::to_string(seconds));
	}
	unsigned int h, m, s;
	GetComponents(h, m, s);
	t = ComponentsToSeconds(h, m, seconds);
}

void TimeCode::reset(){
	t = 0;
}

unsigned int TimeCode::GetHours() const {
	unsigned int h, m, s;
	GetComponents(h, m, s);
	return h;
}

unsigned int TimeCode::GetMinutes() const {
	unsigned int h, m, s;
	GetComponents(h, m, s);
	return m;
}

unsigned int TimeCode::GetSeconds() const {
	unsigned int h, m, s;
	GetComponents(h, m, s);
	return s;
}

// converts the time code components into a string with a formatted structure
std::string TimeCode::ToString() const {
	unsigned int h, m, s;
	GetComponents(h, m, s);
	return std::to_string(h) + ":" + std::to_string(m) + ":" + std::to_string(s);
}

// adds two time codes together
TimeCode TimeCode::operator+(const TimeCode& other) const {
	TimeCode result;
	result.t = this->t + other.t;
	return result;
}

// subtracts two time codes and checks if it would yield a negative number
TimeCode TimeCode::operator-(const TimeCode& other) const {
	if (this->t < other.t){
		throw std::invalid_argument("Negative arguments not allowed");
	}
	TimeCode result;
	result.t = this->t - other.t;
	return result;
}

// multiplies the time code by a scalar and throws an error for negative values
TimeCode TimeCode::operator*(double a) const {
	if (a < 0){
		throw std::invalid_argument("Negative arguments not allowed: " + std::to_string(a));
	}
	TimeCode result;
	result.t = static_cast<long long unsigned int>(this->t * a);
	return result;
}

// divides the time code by a scalar and throws an error for negative values or zero
TimeCode TimeCode::operator/(double a) const {
	if (a == 0){
		throw std::invalid_argument("Division by zero is not allowed.");
	} else if (a < 0){
		throw std::invalid_argument("Negative arguments not allowed: " + std::to_string(a));
	} else {
		TimeCode result;
		result.t = static_cast<long long unsigned int>(this->t / a);
		return result;
	}
}

// comparisons
bool TimeCode::operator==(const TimeCode& other) const { return this->t == other.t; }
bool TimeCode::operator!=(const TimeCode& other) const { return this->t != other.t; }
bool TimeCode::operator<(const TimeCode& other) const { return this->t < other.t; }
bool TimeCode::operator<=(const TimeCode& other) const { return this->t <= other.t; }
bool TimeCode::operator>(const TimeCode& other) const { return this->t > other.t; }
bool TimeCode::operator>=(const TimeCode& other) const { return this->t >= other.t; }
