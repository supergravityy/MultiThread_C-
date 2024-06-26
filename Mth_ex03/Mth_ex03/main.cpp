#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;	// ���ؽ��� �� �������� �����ߴ°�?



int cnt; // �����ڿ�
int cnt2;

void increment()
{
	for (int i = 0; i < 100000; i++)
	{
		mtx.lock(); // cnt�� ������ ������ asm �ܰ迡���� contxt ����Ī�� ���Ͼ
		cnt++;
		mtx.unlock(); 
	}
}

void increment2()
{
	// ������� �ڿ�ȹ���� �ʱ�ȭ�� ���� -> �����Ҵ��� ��� lock���� ���ֵ�
	// �ڿ������� �ı��� ���� -> �����Ҵ��� free�� ��� unlock���� ���ֵ�
	
	for (int i = 0; i < 100000; i++)
	{
		lock_guard<mutex> lck(mtx); // �ϳ��� �ݺ��� ������ lock�� �ڵ����� ����
		cnt2++;

		// ���� lck ������ �߰�ȣ�� ���������� �ڵ��Ҹ�Ǳ⿡ lock�� �����Ǵ°� (mutex �ν��Ͻ��� �����Ѵٴ� ����)
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

	cout << "ù��° ���� �� : " << cnt << endl;
	// ���ؽ��� �Ⱦ���, cntxt ����Ī������ cnt�� 30���� ���;� �ϴµ� �ȳ��´�.

	thread th4(increment2);
	thread th5(increment2);
	thread th6(increment2);

	th4.join();
	th5.join();
	th6.join();

	cout << "�ι�° ���� �� : " << cnt2 << endl;

	return 0;
}