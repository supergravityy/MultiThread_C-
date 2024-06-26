#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

class BankAccount
{
private:
	int balance = 1000;

public:
	void Deposit(int amount)
	{
		this->balance += amount;
		cout << endl << "�����ܰ� : " << this->balance << endl;
	}

	void Withdraw(int amount)
	{
		this->balance -= amount;
		cout << endl << "�����ܰ� : " << this->balance << endl;
	}

	int print()
	{
		return this->balance;
	}
};

void input_deposit(int *amount, int* num)
{
	cout << "�Աݱݾ�, Ƚ�� ������ �Է�" << endl;
	cin >> *amount >> *num;
}

void input_withdraw(int* amount, int* num)
{
	cout << "��ݱݾ�, Ƚ�� ������ �Է�" << endl;
	cin >> *amount >> *num;
}

void Do_deposit(BankAccount &account ,int amount, int num)
{
	for (int i = 0; i < num; i++)
	{
		//mtx.lock();

		account.Deposit(amount);

		//mtx.unlock();
	}
}

void Do_withdraw(BankAccount& account, int amount, int num)
{
	for (int i = 0; i < num; i++)
	{
		//mtx.lock();

		account.Withdraw(amount);

		//mtx.unlock();
	}
}

int main()
{
	BankAccount Myaccount;

	int numD, amountD;
	input_deposit(&amountD, &numD);

	int numW, amountW;
	input_withdraw(&amountW, &numW);

	thread deposit(Do_deposit, std::ref(Myaccount), amountD, numD);
	thread withdraw(Do_withdraw, std::ref(Myaccount), amountW, numW);

	cout << "������ : " << Myaccount.print() << endl;

	deposit.join();
	withdraw.join();

	return 0;
}