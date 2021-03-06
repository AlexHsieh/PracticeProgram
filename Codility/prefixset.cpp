/*
PrefixSet
=======================
A non-empty zero-indexed array A consisting of N integers is given. The first covering prefix of array A is the smallest integer P such that 0≤P<N and such that every value that occurs in array A also occurs in sequence A[0], A[1], ..., A[P].

For example, the first covering prefix of the following 5−element array A:

A[0] = 2
A[1] = 2
A[2] = 1
A[3] = 0
A[4] = 1
is 3, because sequence [ A[0], A[1], A[2], A[3] ] equal to [2, 2, 1, 0], contains all values that occur in array A.

Write a function

int solution(int A[], int N);

that, given a zero-indexed non-empty array A consisting of N integers, returns the first covering prefix of A.

For example, given array A such that

A[0] = 2
A[1] = 2
A[2] = 1
A[3] = 0
A[4] = 1
the function should return 3, as explained above.

Assume that:

N is an integer within the range [1..1,000,000];
each element of array A is an integer within the range [0..N−1].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).
Elements of input arrays can be modified.
*/

/*
complie :  g++ -std=c++11 prefixset.cpp -o prefixset
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int solution(vector<int> &A) 
// int solution(int A[]) 
{
    // write your code in C++11 (g++ 4.8.2)
  int count = A.size();
  std::vector<int> B = {};
  for (int i = 0; i<10; i++ )
        B.push_back(-1);

  int index = 0;
  // for (vector<int>::size_type i = 0; i < count; ++i)
  for (int i = 0; i < count; ++i)
  {
    //replace arr B based on A value
    // std::cout << "i=" << i <<", A[i] : " << A[i] << ", B[A[i]] : " << B[A[i]] << endl;
    if (B[A[i]] == -1) {
      std::vector<int>::iterator it;
      it=B.begin()+A[i];
      std::replace(it,it+1,-1,1);      
      index = i;
    }
  }
  
  return index;

}

int main ()
{

  // print out the result:
  std::vector<int> A = {2,2,1,0,1,2};
  cout << solution(A) << endl;


  return 0;
}
