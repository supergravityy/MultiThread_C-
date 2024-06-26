#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

class BankAccount
{
public:
	BankAccount(int initVal) : balance(initVal) {}

	void Withdraw(int amount)
	{
        int current_balance = balance.load();
        // �߶��� ��������� contxt ����Ī�� �Ͼ�� �ջ�Ǹ� �ȵǱ� ������ ���� ����
        if (current_balance >= amount) 
        {
            // balance -= amount; ������ �����ε��̾ �򰥸� �� ������, ���� fetch_add�� �������
            balance.fetch_add(-amount);
            cout << "���� �ܰ� : "<< balance.load() << endl; 
        }
        else 
            cout << "��� ���� " << endl;
        
	}

    void Deposit(int amount)
    {
        balance.fetch_add(amount);
        cout << "���� �ܰ� : " << balance << endl;
    }

    int get_balance() const 
    {
        return balance.load();
    }

private:
	atomic<int> balance; // �ش� ������ ������ ������ lock�� ��
};

void deposit_task(BankAccount& account, int amount, int times) 
{
    for (int i = 0; i < times; ++i) 
        account.Deposit(amount);  
}

void withdraw_task(BankAccount& account, int amount, int times) 
{
    for (int i = 0; i < times; ++i) 
        account.Withdraw(amount);
}

int main() {
    BankAccount account(1000); // �ʱ� �ܰ� 1000

    thread t1(deposit_task, ref(account), 50, 20); 
    thread t2(withdraw_task, ref(account), 30, 30); 

    t1.join();
    t2.join();

    cout << "���� �ܰ� : " << account.get_balance() << endl;

    return 0;
}