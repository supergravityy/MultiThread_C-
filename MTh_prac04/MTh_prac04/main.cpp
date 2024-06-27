#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <windows.h>


using namespace std;

mutex MTX;
bool Alarm_set = false;
int cnt;
condition_variable CV;

bool checking()
{
	return Alarm_set;
}

void TikToking()
{
	// 사용자에게 sec단위 시간을 입력받아서 카운팅 하여 다른 스레드에게 알림보내기
	
	cout << "원하는 만큼의 초를 입력하시오 : ";
	cin >> cnt;

	for (int i = 0; i < cnt; i++)
	{
		this_thread::sleep_for(chrono::seconds(1));
		unique_lock<mutex> lck(MTX);
	}
	Alarm_set = true;
	CV.notify_all(); // 다른 모든 스레드를 깨우게함
}

void wait_for_Alarm()
{
	while (1)
	{
		unique_lock<mutex> lck(MTX);
		CV.wait(lck, checking);

		if (Alarm_set)
			break;
	}

	Beep(750, 1000);
	cout << "알람이 울립니다!" << endl;
}

int main()
{
	cout << "알람을 기다리는 중 .." << endl;

	thread timer(TikToking);
	thread checker(wait_for_Alarm);

	checker.join();
	timer.join();

	return 0;
}