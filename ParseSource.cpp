#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>


using namespace std;

struct func {
  string name;
  string ret_type;
  // string text;
  int start_index;
  int end_index;

};

string * getLines(string code_text, int* code_size){
  code_text += "\n";                                            //Append a newline for safety
  size_t current_index = 0;
  size_t newline_index = 0;
  //cout << "Here?";
  int num_lines = count(code_text.begin(), code_text.end(), '\n' ); //Count all of the newlines
  //cout << num_lines;
  string* code_array = new string[num_lines];                      //Make an array to hold all of the lines
  
  for(int i = 0; i < num_lines; i++){                               //For each line
    
    
    //code_array[i] = code_text.substr(current_index);
    
    newline_index = code_text.find("\n", current_index);            //find the next newline
    /*if(newline_index == string::npos){
      cout << newline_index;
      code_array[i] = code_text.substr(current_index);
    } */
    
    //cout << newline_index;
    cout << i << endl;
    code_array[i] = code_text.substr(current_index, newline_index - current_index); //take the line from the current postition to the next newline and store it
    current_index = newline_index + 1;                              //update the current position
    
    cout << code_array[i] << endl;

  }
  *code_size = num_lines;
  return code_array;

}

int parseCode(string code){
  
  string type_keywords[4] = {"int", "string", "bool", "void"};
  vector<string> code_words;  //Make a vector to hold onto each word in the code, separated by whitespace
  vector<func> func_list;    // Hold onto all functions
  
  int * line_count = new int;
  string* lines = getLines(code, line_count);

  int header_indices[*line_count];
  int header_indices_size = 0;

  //cout << "Hey!" << endl;
  //Search for all function headers
  for(int i = 0; i < *line_count; i++){ //Go through every line
    code_words.clear();                 //Empty the vector
    string temp_word = "";                   //Create a temporary word holder
    string temp_line = lines[i];             //Create a temporary line holder
    //cout << "i is: " << i << endl;
    // cout << "temp_line is: " << temp_line << endl;
    for(int x = 0; x < temp_line.size();x++){ //In each line
      //cout << "x is: " << x << endl;
      //cout << temp_line << endl;
      
      if(temp_line[x] != ' ' && x < temp_line.size() - 1){  //Not a space, not at the very end, not the first character
	temp_word += temp_line[x];   //Add it to word	
      }
      else{
	if(x == temp_line.size() - 1){
	  temp_word += temp_line[x];
	}
	if( temp_word != ""){
	  code_words.push_back(temp_word); //Add this 'word' to the vector
	  cout << temp_word << endl;
	  temp_word = "";               //Reset the holder
	}
	//x++;                           //move x past the space
      }

    }

    //All words found
    //cout << "Words found!" << endl;

    bool found_bracket = false;
    if(code_words[0] == "int" || code_words[0] == "string" || code_words[0] == "bool"){ //First word is the type
      //Could be var or function
      for( int s = 1; s < code_words.size(); s++){  //Find the opening brace, if there is one
	if(code_words[s].find('{') != string::npos){
	  found_bracket = true;
	}
      }
      
      if(code_words[1].find('(') != string::npos && found_bracket){ //Open parenthesis and bracket found

	       
	//Must be a function
	int open_brackets = 1;  //Count { and }
	int close_brackets = 0;
	int l = i + 1;         //Iterate through line number
	//cout << "I think" <<endl;
	while(open_brackets != close_brackets && l < *line_count){ //for(int l = i+1; l < *line_count; l++){ //Go start looking for {}
	  open_brackets += count(lines[l].begin(), lines[l].end(), '{');
	  close_brackets += count(lines[l].begin(), lines[l].end(), '}');
	  
	  l++;
	}
	func temp = {"temp", code_words[0], i, l};
	//	cout << temp.start_index << " ," << temp.end_index << endl;
	func_list.push_back(temp);
	i = l;                                                     //Move i, avoid rescanning lines
      }
      else{
	//Must be a global variable

	
      }
    }
  }
  cout << "The list: " << endl;
  for(int j = 0; j < func_list.size(); j++){
    cout << func_list[j].ret_type << ",    " << func_list[j].start_index << "-" << func_list[j].end_index << endl;

  }
  
  
  delete line_count;
  delete[] lines;
  return 0;
}


int main(){

  string test_code = "int main(){\nstring code = \"\";\n  cout << \"Input the code: \";\n  cin >> code;\n  parseCode(code);\n}";
  string real_code = "";
  string code_line = "";
  
  ifstream codeFile("code.txt");
  if (codeFile){
    while( getline( codeFile, code_line)){
      real_code += code_line;
      real_code += '\n';
    }
  }

  //cout << test_code << endl;
  //cout << "Input the code: " << endl;
  //cin >> code;
  //cout << code;
  
  parseCode(real_code);
}
