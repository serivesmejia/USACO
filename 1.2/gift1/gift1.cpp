/*
ID: s3rives1
TASK: gift1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

ofstream fout ("gift1.out");
ifstream fin ("gift1.in");

struct friend_data {
  string name;

  int money = 0;

  int giving_to = 0;
  int money_to_each = 0;
};

map<string, friend_data*> friends;
int friends_amount;

vector<string> original_friends_order;

vector<string> split_string_by_spaces(string str) {
  vector<string> words;

  istringstream ss(str);
  string word;

  while(ss >> word) {
    words.push_back(word);
  }

  return words;
}

int main() {
  string line;
  int line_number = 0;

  friend_data *current_giver = NULL;

  while(getline(fin, line)) {
    //grab the amount of friends from the first line
    if(line_number == 0) {
      istringstream line_is(line);
      line_is >> friends_amount;

      goto before_end;
    } else if(line_number <= friends_amount) {
      friend_data* data = new friend_data();
      data->name = line;

      friends.insert({line, data});
      original_friends_order.push_back(line);

      cout << line << "\n";

      goto before_end;
    }

    start:
    if(current_giver == NULL) {
      current_giver = friends[line];

      current_giver->giving_to = -1;

      cout << current_giver->name << " is giving" << "\n";
    } else if(current_giver != NULL && current_giver->giving_to == -1) {
      vector<string> money_and_giving = split_string_by_spaces(line);

      int to_give_money;

      istringstream money_is(money_and_giving[0]);
      money_is >> to_give_money;

      current_giver->money -= to_give_money;

      istringstream giving_to_is(money_and_giving[1]);
      giving_to_is >> current_giver->giving_to;

      if(current_giver->giving_to == 0) {
        current_giver->giving_to = -1;
        current_giver = NULL;
        continue;
      }

      int remainder = 0;

      if(to_give_money != 0) {
        current_giver->money_to_each = to_give_money / current_giver->giving_to;
        remainder = to_give_money % current_giver->giving_to;
      } else {
        current_giver->money_to_each = 0;
      }

      current_giver->money += remainder;

      cout << current_giver->name << " is giving " << to_give_money
        << " to " << current_giver->giving_to
        << ", remainder " << remainder
        << ", has " << current_giver->money
        << "\n";
    } else if(current_giver != NULL && current_giver->giving_to > 0) {
      friend_data *f = friends[line];

      f->money += current_giver->money_to_each;

      current_giver->giving_to--;

      cout << current_giver->name << " gave " << current_giver->money_to_each <<
        " to " << f->name << "\n";
    } else {
      current_giver = NULL;
      goto start;
    }

    before_end:
    line_number++;
  }

  for(string name : original_friends_order) {
    fout << name << " " << friends[name]->money << "\n";
  }

  return 0;
}
