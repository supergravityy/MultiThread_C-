#include <iostream>
#include <thread>

void printMSG()
{
    std::cout << "Hello from thread!" << std::endl;
}

int main()
{
    std::thread th(printMSG);   // ���ο� ������ ����
    th.join();                  // ���� �����尡 th �����尡 ����� �� ���� ���

    /*-----------------------*/
    // join�� ���� ���� : ������ ������� ���μ����� ���ӵǾ� �ֱ⿡, 
    // main�� ������ �Ǹ�, �����尡 ������������ʰ� �ٷ� �����.
    // �׷��� join �޼��带 ����Ͽ� ��ٸ��°�.
    /*-----------------------*/

    return 0;
}