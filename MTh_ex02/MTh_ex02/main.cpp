#include <iostream>
#include <thread>

using namespace std;

void printMSG(int n, int num)
{
	for (int i = 0; i < n; i++)
		cout << "Hello world! This is thread " << num << endl;
}

int main()
{
	thread th1(printMSG, 5, 1);
	thread th2(printMSG, 10, 2);

	th1.join();
	th2.join();
	return 0;
}