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
		cout << "����� : " << i << endl;
		CV.notify_one();	// �����Ͱ� �غ���� �˸�
	}

	// �۾��ϷḦ �˸�
	// ����ũ �� ��ü�� �����ֱ⸦ �����ϱ����� �߰�ȣ ���
	{
		unique_lock<mutex> lck(Mtx);
		done = true;		// 10���� ������ ������ �÷��� ���
		CV.notify_all();	// �ٸ� ��� �����带 ����� ������ Ȯ������

		// condition_variable ��ü�� ����ϴ� �� �ٸ� �����尡 �ϳ��� ���� ���
		// CV.notify_one(); �� ���
	}
}

void consumer()
{
	while (true)
	{
		unique_lock<mutex> lck(Mtx);
		CV.wait(lck, [] {return !Data.empty() || done; }); // ť�� �����Ͱ� �ְų�, 10���� ������ �Ϸ�Ǿ��������� ���Ǻ��� CV�� ����Ͽ� ���

		if (!Data.empty())	// ť�� �����Ͱ� ����
		{
			int val = Data.front(); // pop �ϱ�
			Data.pop();
			cout << "�Һ�� : " << val << endl;
		}

		else if (done)
			break; // �����ڰ� �۾��� ��ġ�� ���� ����
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