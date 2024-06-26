#include <iostream>
#include <thread>
#include <mutex>
#include <chrono> // 유니크 락을 사용하기 위한 헤더

using namespace std;

mutex mtx;

// 유니크 락은 뮤텍스를 즉시 잠그지 않고 시작가능 -> lock가드보다 더 세밀하게 lock사용 상황제공

void try_to_Lock(int id)
{
	unique_lock<mutex> lck(mtx, defer_lock); // defer_lock 태크를 사용하여 lock을 바로 획득하지 않음

	if (lck.try_lock())						
	// 그리고 try_lock 메서드를 호출하여 lock시도 -> 뮤텍스가 다른 쓰레드를 잠그지 않았을때 lock하고, true 반환
	{
		cout << "쓰레드(" << id << ")가 lock 되었습니다" << endl;
		this_thread::sleep_for(chrono::seconds(1)); // 자원 사용 시뮬 (1초 슬립함수)

		lck.unlock();
	}
	else
		cout << "쓰레드(" << id << ")가 lock 되지 않았습니다" << endl; // 이미 다른 스레드가 뮤텍스 lock을 사용중이기에 lock 안함
}


/* 이부분이 이해가 잘 안됨 */

void use_Release(int id)
{
	unique_lock<mutex> lck(mtx); // lock을 바로 획득
	
	cout << "쓰레드(" << id << ")가 lock 되었고 곧 유니크락에서 해방될것입니다" << endl;
	this_thread::sleep_for(chrono::seconds(1)); // 자원 사용 시뮬

	mutex* mtx_ptr = lck.release(); // 유니크 락 객체는 더이상 해당 뮤텍스에 대한 소유권을 잃음 -> 해당 주소값 반환
	cout << "쓰레드(" << id << ")가 유니크락에서 해방되었지만 mutex는 남았습니다" << endl << "수동 unlock이 필요합니다"<<endl;

	mtx_ptr->unlock();
	// 사용자가 수동으로 뮤텍스 포인터를 사용하여 뮤텍스를 lock 하기 (더이상 자동이 아니다)
	// 혹은 다른 유니크 락이나 아토믹을 사용하여, 뮤텍스를 관리하게 할 수 있음
}

int main()
{
	thread th1(try_to_Lock, 1);
	thread th2(try_to_Lock, 2);
	thread th3(use_Release, 3);

	th1.join();
	th2.join();
	th3.join();

	return 0;
}