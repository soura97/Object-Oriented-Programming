#include <iostream>

using namespace std;
///class to store and manipulate TOLLTAX values
class TOLLTAX {
	int *cars, ///<member to hold array of cars tolled
		*toll, ///<member to hold array of toll tax collected
		total; ///<member to hold total toll tax collected
	public:
		static const int maxType = 20; ///<member to hold upper limit of car types
		///constructor to initialize data members and validate class invariants
		TOLLTAX() : cars{new int[maxType]}, toll{new int[maxType]}, total{0} {
			for(int i = 0; i < maxType; ++i) {
				cars[i] = 0;
				toll[i] = 10 * i;
			}
		}
		///setter function for collecting toll
		void setToll(int i) {
			if((i < 0) || (i >= maxType))
				printf("Invalid input");
			cars[i]++;
			total += toll[i];
		}
		///getter function for collecting toll
		int getToll(int i) {
			if((i < 0) || (i >= maxType))
				printf("Invalid input");
			return cars[i] * toll[i];
		}
		///getter function for total
		int getTotal() {
			return total;
		}
};

void collectToll(TOLLTAX& taxer) {
	int wheels;
	cout << "Input number of wheels: ";
	cin >> wheels;
	if(!cin)
		printf("Invalid input");
	taxer.setToll(wheels);
}

void viewToll(TOLLTAX& taxer) {
	int wheels;
	cout << "Input number of wheels: ";
	cin >> wheels;
	if(!cin)
		printf("Invalid input");
	cout << "Toll collected for " << wheels << " wheelers is Rs " << taxer.getToll(wheels) << endl;
}

void viewTotal(TOLLTAX& taxer) {
	cout << "Total toll collected is Rs " << taxer.getTotal() << endl;
}
int main() {
	int c;
	TOLLTAX taxer;
	cout << endl << "MENU:\n\nOperation Codes" << endl << endl << "0 Exit" << endl
		<< "1 Collect toll for a vehicle" << endl
		<< "2 Get toll collected for a vehicle type" << endl
		<< "3 Get total toll collected" << endl;
	do {
		cout << endl << "Enter operation code: ";
		
			if(!(cin >> c))
				printf("Invalid input");
			switch(c) {
				case 0: cout << "Exiting program" << endl; break;
				case 1:	collectToll(taxer); break;
				case 2: viewToll(taxer); break;
				case 3: viewTotal(taxer); break;
				default: printf("Invalid input");
			}
		
		
	}	while(c);
	return 0;
}
