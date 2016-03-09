#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// void replace (,
//                 const T& old_value, const T& new_value)
// {
//   while (first!=last) {
//     if (*first == old_value) *first=new_value;
//     ++first;
//   }
// }

 //  std::cout << "B contains:";
 // for (std::vector<int>::iterator it=B.begin(); it!=B.end(); ++it)
 //     std::cout << ' ' << *it;
 //   std::cout << '\n';


int solution(int K, int L, int M, int N, int P, int Q, int R, int S) {
    // write your code in C++11 (g++ 4.8.2)
  int minRightx = M > R ? R:M;
  int maxLeftx = P > K ? P:K;
  int minTopY = N > S ? S:N;
  int maxButtonY = L > Q ? L:Q;
  int overlap = 0;
  if (maxLeftx > minRightx && maxButtonY > minTopY) {

  } else {
    overlap =   abs(minRightx - maxLeftx) * abs(minTopY - maxButtonY);    
  }

  long long area1 = abs((long long)(M-K)*(N-L));
  long long area2 = abs((long long)(R-P)*(S-Q));
  std::cout << "area1 : " << area1 << ", area2 : " << area2 << ", overlap : " << overlap << endl;

  long long sum = area1 + area2 - overlap;
  if (sum > 2147483647)
  {
    sum = -1;
  }
  return sum;

}


int main ()
{
 
  // int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
  // std::vector<int> myvector (myints, myints+8);            // 10 20 30 30 20 10 10 20

  // std::replace (myvector.begin(), myvector.end(), 20, 99); // 10 99 30 30 99 10 10 99
  // // std::cout << "myvector.begin() : " << myvector.begin() << endl;

  // print out the result:
  // std::vector<int> A = {1,5,2,1,4,0};
  // cout << solution(A) << endl;
  // std::vector<int> B = {2147483640,2147483640,1,1};
  cout << "solution:" << solution(-2147483640,-2147483640,0,0,0,0,214748364,214748364) << endl;


  // string mystring;
  // mystring = "This is the initial string content";
  // cout << mystring << endl;

  // char question1[] = "What is your name? ";
  // string question2 = "Where do you live? ";
  // char answer1 [80];
  // string answer2;
  // cout << question1;
  // cin >> answer1;
  // cout << question2;
  // cin >> answer2;
  // cout << "Hello, " << answer1;
  // cout << " from " << answer2 << "!\n";
  return 0;
}

// long factorial (long a)
// {
//   if (a > 1)
//    return (a * factorial (a-1));
//   else
//    return 1;
// }
/*
int main ()
{
  long number;
  do {
    cout << "enter a number(0 to exit) :";
    cin >> number;
    cout << number << "! = " << factorial (number) << endl;    
  } while (number != 0);
  return 0;
}
*/