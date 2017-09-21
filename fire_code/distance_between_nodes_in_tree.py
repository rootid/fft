#!/usr/bin/env python
# -*- coding: utf-8 -*-

#Write a function that given a BST, it will return the distance between 2 nodes.
#For example, given this tree
#
#         A
#        / \
#       B   C
#      / \   \
#     D   E   F
#    /         \
#   G           H
#The distance between G and F is : [G->D->B->A->C->F]
#The distance between E and H is : [E->B->A->C->F->H]
#bottom-up approach, which takes worst case O(n) time. A similar problem on Leetcode is a question called "maximum path sum" I think.
def findDistance(TreeNode root, TreeNode p, TreeNode q):

if root == null or p == q:
	return 0

distance_left = findDistance(root.left, p, q)
distance_right = findDistance(root.right, p, q)

if (distance_left > 0 and distance_right > 0):
	return distance_left + distance_right
if (distance_left > 0 and root is p or q):
	return distance_left
if (distance_right > 0 and root is p or q):
	return distance_right
if (distance_left == 0 and distance_right == 0):
	return 0 if root is not p and not q
	return 1 if root is p or q
else:
	return max(distance_left, distance_right) + 1


# Find distance between two given keys of a Binary Tree

class TreeNode(object):
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class BTree(object):

    def __init__(self):
        self.root = TreeNode(1)
        node = TreeNode(2)
        self.root.left = node
        node = TreeNode(3)
        self.root.right = node
        node = TreeNode(4)
        self.root.left.left = node
        node = TreeNode(5)
        self.root.left.right = node
        node = TreeNode(6)
        self.root.right.left = node
        node = TreeNode(7)
        self.root.right.right = node
        node = TreeNode(8)
        self.root.right.left.right = node

    def getBTHead(self):
        return self.root

class BTreeDistance(object):

    dis = 0

    def findDistance(self, root, p, q):
        if not root:
            return 0

        ldepth = self.findDistance(root.left, p, q)
        rdepth = self.findDistance(root.right, p, q)

        if root.val == p or root.val == q:
            if max(ldepth, rdepth) != 0:
                # 给定节点为上下级关系，如4,2
                self.dis = max(ldepth, rdepth)
            # level + 1
            return 1
        if ldepth != 0 and rdepth == 0 or ldepth == 0 and rdepth != 0:
            # 如果左右节点有一个level>1，增+1 返回
            return max(ldepth, rdepth) + 1

        if ldepth > 0 and rdepth > 0:
            # 如果左右节level大于1，则相加，保存结果
            self.dis = ldepth + rdepth

        return 0
    
    def getResult(self, root, p, q):
        self.findDistance(root, p, q)
        return self.dis

tree = BTree()
root = tree.getBTHead()

bd = BTreeDistance()
print bd.getResult(root, 4, 5)
