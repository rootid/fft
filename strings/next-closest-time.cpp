//Next Closest Time
//Given a time represented in the format "HH:MM", form the next closest time by
//reusing the current digits. There is no limit on how many times a digit can
//be reused.
//You may assume the given input string is always valid. For example, "01:34",
//"12:09" are all valid. "1:34", "12:9" are all invalid.
//Example 1:
//Input: "19:34"
//Output: "19:39"
//Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39,
//which occurs 5 minutes later.  It is not 19:33, because this occurs 23 hours
//and 59 minutes later.
//Example 2:
//Input: "23:59"
//Output: "22:22"
//Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22.
//It may be assumed that the returned time is next day's time since it is
//smaller than the input time numerically.

//############################### solution 1 ###############################
//Just turn the clock forwards one minute at a time until you reach a time with
//the original digits.
from datetime import *

class Solution(object):
    def nextClosestTime(self, time):
        digits = set(time)
        while True:
            time = (datetime.strptime(time, '%H:%M') + timedelta(minutes=1)).strftime('%H:%M')
            if set(time) <= digits:
                return time

//############################### solution 2 ###############################
//Return the smallest time that uses the given digits, just make being larger
//than the input a priority.
def nextClosestTime(self, time):
    return min((t <= time, t)
               for i in range(24 * 60)
               for t in ['%02d:%02d' % divmod(i, 60)]
               if set(t) <= set(time))[1]

//#### increase the time until we reach one with the allowed digits. Using the given time as a character class in a regular expression.
public String nextClosestTime(String time) {
    int h = Integer.parseInt(time.substring(0, 2));
    int m = Integer.parseInt(time.substring(3));
    for (int t=60*h+m+1; ; t++) {
        String s = String.format("%02d:%02d", t / 60 % 24, t % 60);
        if (s.matches("[" + time + "]*"))
            return s;
    }
}

//######################################### Backtrack #########################################
This approach here is trying to find next digit for each postion in "HH:MM" from right to left. If the next digit is greater than current digit, return directly and keep other digits unchanged.
Here is the steps: (e.g. "17:38")

Retrieve all four digits from given string and sort them in asscending order, "17:38" -> digits[] {'1', '3', '7', '8'}

Apply findNext() from the right most digit to left most digit, try to find next greater digit from digits[] (if exist) which is suitable for current position, otherwise return the minimum digit (digits[0]):

"HH:M_": there is no upperLimit for this position (0-9). Just pick the next different digit in the sequence. In the example above, '8' is already the greatest one, so we change it into the smallest one (digits[0] i.e. '1') and move to next step: "17:38" -> "17:31"

"HH:_M": the upperLimit is '5' (00~59). The next different digit for '3' is '7', which is greater than '5', so we should omit it and try next. Similarly, '8' is beyond the limit, so we should choose next, i.e. '1': "17:38" -> "17:11"

"H_:MM": the upperLimit depends on digits[0]. If digits[0] == '2', then it should be no more than '3'; else no upperLimit (0-9). Here we have digits[0] = '1', so we could choose any digit we want. The next digit for '7' is '8', so we change it and return the result directly. "17:38" -> "18:11"

"_H:MM": the upperLimit is '2' (00~23). Here we don't need to change because we have found a greater available digit in previous position. So "18:11" is the disired next closest time.

class Solution {

    public String nextClosestTime(String time) {
        char[] result = time.toCharArray();
        char[] digits = new char[] {result[0], result[1], result[3], result[4]};
        Arrays.sort(digits);

        // find next digit for HH:M_
        result[4] = findNext(result[4], (char)('9' + 1), digits);  // no upperLimit for this digit, i.e. 0-9
        if(result[4] > time.charAt(4)) return String.valueOf(result);  // e.g. 23:43 -> 23:44

        // find next digit for HH:_M
        result[3] = findNext(result[3], '5', digits);
        if(result[3] > time.charAt(3)) return String.valueOf(result);  // e.g. 14:29 -> 14:41

        // find next digit for H_:MM
        result[1] = digits[0] == '2' ? findNext(result[1], '3', digits) : findNext(result[1], (char)('9' + 1), digits);
        if(result[1] > time.charAt(1)) return String.valueOf(result);  // e.g. 02:37 -> 03:00

        // find next digit for _H:MM
        result[0] = findNext(result[0], '2', digits);
        return String.valueOf(result);  // e.g. 19:59 -> 11:11
    }

