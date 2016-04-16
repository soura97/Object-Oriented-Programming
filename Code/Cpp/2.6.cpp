#include <iostream>
#include <stdexcept>
#include <limits>
using namespace std;
///class to store and manipulate STRING values
class STRING {
	char *str; ///<member to hold array of characters
	int size, ///<member to hold size of array
		*copy; ///<member to hold number of copies of array
	public:
		///constructor to initialize data members and validate class invariants
		STRING(int len=1, char init='\0') : str{new char[len]}, size{len}, copy{new int} {
			*copy = 1;
			for(int i = 0; i < size; ++i)
				str[i] = init;
		}
		///copy constructor to initialize data members and validate class invariants
		STRING(const STRING &a) : str{a.str}, size{a.size}, copy{a.copy} {
			(*copy)++;
			for(int i = 0; i < size; i++)
				str[i] = a.str[i];
		}
		///constructor to initialize data members and validate class invariants from raw string
		STRING(char *a, int len) : str{new char[len]}, size{len}, copy{new int} {
			*copy = 1;
			for(int i = 0; i < size; i++)
				str[i] = a[i];
		}
		///member operator overload to add a string
		STRING& operator+=(STRING& a) {
			char *ptr = new char[size + a.size];
			int i;
			for(i = 0; i < size; i++)
				ptr[i] = str[i];
			for(i = size; i < size + a.size; i++)
				ptr[i] = a.str[i - size];
			size += a.size;
			str = ptr;
			return *this;
		}
		///member operator overload to assign a string
		STRING& operator=(const STRING& a) {
			(*copy)--;
			size = a.size;
			str = new char[size];
			copy = a.copy;
			(*copy)++;
			for(int i = 0; i < size; i++)
				str[i] = a.str[i];
			return *this;
		}
		///member operator overload to check for equality
		bool operator==(const STRING& a) {
			if(size != a.size)
				return false;
			int i;
			for(i = 0; i < size; ++i)
				if(str[i] != a.str[i])
					break;
			if(i < size)
				return false;
			return true;
		}
		///member operator overload to compare
		bool operator<(const STRING& a) {
			int i;
			for(i = 0; (i < size) && (i < a.size); ++i)
				if(str[i] != a.str[i])
					break;
			if((i < size) && (i < a.size))
				return str[i] < a.str[i];
			return size < a.size;
		}
		///member operator overload to compare
		bool operator>(const STRING& a) {
			int i;
			for(i = 0; (i < size) && (i < a.size); ++i)
				if(str[i] != a.str[i])
					break;
			if((i < size) && (i < a.size))
				return str[i] > a.str[i];
			return size > a.size;
		}
		///member operator overload to access by index
		char operator[](int i) {
			if((i < 1) || (i > size))
				throw invalid_argument("argument out of range");
			return str[i-1];
		}
		///destructor to free memory allocated on freestore
		~STRING() {
			(*copy)--;
			if((*copy) == 0)
				free(str);
		}
		friend ostream& operator<<(ostream&, STRING);
};
///operator overload to check for inequality
bool operator!=(STRING& a, STRING& b) {
	return !(a == b);
}
///operator overload to compare
bool operator<=(STRING& a, STRING& b) {
	return !(a > b);
}
///operator overload to compare
bool operator>=(STRING& a, STRING& b) {
	return !(a < b);
}
///operator overload to add a string
STRING operator+(STRING a, STRING b) {
	return a += b;
}
///friend operator overload to output a string
ostream& operator<<(ostream& out, STRING a) {
	for(int i = 0; i < a.size; ++i)
		out << a.str[i];
	return out;
}int main() {
	int c, len, length = 1;
	char *str = new char[1]{'\0'}, temp;
	STRING string1{}, string2{};
	do {
		cout << endl << "MENU:" << endl << endl << "0 Exit" << endl
			<< "(1) Creation" << endl
			<< "(2) Assignment" << endl
			<< "(3) Addition operations" << endl
			<< "(4) Comparison operations" << endl
			<< "(5) Print" << endl
			<< endl << "Enter operation code: ";
		try {
			if(!(cin >> c))
				throw invalid_argument("arguments of invalid type");
			switch(c) {
				case 0: cout << "Exiting program" << endl; break;
				case 1: cout << "(1) Create a string" << endl
							<< "(2) Create a raw string" << endl
							<< endl << "Enter operation code: ";
						if(!(cin >> c))
							throw invalid_argument("arguments of invalid type");
						switch(c) {
							case 1: cout << "Enter length of string and constant of initialization: ";
									if(!(cin >> len >> temp))
										throw invalid_argument("arguments of invalid type");
									string1 = STRING{len, temp};
									break;
							case 2: cout << "Enter length of raw string: ";
									if(!(cin >> length))
										throw invalid_argument("arguments of invalid type");
									str = new char[length];
									cout << "Enter string elements: ";
									for(int i = 0; i < length; ++i) {
										if(!(cin >> temp))
											throw invalid_argument("arguments of invalid type");
										str[i] = temp;
									}
									break;
						}
						break;
				case 2: cout << "(1) Assign a raw string" << endl
							<< "(2) Assign another string" << endl
							<< endl << "Enter operation code: ";
						if(!(cin >> c))
							throw invalid_argument("arguments of invalid type");
						switch(c) {
							case 1: string1 = STRING(str, length); break;
							case 2: string2 = string1; break;
						}
						break;
				case 3: cout << "(1) Preadd the other string" << endl
							<< "(2) Postadd the other string" << endl
							<< endl << "Enter operation code: ";
						if(!(cin >> c))
							throw invalid_argument("arguments of invalid type");
						switch(c) {
							case 1: string1 = string2 + string1; break;
							case 2: string1 = string1 + string2; break;
						}
						break;
				case 4: cout << "Check if: " << endl
							<< "(1) Equal to" << endl
							<< "(2) Less than" << endl
							<< "(3) Greater than" << endl
							<< "(4) Less than or equal to" << endl
							<< "(5) Greater than or equal to" << endl
							<< endl << "Enter operation code: ";
						if(!(cin >> c))
							throw invalid_argument("arguments of invalid type");
						switch(c) {
							case 1:	if(string1 == string2) cout << "yes" << endl; else cout << "no" << endl; break;
							case 2:	if(string1 < string2) cout << "yes" << endl; else cout << "no" << endl; break;
							case 3:	if(string1 > string2) cout << "yes" << endl; else cout << "no" << endl; break;
							case 4:	if(string1 <= string2) cout << "yes" << endl; else cout << "no" << endl; break;
							case 5:	if(string1 >= string2) cout << "yes" << endl; else cout << "no" << endl; break;
						}
						break;
				case 5: cout << "(1) Print string" << endl
							<< "(2) Print other string" << endl
							<< endl << "Enter operation code: ";
						if(!(cin >> c))
							throw invalid_argument("arguments of invalid type");
						switch(c) {
							case 1: cout << string1 << endl; break;
							case 2: cout << string2 << endl; break;
						}
						break;
				default: throw invalid_argument("arguments of invalid type");
			}
		}
		catch(invalid_argument e) {
			cin.clear();
			cout << e.what() << ": try again" << endl;
		}
	}	while(c);
	return 0;
}
