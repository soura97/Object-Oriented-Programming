#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <algorithm>

class DATE
{
    int day;               
    int mon;               
    int year;              
    char date[10];
public:
    void get_values(void);
    void disp_details(void);
    int operator - (const DATE&) const;
    DATE operator + (int) const;
    void operator = (const DATE&);
    char* ret_str(void);
};


void DATE::get_values(void)
{
    scanf("%d-%d-%d", &day, &mon, &year);
}


void DATE::disp_details(void)
{
    std::cout << day << "-" << mon << "-" << year <<"\n";
}


int DATE::operator - (const DATE& d) const
{
    return (year - d.year) * 365
         + (mon - d.mon) * 30
         + (day - d.day);
}


DATE DATE::operator + (int period) const
{
    DATE d2;
    d2.day  = day + period > 30? day + period - 30: day + period;
    d2.mon  = day + period > 30? mon + 1: mon;
    d2.year = d2.mon > 12? year + 1: year;
    d2.mon  = d2.mon > 12? d2.mon - 12: d2.mon;
    return d2;
}

void DATE::operator = (const DATE& d2)
{
    day  = d2.day;
    mon  = d2.mon;
    year = d2.year;
}


char* DATE::ret_str(void)
{
    char d[5], m[5], y[5];
    sprintf(d, "%d", day);
    sprintf(m, "%d", mon);
    sprintf(y, "%d", year);
    strcpy(date, d);
    strcat(date, "-");
    strcat(date, m);
    strcat(date, "-");
    strcat(date, y);
    return date;
}

class TRANSACTION
{
    char transaction_id[50];
    char card_num[50];
    char acc_num[50];
    int book_or_journal;
    int student_or_faculty;
    int issue_period;
    DATE issue_date, return_date;
    int fine;
    bool returned;
    void gen_random(char *, int);
public:
    void get_values(char*, char*, int);
    void disp_details_issue(void);
    void disp_details_ret(int);
    char* ret_identity(void);
    int ret_book_or_journal(void);
    int ret_student_or_faculty(void);
    char* ret_card_num(void);
    char* ret_acc_num(void);
    bool ret_returned(void);
    void alter_returned(bool);
    DATE ret_return_date(void);
};

void TRANSACTION::gen_random(char *s, int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}
void TRANSACTION::get_values(char* key1, char* key2, int val)
{
    strcpy(card_num, key1);
    strcpy(acc_num, key2);
    gen_random(transaction_id, 5);
    book_or_journal = val;
    returned = false;
    issue_period = 15;
    std::cout << "Enter the issue date (dd-mm-yyyy): ";
    issue_date.get_values();
    return_date = issue_date + issue_period;
}

void TRANSACTION::disp_details_issue(void)
{
    std::cout<<"Transaction ID:  "<<transaction_id;
    std::cout<<"\nCard no.:  "<<card_num;
    std::cout<<"\nAccession no.:  "<<acc_num;
    std::cout<<"\nIssue Date:  "<<issue_date.ret_str();
    std::cout<<"\nReturn Date: "<<return_date.ret_str();
}

void TRANSACTION::disp_details_ret(int charge)
{
    std::cout<<"Transaction ID:  "<<transaction_id;
    std::cout<<"\nCard no.:  "<<card_num;
    std::cout<<"\nAccession no.:  "<<acc_num;
    std::cout<<"\nFine:  "<<fine;
}

DATE TRANSACTION::ret_return_date(void) { return return_date; }

char* TRANSACTION::ret_identity(void) { return transaction_id; }

int TRANSACTION::ret_book_or_journal(void) { return book_or_journal; } 

int TRANSACTION::ret_student_or_faculty(void) { return student_or_faculty; }

char* TRANSACTION::ret_card_num(void) { return card_num; }

char* TRANSACTION::ret_acc_num(void) { return acc_num; }

bool TRANSACTION::ret_returned(void) { return returned; }

void TRANSACTION::alter_returned(bool val) { returned = val; }

