#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

atomic<int> cnt(0); // ��������� ����

void increment(int iterations)
{
	for (int i = 0; i < iterations; i++)
		cnt++;

	// ��������� ����ϸ�, �ش� ������ ����� ��, asm �ܿ��� cnttxt ����Ī�� �߻����� ����
}

int main()
{
	const int num_threads = 10;
	const int num_iterations = 1000;

	vector<thread> threads;

	for (int i = 0; i < num_threads; i++)
		threads.push_back(thread(increment, num_iterations));

	for (auto& th : threads)
		th.join();

	cout << "���� ī���� �� : " << cnt << endl;

	return 0;
}