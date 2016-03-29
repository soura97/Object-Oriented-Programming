#include<iostream>
#include<math.h>
#include<string>
#include<stdlib.h>
using namespace std;
class Complex
{
	float real, img;
	string exps;
	string exps1,exps2;	
	int i;
	char sign;								//real and imaginary parts are decclared
	public:
	void getComplex()													//fucntion to input a complex number
	{
		
		scanf("%f%ci%f", &real,&sign,&img);	
		if(sign=='-')
			img=-img;
									//input the real & imaginary part
	}
	void display()														//display the complex number
	{
		printf("%f+i(%f)\n", real,img);
	}
	Complex operator+(Complex a2)  										// '+' operator overloaded to add two complex numbers
  	{  
  		Complex a;  
  		a.real=real+a2.real;  											//real parts are added
  		a.img=img+a2.img;  												//iaginary parts are added
  		return a;  														//the added complex number is returned
  	}  
	Complex operator-(Complex a2)  										// '-' operator overloaded to add two complex numbers
  	{  
  		Complex a;  
  		a.real=real-a2.real;  											//real parts are subtracted
  		a.img=img-a2.img;  												//imaginary parts are subtracted
  		return a;  														////the subtracted complex number is returned
  	} 
		
};

int main(void)
{
	Complex a,b,c,d;
	cout<<"Enter in a+ib format(no spaces)"<<"\nEnter first complex number"<<endl;
	a.getComplex();
	cout<<"Enter second complex number"<<endl;
	b.getComplex();
	cout<<"The first complex number is: ";
	a.display();
	cout<<"The second complex number is: ";
	b.display();
	c=a+b;
	cout<<"The added complex number is: "<<endl;
	c.display();
	d=a-b;
	cout<<"The subtracted complex number is: "<<endl;
	d.display();
	return 0;
}