    /**
     * find the next bigger digit which is no more than upperLimit.
     * If no such digit exists in digits[], return the minimum one i.e. digits[0]
     * @param current the current digit
     * @param upperLimit the maximum possible value for current digit
     * @param digits[] the sorted digits array
     * @return
     */
    private char findNext(char current, char upperLimit, char[] digits) {
        //System.out.println(current);
        if(current == upperLimit) {
            return digits[0];
        }
        int pos = Arrays.binarySearch(digits, current) + 1;
        while(pos < 4 && (digits[pos] > upperLimit || digits[pos] == current)) { // traverse one by one to find next greater digit
            pos++;
        }
        return pos == 4 ? digits[0] : digits[pos];
    }

//######################################### increament  #########################################
//1440 : 24hr
class Solution {
    int mins[4] = { 600, 60, 10, 1 }; //10hr 1hr 10min 1min
public:
    string nextClosestTime(string time) {
        size_t colon = time.find(':');
        int cur = stoi(time.substr(0, colon)) * 60 + stoi(time.substr(colon + 1));
        string next = "0000";
        for (int i = 1, d = 0; i <= 1440 && d < 4; i++) {
            int m = (cur + i) % 1440;
            for (d = 0; d < 4; d++) {
                next[d] = '0' + m / mins[d]; m %= mins[d];
                if (time.find(next[d]) == string::npos) break;
            }
        }
        return next.substr(0, 2) + ':' + next.substr(2, 2);
    }
};

//######################################### increament  #########################################
class Solution {
    static int[] mins = { 600, 60, 10, 1 };
    public String nextClosestTime(String time) {
        int colon = time.indexOf(':');
        int cur = Integer.valueOf(time.substring(0, colon)) * 60 + Integer.valueOf(time.substring(colon + 1));
        char[] next = new char[4];
        for (int i = 1, d = 0; i <= 1440 && d < 4; i++) {
            int m = (cur + i) % 1440;
            for (d = 0; d < 4; d++) {
                next[d] = (char)('0' + m / mins[d]); m %= mins[d];
                if (time.indexOf(next[d]) == -1) break;
            }
        }
        return new String(next, 0, 2) + ':' + new String(next, 2, 2);
    }
}

Solution 1:
we can try to increase the minute and the hour one by one. If all these four digits of the next time is in hashset, we find it and output! because these four digits are all reused.

    public String nextClosestTime(String time) {
        String[] val = time.split(":");
        Set<Integer> set = new HashSet<>();
        int hour = add(set, val[0]);
        int minu = add(set, val[1]);

        int[] times = new int[] {hour, minu};
        nxt(times);

        while (!contains(times[0], times[1], set)) {
            nxt(times);
        }
        return valid(times[0]) + ":" + valid(times[1]);
    }

    public void nxt(int[] time) {
        int hour = time[0];
        int minu = time[1];
        minu ++;
        if (minu == 60) {
            hour ++;
            minu = 0;
            if (hour == 24) hour = 0;
        }
        time[0] = hour;
        time[1] = minu;
    }

    public int add(Set<Integer> set, String timeStr) {
        int time = Integer.parseInt(timeStr);
        set.add(time / 10);
        set.add(time % 10);
        return time;
    }

    public String valid(int time) {
        if (time >= 0 && time <= 9) return "0" + time;
        else return time + "";
    }

