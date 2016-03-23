#include <iostream>
#include <string>
#include<vector>
#include <cstdlib>
#include <stdexcept>
#include <limits>
#include <ctime>
using namespace std;
///class to store and manipulate STUDENT values
class STUDENT {
	int roll, ///<member to hold roll number
		*marks; ///<member to hold marks obtained
	
	string name, ///<member to hold name
		course, ///<member to hold course
		admission; ///<member to hold time of admission
	bool validMarks; ///<member to hold validity of marks
	public:
		static const int maxSubjects = 5; ///<member to hold maximum number of subjects
		 
		///constructor to initialize data members and validate class invariants
		STUDENT(int rl=0, string nm=string{}, string cr=string{}) : roll{rl}, marks{new int[maxSubjects]}, name{nm}, course{cr}, validMarks{false} {
			for(int i = 0; i < maxSubjects; ++i)
				marks[i] = 0;
			time_t t = time(0);
			admission = ctime(&t);
		}
		///getter function for roll
		int getRoll() {
			return roll;
		}
		///getter function for marks
		int* getMarks() {
			return marks;
		}
		///setter function for marks
		void setMarks(int *mks) {
			validMarks = true;
			for(int i = 0; i < maxSubjects; ++i)
				marks[i] = mks[i];
		}
		///getter function for setMarks
		bool getValidMarks() {
			return validMarks;
		}
		///getter function name
		string getName() {
			return name;
		}
		///getter function for course
		string getCourse() {
			return course;
		}
		///getter function for admission
		string getAdmission() {
			return admission;
		}
};
///class to store and manipulate BATCH values
class BATCH {
	int students, ///<member to hold students admitted
		capacity; ///<member to hold student capacity
	STUDENT* list; ///<member to hold array of students
	public:
		///constructor to initialize data members and validate class invariants
		BATCH(int cap=10) : students{0}, capacity{cap}, list{new STUDENT[cap]} {
		}
		///member function to admit a student
		void admission(string name, string course) {
			if(students == capacity)
				throw invalid_argument("capacity exceeded");
			list[students] = STUDENT{students + 1, name, course};
			students++;
		}
		///member function to examine student
		void examination(int roll, int *marks) {
			list[roll - 1].setMarks(marks);
		}
		///member function to check student roll validity
		bool checkStudent(int roll) {
			return (roll > 0) && (roll <= students);
		}
		///getter function for students
		int getStudents() {
			return students;
		}
		///getter function for list
		STUDENT* getList() {
			return list;
		}
};
///helper function to input and admit a student to batch
void admitStudent(BATCH& batch) {
	string name, course;
	cout << "enter name of student: ";
	cin.ignore();
	getline(cin,name);
	cout << "enter course of admission: ";
	cin >> course;
	batch.admission(name, course);	
}
///helper function to input and examine a student in batch
void prepareMarksheet(BATCH& batch) {
	int roll, *marks = new int[STUDENT::maxSubjects];
	cout << "enter roll: ";
	if(!(cin >> roll) || !batch.checkStudent(roll))
		printf("Invalid input");
	cout << "enter marks in " << STUDENT::maxSubjects << " subjects <Math, Humanities, Physics, Drawing, Lab> respectively: ";
	for(int i = 0; i < STUDENT::maxSubjects; ++i)
		if(!(cin >> marks[i]) || marks[i]>100)
			printf("Invalid input");
	batch.examination(roll, marks);
}
///helper function to output student report
void printReport(STUDENT& student) {
	cout << "name: " << student.getName() << endl
		<< "roll: " << student.getRoll() << endl
		<< "course: " << student.getCourse() << endl
		<< "admission date: " << student.getAdmission()
		<< "marks: ";
	if(!student.getValidMarks())
		cout << "not set" << endl;
	else {
		int *marks = student.getMarks();
		
			cout <<"\n\nMath\t\t" <<marks[0] <<endl
				<<"Humanities\t"<<marks[1]<<endl
				<<"Physics\t\t"<<marks[2]<<endl
				<<"Drawing\t\t"<<marks[3]<<endl
				<<"Lab\t\t"<<marks[4]<<endl
				<<"\n\nSGPA\t\t"<<((float)(marks[0]+marks[1]+marks[2]+marks[3]+marks[4])/5)/10<<endl;
		cout << endl;
	}
}
///helper function to output report of student in batch
void printStudentReport(BATCH& batch) {
	int roll;
	cout << "enter roll: ";
	if(!(cin >> roll) || !batch.checkStudent(roll))
		printf("Invalid roll");
	STUDENT* list = batch.getList();
	printReport(list[roll - 1]);
}
///helper function to output report of batch
void printBatchReport(BATCH& batch) {
	STUDENT* list = batch.getList();
	for(int i = 0; i < batch.getStudents(); ++i) {
		printReport(list[i]);
		cout << endl;
	}
}
int main() {
	int c;
	BATCH batch;
	cout << endl << "MENU:" << endl << endl << "0 Exit" << endl
		<< "1 Create a new batch" << endl
		<< "2 Admit a student" << endl
		<< "3 Prepare student marksheet" << endl
		<< "4 Print student report" << endl
		<< "5 Print batch report" << endl;
	do {
		cout << endl << "Enter operation code: ";
		
			if(!(cin >> c))
				printf("Invalid input");
			switch(c) {
				case 0: cout << "terminating program" << endl; break;
				case 1: int n; cout << "enter batch size: ";
						if(!(cin >> n))  printf("Invalid input");
						batch = BATCH{n}; break;
				case 2:	admitStudent(batch);
						cout << "roll no: " << batch.getStudents() << endl; break;
				case 3: prepareMarksheet(batch); break;
				case 4: printStudentReport(batch); break;
				case 5: printBatchReport(batch); break;
				default: printf("Invalid input");
			}
		
	}	while(c);
	return 0;
}
