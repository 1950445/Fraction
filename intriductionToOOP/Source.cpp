#include <iostream>
using namespace std;
#define delimiter "\n----------------------------------------------------------------------\n"
class Fraction
{
	int integer;//целая часть
	int numerator;//числитель
	int denominator;//знаменатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//Constructors

	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstruct:/t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1ArgConstructor:/t" << this << endl;
	}

	Fraction(double decimal)
	{
		decimal += 1e-10;//1*10^-10
		integer = decimal;
		decimal -= integer;
		denominator = 1e+9;//1*10^9 точность всегда будет 9 знаков после запятой
		numerator = decimal * denominator;
		reduce();
		cout << "1ArgDConstructor:\t" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:/t" << this << endl;
	}

	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructors:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyComstructor:/t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}
	//Operators
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssgment:/t" << this << endl;
		return *this;
	}
	//Type-cast oparators
	explicit operator int()const
	{
		return integer;
	}
	explicit  operator double()const
	{
		return integer + (double)numerator / denominator;
	}


	//Methods
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		std::swap(inverted.numerator, inverted.denominator);
		return inverted;
	}
	Fraction& reduce()
	{
		to_proper();
		int more, less, rest;
		if (numerator > denominator)more = numerator, less = denominator;
		else less = numerator, more = denominator;
		do {
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more;//GCD-Greatest Common Divisor(наибльший общтй делитель)
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}

	void print()const
	{
		if (integer)cout << integer;//если есть целая часть выводим ее на экран
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}


};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	{
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator(),

	}. to_proper().reduce();
};

Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();
};
bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	//if (left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator())
		//return true;
	//else
		//return false;
	return left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator() * right.get_denominator() > right.get_numerator() * left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator() * right.get_denominator() < right.get_numerator() * left.get_denominator();
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
	//return left > right || left == right;
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
}
std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}
std:: istream& operator >> (std::istream& is, Fraction& obj)
{
	int integer, numerator, denominator;
	is >> integer >> numerator >> denominator;
	obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);
	return is;

}
#define TYPE_CONVERSIONS_BASICS
void main()
{
	setlocale(LC_ALL, "Russian");

	/*/Fraction A;//Def constructor
	A.print();

	Fraction B = 5;
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E = C;//Copy constructor
	E.print();

	Fraction F;
	F = D;
	F.print();*/


	/* Fraction A(2, 3, 4);
	A.print();

	Fraction B(3, 4, 5);
	B.print();
	Fraction C = A * B;
	C.print();

	Fraction D = A / B;
	D.print();*/


	/*cout << (2 == 3) << endl;
	Fraction A(1, 3);
	Fraction B(5, 10);
	cout << (A > B) << endl;*/


    /*fraction  a(840, 3600);
	a.print();
	a.reduce();
	a.print();*/

	/*Fraction A(5, 10);
	cout << "Введите простую дробь:"; cin >> A;
	cout << A << endl;
	A.reduce();
	cout << A << endl;*/

	/*Fraction A =(Fraction) 5;
	cout << A << endl;
	cout << delimiter << endl;
	Fraction B;
	B =Fraction(8);
	cout << delimiter << endl;
	cout << B << endl;*/

	////Fraction C = 12;
	//Fraction C(12);
	//cout << C << endl; 

	/*Fraction A(2, 1, 2);
	cout << A << endl;
	int a =(int) A;
	cout << a << endl;

	Fraction B(2, 3, 4);
	cout << B << endl;
	double b = (double)B;
	cout << b << endl;*/
	Fraction A = 2.76;
	cout << A << endl;

	Fraction B = 3.333;
	cout << B << endl;
}