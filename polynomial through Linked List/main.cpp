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
	P() {
		head = NULL;
	}
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
	P operator+(P& Poly2) {
		P result;
		NODEPTR p1 = head;
		NODEPTR p2 = Poly2.head;
		 
		while (p1 != nullptr || p2 != nullptr) {
			if (p1 == nullptr ) {
				result.insertTerm(p2->coefficient, p2->exponent);
				p2 = p2->next;
			}
			else if (p2 == nullptr) {
				result.insertTerm(p1->coefficient, p1->exponent);
				p1 = p1->next;
			}
			else if (p1->exponent > p2->exponent) {
				result.insertTerm(p1->coefficient, p1->exponent);
				p1 = p1->next;
			}
			else if (p1->exponent < p2->exponent) {
				result.insertTerm(p2->coefficient, p2->exponent);
				p2 = p2->next;
			}
			else {
				result.insertTerm(p1->coefficient + p2->coefficient, p1->exponent);
				p1 = p1->next;
				p2 = p2->next;
			}
		}
		return result;
	}
	P operator-(P& Poly2) {
		P result;
		NODEPTR p1 = head;
		NODEPTR p2 = Poly2.head;

		while (p1 != nullptr || p2 != nullptr) {
			if (p1 == nullptr) {
				result.insertTerm(-p2->coefficient, p2->exponent);
				p2 = p2->next;
			}
			else if (p2 == nullptr) {
				result.insertTerm(p1->coefficient, p1->exponent);
				p1 = p1->next;
			}
			else if (p1->exponent > p2->exponent) {
				result.insertTerm(p1->coefficient, p1->exponent);
				p1 = p1->next;
			}
			else if (p1->exponent < p2->exponent) {
				result.insertTerm(-p2->coefficient, p2->exponent);
				p2 = p2->next;
			}
			else {
				result.insertTerm(p1->coefficient - p2->coefficient, p1->exponent);
				p1 = p1->next;
				p2 = p2->next;
			}
		}
		return result;
	}
	P operator*(P& Poly2) {
		P result;
		for (NODEPTR p1 = head; p1 != nullptr; p1 = p1->next) {
			P temp;
			for (NODEPTR p2 = Poly2.head; p2 != nullptr; p2 = p2->next) {
				int newCoefficient = p1->coefficient * p2->coefficient;
				int newExponent = p1->exponent + p2->exponent;
				temp.insertTerm(newCoefficient, newExponent);
			}
			result = result + temp;
		}
		return result;
	}

	//-----------------------------------------------------
	int evaluate() {
		int x;
		cout << "Enter the value for x: ";
		cin >> x;
		int result = 0;
		NODEPTR current = head;
		while (current) {
			result += current->coefficient * pow(x, current->exponent);
			current = current->next;
		}
		return result;
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
			if (current->exponent != 0) {
				  cout << current->coefficient << "x^" << current->exponent;
			}
			else {
				cout << current->coefficient;
			}
			current = current->next;
			if (current != nullptr && current->coefficient > 0) {
				cout << " + ";
			}
			if (current != nullptr && current->coefficient < 0) {
				cout << " ";
			}
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
		cout << "3.ADD two Polynomials." << endl;
		cout << "4.SUBTRACT two Polynomials." << endl;
		cout << "5.MULTIPLE two Polynomials." << endl;
		cout << "6.Evaluation." << endl;
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
		else if (option == '3') {
			system("cls");
			OutputScreen();
			cout << "1st polynomial: " << endl;
			int id1 = Id();
			cout << "2nd polynomial: " << endl;
			int id2 = Id();
			cout << "Result Polynomial id: ";
			int resultid;
			cin >> resultid;
			if (list.find(id1) != list.end() && list.find(id2) != list.end()) {
				list[resultid] = list[id1] + list[id2];
			}
		}
		else if (option == '4'){
			system("cls");
			OutputScreen();
			cout << "1st polynomial: " << endl;
			int id1 = Id();
			cout << "2nd polynomial: " << endl;
			int id2 = Id();
			cout << "Result Polynomial id: ";
			int resultid;
			cin >> resultid;
			if (list.find(id1) != list.end() && list.find(id2) != list.end()) {
				list[resultid] = list[id1] - list[id2];
			}
		}
		else if (option == '5'){
			system("cls");
			OutputScreen();
			cout << "1st polynomial: " << endl;
			int id1 = Id();
			cout << "2nd polynomial: " << endl;
			int id2 = Id();
			cout << "Result Polynomial id: ";
			int resultid;
			cin >> resultid;
			if (list.find(id1) != list.end() && list.find(id2) != list.end()) {
				list[resultid] = list[id1] * list[id2];
			}
		}
		else if (option == '6') {
			system("cls");
			OutputScreen();
			cout << "Enter Polynomial id which you want to evaluate." << endl;
			int id = Id();
			cout << endl;
			if (list.find(id) != list.end()) {
				cout << "Result: " << list[id].evaluate() << endl;
			}
			else {
				cout << "Polynomial with ID " << id << " does not exist." << endl;
			}
			system("pause");
		}
		else if (option == '0') {
			exit(1);
		}
		else {
			cout << "Invalid Input!!!" << endl;
			system("pause");
		}
	} while (true);

}