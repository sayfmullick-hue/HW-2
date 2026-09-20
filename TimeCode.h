#ifndef TIMECODE_H
#define TIMECODE_H

#include <iostream> 

using namespace std;

class TimeCode {
    public:
        TimeCode(unsigned int hr = 0, unsigned int min = 0, unsigned long long int sec = 0);
        TimeCode(const TimeCode& tc);
        ~TimeCode(){};

        void SetHours(unsigned int hours);
        void SetMinutes(unsigned int minutes);
        void SetSeconds(unsigned int seconds);

        void reset();

        unsigned int GetHours() const;
        unsigned int GetMinutes() const;
        unsigned int GetSeconds() const;

        unsigned long long int GetTimeCodeAsSeconds() const { return t; };
        void GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const;
        static unsigned long long int ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec);

        string ToString() const;

        TimeCode operator+(const TimeCode& other) const;
        TimeCode operator-(const TimeCode& other) const;
        TimeCode operator*(double a) const;
        TimeCode operator/(double a) const;

        bool operator == (const TimeCode& other) const;
        bool operator != (const TimeCode& other) const;

        bool operator < (const TimeCode& other) const;
        bool operator <= (const TimeCode& other) const;

        bool operator > (const TimeCode& other) const;
        bool operator >= (const TimeCode& other) const;

    private:
        unsigned long long int t = 0;
};

#endif
