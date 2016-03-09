#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> &A) 
{
    unsigned int count = A.size();
    int sum = 0;
    for(vector<int>::size_type i=0;i<count;i++) {
        sum = sum + A[i];
    }
    
    int sum1 = 0;
    int sum2 = 0;
    // if (sum == 0) {
    //     return
    // }
    for(vector<int>::size_type i=0;i<count;i++) {
        if (i==0){
            sum1 = 0;
            sum2 = sum - A[0];
        } else if (i!=count-1) {
            sum1 = sum1 + A[i-1];
            sum2 = sum - sum1 - A[i];
        }else {
            sum1 = sum - A[i];
            sum2 = 0;
        }
        
        if(sum1 == sum2){
            return i;
        }
    }
    return -1;   
}

int main ()
{
 
  // print out the result:
  std::vector<int> B = {-1,3,-4,5,1,-6,2,1};
  cout << solution(B) << endl;


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

long factorial (long a)
{
  if (a > 1)
   return (a * factorial (a-1));
  else
   return 1;
}
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