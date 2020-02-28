#include <iostream>

using namespace std;

int getMin(int a[10], int num_vars){
  int min = a[0];
  for(int i = 0; i < num_vars; i++){
    if(a[i] < min){
      min = a[i];
    }
  }
  return min;
}

int getMax(int a[10], int num_vars){
  int max = a[0];
  for(int i = 0; i < num_vars; i++){
    if(a[i] > max){
      max = a[i];
    }
  }
  return max;
  
}
int main(){
  int user_nums[10];
  int user_input;
  int user_count = 0;
  for(int i = 0; i < 10; i++){
    cout << "Please input a number: ";
    cin >> user_input;
    user_count += 1;
    user_nums[i] = user_input;
    
    cout << "Min: " << getMin(user_nums, user_count) << " , Max:" << getMax(user_nums, user_count) << endl;  
  }
  
  return 0;
}

