#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// ������ ���� �ƴ� ���簡 § �ڵ� (�����)
// �� �ڵ忡�� �޼��� �ȿ� ���ؽ��� ���.

class BankAccount
{
public:
	BankAccount(int initVal) : balance(initVal) {}

	void Deposit(int amount)
	{
		lock_guard<mutex> lck(mtx);
		this -> balance += amount;
		cout << "�����ܰ� : " << this->balance << endl;
	}

	void Withdraw(int amount)
	{
		lock_guard<mutex> lck(mtx);
		
		if (this->balance >= amount)
		{
			this->balance -= amount;
			cout << "�����ܰ� : " << this->balance << endl;
		}
		else
			cout << "��ݽ���" << endl;
	}

	int get_balance() const
	{
		lock_guard<mutex> lck(mtx);
		return this->balance;
	}

private:
	int balance;
	mutable mutex mtx;
	// mutable�� �� ���� : ����, get_balance �޼��尡 const�� ����Ǿ��� ������, �޼��� �ȿ��� ��ȭ�ϴ°� ����� �Ѵ�
	// �׷���, mtx�� ���´� �޶����� �ϱ⿡, mutable�� �����Ͽ�, const �޼��忡 �鿪�� �ο��Ѵ�. 
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
	BankAccount account(1000); // �ʱ� �ܰ� 1000

	thread th1(deposit_task, ref(account), 50, 20);
	thread th2(withdraw_task, ref(account), 30, 30);

	th1.join();
	th2.join();

	cout << "�����ܰ� : " << account.get_balance() << endl;

	return 0;
}