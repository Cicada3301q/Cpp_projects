#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <vector>
//Author Quenten welch



std::string max_pali;


//a bool that checks if a given word is a palindrome, returns true iff yes
bool
is_palindrome( const std::string & s)
{
  for( size_t i = 0 ; i < s.size() / 2 ; i ++)
    if( tolower(s[i]) != tolower(s[s.size()-i-1]))
      return false;
  return true;
}


//function split that splits characted by white spaces to form words, once word has been formed it checks
//the words size again the current largest palindrome
//if the word size is larger it will check if the larger word is a palindrome if it is it will replace the current largest palindrom

std::vector<std::string>
split( const std::string & p_line)
{
  auto line = p_line + " ";
  std::vector<std::string> res;
  bool in_str = false;
  std::string curr_word = "";
  for( auto c : line) {
    if( isspace(c)) {
      if( in_str)
        if(curr_word.size() > max_pali.size())
	  if(is_palindrome(curr_word))
		max_pali = curr_word;
      in_str = false;
      curr_word = "";
    }
    else {
      curr_word.push_back(c);
      in_str = true;
    }
  }
  return res;
}

// global variable used in stdin_readline()
char buffer[8389000];

// reads in a line from STDIN
// loops until bytes read = 0
// returns empty string on EOF
std::string
stdin_readline()
{
  std::string result;
  while( read( STDIN_FILENO, & buffer, 8389000) > 0) {
    result = buffer;
    break;
  }
  return result;
}

// returns true if a word is palindrome
// palindrome is a string that reads the same forward and backward
//    after converting all characters to lower case


// returns the longest palindrome on standard input
// in case of ties for length, returns the first palindrome
// all input is broken into words, and each word is checked
// word is a sequence of characters separated by white space
// white space is whatever isspace() says it is
//    i.e. ' ', '\n', '\r', '\t', '\n', '\f'
std::string
get_longest_palindrome()
{

  while(1) {
    std::string line = stdin_readline();
    if( line.size() == 0) break;
    auto words = split( line);

  }
  return max_pali;
}

int
main()
{
  std::string max_pali = get_longest_palindrome();
  printf("Longest palindrome: %s\n", max_pali.c_str());
  return 0;
}

