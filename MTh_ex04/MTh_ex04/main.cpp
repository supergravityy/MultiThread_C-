#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

atomic<int> cnt(0); // 아토믹으로 선언

void increment(int iterations)
{
	for (int i = 0; i < iterations; i++)
		cnt++;

	// 아토믹으로 사용하면, 해당 변수를 사용할 때, asm 단에서 cnttxt 스위칭이 발생하지 않음
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

	cout << "최종 카운터 값 : " << cnt << endl;

	return 0;
}