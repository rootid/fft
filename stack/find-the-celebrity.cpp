//Find the Celebrity
//Suppose you are at a party with n people (labeled from 0 to n - 1) and among
//them, there may exist one celebrity. The definition of a celebrity is that
//all the other n - 1 people know him/her but he/she does not know any of them.
//Now you want to find out who the celebrity is or verify that there is not
//one. The only thing you are allowed to do is to ask questions like: "Hi, A.
//Do you know B?" to get information of whether A knows B. You need to find out
//the celebrity (or verify there is not one) by asking as few questions as
//possible (in the asymptotic sense).
//You are given a helper function bool knows(a, b) which tells you whether A
//knows B. Implement a function int findCelebrity(n), your function should
//minimize the number of calls to knows.
//Note: There will be exactly one celebrity if he/she is in the party. Return
//the celebrity‘s label if there is a celebrity in the party. If there is no
//celebrity, return -1.

//######################################### Stack approach #########################################
// TC : O(n) , SC : O(n)
public int findCelebrity(int n) {
    // base case
    if (n <= 0) return -1;
    if (n == 1) return 0; //only 1 persion in the party
    Stack<Integer> stack = new Stack<>();
    // put all people to the stack
    for (int i = 0; i < n; i++) stack.push(i);
    int a = 0, b = 0;
    while (stack.size() > 1) {
        a = stack.pop();
		b = stack.pop();
        if (knows(a, b)) //b : famous/celibrity
            // a knows b, so a is not the celebrity, but b may be
            stack.push(b);
        else
            // a doesn't know b, so b is not the celebrity, but a may be
            stack.push(a);
    }
    // double check the potential celebrity
    int c = stack.pop();
    for (int i = 0; i < n; i++) {
        // c should not know anyone else
        if (i != c && (knows(c, i) || !knows(i, c)))
            return -1;
	}
    return c;
}

//#########################################  Constant space #########################################
//TC : O(3n-1)
//SP : O(1)
int findCelebrity(int n) {
    if(n<2) return n ? 0 : -1;
    int curr = 0, next = 1;
    for(;next<n;next++)
		if (knows(curr,next))  //next might be a celibrity
			curr = next;
    for(int i=0; i<n; i++) if(curr != i && (knows(curr, i) || !knows(i, curr))) return -1;
    return curr;
}

//#########################################  2 pointer solution #########################################
public int findCelebrity(int n) {
    if (n < 0) return 0;
    int l = 0, r = n - 1;
    while (l < r) {
        if (knows(l, r)) l++;
        else r--;
    }
    int i = 0;
    while (i < n) {
        if (i != l && (knows(l, i) || !knows(i, l))) return -1;
        i++;
    }
    return l;
}



//The first loop is to exclude n - 1 labels that are not possible to be a
//celebrity.
//After the first loop, x is the only candidate.
//The second and third loop is to verify x is actually a celebrity by
//definition.
//The key part is the first loop. To understand this you can think the
//knows(a,b) as a a < b comparison, if a knows b then a < b, if a does not know
//b, a > b.
//Then if there is a celebrity, he/she must be the "maximum" of the n people.
//However, the "maximum" may not be the celebrity in the case of no celebrity
//at all.
//Thus we need the second and third loop to check if x is actually celebrity by
//definition.
//The total calls of knows is thus 3n at most. One small improvement is that in
//the second loop we only need to check i in the range [0, x). You can figure
//that out yourself easily.

public class Solution extends Relation {
     public int findCelebrity(int n) {
        int x = 0;
        for (int i = 0; i < n; ++i) if (knows(x, i)) x = i; // x is celibrity
        for (int i = 0; i < x; ++i) if (knows(x, i)) return -1;
        for (int i = 0; i < n; ++i) if (!knows(i, x)) return -1;
        return x;
    }
}


def findCelebrity(self, n):
    x = 0
    for i in xrange(n):
        if knows(x, i):
            x = i
    if any(knows(x, i) for i in xrange(x)):
        return -1
    if any(not knows(i, x) for i in xrange(n)):
        return -1
    return x
