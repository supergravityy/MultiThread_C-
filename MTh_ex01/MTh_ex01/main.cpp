#include <iostream>
#include <thread>

void printMSG()
{
    std::cout << "Hello from thread!" << std::endl;
}

int main()
{
    std::thread th(printMSG);   // 새로운 스레드 생성
    th.join();                  // 메인 스레드가 th 스레드가 종료될 때 까지 대기

    /*-----------------------*/
    // join을 쓰는 이유 : 생성된 스레드는 프로세스에 종속되어 있기에, 
    // main이 끝나게 되면, 스레드가 정상종료되지않고 바로 종료됨.
    // 그래서 join 메서드를 사용하여 기다리는것.
    /*-----------------------*/

    return 0;
}