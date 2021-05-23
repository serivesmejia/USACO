/*
ID: s3rives1
TASK: friday
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ofstream fout ("friday.out");
ifstream fin ("friday.in");

// saturday, sunday, monday, tuesday... friday
int weekdays_count[] = { 0, 0, 0, 0, 0, 0, 0 };

int days_in_month(int month, bool is_leap) {
  int days = 31;

  if(month == 2) {
    if(is_leap) {
      days = 29;
    } else {
      days = 28;
    }
  } else if(month == 4 || month == 6 || month == 9 || month == 11) {
    days = 30;
  }

  return days;
}

int main() {
  int years = 0;

  fin >> years;

  int total_days = 0;

  int weekday = 2;

  for(int i = 0 ; i <= (years - 1) ; i++) {
    int actual_year = i + 1900;

    // leap years should be divisible by four
    bool is_leap = (actual_year % 4 == 0);

    // century years are a special case,
    // they must also be divisible by four hundred
    if(actual_year % 100 == 0) {
      is_leap = is_leap && actual_year % 400 == 0;
    }

    for(int j = 1 ; j <= 12 ; j++) {
      for(int k = 1 ; k <= days_in_month(j, is_leap) ; k++) {
        if(k == 13) {
          if(weekday >= 1 && weekday < 7) {
            weekdays_count[weekday]++;
          } else {
            weekdays_count[weekday-7]++;
          }
        }

        weekday++;
        total_days++;

        if(weekday > 7) weekday = 1;
      }
    }
  }

  cout << total_days << " \n";

  for(int i = 0 ; i < 7 ; i++) {
    fout << weekdays_count[i];

    if(i != 6) {
      fout << " ";
    } else {
      fout << "\n";
    }
  }

  return 0;
}
