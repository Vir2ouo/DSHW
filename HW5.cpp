// HW5.cpp : �w�q�D���x���ε{�����i�J�I�C
//
#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm { 
public:                          
	int coef;
	int expo;
};                                                                          
                                                                         
class ArrayPolynomial {                                        
public:                                                                  
	PolynomialTerm terms[MAX_TERMS]; 

	void clear() 
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputTerms(int coef, int expo) 
	{
		if (terms[0].coef == 0 && terms[0].expo == 0)
		{
			if (coef != 0)
			{
				terms[0].coef = coef;
				terms[0].expo = expo;
			}
		}
		else
		{
			for (int i = 0; i < MAX_TERMS; i++)
			{
				if (terms[i].expo == expo)
				{
					if (coef != 0)
					{
						terms[i].coef = coef;
						break;
					}
					else
					{
						for (int j = i; j < MAX_TERMS - 1; j++)
						{
							terms[j].coef = terms[j + 1].coef;
							terms[j].expo = terms[j + 1].expo;
						}
						terms[MAX_TERMS - 1].coef = 0;
						terms[MAX_TERMS - 1].expo = 0;
						break;
					}
				}
				else
				{
					if (terms[i].expo < expo && terms[i].coef!=0)
					{
						if (coef != 0)
						{
							for (int j = MAX_TERMS - 2; j >= i ; j--)
							{
								terms[j + 1].coef = terms[j].coef;
								terms[j + 1].expo = terms[j].expo;
							}
							terms[i].coef = coef;
							terms[i].expo = expo;
						}
						break;
					}
					else
					{
						if (terms[i].coef == 0 && terms[i].expo == 0)
						{
							terms[i].coef = coef;
							terms[i].expo = expo;
							break;
						}
					}
				}
			}
		}

		return;
	}

	void addArrayBasedPoly(ArrayPolynomial &a, ArrayPolynomial &b) /////
	{
		int i = 0;
		int j = 0;
		int k = 0;

		while (i < MAX_TERMS && j < MAX_TERMS)
		{
			if (a.terms[i].expo == b.terms[j].expo) //�ۦP�Y��
			{
				if (a.terms[i].coef + b.terms[j].coef != 0)
				{
					terms[k].coef = a.terms[i].coef + b.terms[j].coef;
					terms[k].expo = a.terms[i].expo;
					i++;
					j++;
					k++;
				}
				else
				{
					i++;
					j++;
				}
			}
			else if (a.terms[i].expo > b.terms[j].expo)
			{
				terms[k].coef = a.terms[i].coef;
				terms[k].expo = a.terms[i].expo;
				i++;
				k++;
			}
			else if (a.terms[i].expo < b.terms[j].expo)
			{
				terms[k].coef = b.terms[j].coef;
				terms[k].expo = b.terms[j].expo;
				j++;
				k++;
			}
		}

		return;
	}

	void reverseArrayBasedPoly() /////
	{
		int len = 0;
		ArrayPolynomial f;
		for (int i = 0; i < MAX_TERMS ; i++)
		{
			if (terms[i].coef != 0)
			{
				len++;
			}
		}
		int t = 0;
		int temp = len - 1;
		while(temp>=0)
		{
			f.terms[t].coef = terms[temp].coef;
			f.terms[t].expo = terms[temp].expo;
			t++;
			temp--;
		}
		for (int i = 0; i < len; i++)
		{
			terms[i].coef = f.terms[i].coef;
			terms[i].expo = f.terms[i].expo;
		}
		return;
	}

	void printArrayBasedPoly() /////
	{
		if (terms[0].coef == 0)
			return;
		if (terms[0].expo == 0)
			std::cout << terms[0].coef;
		else
			std::cout << terms[0].coef << "X^" << terms[0].expo;

		for (int i = 1; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				return;

			if (terms[i].expo == 0)
				std::cout << " + " << terms[i].coef;
			else
				std::cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}

		return;
	}

	int compute(int x)
	{
		int sum = 0;
		for (int i = 0, pd = 1; terms[i].coef != 0; i++, pd = 1)
		{
			for (int j = 0; j < terms[i].expo; j++)
			{
				pd *= x;
			}
			pd *= terms[i].coef;
			sum += pd;
		}
		return sum;
	}
};                                                                

class LinkedPolynomialTerm {                       
public:                                                          
	int coef;
	int expo;
	LinkedPolynomialTerm *nextTermPtr; 
};                                                                  

