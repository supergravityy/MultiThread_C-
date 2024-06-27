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
	// ����ڿ��� sec���� �ð��� �Է¹޾Ƽ� ī���� �Ͽ� �ٸ� �����忡�� �˸�������
	
	cout << "���ϴ� ��ŭ�� �ʸ� �Է��Ͻÿ� : ";
	cin >> cnt;

	for (int i = 0; i < cnt; i++)
	{
		this_thread::sleep_for(chrono::seconds(1));
		unique_lock<mutex> lck(MTX);
	}
	Alarm_set = true;
	CV.notify_all(); // �ٸ� ��� �����带 �������
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
	cout << "�˶��� �︳�ϴ�!" << endl;
}

int main()
{
	cout << "�˶��� ��ٸ��� �� .." << endl;

	thread timer(TikToking);
	thread checker(wait_for_Alarm);

	checker.join();
	timer.join();

	return 0;
}