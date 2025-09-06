#include <iostream>
#include <functional>
using namespace std;
 function<int()> makeCounter() {

 int count = 0;
 return [=]() mutable {
 return ++count;
 };
}
  int main() {
 auto counter1 = makeCounter();
 cout << counter1() << endl; 
 cout << counter1() << endl;
 return 0;
 }