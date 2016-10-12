#include <iostream>

using namespace std;

template <class T>
class BankAccount
{
	private:
		T balance;
	public:
		BankAccount(T amount);
		T getBalance();
		void add(T amount);
		void remove(T amount);
		void print();
};

template<class T> 
BankAccount<T>::BankAccount(T amount)
	: balance(amount)
{
	// done
}
template<class T> 
T BankAccount<T>::getBalance()
{
	return balance;
}
template<class T> 
void BankAccount<T>::add(T amount)
{
	balance += amount;
}
template<class T> 
void BankAccount<T>::remove(T amount)
{
	balance -= amount;
}
template<class T> 
void BankAccount<T>::print()
{
	cout << "Account has $" << balance << endl;
}

int main()
{
	BankAccount<double> a = BankAccount<double>(2000.00);
	a.print();
	BankAccount<int> b = BankAccount<int>(2000);
	b.print();
	a.add(50.00);
	a.print();
	b.remove(50);
	b.print();
	return 0;
}