    public boolean contains(int hour, int minu, Set<Integer> set) {
        return set.contains(hour / 10) && set.contains(hour % 10) && set.contains(minu / 10) && set.contains(minu % 10);
    }
but in this way, the cost will be 24* 60 = 1440.

Solution 2:
Because these four digits can be reused,so the next time can be constructed by these digits, so we try to use dfs to search all the next time.

it will search 4 * 4 * 4 * 4 = 256 times.

    int diff = 0x3f3f3f3f;
    String result = "";
    int h;
    int m;
    public String nextClosestTime(String time) {
        int[] digit = new int[4];
        int tot = 0;
        String[] val = time.split(":");
        int hour = Integer.parseInt(val[0]);
        int minu = Integer.parseInt(val[1]);
        digit[tot++] = hour / 10;
        digit[tot++] = hour % 10;
        digit[tot++] = minu / 10;
        digit[tot++] = minu % 10;

        h = hour;
        m = minu;

        dfs(digit, 0, new int[4]);

        return result;
    }

    void dfs(int[] digit, int i, int[] ans) {
        if (i == 4) {
            int hour = 10 * ans[0] + ans[1];
            int minu = 10 * ans[2] + ans[3];
            if (hour >= 0 && hour <= 23 && minu >= 0 && minu <= 59) {
                int df = diff(hour, minu);
                if (df < diff) {
                    diff = df;
                    result = valid(hour) + ":" + valid(minu);
                }
            }
        }
        else {
            for (int j = 0; j < 4; ++j) {
                ans[i] = digit[j];
                dfs(digit, i + 1, ans);
            }
        }
    }

    int diff(int hour, int minu) {
        int c2o = 60 * 60 - h * 60 - m;
        int n2o = 60 * 60 - hour * 60 - minu;
        return n2o < c2o ? c2o - n2o : c2o - n2o + 3600;
    }

    public String valid(int time) {
        if (time >= 0 && time <= 9) return "0" + time;
        else return time + "";
    }
Solution 3:
Of course, we can try to prune, if hour and minute is not valid, just stop search.

for the test case "23:59", it will search 24 times, but solution 2 searches 256 times.

    int diff = 0x3f3f3f3f;
    String result = "";
    int h;
    int m;
    public String nextClosestTime(String time) {
        int[] digit = new int[4];
        int tot = 0;
        String[] val = time.split(":");
        int hour = Integer.parseInt(val[0]);
        int minu = Integer.parseInt(val[1]);
        digit[tot++] = hour / 10;
        digit[tot++] = hour % 10;
        digit[tot++] = minu / 10;
        digit[tot++] = minu % 10;

        h = hour;
        m = minu;

        dfs(digit, 0, new int[4]);

        return result;
    }

    void dfs(int[] digit, int i, int[] ans) {
        if (i == 4) {
            int hour = 10 * ans[0] + ans[1];
            int minu = 10 * ans[2] + ans[3];
            int df = diff(hour, minu);
            if (df < diff) {
                diff = df;
                result = valid(hour) + ":" + valid(minu);
            }
        }
        else {
            for (int j = 0; j < 4; ++j) {
                ans[i] = digit[j];
                if (i == 1) {
                    int hour = 10 * ans[0] + ans[1];
                    if (hour >= 0 && hour <= 23) dfs(digit, i + 1, ans);
                }
                else if (i == 3) {
                    int minu = 10 * ans[2] + ans[3];
                    if (minu >= 0 && minu <= 59) dfs(digit, i + 1, ans);
                }
                else {
                    dfs(digit, i + 1, ans);
                }
            }
        }
    }

    int diff(int hour, int minu) {
        int c2o = 60 * 60 - h * 60 - m;
        int n2o = 60 * 60 - hour * 60 - minu;
        return n2o < c2o ? c2o - n2o : c2o - n2o + 3600;
    }

    public String valid(int time) {
        if (time >= 0 && time <= 9) return "0" + time;
        else return time + "";
    }

