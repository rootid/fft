#include<iostream>
#include<vector>
#include<string>
#define R 26
using namespace std;

struct TrieNode {
    char data;
    int leafValue; //To check for the leaf node
    TrieNode* next[R];
    TrieNode (char adata,int aleafValue) :
        data(adata),leafValue(aleafValue) {

    };
};

//insert,search 
//insert at once
void insertInTrie (vector<string>& inputVec,vector<int>& leafValue,TrieNode** rootHead) {
    if (*rootHead == NULL) {
        *rootHead = new TrieNode(-1,-1);
    }
    int leafVal = -1;
    for (int k=0;k<inputVec.size();k++)  {
        string input = inputVec[k];
        int len = input.length();
        TrieNode* crawlNode = *rootHead;
        for (int i=0;i<len;i++) {
                leafVal = -1;
                if (i == len - 1) {
                    leafVal = leafValue[k];
                }
                if (crawlNode->next[input[i] - 'a'] == NULL) {
                    crawlNode->next[input[i] - 'a'] = new TrieNode(input[i],leafVal);
                    cout << "IC1=" << crawlNode  << "V=" << input[i]<< endl;
                }
                crawlNode = crawlNode->next[input[i] - 'a'];
        }
    }

}

bool queryFromTrie(TrieNode* root,string& input) {
    for (int i=0;i<input.length();i++) {
        if (root && root->next[input[i] - 'a'] && input[i] == root->next[input[i] - 'a']->data) {
            root = root->next[input[i] - 'a'];
        } else {
            return false;
        }
    }
    if (root->leafValue != -1) {
        cout << "i" << root->leafValue << endl;
        return true;
    } else {
        return false;
    }
}


vector<string> suggestMe (string &input) {

}

void test (string query,TrieNode *root) {

    if ( queryFromTrie (root,query) ) {
        cout << "query = (" << query << ") found in the tree." << endl;
    } else {
        cout << "query = (" << query << ") not found in the tree." << endl;
    }
}


int main () {

    TrieNode *root = NULL;
    string inputSet[] = {"she","sells","sea","shells"};
    int leafValues[] = {10,2,5,6};
    vector<string> inputVec (inputSet,inputSet+sizeof(inputSet)/sizeof(inputSet[0]));
    vector<int> inputLeaf (leafValues,leafValues+sizeof(leafValues)/sizeof(leafValues[0]));
    insertInTrie (inputVec,inputLeaf,&root);

    //string query = "she";
    test ("she",root);
    test ("sells",root);
    test ("shee",root);
}
