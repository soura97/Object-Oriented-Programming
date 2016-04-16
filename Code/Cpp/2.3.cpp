#include <iostream>
#include <cstdlib>
using namespace std;
 

struct node				//structure to define node of the priority queue linked list
{
	int priority;			//member to define priority of a node
	int info;			//member to store information of the node
	struct node *link;
};

class Priority_Queue			//class to define operations of a priority queue
{
        node *front;			//front node of the queue
   
    public:
        Priority_Queue()		//constructor to iniialise front node
        {
            front = NULL;
        }

        void push(int item, int priority)	//function to push a member in the queue
        {
            node *tmp, *q;
            tmp = new node;
            tmp->info = item;
            tmp->priority = priority;
            if (front == NULL || priority < front->priority)
            {
                tmp->link = front;
                front = tmp;
            }
            else
            {
                q = front;
                while (q->link != NULL && q->link->priority <= priority)
                    q=q->link;
                tmp->link = q->link;
                q->link = tmp;
            }
        }
        
        void pop()			//function to pop a member from the queue
        {
            node *tmp;
            if(front == NULL)
                cout<<"Queue Underflow\n";
            else
            {
                tmp = front;
                cout<<"Popped item is: "<<tmp->info<<endl;
                front = front->link;
                free(tmp);
            }
        }
       
        void display()			//function to display the contents of the queue
        {
            node *ptr;
            ptr = front;
            if (front == NULL)
                cout<<"Queue is empty\n";
            else
            {	cout<<"Queue is :\n";
                cout<<"Priority       Item\n";
                while(ptr != NULL)
                {
                    cout<<ptr->priority<<"                 "<<ptr->info<<endl;
                    ptr = ptr->link;
                }
            }
        }
};

int main()
{
    int choice, item, priority;
    Priority_Queue pq; 
    do
    {
       
        cout <<"1 Push"<<endl
            <<"2 Pop"<<endl
            <<"3 Display"<<endl
	    <<"4 Exit"<<endl;
        cout<<"Enter operation code : "; 
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Input the item to be added in the queue : ";
            cin>>item;
            cout<<"Enter its priority : ";
            cin>>priority;
            pq.push(item, priority);
            break;
        case 2:
            pq.pop();
            break;
        case 3:
            pq.display();
            break;
        case 4:cout<<"Exiting program"<<endl;
            break;
        default :
            cout<<"Wrong choice\n";
        }
    }
    while(choice != 4);
    return 0;
}
