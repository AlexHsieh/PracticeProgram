/*
Questions: Equi
============
A zero-indexed array A consisting of N integers is given. An equilibrium index of this array is any integer P such that 0 ≤ P < N and the sum of elements of lower indices is equal to the sum of elements of higher indices, i.e. 
A[0] + A[1] + ... + A[P−1] = A[P+1] + ... + A[N−2] + A[N−1].
Sum of zero elements is assumed to be equal to 0. This can happen if P = 0 or if P = N−1.

For example, consider the following array A consisting of N = 8 elements:

  A[0] = -1
  A[1] =  3
  A[2] = -4
  A[3] =  5
  A[4] =  1
  A[5] = -6
  A[6] =  2
  A[7] =  1
P = 1 is an equilibrium index of this array, because:

A[0] = −1 = A[2] + A[3] + A[4] + A[5] + A[6] + A[7]
P = 3 is an equilibrium index of this array, because:

A[0] + A[1] + A[2] = −2 = A[4] + A[5] + A[6] + A[7]
P = 7 is also an equilibrium index, because:

A[0] + A[1] + A[2] + A[3] + A[4] + A[5] + A[6] = 0
and there are no elements with indices greater than 7.

P = 8 is not an equilibrium index, because it does not fulfill the condition 0 ≤ P < N.

Write a function:

int solution(int A[], int N);

that, given a zero-indexed array A consisting of N integers, returns any of its equilibrium indices. The function should return −1 if no equilibrium index exists.

For example, given array A shown above, the function may return 1, 3 or 7, as explained above.

Assume that:

N is an integer within the range [0..100,000];
each element of array A is an integer within the range [−2,147,483,648..2,147,483,647].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).
Elements of input arrays can be modified.

*/



#include <iostream>
#include <vector>
using namespace std;

// int solution(int N) {
//     // write your code in C++11 (g++ 4.8.2)
//   std::vector<int> binaryVector;
//   int divi = N;
//   do {
//     int rema = divi % 2;
//     binaryVector.push_back(rema);
//     divi = divi /2;
//   }while(divi != 0);
  
//   std::reverse(binaryVector.begin(),binaryVector.end());
  
// }

int solution(vector<int> &A) 
// int solution(int A[]) 
{
    // write your code in C++11 (g++ 4.8.2)
  int count = A.size();
  int sum = 0;
  for (vector<int>::size_type i = 0; i < count; ++i)
  {
    sum = sum + A[i];
  }

  cout << "sum:" << sum << endl;
  
  int sum1 = 0;
  int sum2 = 0;
  for (int j = 0; j < count; ++j)
  {
    if (j == 0)
    {
      sum2 = sum;
    } else if(j == count-1) {
      sum1 = sum;
    } else {
      sum1 = sum1 + A[j-1];
      sum2 = sum - sum1 - A[j];      
    }

    cout << "abs(sum-sum1):" << abs(sum - sum1) << endl;
    cout << "abs(sum-sum2):" << abs(sum-sum2) << endl;
    cout << "---------------" << endl;
    if (abs(sum - sum1) == abs(sum-sum2))
    {
      return j;
    }
  }
  return -1;

}

int main ()
{
 
  // print out the result:
  std::vector<int> B = {-1,3,-4,5,1,-6,2,1};
  cout << solution(B) << endl;

  return 0;
}