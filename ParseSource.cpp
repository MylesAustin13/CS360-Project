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
  vector<string> para_types;
  int para_count;
};

string getName(string header){
  size_t paren_index = header.find('(');
  return header.substr(0, paren_index);

}

vector<string> getParas(string header){
  size_t paren_index = header.find('('); 
  size_t space_index = header.find(' ', paren_index);
  size_t comma_index = header.find(',', space_index);

  size_t letter_index = header.find_first_of("abcdefghijklmnopqrstuvwxyz", paren_index);
  vector<string> result;
    
  result.push_back(header.substr(letter_index, space_index - letter_index)); //from the start of the word to the space

  comma_index = header.find(',',comma_index); //Find the next comma
  letter_index = header.find_first_of("abcdefghijklmnopqrstuvwxyz", comma_index); //Find next parameter type
  space_index = header.find(' ', letter_index);//Find the space after it
  
  while(comma_index != string::npos){ //While there are commas
    
    result.push_back(header.substr(letter_index, space_index - letter_index)); //Add to vector
    comma_index = header.find(',',comma_index+1); //Find the next comma
    letter_index = header.find_first_of("abcdefghijklmnopqrstuvwxyz", comma_index); //Find next parameter type
    space_index = header.find(' ',letter_index+2); //Find the next space after the parameter type
    
    
		  
  }
  return result;

}

string* getLines(string code_text, int* code_size){
  code_text += "\n";                                            //Append a newline for safety
  size_t current_index = 0;
  size_t newline_index = 0;
  
  int num_lines = count(code_text.begin(), code_text.end(), '\n' ); //Count all of the newlines
  
  string* code_array = new string[num_lines];                      //Make an array to hold all of the lines
  
  for(int i = 0; i < num_lines; i++){                               //For each line
        
    newline_index = code_text.find("\n", current_index);            //find the next newline
    
    code_array[i] = code_text.substr(current_index, newline_index - current_index); //take the line from the current postition to the next newline and store it
    current_index = newline_index + 1;                              //update the current position
    
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
  //cout << "Got the lines" << endl;
  int header_indices[*line_count];
  int header_indices_size = 0;

  
  //Search for all function headers
  for(int i = 0; i < *line_count; i++){ //Go through every line
    code_words.clear();                 //Empty the vector
    string temp_word = "";                   //Create a temporary word holder
    string temp_line = lines[i];             //Create a temporary line holder

    for(int x = 0; x < temp_line.size();x++){ //In each line
      
      if(temp_line[x] != ' ' && x < temp_line.size() - 1){  //Not a space, not at the very end, not the first character
	temp_word += temp_line[x];   //Add it to word	
      }
      else{
	if(x == temp_line.size() - 1){
	  temp_word += temp_line[x];
	}
	if( temp_word != ""){
	  code_words.push_back(temp_word); //Add this 'word' to the vector
	  temp_word = "";               //Reset the holder
	}
	
      }

    }

    //All words found
    
    bool found_bracket = false;
    bool found_paren = false;
    
    if(code_words.size() > 0 && (code_words[0] == "int" || code_words[0] == "string" || code_words[0] == "bool" || code_words[0] == "void")){ //First word is the type
      //Could be var or function
      
      for( int s = 1; s < code_words.size(); s++){  //Find the opening brace, if there is one
	if(code_words[s].find('{') != string::npos){
	  
	  found_bracket = true;
	}
	if(code_words[s].find('(') != string::npos){
	  
	  found_paren = true;
	}
      }
      
      if(found_paren && found_bracket){ //Open parenthesis and bracket found

	       
	//Must be a function
	int open_brackets = 1;  //Count { and }
	int close_brackets = 0;
	int l = i + 1;         //Iterate through line number
	
	while(open_brackets != close_brackets && l < *line_count){ //Go start looking for {}
	  open_brackets += count(lines[l].begin(), lines[l].end(), '{');
	  close_brackets += count(lines[l].begin(), lines[l].end(), '}');
	  
	  l++;
	  
	}
	
	func temp = {getName(code_words[1]), code_words[0], i, l};
	
	if(code_words[1].find(')') == string::npos){ //If there is a space between ( and ), check for args
	  
	  temp.para_types = getParas(temp_line);
	  temp.para_count = temp.para_types.size();
	}
       
	func_list.push_back(temp);
	
      }
      else{
	//Must be a global variable

	
      }
    }
   
  }
  
  cout << "The list: " << endl;  //FOR TESTING
  for(int j = 0; j < func_list.size(); j++){
    cout << func_list[j].ret_type << ", " << func_list[j].name << ", " << func_list[j].start_index << "-" << func_list[j].end_index << endl;

    if(func_list[j].para_count == 0){
      cout << "No parameters." << "\n" <<  endl;
    }
    else{
      cout << func_list[j].para_count << " parameter(s)." << endl;
      cout << "Parameters: " << endl;
      for(int q = 0; q < func_list[j].para_count;q++){
	cout << func_list[j].para_types[q] << ", ";
      }
      cout << "\n" << endl;
    }
  }
  
  
  delete line_count;
  delete[] lines;
  return 0;
}


int main(){

  //string test_code = "int main(){\nstring code = \"\";\n  cout << \"Input the code: \";\n  cin >> code;\n  parseCode(code);\n}";
  string real_code = "";
  string code_line = "";
  
  
  ifstream codeFile("code2.txt");
  
  if (codeFile){
    while( !getline( codeFile, code_line).eof()){
      
      code_line += '\n';
      real_code += code_line;
      
     
    }
    
  }
  cout << real_code << endl;

  parseCode(real_code);
}
