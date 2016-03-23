#include <iostream>
#include <string>

using namespace std;
///class to store and manipulate TIME values
class TIME {
	int hours, ///<member to hold hours
		minutes, ///<member to hold minutes
		seconds; ///<member to hold seconds 
	public:
		static const int maxHours = 24, ///<member to hold upper limit of hours
				 maxMinutes = 60, ///<member to hold upper limit of minutes
				 maxSeconds = 60; ///<member to hold upper limit of seconds
		///constructor to initialize data members and validate class invariants
		TIME(int hr=0, int min=0, int sec=0) : hours{hr}, minutes{min}, seconds{sec} {
			if(!((hours < maxHours) && (minutes < maxMinutes) && (seconds < maxSeconds) && (hours >= 0) && (minutes >= 0) && (seconds >= 0))) 
			{
				hours = minutes = seconds = 0;
				printf("Invalid input");
			}
		}
		///getter function for hours
		int getHours() {
			return hours;
		}
		///getter function for minutes
		int getMinutes() {
			return minutes;
		}
		///getter function for seconds
		int getSeconds() {
			return seconds;
		}
		///member function to add minutes
		void addMinutes(int min) {
			minutes += min;
			hours += minutes / maxMinutes;
			minutes %= maxMinutes;
			hours %= maxHours;
		}
};

void get24(TIME t) {
	cout << "The time is " << t.getHours() << ":" << t.getMinutes() << ":" << t.getSeconds() << endl;
}

void get12(TIME t) {
	if(t.getHours() < TIME::maxHours / 2)
		cout << "The time is " << t.getHours() << ":" << t.getMinutes() << ":" << t.getSeconds() << " AM" << endl;
	else
		cout << "The time is " << t.getHours() - TIME::maxHours / 2 << ":" << t.getMinutes() << ":" << t.getSeconds() << " PM" << endl;
}

TIME set24() {
	cout << "Input Time: ";
	int hr, min, sec;
	
	if(!cin)
		printf("Invalid input");
	TIME t(hr, min, sec);
	return t;
}

TIME set12() {
	cout << "Input Time: ";
	int hr, min, sec;
	string ampm;
	
	if(!cin)
		printf("Invalid input");
	if((ampm == "AM") || (ampm == "am"))
		return TIME{hr, min, sec};
	else if((ampm == "PM") || (ampm == "pm"))
		return TIME{hr + 12, min, sec};
}

void addTime(TIME& t) {
	cout << "how much time would you like to add? ";
	int min;
	if(!(cin >> min) || (min < 0))
		printf("Invalid input");
	t.addMinutes(min);
}
int main() {
	int c;
	TIME time;
	cout << endl << "MENU:" << endl << endl << "0 Exit" << endl
		<< "1 Input a time in 24 hour format" << endl
		<< "2 Input a time in 12 hour format" << endl
		<< "3 Display a time in 24 hour format" << endl
		<< "4 Display a time in 12 hour format" << endl
		<< "5 Add minutes to time" << endl << endl;
	do {
		cout << endl << "Enter: ";
	
			if(!(cin >> c))
				printf("Invalid input\n");
			switch(c) {
				case 0: cout << "Exiting program" << endl; break;
				case 1:	time = set24(); break;
				case 2: time = set12(); break;
				case 3: get24(time); break;
				case 4: get12(time); break;
				case 5: addTime(time); break;
				default: printf("Invalid input");
			}
		
	
	}	while(c);
	return 0;
}

