//Given a list of 24-hour clock time points in "Hour:Minutes" format, find the
//minimum minutes difference between any two time points in the list.
//Example 1:
//Input: ["23:59","00:00"]
//Output: 1
//Note:
//The number of time points in the given list is at least 2 and won't exceed
//20000.
//The input time is legal and ranges from 00:00 to 23:59.

//######################################## O(n) ########################################
int getTime(string timePoint) {
  int i=0;
  while (timePoint[i]!=':') i++;
  int hour = stoi(timePoint.substr(0,i));
  int mins = stoi(timePoint.substr(i+1));
  return 60*hour + mins;
}
int findMinDifference(vector<string>& timePoints) {
    int n = timePoints.size();
    int gap = 1440;
    //if(n>gap) return 0;
    vector<int> minutes(gap);
    for(auto tp : timePoints) {
        int t = getTime(tp);
        if(minutes[t] > 0) return 0;
        minutes[t] = 1;
    }
    int start = 0;
    //skip all first zeros
    while(minutes[start] == 0) start++;

    //init result to 1440
    int res = gap;
    for(int i=start+1; start<gap; ++i) {
        int next = i % gap;
        if(minutes[next] != 0) {
            res = min(res, (next - start + gap) % gap);
            start = i;
        }
    }
    return res;
}

//######################################## O(n log n) ########################################
int findMinDifference(vector<string>& timePoints) {
  vector<int> temp;
  int minDiff = 1440;
  int totalMin = 1440;
  for(int i=0;i<timePoints.size();i++) {
      string a, b;
      a.append(timePoints[i].substr(0, 2));
      b.append(timePoints[i].substr(3, 2));
      temp.push_back(atoi(a.c_str())*60+atoi(b.c_str()));
  }
  sort(temp.begin(), temp.end());
  for(int i=0;i<temp.size()-1;i++) {
      if(temp[i+1]==temp[i]) return 0;
      if(temp[i+1]-temp[i]<minDiff) minDiff=temp[i+1]-temp[i];
  }
  if(totalMin - temp[temp.size()-1]+temp[0]< minDiff) {
    minDiff = totalMin -temp[temp.size()-1]+temp[0];
  }
  return minDiff;
}
int findMinDifference(vector<string>& timePoints) {
    int size = timePoints.size();
    vector<int> vi;
    for (auto timePoint : timePoints)
    {
        int time = stoi(timePoint.substr(0, 2)) * 60 +
                   stoi(timePoint.substr(3));
        vi.push_back(time);
    }
    sort(vi.begin(), vi.end());
    int minDiff = vi[0] + 24*60 - vi[size-1];
    for(int i = 1; i < size; i++)
    {
        int diff = vi[i] - vi[i-1];
        if(minDiff > diff) minDiff = diff;
    }
    return minDiff;
}
//######################################## O(n log n) ########################################
int findMinDifference(vector<string>& times) {
  int n = times.size();
  sort(times.begin(), times.end());
  int mindiff = INT_MAX;
  for (int i = 0; i < times.size(); i++) {
    int diff = abs(timeDiff(times[(i - 1 + n) % n], times[i])); //diff between last and first
    diff = min(diff, 1440 - diff);
    mindiff = min(mindiff, diff);
  }
  return mindiff;
}
private:
int timeDiff(string t1, string t2) {
    int h1 = stoi(t1.substr(0, 2)); //08:59 (08)
    int m1 = stoi(t1.substr(3, 2));
    int h2 = stoi(t2.substr(0, 2));
    int m2 = stoi(t2.substr(3, 2));
    return (h2 - h1) * 60 + (m2 - m1);
}
