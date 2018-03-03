//IP to CIDR
//Given a start IP address ip and a number of ips we need to cover n, return a
//representation of the range as a list (of smallest possible length) of CIDR
//blocks.
//A CIDR block is a string consisting of an IP, followed by a slash, and then
//the prefix length. For example: "123.45.67.89/20". That prefix length "20"
//represents the number of common prefix bits in the specified range.
//Example 1:
//Input: ip = "255.0.0.7", n = 10
//Output: ["255.0.0.7/32","255.0.0.8/29","255.0.0.16/32"]
//Explanation:
//The initial ip address, when converted to binary, looks like this (spaces
//added for clarity):
//255.0.0.7 -> 11111111 00000000 00000000 00000111
//The address "255.0.0.7/32" specifies all addresses with a common prefix of 32
//bits to the given address,
//ie. just this one address.
//The address "255.0.0.8/29" specifies all addresses with a common prefix of 29
//bits to the given address:
//255.0.0.8 -> 11111111 00000000 00000000 00001000
//Addresses with common prefix of 29 bits are:
//11111111 00000000 00000000 00001000
//11111111 00000000 00000000 00001001
//11111111 00000000 00000000 00001010
//11111111 00000000 00000000 00001011
//11111111 00000000 00000000 00001100
//11111111 00000000 00000000 00001101
//11111111 00000000 00000000 00001110
//11111111 00000000 00000000 00001111
//The address "255.0.0.16/32" specifies all addresses with a common prefix of
//32 bits to the given address,
//ie. just 11111111 00000000 00000000 00010000.
//In total, the answer specifies the range of 10 ips starting with the address
//255.0.0.7 .
//There were other representations, such as:
//["255.0.0.7/32","255.0.0.8/30", "255.0.0.12/30", "255.0.0.16/32"],
//but our answer was the shortest possible.
//Also note that a representation beginning with say, "255.0.0.7/30" would be
//incorrect,
//because it includes addresses like 255.0.0.4 = 11111111 00000000 00000000
//00000100
//that are outside the specified range.
//Note:
//    ip will be a valid IPv4 address.
//    Every implied address ip + x (for x < n) will be a valid IPv4 address.
//    n will be an integer in the range [1, 1000].
//



//######################################### O(N)  #########################################
//Time Complexity: O(N) where N is the length of nums.
//Space Complexity: O(1) the space used by our int variables.
//Intuition
//This problem is about performing the steps directly as written. The tricky
//part is managing the bit manipulations involved.
//Let's ask the question: for a number n of ip addresses desired, and the
//starting address ip of that range, what is the CIDR block representing the
//most ip addresses in that range starting at ip? Evidently, this greedy
//approach will work, and we can keep repeating this until we are done, so
//let's just focus on creating one largest block.
//Algorithm
//We'll need to be able to convert ip addresses back and forth to integers
//(long). We can do this with some basic manipulations - see the code for more
//details.
//Then, with an ip address like 255.0.0.24 converted to start, it ends in the
//binary 00011000. There are some cases. If n >= 8, then we should use the
//entire block 255.0.0.24/29. Otherwise, we can only take a number of addresses
//equal to the largest power of 2 less than or equal to n.
//In a more general setting, we use the bit lengths of both n and start &
//-start (the lowest bit of start) to compute the mask which represents
//232−mask2^{32 - \text{mask}}2​32−mask​​ ip addresses. Then, we
//adjust start and n appropriately.
//In Java and C++, we should be careful to use long data types to represent the
//converted ip addresses, since the number could exceed
//2312^{31}2​31​​.

  public List<String> ipToCIDR(String ip, int n) {
        long start = ipToLong(ip);
        List<String> ans = new ArrayList();
        while (n > 0) {
            int mask = Math.max(33 - bitLength(Long.lowestOneBit(start)),
                                33 - bitLength(n));
            ans.add(longToIP(start) + "/" + mask);
            start += 1 << (32 - mask);
            n -= 1 << (32 - mask);
        }
        return ans;
    }
    private long ipToLong(String ip) {
        long ans = 0;
        for (String x: ip.split("\\.")) {
            ans = 256 * ans + Integer.valueOf(x);
        }
        return ans;
    }
    private String longToIP(long x) {
        return String.format("%s.%s.%s.%s",
            x >> 24, (x >> 16) % 256, (x >> 8) % 256, x % 256);
    }
    private int bitLength(long x) {
        if (x == 0) return 1;
        int ans = 0;
        while (x > 0) {
            x >>= 1;
            ans++;
        }
        return ans;
    }


