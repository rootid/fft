//Design a logger system that receive stream of messages along with its timestamps, each message should be printed if and only if it is not printed in the last 10 seconds.
//Given a message and a timestamp (in seconds granularity), return true if the message should be printed in the given timestamp, otherwise returns false.
//It is possible that several messages arrive roughly at the same time.
//Example:
//Logger logger = new Logger();
//// logging string "foo" at timestamp 1
//logger.shouldPrintMessage(1, "foo"); returns true; 
//// logging string "bar" at timestamp 2
//logger.shouldPrintMessage(2,"bar"); returns true;
//// logging string "foo" at timestamp 3
//logger.shouldPrintMessage(3,"foo"); returns false;
//// logging string "bar" at timestamp 8
//logger.shouldPrintMessage(8,"bar"); returns false;
//// logging string "foo" at timestamp 10
//logger.shouldPrintMessage(10,"foo"); returns false;
//// logging string "foo" at timestamp 11
//logger.shouldPrintMessage(11,"foo"); returns true;
#include "../headers/global.hpp"
//["Logger","shouldPrintMessage","shouldPrintMessage","shouldPrintMessage","shouldPrintMessage","shouldPrintMessage","shouldPrintMessage"]
//[[],[1,"foo"],[2,"bar"],[3,"foo"],[8,"bar"],[10,"foo"],[11,"foo"]]
//
class Logger {
private :
    unordered_map<string,int> dict;
public:
    /** Initialize your data structure here. */
    Logger() {
      
    }

    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, string message) {
         if(timestamp < dict[message]) {
          return false;
         }
         dict[message] = timestamp + 10;
         return true;
    }
    
    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage_ugly(int timestamp, string message) {
         if(this->dict.find(message) == this->dict.end()) {
            this->dict[message] = timestamp+10;
            return true;
         } else {
             if(this->dict[message] <= timestamp) {
                 this->dict[message] = timestamp+10;
                 return true;
             }
         }
        return false;
    }
};
/**
 * Your Logger object will be instantiated and called as such:
 * Logger obj = new Logger();
 * bool param_1 = obj.shouldPrintMessage(timestamp,message);
 */
int main() {
  shouldPrintMessage(1,"foo");
  shouldPrintMessage(3,"foo");
  shouldPrintMessage(10,"foo");
  shouldPrintMessage(11,"foo");
}
