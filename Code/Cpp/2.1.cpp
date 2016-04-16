#include<string>
#include<iostream>
#include<cstdlib>
using namespace std;

class Coin
{
	int headcount=0, 		//member to store number of times head occurs
		flipcount=0, 		//member to store number of times coin is flipped to get 3 consecutive heads for once
		flipvalue=-1;

	public:
		int count,			//member to store number of times we get 3 consecutive  heads
			totalflip=0;     	//member to store number of times coin is flipped
		int avg;			//average of all the flips
		int flip()			//random function that determines head or tail
		{
			if(rand()%2==0)
				return 1;
			else
				return 0;
		}
		
		void result()			//function to keep flipping until 3 consecutive heads
		{
			while(headcount<3)
			{
				flipvalue=flip();
				if(flipvalue)
				{
					headcount++; flipcount++;
					cout<<"Heads"<<endl;
				}
				else
				{
					headcount=0;
					flipcount++;
					cout<<"Tails"<<endl;
				}
			}
			cout<<"It took "<<flipcount<<" flips to get 3 consecutive Heads"<<endl;
			count++;totalflip+=flipcount;headcount=0;flipcount=0;flipvalue=-1;
		}

};

int main(void)
{
	srand( (unsigned int)time(NULL) );
	Coin c;

	int choice;
	do {
		cout<<"Menu\n\n"<<"0 Exit"<<endl
			<<"1 Flip"<<endl
			<<"2 Show result"<<endl
			<<endl<<"Enter operation code : ";
			cin>>choice;
		switch(choice) {
				case 0:cout<<"Exiting program" << endl; break;
				case 1:
					c.result();break;
				case 2:
					float avg;
					avg=c.totalflip/c.count;
					cout<<"Total flips = "<<c.totalflip<<endl
						<<"Average = "<<avg<<endl<<endl;c.count=c.totalflip=0;break;
					
				}
	}while(choice);
	return 0;
}



