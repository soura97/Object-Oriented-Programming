#include <iostream>
#include <stdexcept>
#include <limits>
using namespace std;

class ARRAY {
	int *arr, 		//the array
		size; 		//size of the array
	public:
		//constrctor to initialise all data members and validate class invariants
		ARRAY(int len=1, int init=0) : arr{new int[len]}, size{len} {		
			for(int i = 0; i < size; i++)
				arr[i] = init;
		}
		//copy constructor to initialise another object
		ARRAY(const ARRAY &a) : arr{new int[a.size]}, size{a.size} {
			for(int i = 0; i < size; i++)
				arr[i] = a.arr[i];
		}
		//constructor to initialise only size of a raw array
		ARRAY(int *a, int l) : arr{new int[l]}, size{l} {
			for(int i = 0; i < size; i++)
				arr[i] = a[i];
		}
		//operator overloaded to add elements of two arrays
		ARRAY& operator+=(ARRAY& a) {
			if(a.size > size) {
				for(int i = 0; i < size; i++)
					a.arr[i] += arr[i];
				return a;
			}
			else {
				for(int i = 0; i < a.size; i++)
					arr[i] += a.arr[i];
				return *this;
			}
		}
		//operator overloaded to subtract elements of an array from another array
		ARRAY& operator-=(ARRAY& a) {
			if(a.size > size) {
				for(int i = 0; i < size; i++)
					a.arr[i] -= arr[i];
				return a;
			}
			else {
				for(int i = 0; i < a.size; i++)
					arr[i] -= a.arr[i];
				return *this;
			}
		}
		//operator overloaded to post add a constant number to all the array elements
		ARRAY& operator+=(int n) {
			for(int i = 0; i < size; i++)
				arr[i] += n;
			return *this;
		}
		//operator overloaded to to subtract a constant number from allarray elements
		ARRAY& operator-=(int n) {
			for(int i = 0; i < size; i++)
				arr[i] -= n;
			return *this;
		}
		//operator overloaded to multiply a constant number to all array elements
		ARRAY& operator*=(int n) {
			for(int i = 0; i < size; i++)
				arr[i] *= n;
			return *this;
		}
		//operator overloaded to divide a constant number from all array elements 
		ARRAY& operator/=(int n) {
			for(int i = 0; i < size; i++)
				arr[i] /= n;
			return *this;
		}
	        //copy constructor to initialise another object
		ARRAY& operator=(const ARRAY& a) {
			size = a.size;
			arr = new int[a.size];
			for(int i = 0; i < size; i++)
				arr[i] = a.arr[i];
			return *this;
		}
		//operator overloaded to access array elements
		int operator[](int i) {
			if((i < 1) || (i > size))
				throw invalid_argument("argument out of range");
			return arr[i-1];
		}
		//destructor to free space for object
		~ARRAY() {
			free(arr);
		}
		//friend function prototype to output array
		friend ostream& operator<<(ostream&, ARRAY);
};
//operator overloaded to add two arrays
ARRAY operator+(ARRAY a, ARRAY b) {
	return a += b;
}
//operator overloaded to subtract two arrays
ARRAY operator-(ARRAY a, ARRAY b) {
	return a -= b;
}
//operator overloaded to pre add a constant number to all the array elements
ARRAY operator+(int n, ARRAY a) {
	return a += n;
}
//operator overloaded to post add a constant number to all the array elements
ARRAY operator+(ARRAY a, int n) {
	return a += n;
}
//operator overloaded to subtract a constant number to all the array elements
ARRAY operator-(ARRAY a, int n) {
	return a -= n;
}
//operator overloaded to pre multiply a constant number to all the array elements
ARRAY operator*(int n, ARRAY a) {
	return a *= n;
}
//operator overloaded to post multiply a constant number to all the array elements
ARRAY operator*(ARRAY a, int n) {
	return a *= n;
}
//operator overloaded to divide a constant number to all the array elements
ARRAY operator/(ARRAY a, int n) {
	return a /= n;
}
//operator overloaded to output array
ostream& operator<<(ostream& out, ARRAY a) {
	for(int i = 0; i < a.size; ++i)
		out << a.arr[i] << " ";
	cout << endl;
	return out;
}
int main() {
	int c, *arr = new int[1]{0}, len, length = 1, temp;
	ARRAY array1{}, array2{};
	do {
		cout << endl << "MENU:" << endl << endl << "0 Exit" << endl
			<< "1 Creation" << endl
			<< "2 Assignment" << endl
			<< "3 Array operations" << endl
			<< "4 Constant operations" << endl
			<< "5 Print" << endl
			<< endl << "Enter operation code: ";
		try {
			if(!(cin >> c))
				throw invalid_argument("arguments of invalid type");
			switch(c) {
				case 0: cout << "Exiting program" << endl; break;
				case 1: cout << "1 Create an array" << endl
							<< "2 Create a raw array" << endl
							<< endl << "Enter operation code: ";
						if(!(cin >> c))
							throw invalid_argument("arguments of invalid type");
						switch(c) {
							case 1: cout << "Enter length of array and constant of initialization: ";
									if(!(cin >> len >> temp))
										throw invalid_argument("arguments of invalid type");
									array1 = ARRAY{len, temp};
									break;
							case 2: cout << "Enter length of raw array: ";
									if(!(cin >> length))
										throw invalid_argument("arguments of invalid type");
									arr = new int[length];
									cout << "Enter array elements: ";
									for(int i = 0; i < length; ++i) {
										if(!(cin >> temp))
											throw invalid_argument("arguments of invalid type");
										arr[i] = temp;
									}
									break;
						}
						break;
				case 2: cout << "1 Assign a raw array" << endl
							<< "2 Assign another array" << endl
							<< endl << "Enter operation code: ";
						if(!(cin >> c))
							throw invalid_argument("arguments of invalid type");
						switch(c) {
							case 1: array1 = ARRAY(arr, length); break;
							case 2: array2 = array1; break;
						}
						break;
				case 3: cout << "1 Preadd the other array" << endl
							<< "2 Postadd the other array" << endl
							<< "3 Presubtract the other array" << endl
							<< "4 Postsubtract the other array" << endl
							<< endl << "Enter operation code: ";
						if(!(cin >> c))
							throw invalid_argument("arguments of invalid type");
						switch(c) {
							case 1: array1 = array2 + array1; break;
							case 2: array1 = array1 + array2; break;
							case 3: array1 = array1 - array2; break;
							case 4: array1 = array2 - array1; break;
						}
						break;
				case 4: cout << "Enter a constant: ";
						if(!(cin >> temp))
							throw invalid_argument("arguments of invalid type");
						cout << "1 Preadd" << endl
							<< "2 Postadd" << endl
							<< "3 Postsubtract" << endl
							<< "4 Premultiply" << endl
							<< "5 Postmultiply" << endl
							<< "6 Postdivide" << endl
							<< endl << "Enter operation code: ";
						if(!(cin >> c))
							throw invalid_argument("arguments of invalid type");
						switch(c) {
							case 1: array1 = temp + array1; break;
							case 2: array1 = array1 + temp; break;
							case 3: array1 = array1 - temp; break;
							case 4: array1 = temp * array1; break;
							case 5: array1 = array1 * temp; break;
							case 6: array1 = array1 / temp; break;
						}
						break;
				case 5: cout << "1 Print array" << endl
							<< "2 Print other array" << endl
							<< endl << "Enter operation code: ";
						if(!(cin >> c))
							throw invalid_argument("arguments of invalid type");
						switch(c) {
							case 1: cout << array1; break;
							case 2: cout << array2; break;
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