class LinkPolynomial {                                
public:                                                          
	LinkedPolynomialTerm *polynomialTermPtr = nullptr;

	void clear() /////
	{
		LinkedPolynomialTerm *tmpPtr;                       

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputLinkTerms(int coef, int expo) /////
	{
		LinkedPolynomialTerm *tmpPtr, *curr, *pre, *head, *die;                                                 

		tmpPtr = new LinkedPolynomialTerm;                                        
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;
		tmpPtr->nextTermPtr = nullptr;
		
		if (polynomialTermPtr == nullptr && coef != 0)
		{
			polynomialTermPtr = tmpPtr;
		}
		else if(polynomialTermPtr != nullptr)
		{
			curr = polynomialTermPtr;
			pre = polynomialTermPtr;
			head = polynomialTermPtr;
			int door = 1;

			if (head->expo == expo )
			{
				if (coef != 0)
				{
					polynomialTermPtr->coef = tmpPtr->coef;
					door = 0;
				}
				else
				{
					polynomialTermPtr = polynomialTermPtr->nextTermPtr;
					delete head;
					door = 0;
				}
			}
			else if (head->expo < expo && coef != 0)
			{
				tmpPtr->nextTermPtr = polynomialTermPtr;
				polynomialTermPtr = tmpPtr;
				door = 0;
			}
			while (curr != nullptr && door == 1)
			{
				if (curr->expo == expo && coef != 0)
				{
					curr->coef = coef;
					door = 0;
				}
				if(curr->expo == expo && coef == 0)
				{
					die = curr;
					pre->nextTermPtr = curr->nextTermPtr;
					delete die;
					door = 0;
				}
				if (curr->expo < expo && coef != 0)
				{
					tmpPtr->nextTermPtr = curr;
					pre->nextTermPtr = tmpPtr;
					door = 0;
					break;
				}
				else
				{
					pre = curr;
					curr = curr->nextTermPtr;
				}
			}
			if (door == 1)
			{
				curr = tmpPtr;
				pre->nextTermPtr = curr;
			}
		}
		return;
	}

	void addLinkBasedPoly(LinkPolynomial &aPol, LinkPolynomial &bPol) 
	{
	
		LinkedPolynomialTerm *curra, *currb, *currd, *tmpPtr;
		curra = aPol.polynomialTermPtr;
		currb = bPol.polynomialTermPtr;
		currd = polynomialTermPtr;
		int door = 1;

		while (curra != nullptr && currb != nullptr)
		{
			int door = 1;

			tmpPtr = new LinkedPolynomialTerm;
			tmpPtr->coef = 0;
			tmpPtr->expo = 0;
			tmpPtr->nextTermPtr = nullptr;

			if ( curra->expo == currb->expo)
			{
				if (curra->coef + currb->coef != 0)
				{
					tmpPtr->coef = curra->coef + currb->coef;
					tmpPtr->expo = curra->expo;
					
					curra = curra->nextTermPtr;
					currb = currb->nextTermPtr;
				}
				else
				{
					curra = curra->nextTermPtr;
					currb = currb->nextTermPtr;
					door = 0;
				}
			}
			else if (curra->expo > currb->expo)
			{
				tmpPtr->coef = curra->coef;
				tmpPtr->expo = curra->expo;
				curra = curra->nextTermPtr;
			}
			else
			{
				tmpPtr->coef = currb->coef;
				tmpPtr->expo = currb->expo;
				currb = currb->nextTermPtr;
			}
			if (polynomialTermPtr == nullptr && door == 1)
			{
				polynomialTermPtr = new LinkedPolynomialTerm;
				polynomialTermPtr = tmpPtr;
				currd = polynomialTermPtr;
			}
			else if(door == 1)
			{
				currd->nextTermPtr = tmpPtr;
				currd = currd->nextTermPtr;
			}
		}
		while (curra != nullptr)
		{
			tmpPtr = new LinkedPolynomialTerm;
			tmpPtr->coef = curra->coef;
			tmpPtr->expo = curra->expo;
			tmpPtr->nextTermPtr = nullptr;

			if (polynomialTermPtr == nullptr)
			{
				polynomialTermPtr = new LinkedPolynomialTerm;
				polynomialTermPtr = tmpPtr;
				currd = polynomialTermPtr;
				curra = curra->nextTermPtr;
			}
			else
			{
				currd->nextTermPtr = tmpPtr;
				currd = currd->nextTermPtr;
				curra = curra->nextTermPtr;
			}
		}
		while (currb != nullptr)
		{
			tmpPtr = new LinkedPolynomialTerm;
			tmpPtr->coef = currb->coef;
			tmpPtr->expo = currb->expo;
			tmpPtr->nextTermPtr = nullptr;

			if (polynomialTermPtr == nullptr)
			{
				polynomialTermPtr = new LinkedPolynomialTerm;
				polynomialTermPtr = tmpPtr;
				currd = polynomialTermPtr;
				currb = currb->nextTermPtr;
			}
			else
			{
				currd->nextTermPtr = tmpPtr;
				currd = currd->nextTermPtr;
				currb = currb->nextTermPtr;
			}
		}
		return;
	}

	void reverseLinkBasedPoly() 
	{
		LinkedPolynomialTerm *prev, *curr,*box, *head;
		prev = new LinkedPolynomialTerm;
		curr = new LinkedPolynomialTerm;
		head = new LinkedPolynomialTerm;
		box = nullptr;
		if (polynomialTermPtr == nullptr) //空串列
		{
			return;
		}
		else if (polynomialTermPtr->expo == 0) //只有常數項
		{
			return;
		}
		else
		{
			while (1)
			{

				curr = polynomialTermPtr;
				if (curr->nextTermPtr == nullptr)
				{
					if (box == nullptr)
					{
						box = curr;
						head = box;
					}
					else
					{
						box->nextTermPtr = curr;
					}
					break;
				}
				while (curr->nextTermPtr != nullptr)
				{
					prev = curr;
					curr = curr->nextTermPtr;
				}
				prev->nextTermPtr = nullptr;
				if (box == nullptr)
				{
					box = curr;
					head = box;
				}
				else
				{
					box->nextTermPtr = curr;
					box = box->nextTermPtr;
				}
			}
		}
		polynomialTermPtr = head;
		return;
	}

	void printLinkBasedPoly()                                                            /////
	{
		LinkedPolynomialTerm *termPtr = polynomialTermPtr; /////

		if (termPtr == nullptr)
			return;

		if (termPtr->expo == 0)
			cout << termPtr->coef;
		else
			cout << termPtr->coef << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;

		while (termPtr != nullptr) {
			if (termPtr->coef == 0)
				return;

			if (termPtr->expo == 0)
				cout << " + " << termPtr->coef;
			else
				cout << " + " << termPtr->coef << "X^" << termPtr->expo;

			termPtr = termPtr->nextTermPtr;
		}

		return;
	}

	int compute(int x)
	{
		int sum = 0;
		for (int pd = 1; polynomialTermPtr != nullptr; polynomialTermPtr = polynomialTermPtr->nextTermPtr, pd = 1)
		{
			for (int j = 0; j < polynomialTermPtr->expo; j++)
			{
				pd *= x;
			}
			pd *= polynomialTermPtr->coef;
			sum += pd;
		}
		return sum;
		//return 0;

	}
}; 

int main()
{
	ArrayPolynomial a, b, d;                                                              /////
	LinkPolynomial aPol, bPol, dPol;                                             /////

	int coef, expo, x;

          // aPtr = bPtr = dPtr = nullptr; /////

	while (1) {
		a.clear(); b.clear(); d.clear();                                    /////
                      // aPtr->clear(aPtr); bPtr->clear(bPtr); dPtr->clear(dPtr); /////


		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			a.inputTerms(coef, expo);             /////
			aPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\na = ";
		a.printArrayBasedPoly();     /////
		cout << "\na = ";
		aPol.printLinkBasedPoly(); /////
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			b.inputTerms(coef, expo);             /////
			bPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\nb = ";
		b.printArrayBasedPoly();      /////

		cout << "\nb = ";
		bPol.printLinkBasedPoly(); /////

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		d.addArrayBasedPoly(a, b); /////
		cout << "\na + b = ";
		d.printArrayBasedPoly();     /////

		dPol.addLinkBasedPoly(aPol, bPol); /////
		cout << "\na + b = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		d.reverseArrayBasedPoly(); /////
		cout << "\nreversed d = ";
		d.printArrayBasedPoly();     /////
		
		dPol.reverseLinkBasedPoly(); /////
		cout << "\nreversed d = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		cout << "\ninput X: ";
		cin >> x;

		cout << "\nd = ";
		cout << d.compute(x);      //////

		cout << "\nd = ";
		cout << dPol.compute(x); //////

		cout << "\n";

		aPol.clear(); bPol.clear(); dPol.clear(); /////
	}

	return 0;
}
