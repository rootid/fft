//Student Attendance Record I
//You are given a string representing an attendance record for a student. The
//record only contains the following three characters:
//'A' : Absent.
//'L' : Late.
//'P' : Present.
//A student could be rewarded if his attendance record doesn't contain more
//than one 'A' (absent) or more than two continuous 'L' (late).
//You need to return whether the student could be rewarded according to his
//attendance record.
//Example 1:
//Input: "PPALLP"
//Output: True
//Example 2:
//Input: "PPALLL"
//Output: False

#include "../headers/global.hpp"

//######################### regex_search #########################
bool checkRecord(string s) {
    return !regex_search(s, regex("A.*A|LLL"));
}

//######################### count #########################
bool checkRecord(string s) {
  return count(s.begin(), s.end(), 'A') < 2 && s.find("LLL") == string::npos;
}

//####################################### Ugly #######################################
bool checkRecord(string s) {
     int cnt2 = 0;
     int cntL = 1;
     for(auto c:s) {
         if(c == 'A' && cnt2++ >= 1 ) {
             return false;
         }
         if(c == 'L' && ++cntL >= 2) {
             cout << cntL << endl;
             //return false;
         } else if(c != 'L') {
             cntL = max(1,cntL-1);
         }
     }
   return true;
}

//############################## pytonic ##############################
//def check_record(s)
//  !(s.count("A") > 1 || s.include?("LLL"))
//end
//def checkRecord(self, s):
//    return not re.search('A.*A|LLL', s)
//def checkRecord(self, s):
//    return not (s.count('A') > 1 or 'LLL' in s)



int main() {

  checkRecord("PPALLL");
}
