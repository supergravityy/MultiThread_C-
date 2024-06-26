#include <iostream>
#include <thread>

using namespace std;

void printNum(int threadNum)
{
	for (int i = 0; i < 10; i++)
		cout << "This is Thread number : " << threadNum << ", repeat time : " << i+1 << endl;
}

void isFinished(thread& th1, thread& th2, thread& th3, thread& th4, thread& th5)
{
	//while (!(th1.join() && th2.join() && th3.join() && th4.join() && th5.join())); 

	// join은 반환값이 없다 , 무한루프로 기다리기 X

	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();
}

int main()
{
	thread th1(printNum, 1);
	thread th2(printNum, 2);
	thread th3(printNum, 3);
	thread th4(printNum, 4);
	thread th5(printNum, 5);

	isFinished(th1, th2, th3, th4, th5);

	return 0;
}