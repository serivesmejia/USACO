/*
ID-1: s3rives1
TASK: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

ofstream fout ("beads.out");
ifstream fin ("beads.in");

int beads_amount;
vector<char> beads;

struct collectedbeads {
  int starting_index = 0;
  int amount = 0;
  char colour;
};

collectedbeads *biggest_c_beads = NULL;

int main() {
  int line_number = 0;
  string line;

  while(getline(fin, line)) {
    if(line_number == 0) {
      istringstream is(line);
      is >> beads_amount;
    } else if(line_number == 1) {
      for(int i = 0 ; i < beads_amount*2 ; i++) {
        int actual_i = i;

        if(actual_i >= beads_amount) {
          actual_i -= beads_amount;
        }

        cout << actual_i << " : ";

        char colour = line[actual_i];
        if(biggest_c_beads != NULL) {
          if(biggest_c_beads->colour != 'w')
          colour = biggest_c_beads->colour;
        }

        collectedbeads *c_beads = new collectedbeads();
        c_beads->starting_index = actual_i;
        c_beads->colour = colour;

        for(int j = actual_i ; j < beads_amount*2 ; j++) {
          int actual_j = j;
          if(actual_j >= beads_amount) {
            actual_j -= beads_amount;
          }

          char curr_colour = line[actual_i + actual_j];
          cout << actual_j << ",";// << curr_colour << " ";

          if(curr_colour == colour || curr_colour == 'w') {
            c_beads->amount++;
          } else {
            break;
          }
        }

        if(biggest_c_beads == NULL) {
          biggest_c_beads = c_beads;
        } else {
          if(c_beads->amount > biggest_c_beads->amount) {
            delete biggest_c_beads;
            biggest_c_beads = c_beads;
          }
        }

        cout << "\n";
      }
    } else {
      break;
    }

    line_number++;
  }

  cout << biggest_c_beads->amount << "\n";

  return 0;
}
