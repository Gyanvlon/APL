#include <iostream>
#include <vector>
using namespace std;
int main() {

 vector<int>* vec = new vector<int>();
 vec->push_back(1);
 vec->push_back(2);
 cout << "Vector:";
 for (int i : *vec) cout << i <<",";

 delete vec;
 return 0;
 }