//Encode and Decode TinyURL
//TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.
//Design the encode and decode methods for the TinyURL service. There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.


//#################################### With random key ####################################
//#of URLS = (10+26∗2)^6
class Solution {
  String alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  HashMap<String, String> map = new HashMap<>();
  Random rand = new Random();
  String key = getRand();
  public String getRand() {
      StringBuilder sb = new StringBuilder();
      for (int i = 0; i < 6; i++) {
          sb.append(alphabet.charAt(rand.nextInt(62)));
      }
      return sb.toString();
  }

  public String encode(String longUrl) {
      while (map.containsKey(key)) {
          key = getRand();
      }
      map.put(key, longUrl);
      return "http://tinyurl.com/" + key;
  }

  public String decode(String shortUrl) {
      return map.get(shortUrl.replace("http://tinyurl.com/", ""));
  }
}

//#################################### With random key   ####################################
class Solution {
  unordered_map<string, string> index;
  unordered_map<string, string> revIndex;
  string BASE_HOST = "http://tinyurl.com/";
  string charSet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  public:
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
      if (revIndex.count(longUrl)) {
        return BASE_HOST + revIndex[longUrl];
      }
      string key;
     do {
          for (int i = 0; i < 6; i++) {
              int r = rand() % charSet.length();
              key += charSet[r];
          }
      } while (index.count(key)); //make sure we generate unique key
      index[key] =  longUrl;
      revIndex[longUrl] = key;
      return BASE_HOST + key;
  }

  // Decodes a shortened URL to its original URL.
  string decode(string shortUrl) {
      int len = BASE_HOST.size();
      shortUrl.replace(0,len, "");
      return index[shortUrl];
  }
};

//#################################### With index as a random output  ####################################
class Solution {
    vector<string> urls;

public:
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        urls.push_back(longUrl);
        return "http://tinyurl.com/" + to_string(urls.size() - 1);
    }
    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        //Or traverse from right to left and get the number substring
        stringstream ss(shortUrl);
        string val_str;
          while (!ss.eof()) {
            getline(ss, val_str, '/');
        }
        return urls[stoi(val_str) ];
    }
};
// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
//
//(10+26*2)6 = 56,800,235,584 codes with length 6.
class Codec:
    alphabet = string.ascii_letters + '0123456789'
    def __init__(self):
        self.url2code = {}
        self.code2url = {}
    def encode(self, longUrl):
        while longUrl not in self.url2code:
            code = ''.join(random.choice(Codec.alphabet) for _ in range(6))
            if code not in self.code2url:
                self.code2url[code] = longUrl
                self.url2code[longUrl] = code
        return 'http://tinyurl.com/' + self.url2code[longUrl]
    def decode(self, shortUrl):
        return self.code2url[shortUrl[-6:]]


