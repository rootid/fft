//****Longest Absolute File Path
//Suppose we abstract our file system by a string in the following manner:
//The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:
//dir
//    subdir1
//    subdir2
//        file.ext
//The directory dir contains an empty sub-directory subdir1 and a sub-directory
//subdir2 containing a file file.ext.
//The string
//"dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
//represents:
//dir
//    subdir1
//        file1.ext
//        subsubdir1
//    subdir2
//        subsubdir2
//            file2.ext
//The directory dir contains two sub-directories subdir1 and subdir2. subdir1
//contains a file file1.ext and an empty second-level sub-directory subsubdir1.
//subdir2 contains a second-level sub-directory subsubdir2 containing a file
//file2.ext.
//We are interested in finding the longest (number of characters) absolute path
//to a file within our file system. For example, in the second example above,
//the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its
//length is 32 (not including the double quotes).
//Given a string representing the file system in the above format, return the
//length of the longest absolute path to file in the abstracted file system. If
//there is no file in the system, return 0.
//Note:
//The name of a file contains at least a . and an extension.
//The name of a directory or sub-directory will not contain a ..
//Time complexity required: O(n) where n is the size of the input string.
//Notice that a/aa/aaa/file1.txt is not the longest file path, if there is
//another path aaaaaaaaaaaaaaaaaaaaa/sth.png.
//
//
//

//
//dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext
//dir
//    subdir1
//        file1.ext
//        subsubdir1
//    subdir2
//        subsubdir2
//            file2.ext
//
#include "../headers/global.hpp"

// NOTE : \n : new line
int lengthLongestPath(string input) {
        int res = 0;
        istringstream ss(input);
        unordered_map<int, int> m{{0, 0}};
        string line = "";

        cout << "s =  " << input << endl;
        while (getline(ss,line,'\n')) {     //getline : getline(ss,line) default delim : '\n'
            cout << "line " << line << endl;
            int level = line.find_last_of('\t') + 1;
            cout << "level =  " << level << endl;
            int len = line.substr(level).size();
            cout << "len =  " << len << endl;
            if (line.find('.') != string::npos) { //if find the leaf/file with extension
                res = max(res, m[level] + len);
            } else {
                m[level + 1] = m[level] + len + 1;  //next level size = current level + len + 1 ('/' char)
            }
        }
        return res;
}

int main() {
  //string t = "\n\t\t\n\n\t";
  //cout << " lt " << t.size() << endl;
  lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext");
}


//########################### pytonic  ###########################
//the number of tabs is my depth and for each depth I store the current path
//length.
//def lengthLongestPath(self, input):
//    maxlen = 0
//    pathlen = {0: 0}
//    for line in input.splitlines():
//        name = line.lstrip('\t')
//        depth = len(line) - len(name)
//        if '.' in name:
//            maxlen = max(maxlen, pathlen[depth] + len(name))
//        else:
//            pathlen[depth + 1] = pathlen[depth] + len(name) + 1
//    return maxlen

//########################### pytonic  ###########################
//def lengthLongestPath(self, input):
//    m, l = 0, {-1: -1}
//    for s in input.split('\n'):
//        d = s.count('\t')
//        l[d] = 1 + l[d-1] + len(s) - d
//        if '.' in s: m = max(m, l[d])
//    return m

//########################### pytonic  ###########################
//class Solution(object):
//    def lengthLongestPath(self, input):
//        paths, max_length, length, depth = [], 0, 0, 0
//        for line in input.split("\n"):
//            now_depth = collections.Counter(line)['\t']
//            name = line.strip('\t')
//            if now_depth <= depth and paths:
//                for k in range(depth - now_depth + 1):
//                    last = paths.pop()
//                    length -= len(last)
//                    if "." not in last:
//                        length -= 1
//            paths.append(name)
//            length += len(name)
//            if "." in name:
//                max_length = max(max_length, length)
//            else:
//                length += 1
//            depth = now_depth
//        return max_length
