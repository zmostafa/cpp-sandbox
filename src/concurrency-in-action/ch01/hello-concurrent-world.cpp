#include <iostream>
#include <thread>

void hello()
{
    std::cout << "Hello Concurrent world .. ! " << std::endl;
}

int main()
{
  std::thread child(hello);
  child.join();
}
