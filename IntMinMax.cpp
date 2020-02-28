#include <iostream>

using namespace std;

int getMin(int a[10], int num_vars){
  int min = a[0];                       // Initialize minimum to the first element 
  for(int i = 0; i < num_vars; i++){    //  Check for minimum for each element we have
    if(a[i] < min){
      min = a[i];                       //Update if applicable
    }
  }
  return min;
}

int getMax(int a[10], int num_vars){
  int max = a[0];                      //Initialize maximum to the first element
  for(int i = 0; i < num_vars; i++){   // Check for maximum for each element we have
    if(a[i] > max){
      max = a[i];                      //Update if applicable
    }
  }
  return max;
  
}
int main(){
  int user_nums[10];                  //Array of user inputted numbers
  int user_input;                     //Var to hold input
  int user_count = 0;                 //Number of variables inputted by user
  for(int i = 0; i < 10; i++){        //For a max of 10 times, askk for input
    cout << "Please input a number: ";
    cin >> user_input;
    user_count += 1;
    user_nums[i] = user_input; 
    
    cout << "Min: " << getMin(user_nums, user_count) << " , Max:" << getMax(user_nums, user_count) << endl; //Print min and max  
  }
  
  return 0;
}

