#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool isWordValid(const std::string& word, const std::set<std::string>& dict);
void getWords(const std::string& input, const std::string& floating, size_t index,std::string current,std::set<std::string>& words);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> words;
		set<string> ValidWords;
    size_t index = count(in.begin(), in.end(), '-');
    getWords(in, floating, index, "", words);
		
		for (auto iter = words.begin(); iter != words.end(); ++iter) {
        if (isWordValid(*iter, dict)) {
          ValidWords.insert(*iter);
        }
    }
    return ValidWords;
}

bool isWordValid(const std::string& word, const std::set<std::string>& dict) {
    return dict.count(word);
}

// Define any helper functions here
void getWords(const std::string& input, const std::string& floating, size_t index,std::string current,std::set<std::string>& words){   

    //case 1
    if(current.size() == input.size()){ 
      words.insert(current); 
      return;
    }
    //case 2
		
    else if(input[current.size()] == '-'){
			std::string str;
      if(index != floating.size()){
        for(char character = 'a'; character <= 'z'; character++){
        	str = floating;
          if(str.find(character) != std::string::npos) str.erase(str.find(character), 1);
          getWords(input, str, index - 1, current + character, words);
        }
    	}
      else{
				for (const auto& character : floating) {
          str = floating;
          str.erase(str.find(character), 1);
          getWords(input, str, index - 1, current + character, words);
        }
        
      }
    }
		//case 3
    else{
			 current += input[current.size()];
        getWords(input, floating, index, current, words);   
    }
}



