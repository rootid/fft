//Binary Watch
//A binary watch has 4 LEDs on the top which represent the hours (0-11), and
//the 6 LEDs on the bottom represent the minutes (0-59).
//Each LED represents a zero or one, with the least significant bit on the
//right.
//For example, the above binary watch reads "3:25".
//Given a non-negative integer n which represents the number of LEDs that are
//currently on, return all possible times the watch could represent.
//Example:
//Input: n = 1
//Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08",
//"0:16", "0:32"]
//Note:
//The order of output does not matter.
//The hour must not contain a leading zero, for example "01:00" is not valid,
//it should be "1:00".
//The minute must be consist of two digits and may contain a leading zero, for
//example "10:2" is not valid, it should be "10:02".

#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
//Good
vector<string> readBinaryWatch(int num) {
    vector<string> result;
    if(num>8 || num <= 0){  //impossible if num>8 because the max time is 11:59
        return result;
    }
    stringstream ss;
    for(int h=0;h<12;h++) {
        for(int m=0;m<60;m++) {
            if ( bitset<10>( (h << 6) + m).count() == num ) {
            //if ( bitset<16>( (h * 64 ) + m).count() == num ) {
                if(m >= 10) {
                    ss << h << ":" << m;
                } else {
                   ss << h << ":0" << m;
                }
                result.push_back(ss.str());
                stringstream().swap(ss);
            }
        }
    }
    return result;
}

//Bad
void genWatchCandidates(vector<int>& sample_set,vector<int>& sample_wt
    ,vector<int>& visit,int k,int noc,vector<string>& result) {
       if(k == noc) {
           int result_ = 0;
           for(int i=0;i<sample_set.size();i++) {
               if(sample_set[i] == 1) {
                   result_ += sample_wt[i];
               }
           }
           stringstream ss_hr;
           stringstream ss_min;
           int result_hr = result_ / 60;
           int result_min = result_ % 60;
           ss_hr << result_hr;
           ss_min << result_min;
           string hr = ss_hr.str();
           string r_str = "";
           if(result_hr  == 0) {
             hr = "0" + ss_hr.str();
           }
           if(result_min < 10) {
              r_str = hr + ":0" + ss_min.str();
           } else {
              r_str = hr + ":" + ss_min.str();
           }
           //cout << r_str << endl;
           result.push_back(r_str);
           ss_hr.str("");
           ss_min.str("");
           ss_min.clear();
           ss_min.clear();
           //stringstream().swap(ss_hr);
           //stringstream().swap(ss_min);
           k = 0;
           return;
       }
       for(int i=0;i<sample_set.size();i++) {
           if(visit[i] == 0) {
              sample_set[i] = 1;
              visit[i] = 1;
              genWatchCandidates(sample_set,sample_wt,visit,k+1,noc,result);
              sample_set[i] = 0;
              visit[i] = 0;
           }
       }
}

vector<string> readBinaryWatch(int num) {
    vector<int> sample_set(10,0);
    vector<int> sample_wt( {60,120,240,480,1,2,4,8,16,32} );
    int k = 0;
    vector<string> result;
    vector<int> visit(10,0);;
    genWatchCandidates(sample_set,sample_wt,visit,k,num,result);
    return result;
}
int main() {
  readBinaryWatch(1);
  //readBinaryWatch(2);
}
