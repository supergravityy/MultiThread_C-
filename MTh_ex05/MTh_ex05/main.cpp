#include <iostream>
#include <thread>
#include <mutex>
#include <chrono> // ����ũ ���� ����ϱ� ���� ���

using namespace std;

mutex mtx;

// ����ũ ���� ���ؽ��� ��� ����� �ʰ� ���۰��� -> lock���庸�� �� �����ϰ� lock��� ��Ȳ����

void try_to_Lock(int id)
{
	unique_lock<mutex> lck(mtx, defer_lock); // defer_lock ��ũ�� ����Ͽ� lock�� �ٷ� ȹ������ ����

	if (lck.try_lock())						
	// �׸��� try_lock �޼��带 ȣ���Ͽ� lock�õ� -> ���ؽ��� �ٸ� �����带 ����� �ʾ����� lock�ϰ�, true ��ȯ
	{
		cout << "������(" << id << ")�� lock �Ǿ����ϴ�" << endl;
		this_thread::sleep_for(chrono::seconds(1)); // �ڿ� ��� �ù� (1�� �����Լ�)

		lck.unlock();
	}
	else
		cout << "������(" << id << ")�� lock ���� �ʾҽ��ϴ�" << endl; // �̹� �ٸ� �����尡 ���ؽ� lock�� ������̱⿡ lock ����
}


/* �̺κ��� ���ذ� �� �ȵ� */

void use_Release(int id)
{
	unique_lock<mutex> lck(mtx); // lock�� �ٷ� ȹ��
	
	cout << "������(" << id << ")�� lock �Ǿ��� �� ����ũ������ �ع�ɰ��Դϴ�" << endl;
	this_thread::sleep_for(chrono::seconds(1)); // �ڿ� ��� �ù�

	mutex* mtx_ptr = lck.release(); // ����ũ �� ��ü�� ���̻� �ش� ���ؽ��� ���� �������� ���� -> �ش� �ּҰ� ��ȯ
	cout << "������(" << id << ")�� ����ũ������ �ع�Ǿ����� mutex�� ���ҽ��ϴ�" << endl << "���� unlock�� �ʿ��մϴ�"<<endl;

	mtx_ptr->unlock();
	// ����ڰ� �������� ���ؽ� �����͸� ����Ͽ� ���ؽ��� lock �ϱ� (���̻� �ڵ��� �ƴϴ�)
	// Ȥ�� �ٸ� ����ũ ���̳� ������� ����Ͽ�, ���ؽ��� �����ϰ� �� �� ����
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