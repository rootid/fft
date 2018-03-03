//Find Duplicate File in System
//Given a list of directory info including directory path, and all the files
//with contents in this directory, you need to find out all the groups of
//duplicate files in the file system in terms of their paths.
//A group of duplicate files consists of at least two files that have exactly
//the same content.
//A single directory info string in the input list has the following format:
//"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"
//It means there are n files (f1.txt, f2.txt ... fn.txt with content
//f1_content, f2_content ... fn_content, respectively) in directory
//root/d1/d2/.../dm. Note that n >= 1 and m >= 0. If m = 0, it means the
//directory is just the root directory.
//The output is a list of group of duplicate file paths. For each group, it
//contains all the file paths of the files that have the same content. A file
//path is a string that has the following format:
//"directory_path/file_name.txt"
//Example 1:
//Input:
//["root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"]
//Output:
//[["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]
//Note:
//No order is required for the final output.
//You may assume the directory name, file name and file content only has
//letters and digits, and the length of file content is in the range of [1,50].
//The number of files given is in the range of [1,20000].
//You may assume no files or directories share the same name in the same
//directory.
//You may assume each given directory info represents a unique directory.
//Directory path and file info are separated by a single blank space.
//Follow-up beyond contest:
//Imagine you are given a real file system, how will you search files? DFS or
//BFS?
//If the file content is very large (GB level), how will you modify your
//solution?
//If you can only read the file by 1kb each time, how will you modify your
//solution?
//What is the time complexity of your modified solution? What is the most
//time-consuming part and memory consuming part of it? How to optimize?
//How to make sure the duplicated files you find are not false positive?

//############################################ use of istringstream ############################################
vector<vector<string>> findDuplicate(vector<string>& paths) {
    vector<vector<string>> res;
    map<string, vector<string>> files;
    for (string s : paths) {
        std::istringstream ss(s);
        vector<string> toks{ istream_iterator<string>{ss}, istream_iterator<string>{} };
        string path = toks[0];
        for (int i = 1; i < toks.size(); i++) {
            int pos = toks[i].find('(');
            string file = toks[i].substr(0, pos);
            string content = toks[i].substr(pos + 1, toks[i].size() - 2 - pos);
            files[content].push_back(path + "/" + file);
        }
    }
    for (auto p : files) {
        if (p.second.size() > 1) {
            res.push_back(p.second);
        }
    }
    return res;
}
//The subtle issue is that string object is copied multiple times which makes
//it 10 time slower than optimal one according to leetcode submission result.
//It may be better to use string_view, but it's in C++ 17 standard.

//############################################ use of getline ############################################
vector<vector<string>> findDuplicate(vector<string>& paths) {
    unordered_map<string, vector<string>> files;
    vector<vector<string>> result;

    for (auto path : paths) {
	    stringstream ss(path);
	    string root;
	    string s;
	    getline(ss, root, ' ');
	    while (getline(ss, s, ' ')) {
		    string fileName = root + '/' + s.substr(0, s.find('('));
		    string fileContent = s.substr(s.find('(') + 1, s.find(')') - s.find('(') - 1);
		    files[fileContent].push_back(fileName);
	    }
    }

    for (auto file : files) {
	    if (file.second.size() > 1)
		    result.push_back(file.second);
    }

    return result;
}

//Follow up questions:
//1. Imagine you are given a real file system, how will you search files? DFS
//or BFS ?
//In general, BFS will use more memory then DFS. However BFS can take advantage
//of the locality of files in inside directories, and therefore will probably
//be faster
//
//2. If the file content is very large (GB level), how will you modify your
//solution?
//In a real life solution we will not hash the entire file content, since it's
//not practical. Instead we will first map all the files according to size.
//Files with different sizes are guaranteed to be different. We will than hash
//a small part of the files with equal sizes (using MD5 for example). Only if
//the md5 is the same, we will compare the files byte by byte
//
//3. If you can only read the file by 1kb each time, how will you modify your
//solution?
//This won't change the solution. We can create the hash from the 1kb chunks,
//and then read the entire file if a full byte by byte comparison is required.
//
//What is the time complexity of your modified solution? What is the most time
//consuming part and memory consuming part of it? How to optimize?
//Time complexity is O(n^2 * k) since in worse case we might need to compare
//every file to all others. k is the file size
//
//How to make sure the duplicated files you find are not false positive?
//We will use several filters to compare: File size, Hash and byte by byte
//comparisons.
//
//############################################### pytonic #################################################
//class Solution(object):
//    def findDuplicate(self, paths):
//        """
//        :type paths: List[str]
//        :rtype: List[List[str]]
//        """
//        d = collections.defaultdict(list)
//        for path in paths:
//            raw = path.split(" ")
//            dirPath = raw[0]
//            for data in raw[1:]:
//                name, sign = data.split("(")
//                d[sign].append(dirPath + "/" + name)
//        return filter(lambda x: len(x) > 1, d.values())

//After parsing, we have some path and content. Let's store a map M[content] =
//[path1, path2, ...]. At the end, we want all values in this map with length >
//1.
//def findDuplicate(self, paths):
//    M = collections.defaultdict(list)
//    for line in paths:
//        data = line.split()
//        root = data[0]
//        for file in data[1:]:
//            name, _, content = file.partition('(')
//            M[content[:-1]].append(root + '/' + name)
//
//    return [x for x in M.values() if len(x) > 1]
//
//###################### use of find instead partition ######################
//class Solution(object):
//    def findDuplicate(self, paths):
//        """
//        :type paths: List[str]
//        :rtype: List[List[str]]
//        """
//        dic = collections.defaultdict(list)
//        for path in paths:
//            p = path.split()
//            root = p[0]
//            for file in p[1:]:
//                idx = file.find("(")
//                fn, content = file[:idx], file[idx:]
//                dic[content].append(root + "/" + fn)
//        return [dic[key] for key in dic if len(dic[key]) > 1]
