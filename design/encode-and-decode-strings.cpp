//Encode and Decode Strings
//Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.
//Machine 1 (sender) has the function:
//string encode(vector<string> strs) {
//  // ... your code
//  return encoded_string;
//}
//Machine 2 (receiver) has the function:
//vector<string> decode(string s) {
//  //... your code
//  return strs;
//}
//So Machine 1 does:
//string encoded_string = encode(strs);
//and Machine 2 does:
//vector<string> strs2 = decode(encoded_string);
//strs2 in Machine 2 should be the same as strs in Machine 1.
//Implement the encode and decode methods.
//Note:
//The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.
//Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
//Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.


//################################################### Use length  ###################################################
   // Encodes a list of strings to a single string.
    public String encode(List<String> strs) {
        StringBuilder sb = new StringBuilder();
        for(String s : strs) {
            sb.append(s.length()).append('/').append(s);
        }
        return sb.toString();
    }

    // Decodes a single string to a list of strings.
    public List<String> decode(String s) {
        List<String> ret = new ArrayList<String>();
        int i = 0;
        while(i < s.length()) {
            int slash = s.indexOf('/', i);
            int size = Integer.valueOf(s.substring(i, slash));
            ret.add(s.substring(slash + 1, slash + size + 1));
            i = slash + size + 1;
        }
        return ret;
    }
//################################################### Use # ###################################################
//Double any hashes inside the strings, then use standalone hashes (surrounded by spaces) to mark string endings. For example:
//{"abc", "def"}    =>  "abc # def # "
//{'abc', '#def'}   =>  "abc # ##def # "
//{'abc##', 'def'}  =>  "abc#### # def # "
//For decoding, just do the reverse: First split at standalone hashes, then undo the doubling in each string.

public String encode(List<String> strs) {
    StringBuffer out = new StringBuffer();
    for (String s : strs)
        out.append(s.replace("#", "##")).append(" # ");
    return out.toString();
}

public List<String> decode(String s) {
    List strs = new ArrayList();
    String[] array = s.split(" # ", -1);
    for (int i=0; i<array.length-1; ++i)
        strs.add(array[i].replace("##", "#"));
    return strs;
}


//################################################### Streaming ###################################################
public String encode(List<String> strs) {
    return strs.stream()
               .map(s -> s.replace("#", "##") + " # ")
               .collect(Collectors.joining());
}

public List<String> decode(String s) {
    List strs = Stream.of(s.split(" # ", -1))
                      .map(t -> t.replace("##", "#"))
                      .collect(Collectors.toList());
    strs.remove(strs.size() - 1);
    return strs;
}


//################################################### or each str in strs, encode it as <length> + '@' + str ###################################################
class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string encoded = "";
        for (string &str: strs) {
            int len = str.size();
            encoded += to_string(len) + "@" + str;
        }

        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> r;
        int head = 0;
        while (head < s.size())    {
            int at_pos = s.find_first_of('@', head);
            int len = stoi(s.substr(head, at_pos - head));
            head = at_pos + 1;
            r.push_back(s.substr(head, len));
            head += len;
        }

        return r;
    }
};

//################################################### or each str in strs, encode it as <length> + '/' + str ###################################################
public class Codec {

    // Encodes a list of strings to a single string.
    public String encode(List<String> strs) {
        StringBuilder sb = new StringBuilder();
        for(String s : strs) {
            sb.append(s.length()).append('/').append(s);
        }
        return sb.toString();
    }
	//The encoded form of strings is length + '/' +str + length + '/' + str.
	//If you say, there is a '/' in a str. Then it is counted for the length of that str but the added slash is not.
	//For "ab/cd", the encoded one should be "5/ab/cd". The decode function will read the length first, then skip the slash between '5' and 'a', starting from the next character and get the substring of that length which is "ab/cd"
    // Decodes a single string to a list of strings.
    public List<String> decode(String s) {
        List<String> ret = new ArrayList<String>();
        int i = 0;
        while(i < s.length()) {
            int slash = s.indexOf('/', i);
            int size = Integer.valueOf(s.substring(i, slash));
            ret.add(s.substring(slash + 1, slash + size + 1));
            i = slash + size + 1;
        }
        return ret;
    }
}

class Codec:

    def encode(self, strs):
        return ''.join('%d:' % len(s) + s for s in strs)
		//hello = > '1:h1:e1:l1:l1:o'

    def decode(self, s):
        strs = []
        i = 0
        while i < len(s):
            j = s.find(':', i)
            i = j + 1 + int(s[i:j])
            strs.append(s[j+1:i])
        return strs
