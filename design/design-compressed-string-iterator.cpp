//Design Compressed String Iterator
//Design and implement a data structure for a compressed string iterator. It should support the following operations: next and hasNext.
//The given compressed string will be in the form of each letter followed by a positive integer representing the number of this letter existing in the original uncompressed string.
//next() - if the original string still has uncompressed characters, return the next letter; Otherwise return a white space.
//hasNext() - Judge whether there is any letter needs to be uncompressed.
//Note:
//Please remember to RESET your class variables declared in StringIterator, as static/class variables are persisted across multiple test cases. Please see here for more details.
//Example:
//StringIterator iterator = new StringIterator("L1e2t1C1o1d1e1");
//iterator.next(); // return 'L'
//iterator.next(); // return 'e'
//iterator.next(); // return 'e'
//iterator.next(); // return 't'
//iterator.next(); // return 'C'
//iterator.next(); // return 'o'
//iterator.next(); // return 'd'
//iterator.hasNext(); // return true
//iterator.next(); // return 'e'
//iterator.hasNext(); // return false
//iterator.next(); // return ' '
//

//############################################## with istringstream #################################################################
class StringIterator {
public:
    StringIterator(string compressedString) {
        iss = istringstream(compressedString);
        count = c = 0;
    }
    //next
    char next() {
        if (hasNext()) {
            --count;
            return c;
        } else {
            return ' ';
        }
    }
    //Check and get the count and return false if no count
    bool hasNext() {
        if (count == 0) {
            iss >> c >> count;
        }
        return count > 0;
    }
private :
    istringstream iss;
    char c;
    int count;
};

//############################################## with istringstream + SMART SHORTER #################################################################
class StringIterator {
public:
    StringIterator(string compressedString) : in(compressedString) {}
    
    char next() {
        if (!hasNext())
            return ' ';
        number--;
        return curr;
    }
    
    bool hasNext() {
        return number || (in >> curr >> number);
    }

private:
    istringstream in;
    char curr;
    int number = 0;
};

//############################################################# With ATOI + isdigit ############################################################## 
class StringIterator {
public:
    StringIterator(string cs) : cs(cs), i(0), rep(0), ch(' ') { }

    char next() {
        if (rep > 0) {
            rep--;
            return ch;
        }
        else if (i < cs.size()) {
            ch = cs[i];
            int j = i + 1;
            while (j < cs.size() && isdigit(cs[j])) { j++; }
            string num = cs.substr(i + 1, j - 1 - i);
            rep = atoi(num.c_str()) - 1;
            i = j;
            return ch;
        }
        else {
            return ' ';
        }
    }

    bool hasNext() {
        return rep > 0 || i < cs.size();
    }

private:
    string cs;
    int i;
    long rep;
    char ch;
};

//re.finditer instead to save some memory if you like.
//##########################################################  pytonic ########################################################## 
//class StringIterator(object):
//
//    def __init__(self, compressedString):
//        """
//        :type compressedString: str
//        """
//        self.__data = re.findall(r"([a-zA-Z])(\d+)", compressedString)
//        self.__index, self.__count = -1, 0
//
//    def next(self):
//        """
//        :rtype: str
//        """
//        if self.hasNext():
//            self.__count -= 1
//            return self.__data[self.__index][0]
//        else:
//            return ' '
//
//    def hasNext(self):
//        """
//        :rtype: bool
//        """
//        if self.__count == 0 and self.__index + 1 < len(self.__data):
//            self.__index += 1
//            self.__count = int(self.__data[self.__index][1])
//        return self.__count > 0
//
//
//############################# Store string in memory  ############################# 
//
//Let's store the tokens like [('L', 1), ('e', 2), ('t', 1), ('c', 1), ('o', 1), ('d', 1), ('e', 1)], except in reverse. When we want a token, we pop it off the stack: t, n = 'L', 1 and return t. When there is more than one character represented, we need to put the excess back on the stack: t, n = 'e', 2 then tokens.append(('e', 1)).
//We can use a regular expression to find the tokens quickly. The pattern \D\d+ means a non-digit character, followed by 1 or more digit characters. (The + denotes a kleene plus, a wildcard character meaning "one or more of the preceding match.") All of our tokens (and only our tokens) match this pattern as desired.
//
//import re
//class StringIterator(object):
//    def __init__(self, compressedString):
//        self.tokens = []
//        for token in re.findall('\D\d+', compressedString):
//            self.tokens.append((token[0], int(token[1:])))
//        self.tokens = self.tokens[::-1]
//
//    def next(self):
//        if not self.tokens: return ' '
//        t, n = self.tokens.pop()
//        if n > 1: 
//            self.tokens.append((t, n - 1))
//        return t
//
//    def hasNext(self):
//        return bool(self.tokens)
