#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;	// 뮤텍스를 왜 전역으로 선언했는가?



int cnt; // 공유자원
int cnt2;

void increment()
{
	for (int i = 0; i < 100000; i++)
	{
		mtx.lock(); // cnt가 더해질 동안의 asm 단계에서는 contxt 스위칭이 안일어남
		cnt++;
		mtx.unlock(); 
	}
}

void increment2()
{
	// 락가드는 자원획득을 초기화로 간주 -> 동적할당의 경우 lock으로 간주됨
	// 자원해제를 파괴로 간주 -> 동적할당의 free의 경우 unlock으로 간주됨
	
	for (int i = 0; i < 100000; i++)
	{
		lock_guard<mutex> lck(mtx); // 하나의 반복이 끝나면 lock을 자동으로 해제
		cnt2++;

		// 현재 lck 변수가 중괄호를 빠져나가면 자동소멸되기에 lock이 해제되는것 (mutex 인스턴스를 관리한다는 개념)
	}
}


int main()
{
	thread th1(increment);
	thread th2(increment);
	thread th3(increment);

	th1.join();
	th2.join();
	th3.join();

	cout << "첫번째 최종 값 : " << cnt << endl;
	// 뮤텍스를 안쓰면, cntxt 스위칭때문에 cnt가 30만이 나와야 하는데 안나온다.

	thread th4(increment2);
	thread th5(increment2);
	thread th6(increment2);

	th4.join();
	th5.join();
	th6.join();

	cout << "두번째 최종 값 : " << cnt2 << endl;

	return 0;
}