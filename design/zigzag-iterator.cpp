//Given two 1d vectors, implement an iterator to return their elements
//alternately.
//
//For example, given two 1d vectors:
//
//v1 = [1, 2]
//v2 = [3, 4, 5, 6]
//By calling next repeatedly until hasNext returns false, the order of elements
//returned by next should be: [1, 3, 2, 4, 5, 6].
//
//Follow up: What if you are given k 1d vectors? How well can your code be
//extended to such cases?
//
//Clarification for the follow up question - Update (2015-09-18):
//The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases.
//If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For
//example, given the following input:
//
//[1,2,3]
//[4,5,6,7]
//[8,9]
//It should return [1,4,8,2,5,9,3,6,7].
//
class ZigzagIterator {
private :
    vector<int>::iterator bv[2], ev[2];
    int m_next;
public:

    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        bv[0] = v1.begin();
        bv[1] = v2.begin();
        ev[0] = v1.end();
        ev[1] = v2.end();
        m_next = 0;
    }
    int next() {
        int elem;
        if(hasNext()) {
            if(bv[0] == ev[0]) {
                elem = *bv[1]++;
            } else if(bv[1] == ev[1]) {
                elem = *bv[0]++;
            } else {
                elem = *bv[m_next]++;
                m_next = 1 - m_next;
            }
            return elem;
        }
        return NULL;
    }
    bool hasNext() {
        return ( (bv[0] != ev[0]) || (bv[1] != ev[1]) );
    }
};
/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */
