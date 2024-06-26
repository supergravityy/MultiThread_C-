#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

mutex Mtx;
condition_variable CV;
queue<int> Data;
bool done = false;

void producer()
{
	for (int i = 0; i < 10; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(500));
		unique_lock<mutex> lck(Mtx);
		Data.push(i);
		cout << "생산됨 : " << i << endl;
		CV.notify_one();				// 데이터가 준비됨을 알림
	}

	// 작업완료를 알림
	// 유니크 락 객체의 생명주기를 조절하기위해 중괄호 사용
	{
		unique_lock<mutex> lck(Mtx);
		done = true;
		CV.notify_all(); // 다른 모든 스레드를 깨우고 조건을 확인케함

		// condition_variable 객체를 사용하는 또 다른 스레드가 하나만 있을 경우
		// CV.notify_one(); 을 사용
	}
}

void consumer()
{
	while (true)
	{
		unique_lock<mutex> lck(Mtx);
		CV.wait(lck, [] {return !Data.empty() || done; }); // 데이터가 준비될때까지 대기

		if (!Data.empty())
		{
			int val = Data.front();
			Data.pop();
			cout << "소비됨 : " << val << endl;
		}

		else if (done)
			break; // 생산자가 작업을 마치면 루프 종료
	}
}

int main()
{
	thread producerTH(producer);
	thread consumerTH(consumer);

	producerTH.join();
	consumerTH.join();

	return 0;
}