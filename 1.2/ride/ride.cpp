/*
ID: s3rives1
TASK: ride
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string name = "ride";

int a_letter_code = (int)'a';

int main() {
  ofstream fout (name + ".out");
  ifstream fin (name + ".in");

  string line;
  int line_number = 0;

  int comet_number = 1;
  int group_number = 1;

  //iterate through the lines of the file
  while(getline(fin, line)) {
    //iterate through the characters of the line
    for(string::size_type i = 0 ; i < line.size() ; i++) {
      // make lowercase to make results the same independent of capitalization
      char lower_char = ::tolower(line[i]);

      // convert char to int and start counting from 96 since a starts in 97
      // and the charset seems to go in order from continuous a-z. blank spaces
      // are considered 0, so if we find a whitespace we just skip the a-z normal calculation.
      int letter_number = (int) lower_char - (a_letter_code - 1); // start counting from a

      if(letter_number < 1 || letter_number > 26)
        continue;

      if(line_number == 0)
        group_number *= letter_number;
      else if(line_number == 1)
        comet_number *= letter_number;
      else
        break;
    }

    line_number++;
  }

  if(group_number % 47 == comet_number % 47)
    fout << "GO";
  else
    fout << "STAY";

  fout << "\n" << "\0";

  return 0;
}
