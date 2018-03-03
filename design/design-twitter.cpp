//Design Twitter
//Design a simplified version of Twitter where users can post tweets,
//follow/unfollow another user and is able to see the 10 most recent tweets in
//the user's news feed. Your design should support the following methods:
//postTweet(userId, tweetId): Compose a new tweet.
//getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news
//feed. Each item in the news feed must be posted by users who the user
//followed or by the user herself. Tweets must be ordered from most recent to
//least recent.
//follow(followerId, followeeId): Follower follows a followee.
//unfollow(followerId, followeeId): Follower unfollows a followee.
//Example:
//Twitter twitter = new Twitter();
//// User 1 posts a new tweet (id = 5).
//twitter.postTweet(1, 5);
//// User 1's news feed should return a list with 1 tweet id -> [5].
//twitter.getNewsFeed(1);
//// User 1 follows user 2.
//twitter.follow(1, 2);
//// User 2 posts a new tweet (id = 6).
//twitter.postTweet(2, 6);
//// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
//// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
//twitter.getNewsFeed(1);
//// User 1 unfollows user 2.
//twitter.unfollow(1, 2);
//// User 1's news feed should return a list with 1 tweet id -> [5],
//// since user 1 is no longer following user 2.
//twitter.getNewsFeed(1);

//############################################################# struct approach #############################################################
class Twitter {
    struct Tweet {
        int time;
        int id;
        Tweet(int time, int id) : time(time), id(id) {}
    };

    unordered_map<int, vector<Tweet>> tweets; // [u] = array of tweets by u
    unordered_map<int, unordered_set<int>> following_map; // [u] = array of users followed by u
    int time;

//Use std::vector to store tweets,
//std::unordered_set to store followed users,
//std::unordered_map to associate each user with their tweets and followed
//users.

public:
    Twitter() : time(0) {}

    //O(1)
    void postTweet(int userId, int tweetId) {
        tweets[userId].emplace_back(time++, tweetId);
    }

    //O(n + k log n) newsfeed for getting k tweets from n followed users
    vector<int> getNewsFeed(int userId) {
        vector<pair<Tweet*, Tweet*>> h; // pair of pointers (begin, current)

        // with the O(n) part coming from constructing the heap of followed users
        for (auto& u: following_map[userId]) {
            auto& t = tweets[u];
            if (t.size() > 0)
                h.emplace_back(t.data(), t.data() + t.size() - 1);
        }
        auto& t = tweets[userId]; // self
        if (t.size() > 0)
            h.emplace_back(t.data(), t.data() + t.size() - 1);
        auto f = [](const pair<Tweet*, Tweet*>& x, const pair<Tweet*, Tweet*>& y) {
            return x.second->time < y.second->time;
        };
        make_heap(h.begin(), h.end(), f);
        const int n = 10;
        vector<int> o;
        o.reserve(n);
        for (int i = 0; (i < n) && !h.empty(); ++i) {
            pop_heap(h.begin(), h.end(), f);
            auto& hb = h.back();
            o.push_back(hb.second->id);
            if (hb.first == hb.second--)
                h.pop_back();
            else
                push_heap(h.begin(), h.end(), f);
        }
        return o;
    }

    //O(1) : map
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId)
            following_map[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        following_map[followerId].erase(followeeId);
    }
};


//################################################### Friend approach ###################################################
class Tweet {
    friend class Twitter;
    friend class Compare;
  private:
    int id;
    int time;
  public:
    Tweet(int id, int time) : id(id), time(time) {
    }
};
class Compare {
    public:
        bool operator()(pair<vector<Tweet>::iterator,vector<Tweet>::iterator> p1, pair<vector<Tweet>::iterator,vector<Tweet>::iterator> p2 ) {
            return (p1.first->time < p2.first->time);
        }
};
class Twitter {
private:
    int time;
    unordered_map<int, unordered_set<int>> followmap;
    unordered_map<int, vector<Tweet>> tweets;
public:
    Twitter( int time=0) : time(time) {

    }

    void postTweet(int userId, int tweetId) {
        tweets[userId].insert(tweets[userId].begin(),Tweet(tweetId,time++));
    }

    vector<int> getNewsFeed(int userId) {

        priority_queue<pair<vector<Tweet>::iterator,vector<Tweet>::iterator>, vector<pair<vector<Tweet>::iterator,vector<Tweet>::iterator>>, Compare> pq;
        vector<int> res;
        for (auto follower : followmap[userId]) {
            if (tweets.count(follower) && tweets[follower].size())
                pq.push(make_pair(tweets[follower].begin(), tweets[follower].end()));
        }
        if (tweets.count(userId) && tweets[userId].size())
            pq.push(make_pair(tweets[userId].begin(),tweets[userId].end()));
        for (int i=0; i<10 && !pq.empty(); ++i) {
            auto temp = pq.top();
            pq.pop();
            res.push_back(temp.first->id);
            if (++temp.first != temp.second) pq.push(temp);
        }
        return res;
    }

    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) followmap[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        if (followmap.count(followerId)) followmap[followerId].erase(followeeId);
    }
};


//######################################## pytonic ########################################

//class Twitter(object):
//
//    def __init__(self):
//        self.timer = itertools.count(step=-1)
//        self.tweets = collections.defaultdict(collections.deque)
//        self.followees = collections.defaultdict(set)
//
//    def postTweet(self, userId, tweetId):
//        self.tweets[userId].appendleft((next(self.timer), tweetId))
//
//    def getNewsFeed(self, userId):
//        tweets = heapq.merge(*(self.tweets[u] for u in self.followees[userId] | {userId}))
//        return [t for _, t in itertools.islice(tweets, 10)]
//
//    def follow(self, followerId, followeeId):
//        self.followees[followerId].add(followeeId)
//
//    def unfollow(self, followerId, followeeId):
//        self.followees[followerId].discard(followeeId)
//
//
//
//You could've used a heap in which you store only the heads and then do 10
//extractions (similar to what we do when we merge k sorted linked lists
//
//import heapq
//
//class Twitter(object):
//
//    def __init__(self):
//        self.time = 0
//        self.tweets = {}
//        self.followee = {}
//
//
//    def postTweet(self, user, tweet):
//        self.time += 1
//        self.tweets[user] = self.tweets.get(user, []) + [(-self.time,  tweet)]
//
//
//
//    def getNewsFeed(self, user):
//        h, tweets = [], self.tweets
//        people = self.followee.get(user, set()) | set([user])
//        for person in people:
//            if person in tweets and tweets[person]:
//                time, tweet = tweets[person][-1]
//                h.append((time, tweet, person, len(tweets[person]) - 1))
//        heapq.heapify(h)
//        news = []
//        for _ in range(10):
//            if h:
//                time, tweet, person, idx = heapq.heappop(h)
//                news.append(tweet)
//                if idx:
//                    new_time, new_tweet = tweets[person][idx-1]
//                    heapq.heappush(h, (new_time, new_tweet, person, idx - 1))
//        return news
//
//
//
//    def follow(self, follower, other):
//        self.followee[follower] = self.followee.get(follower, set()) | set([other])
//
//
//
//    def unfollow(self, follower, other):
//        if follower in self.followee:
//            self.followee[follower].discard(other)
//
////K is the number of followee of user. We have O(log(K)) runtime for getting news feed because we do maximum 10 extractions in a heap that holds maximum K elements (similar to what is done in merge K linked lists). The other ops are obviously O(1)
