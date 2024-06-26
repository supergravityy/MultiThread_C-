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
		cout << endl << "현재잔고 : " << this->balance << endl;
	}

	void Withdraw(int amount)
	{
		this->balance -= amount;
		cout << endl << "현재잔고 : " << this->balance << endl;
	}

	int print()
	{
		return this->balance;
	}
};

void input_deposit(int *amount, int* num)
{
	cout << "입금금액, 횟수 순으로 입력" << endl;
	cin >> *amount >> *num;
}

void input_withdraw(int* amount, int* num)
{
	cout << "출금금액, 횟수 순으로 입력" << endl;
	cin >> *amount >> *num;
}

void Do_deposit(BankAccount &account ,int amount, int num)
{
	for (int i = 0; i < num; i++)
	{
		mtx.lock();

		account.Deposit(amount);

		mtx.unlock();
	}
}

void Do_withdraw(BankAccount& account, int amount, int num)
{
	for (int i = 0; i < num; i++)
	{
		mtx.lock();

		account.Withdraw(amount);

		mtx.unlock();
	}
}

int main()
{
	BankAccount Myaccount;

	int numD, amountD;
	input_deposit(&amountD, &numD);

	int numW, amountW;
	input_withdraw(&amountW, &numW);

	thread deposit(Do_deposit, ref(Myaccount), amountD, numD);
	thread withdraw(Do_withdraw, ref(Myaccount), amountW, numW);

	/* ref를 쓰는 이유 
	thread 클래스의 생성자가 기본적으로 인자를 내부적으로 튜플에 저장하여, 인자들을 복사하기 때문
	그래서 ref를 사용하여 참조의 ref를 만들어 넘겨주면 원본객체에 대한 참조를 유지가능 */
	

	cout << "최종값 : " << Myaccount.print() << endl;

	deposit.join();
	withdraw.join();

	return 0;
}