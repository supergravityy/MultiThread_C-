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
        // 발란스 멤버변수가 contxt 스위칭이 일어나서 손상되면 안되기 때문에 값을 복사
        if (current_balance >= amount) 
        {
            // balance -= amount; 연산자 오버로딩이어서 헷갈릴 수 있으니, 차라리 fetch_add를 사용하자
            balance.fetch_add(-amount);
            cout << "현재 잔고 : "<< balance.load() << endl; 
        }
        else 
            cout << "출금 실패 " << endl;
        
	}

    void Deposit(int amount)
    {
        balance.fetch_add(amount);
        cout << "현재 잔고 : " << balance << endl;
    }

    int get_balance() const 
    {
        return balance.load();
    }

private:
	atomic<int> balance; // 해당 변수를 변경할 때에는 lock이 됨
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
    BankAccount account(1000); // 초기 잔고 1000

    thread t1(deposit_task, ref(account), 50, 20); 
    thread t2(withdraw_task, ref(account), 30, 30); 

    t1.join();
    t2.join();

    cout << "최종 잔고 : " << account.get_balance() << endl;

    return 0;
}