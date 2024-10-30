#include<iostream>
#include<map>
using namespace std;

void OutputScreen() {
	cout << "====================================================" << endl;
	cout << "         Arithmetic operations on polynomials       " << endl;
	cout << "====================================================" << endl;

}
int Input_Term_coefficient() {
	int Coffe;
	cout << "Enter the coefficient: ";
	cin >> Coffe;
	return Coffe;
}
int Input_Term_Exponent() {
	int Exp;
	cout << "Enter the Exponent: ";
	cin >> Exp;
	return Exp;
}
int Id() {
	int id;
	cout << "Enter the Polynomial Id: ";
	cin >> id;
	return id;
}
//class for polynomial
class P {
private:
	struct Node
	{
		int coefficient;
		int exponent;
		Node* next;

	};
	typedef Node* NODEPTR;
	NODEPTR head = NULL;
public:
	//-----------------------------------------------------
	bool check_Duplicate(int coff,int exp) {
		NODEPTR p = new Node();
		for (p = head; p != nullptr; p = p->next) {
			if (p->exponent == exp) {
				p->coefficient = coff;
				return true;
			}
			if (p->next == nullptr)
				break;
		}
		return false;
	}
	//-----------------------------------------------------
	void insertTerm(int coff, int exp) {
		NODEPTR p, current;
		p = new Node();
		current = new Node();
		//case 0 :o	Avoid duplicate terms 
		if (check_Duplicate(coff,exp))
		{	
			return;
		}
		//Case 1:If there is No item in List
		if (head == NULL) {
			p->coefficient = coff;
			p->exponent = exp;
			p->next = head;
			head = p;
			return;
		}
		current = head;
		//Case 2 : if the user entered the exponent which is greater than first one in the List
		if (current->exponent < exp) {
			p->coefficient = coff;
			p->exponent = exp;
			p->next = current;
			head = p;
			return;
		}
		//Case 3: Somewhere in Middle
		while (current)
		{
			if (current->next != nullptr && current->next->exponent > exp )
			{
				current = current->next;
				continue;
			}
			else {
				p->coefficient = coff;
				p->exponent = exp;
				p->next = current->next;
				current->next = p;
				break;
			}
		}

	}
	//-----------------------------------------------------
	P operator+(P &R) {

	}
	//-----------------------------------------------------
	void Display() {

		NODEPTR current = new Node();
		current = head;
		if (head == NULL) {
			cout << "No Polynomial Found yet." << endl;
			return;
		}
		while (current != nullptr) {
			if (current->exponent  != 0) 
			{
			  cout << current->coefficient << "x^" << current->exponent;
			  current = current->next;
			if (current->next != nullptr) {
				cout << " + ";
			}
			  continue;
			}
			cout << " + ";
			cout << current->coefficient;
			current = current->next;
		}
		cout << endl;
		system("pause");
	}
};

int main() {
	map< int , P >list;
	int count = 0;
	do
	{
		char option;
		system("cls");
		OutputScreen();
		cout << "1.Insert the Term." << endl;
		cout << "2.Display the Polynomial in a readible Format." << endl;
		cout << "0.EXIT" << endl;
		cout << "Option: ";
		cin >> option;

		if (option == '1') {
			system("cls");
			OutputScreen();
			int id,Cof, exp;
			id = Id();
			Cof = Input_Term_coefficient();
			exp = Input_Term_Exponent();
			list[id].insertTerm(Cof, exp);
			if (list.find(id) == list.end()) {
				++count;  
			}

		}
		else if (option == '2') {
			system("cls");
			OutputScreen();
			int id = Id();
			cout << "Polynomial in a Readable Format: " << endl;
			cout << "Id " << id << " Polynomial as follow: " << endl;
			list[id].Display();
			cout << endl;
		}

		
	} while (true);

}