#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// 기존의 것이 아닌 강사가 짠 코드 (참고용)
// 이 코드에선 메서드 안에 뮤텍스를 썼다.

class BankAccount
{
public:
	BankAccount(int initVal) : balance(initVal) {}

	void Deposit(int amount)
	{
		lock_guard<mutex> lck(mtx);
		this -> balance += amount;
		cout << "현재잔고 : " << this->balance << endl;
	}

	void Withdraw(int amount)
	{
		lock_guard<mutex> lck(mtx);
		
		if (this->balance >= amount)
		{
			this->balance -= amount;
			cout << "현재잔고 : " << this->balance << endl;
		}
		else
			cout << "출금실패" << endl;
	}

	int get_balance() const
	{
		lock_guard<mutex> lck(mtx);
		return this->balance;
	}

private:
	int balance;
	mutable mutex mtx;
	// mutable을 쓴 이유 : 현재, get_balance 메서드가 const로 선언되었기 때문에, 메서드 안에선 변화하는게 없어야 한다
	// 그런데, mtx의 상태는 달라져야 하기에, mutable로 선언하여, const 메서드에 면역을 부여한다. 
};

void deposit_task(BankAccount& account, int amount, int times) {

	for (int i = 0; i < times; ++i) {
		account.Deposit(amount);
	}
}

void withdraw_task(BankAccount& account, int amount, int times) {
	for (int i = 0; i < times; ++i) {
		account.Withdraw(amount);
	}
}

int main()
{
	BankAccount account(1000); // 초기 잔고 1000

	thread th1(deposit_task, ref(account), 50, 20);
	thread th2(withdraw_task, ref(account), 30, 30);

	th1.join();
	th2.join();

	cout << "최종잔고 : " << account.get_balance() << endl;

	return 0;
}