//#########################################  #########################################
public List<String> ipToCIDR(String ip, int range) {
		long x = 0;
		String[] ips = ip.split("\\.");
		for (int i = 0; i < ips.length; ++i) {
			x = Integer.parseInt(ips[i]) + x * 256;
		}
		List<String> ans = new ArrayList<>();
		while (range > 0) {
			long step = x & -x;
			while (step > range) step /= 2;
			ans.add(longToIP(x, (int)step));
			x += step;
			range -= step;
		}
		return ans;
	}

	String longToIP(long x, int step) {
		int[] ans = new int[4];
		ans[0] = (int) (x & 255); x >>= 8;
		ans[1] = (int) (x & 255); x >>= 8;
		ans[2] = (int) (x & 255); x >>= 8;
		ans[3] = (int) x;
		int len = 33;
		while (step > 0) {
			len --;
			step /= 2;
		}
		return ans[3] + "." + ans[2] + "." + ans[1] + "." + ans[0] + "/" + len;
	}


//#########################################  #########################################
//What we need to do is to find the minimum cover(n) starting from the given
//ip. The main idea is that calculating the n next ips in the form of
//number(11111111 00000000 00000000 00000111) instead of ip(e.g. 255.0.0.7).
//Plus, as for 255.0.0.7/x, x indicates 2^(32-x) can be covered.
//ip2number(self,ip) helps us get the corresponding number(32bit) of ip, so we
//know where to start.
//Then, number2ip(self,n) helps us to get the ip form.
//ilowbit(self,x) would return the index i of the first '1' starting from the
//right. The index of the first 1 helps to define how many ips have the same
//(32-i)part. For example, 255.0.0.8 - 255.0.0.15 have the same part 11111111
//00000000 00000000 00001xxx.
//The rest thing is just countdown from the given ip. For example, 255.0.0.7/32
//(must start from this) is the first ip because 255.0.0.7/31 has 255.0.0.6
//when the 32th bit can be 0 or 1. Then, 255.0.0.8/29 has the last 3bits can be
//000 to 111. Now we get 9 ips, after adding 255.0.0.16/32, we get the answer.
'''
def ip2number(self, ip):
    numbers = list(map(int, ip.split(".")))
    n = (numbers[0]<<24) + (numbers[1]<<16) + (numbers[2]<<8) + numbers[3]
    return n
def number2ip(self,n):
    return ".".join([str(n>>24&255), str(n>>16&255),str(n>>8&255), str(n&255)])
def ilowbit(self,x):
    for i in range(32):
        if(x & (1<<i)):
            return i
def lowbit(self,x):
    return 1<<self.ilowbit(x)
def ipToCIDR(self, ip, n):
    number = self.ip2number(ip)
    result = []
    while n>0:
        lb = self.lowbit(number)
        while lb>n:
            lb = lb//2

        n = n - lb

        result.append(self.number2ip(number) + "/" + str(32-self.ilowbit(lb)))
        number = number + lb;
    return result
'''
//To make it more clear, my answer for n = 8 is ['255.0.0.7/32',
//'255.0.0.8/30', '255.0.0.12/31', '255.0.0.14/32'].
//As we start from 255.0.0.7 with 32 bits fixed, then we still need to find 7
//ips, which indicates 7 = 4 + 2 + 1 (30, 31, 32). For example, starting from
//255.0.0.8, we want generate 4 ips which has the same 30 bits prifix as
//255.0.0.8. I mean they look like this 11111111 00000000 00000000 000010xx.
//Same rules for the others.