class BOOK
{
protected:
    char name[50];                  
    char author_name[50];           
    char acc_num[50];               
    int quantity;                   
public:
    void get_values(char*);
    void disp_details(void);
    char* ret_identity(void);
    void alter_quantity(int);
    bool is_possible(int);
};


void BOOK::get_values(char* val)
{
    std::cout << "Enter name: ";
    std::cin.getline(name, 50);
    std::cout << "Enter author's name: ";
    std::cin.getline(author_name, 50);
    strcpy(acc_num, val);
    std::cout << "Enter quantity: ";
    std::cin >> quantity;
}


void BOOK::disp_details(void)
{
    std::cout<<"Name:  "<<name;
   	std::cout<<"\nAuthor:  "<<author_name;
   	std::cout<<"\nAccession no.:  "<<acc_num;
   	std::cout<<"\nQuantity:  "<<quantity;
}


char* BOOK::ret_identity(void)
{
    return acc_num;
}


void BOOK::alter_quantity(int val)
{
    quantity += val;
}


bool BOOK::is_possible(int val)
{
    if(quantity + val >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

class JOURNAL: public BOOK
{
    int issue_num;                  
    DATE publish_date;              
    int vol_num;                   
public:
    void get_values(char*);
    void disp_details(void);
};


void JOURNAL::get_values(char* val)
{
    BOOK::get_values(val);
    std::cout << "Enter issue number: ";
    std::cin >> issue_num;
    std::cout << "Enter publish date (dd-mm-yyyy): ";
    publish_date.get_values();
    std::cout << "Enter volume number: ";
    std::cin >> vol_num;
}


void JOURNAL::disp_details(void) 
{
    std::cout<<"Name:  "<<name;
    std::cout<<"\nAuthor:  "<<author_name;
    std::cout<<"\nAcession no.:  "<<acc_num;
    std::cout<<"\nQuantiy:  "<<quantity;
    std::cout<<"\nIssue no.  "<<issue_num;
    std::cout<<"\nVolume no.:  "<<vol_num;
}

class MEMBER
{
    char name[50];                  
    char card_num[50];           
    int category;                
    int count, max_count;        
    int charge;                  
public:
    void get_values(char*);
    void disp_details(void);
    char* ret_identity(void);
    void alter_count(int);
    bool is_possible(int);
    int calculate_charge(int);
};


void MEMBER::get_values(char* val)
{
    std::cout << "Enter name: ";
    std::cin.getline(name, 50);
    strcpy(card_num, val);
    std::cout << "Choose option\n<0> Student\t<1> Faculty\n";
    std::cin >> category;
    max_count = category == 0? 2: 10;
    charge = category == 0? 1: 0;
    count = 0;
}


void MEMBER::disp_details(void)
{
    std::cout<<"Name:  "<<name;
    std::cout<<"\nCard no.: "<<card_num;
    std::cout<<"\nCategory:  ";
    if(category == 0)
    	std::cout<<"Student";
    else std::cout<<"Faculty";
    std::cout<<"\nBooks Issued:  "<<count;
}


char* MEMBER::ret_identity(void)
{
    return card_num;
}


void MEMBER::alter_count(int val)
{
    count += val;
}


bool MEMBER::is_possible(int val)
{
    if(count + val < 0 || count + val > max_count)
    {
        return false;
    }
    else
    {
        return true;
    }
}


int MEMBER::calculate_charge(int day)
{
    if(day > 0)
        return charge * day;
    return 0;
}
class LIBRARY
{
    char book_list[50];                 
    char journal_list[50];              
    char member_list[50];              
    char register_list[50];            
    int search(char*, char*, int);     
public:
    LIBRARY(void);
    void add_book(void);
    void add_journal(void);
    void add_member(void);
    void issue_book(void);
    void issue_journal(void);
    void show_details(void);
    void ret_(void);
};


LIBRARY::LIBRARY(void)
{
    strcpy(book_list, "Book.dat");
    strcpy(journal_list, "Journal.dat");
    strcpy(member_list, "Member.dat");
    strcpy(register_list, "Register.dat");
}


int LIBRARY::search(char *file, char* key, int option)
{
    
	std::fstream fp;
	fp.open(file, std::ios::in | std::ios::binary);
	int found = -1, count = -1;
	switch (option) {
	    case 1:                
        {
            BOOK temp;
            while(fp.read((char *) &temp, sizeof(temp)))
            {
        		count++;
        		if(strcmp(temp.ret_identity(), key) == 0)
                {
        			found = count;
        			break;
        		}
        	}
            break;
        }
        case 2:               
        {
            JOURNAL temp;
            while(fp.read((char *) &temp, sizeof(temp)))
            {
        		count++;
        		if(strcmp(temp.ret_identity(), key) == 0)
                {
        			found = count;
        			break;
        		}
        	}
            break;
        }
        case 3:               
        {
            MEMBER temp;
            while(fp.read((char *) &temp, sizeof(temp)))
            {
        		count++;
        		if(strcmp(temp.ret_identity(), key) == 0)
                {
        			found = count;
        			break;
        		}
        	}
            break;
        }
        default:
            break;
	}
	return found;
}

void LIBRARY::show_details(void)
{
    int choice;
    std::cout << "<1> Book  <2> Journal  <3> Member\nChoice: ";
    std::cin >> choice;
    std::cin.ignore();
    switch(choice)
    {
        case 1:
        {
            char acc_num[50];
            std::cout << "Accession no.: ";
            std::cin >> acc_num;
            int pos_b = search(book_list, acc_num, choice);
            if(pos_b == -1)
            {
                std::cout << "No such record found.\n";
                break;
            }
            std::fstream fp_b;
            BOOK temp_b;
            fp_b.open(book_list, std::ios::in | std::ios::binary);
            fp_b.seekg(pos_b * sizeof(temp_b), std::ios::beg);
            // reads the BOOK object
            fp_b.read((char *)&temp_b, sizeof(temp_b));
            temp_b.disp_details();
            fp_b.close();
            break;
        }
        case 2:
        {
            char acc_num[50];
            std::cout << "Accession no.: ";
            std::cin >> acc_num;
            int pos_j = search(journal_list, acc_num, choice);
            if(pos_j == -1)
            {
                std::cout << "No such record found.\n";
                break;
            }
            std::fstream fp_j;
            JOURNAL temp_j;
            fp_j.open(journal_list, std::ios::in | std::ios::binary);
            fp_j.seekg(pos_j * sizeof(temp_j), std::ios::beg);
            // reads the BOOK object
            fp_j.read((char *)&temp_j, sizeof(temp_j));
            temp_j.disp_details();
            fp_j.close();
            break;
        }
        case 3:
        {
            char card_num[50];
            std::cout << "Card no.: ";
            std::cin >> card_num;
            int pos_m = search(member_list, card_num, choice);
            if(pos_m == -1)
            {
                std::cout << "No such record found.\n";
                break;
            }
            std::fstream fp_m;
            MEMBER temp_m;
            fp_m.open(member_list, std::ios::in | std::ios::binary);
            fp_m.seekg(pos_m * sizeof(temp_m), std::ios::beg);
            // reads the BOOK object
            fp_m.read((char *)&temp_m, sizeof(temp_m));
            temp_m.disp_details();
            fp_m.close();
            break;
        }
        default:
            break;
    }
}
// Adds book to the list
void LIBRARY::add_book(void)
{
	char acc_num[50];
	std::cout << "Accession number: ";
    std::cin.getline(acc_num, 50);
    // Checks with the accession number if already registered
	int pos = search(book_list, acc_num, 1);
	if(pos != -1)              // Already registered
    {
        // Opening the book list file in update mode
        std::fstream fp;
        BOOK temp;
		std::cout << "The entered book already exists. Change quantity instead.\n";
        fp.open(book_list, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
        fp.seekg(pos * sizeof(temp), std::ios::beg);
        // Reads the BOOK object,
        fp.read((char *)&temp, sizeof(temp));
        // changes its quantity
        int quantity;
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        temp.alter_quantity(quantity);
        temp.disp_details();
        fp.seekp(pos * sizeof(temp), std::ios::beg);
        // and update the book list with new quantity
        fp.write((char *)&temp, sizeof(temp));
        fp.close();
		return;
	}
    // Creates a BOOK object to save the new book in the book list  file
    std::fstream fp;
    BOOK temp;
	temp.get_values(acc_num);
    // Opening the file in output and append mode
	fp.open(book_list, std::ios::out | std::ios :: app | std::ios :: binary);
    // and writes the new book object
	fp.write((char *) &temp, sizeof(temp));
	std::cout << "Your book was successfully updated into the list.\n";
    temp.disp_details();
	fp.close();
}

// Adds journal
void LIBRARY::add_journal(void)
{
	char acc_num[50];
	std::cout << "Accession number: ";
    std::cin.getline(acc_num, 50);
    // Checks with the accession number if already registered
	int pos = search(journal_list, acc_num, 2);
	if(pos != -1)              // Already registered
    {
        // Opening the book list file in update mode
        std::fstream fp;
        JOURNAL temp;
		std::cout << "The entered journal already exists. Change quantity instead.\n";
        fp.open(journal_list, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
        fp.seekg(pos * sizeof(temp), std::ios::beg);
        // Reads the BOOK object,
        fp.read((char *)&temp, sizeof(temp));
        int quantity;
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        // changes its quantity
        temp.alter_quantity(quantity);
        temp.disp_details();
        fp.seekp(pos * sizeof(temp), std::ios::beg);
        // and update the book list with new quantity
        fp.write((char *)&temp, sizeof(temp));
        fp.close();
		return;
	}
    // Creates a BOOK object to save the new book in the book list  file
    std::fstream fp;
    JOURNAL temp;
	temp.get_values(acc_num);
    // Opening the file in output and append mode
	fp.open(journal_list, std::ios::out | std::ios::app | std::ios::binary);
    // and writes the new book object
	fp.write((char *) &temp, sizeof(temp));
	std::cout << "Your journal was successfully updated into the list.\n";
    temp.disp_details();
	fp.close();
}

// Adds member
void LIBRARY::add_member(void) {
	char card_num[50];
	std::cout << "Card number: ";
    std::cin.getline(card_num, 50);
    // Checks if the member is already registered
	int pos = search(member_list, card_num, 3);
	if(pos != -1) {
        std::cout << "The entered member already exists.\n";
		return;
	}
    // Opening the file and creating a new MEMBER object
    std::fstream fp;
    MEMBER temp;
	temp.get_values(card_num);
    // Opening the file in output and update mode
	fp.open(member_list, std::ios::out | std::ios::app | std::ios::binary);
    // Write the new object back to the file
	fp.write((char *) &temp, sizeof(temp));
	std::cout << "Member was successfully updated into the list.\n";
    temp.disp_details();
	fp.close();
}

// Issues book
void LIBRARY::issue_book(void)
{
    char card_num[50], acc_num[50];
    std::cout << "Enter card number: ";
    std::cin.getline(card_num, 50);
    // Checks if card number exists in the database
    int pos_m = search(member_list, card_num, 3);
    if(pos_m == -1)         // Does not exist
    {
        std::cout << "The entered member does not exist. Try adding instead.\n";
		return;
    }
    std::cout << "Enter accession number: ";
    std::cin.getline(acc_num, 50);
    // Checks if acc number exists in the database
    int pos_b = search(book_list, acc_num, 1);
    if(pos_b == -1)         // Does not exist
    {
        std::cout << "The entered book does not exist. Try adding instead.\n";
		return;
    } 
    // Opens member list file and MEMBER object
    std::fstream fp_m;
    MEMBER temp_m;
    fp_m.open(member_list, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
    fp_m.seekg(pos_m * sizeof(temp_m), std::ios::beg);
    // reads the MEMBER object
    fp_m.read((char *)&temp_m, sizeof(temp_m));
    // Opens book list file and BOOK object
    std::fstream fp_b;
    BOOK temp_b;
    fp_b.open(book_list, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
    fp_b.seekg(pos_b * sizeof(temp_b), std::ios::beg);
    // reads the BOOK object
    fp_b.read((char *)&temp_b, sizeof(temp_b));
    if(!temp_m.is_possible(1) || !temp_b.is_possible(-1))
    {
        std::cout << "Issuing not possible!\n";
    }
    else
    {
        // Change count and quantity after transaction
        temp_m.alter_count(1);
        temp_b.alter_quantity(-1);
        fp_m.seekp(pos_m * sizeof(temp_m), std::ios::beg);
        // and write it back into the file
        fp_m.write((char *)&temp_m, sizeof(temp_m));
        fp_b.seekp(pos_b * sizeof(temp_b), std::ios::beg);
        fp_b.write((char *)&temp_b, sizeof(temp_b));
        // Creates TRANSACTION object
        TRANSACTION temp_tr;
        temp_tr.get_values(card_num, acc_num, 0);
        std::fstream fp_tr;
        fp_tr.open(register_list, std::ios::out | std::ios::app | std::ios::binary);
        // and writes it to the register file
        fp_tr.write((char *)&temp_tr, sizeof(temp_tr));
        fp_tr.close();
        temp_tr.disp_details_issue();
    }
    fp_m.close();
    fp_b.close();
}

// Issues journal
void LIBRARY::issue_journal(void)
{
    char card_num[50], acc_num[50];
    std::cout << "Enter card number: ";
    std::cin.getline(card_num, 50);
    // Checks if card number exists in the database
    int pos_m = search(member_list, card_num, 3);
    if(pos_m == -1)         // Does not exist
    {
        std::cout << "The entered member does not exist. Try adding instead.\n";
		return;
    }
    std::cout << "Enter accession number: ";
    std::cin.getline(acc_num, 50);
    // Checks if acc number exists in the database
    int pos_j = search(journal_list, acc_num, 2);
    if(pos_j == -1)         // Does not exist
    {
        std::cout << "The entered journal does not exist. Try adding instead.\n";
		return;
    }
    // Opens member list file and MEMBER object
    std::fstream fp_m;
    MEMBER temp_m;
    fp_m.open(member_list, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
    fp_m.seekg(pos_m * sizeof(temp_m), std::ios::beg);
    // reads the MEMBER object
    fp_m.read((char *)&temp_m, sizeof(temp_m));
    // Opens journal list file and JOURNAL object
    std::fstream fp_j;
    JOURNAL temp_j;
    fp_j.open(journal_list, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
    fp_j.seekg(pos_j * sizeof(temp_j), std::ios::beg);
    // reads the JOURNAL object
    fp_j.read((char *)&temp_j, sizeof(temp_j));
    if(!temp_m.is_possible(1) || !temp_j.is_possible(-1))
    {
        std::cout << "Issuing not possible!\n";
    }
    else
    {
        // Change count and quantity after transaction
        temp_m.alter_count(1);
        temp_j.alter_quantity(-1);
        fp_m.seekp(pos_m * sizeof(temp_m), std::ios::beg);
        // and write it back into the file
        fp_m.write((char *)&temp_m, sizeof(temp_m));
        fp_j.seekp(pos_j * sizeof(temp_j), std::ios::beg);
        fp_j.write((char *)&temp_j, sizeof(temp_j));
        // Creates TRANSACTION object
        TRANSACTION temp_tr;
        temp_tr.get_values(card_num, acc_num, 1);
        std::fstream fp_tr;
        fp_tr.open(register_list, std::ios::out | std::ios::app | std::ios::binary);
        // and writes it to the register file
        fp_tr.write((char *)&temp_tr, sizeof(temp_tr));
        fp_tr.close();
        temp_tr.disp_details_issue();
    }
    fp_m.close();
    fp_j.close();
}

void LIBRARY::ret_(void)
{
    char transaction_id[50];
    std::cout << "Enter Transaction ID: ";
    std::cin.getline(transaction_id, 50);
    // Opens the file and TRANSACTION object
    std::fstream fp_tr;
    TRANSACTION temp_tr;
    fp_tr.open(register_list, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
    // Searches the register list for the transaction id
    int count = -1, pos_tr = -1;
    fp_tr.seekg(0, std::ios::beg);
    while(fp_tr.read((char *)&temp_tr, sizeof(temp_tr)))
    {
        count++;
        if(strcmp(temp_tr.ret_identity(), transaction_id) == 0 && temp_tr.ret_returned() == false)
        {
            pos_tr = count;
            break;
        }
    }
    if(pos_tr == -1)            // Does not exist
    {
        std::cout << "No matching record found.\n";
        return;
    }
    // Mark it returned
    temp_tr.alter_returned(true);

    char acc_num[50], card_num[50];
    strcpy(card_num, temp_tr.ret_card_num());
    strcpy(acc_num, temp_tr.ret_acc_num());

    // Searches for the member
    int pos_m = search(member_list, card_num, 3);

    std::fstream fp_m;
    // creates a MEMBER object
    MEMBER temp_m;
    fp_m.open(member_list, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
    fp_m.seekg(pos_m * sizeof(temp_m), std::ios::beg);
    // and reads from the file
    fp_m.read((char *)&temp_m, sizeof(temp_m));
    // change the count
    temp_m.alter_count(-1);
    fp_m.seekp(pos_m * sizeof(temp_m), std::ios::beg);
    fp_m.write((char *)&temp_m, sizeof(temp_m));
    fp_m.close();
    std::cout << "Enter date: ";
    DATE temp_d;
    temp_d.get_values();
    temp_tr.disp_details_ret(temp_m.calculate_charge(temp_d - temp_tr.ret_return_date()));

    fp_tr.seekp(pos_tr * sizeof(temp_tr), std::ios::beg);
    // write it back to the file
    fp_tr.write((char *)&temp_tr, sizeof(temp_tr));
    fp_tr.close();

    // Checks if book or journal
    if(temp_tr.ret_book_or_journal() == 0)  // book
    {
        // Searches for the book
        int pos_b = search(book_list, acc_num, 1);
        // Opens the book list file and creates BOOK object
        std::fstream fp_b;
        BOOK temp_b;
        fp_b.open(book_list, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
        fp_b.seekg(pos_b * sizeof(temp_b), std::ios::beg);
        fp_b.read((char *)&temp_b, sizeof(temp_b));
        // Change quantity after transaction
        temp_b.alter_quantity(1);
        fp_b.seekp(pos_b * sizeof(temp_b), std::ios::beg);
        // and write it back into the file
        fp_b.write((char *)&temp_b, sizeof(temp_b));
        fp_b.close();
    }
    else                                   // journal
    {
        // Searches for the journal
        int pos_j = search(journal_list, acc_num, 2);
        // Opens the book list file and creates JOURNAL object
        std::fstream fp_j;
        JOURNAL temp_j;
        fp_j.open(journal_list, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
        fp_j.seekg(pos_j * sizeof(temp_j), std::ios::beg);
        fp_j.read((char *)&temp_j, sizeof(temp_j));
        // Change quantity after transaction
        temp_j.alter_quantity(1);
        fp_j.seekp(pos_j * sizeof(temp_j), std::ios::beg);
        // and write it back into the file
        fp_j.write((char *)&temp_j, sizeof(temp_j));
        fp_j.close();
    }
}

int main() {
	int choice;
	LIBRARY lib;
	std::cout << "Enter your choice.\n";
    std::cout << "<1> Add member      <2> Add book        <3> Add journal     \n";
	std::cout << "<4> Issue book      <5> Issue journal   <6> Return          \n";
    std::cout << "<7> Show details    <0> Quit\n";
	while(true) {
		std::cout << "\nChoice: ";
		std::cin >> choice;
        std::cin.ignore();
		switch (choice) {
		    case 1:
                lib.add_member();
                break;
            case 2:
                lib.add_book();
                break;
            case 3:
                lib.add_journal();
                break;
            case 4:
                lib.issue_book();
                break;
            case 5:
                lib.issue_journal();
                break;
            case 6:
                lib.ret_();
                break;
            case 7:
                lib.show_details();
                break;
            default:
                return 0;
		}
	}
	return 0;
}
