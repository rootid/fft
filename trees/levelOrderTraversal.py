
# solutioin 1
def levelOrderBottom(self, root):
    if not root:
        return []
    level = [root]
    stack = []
    while level:
        stack.append([each.val for each in level])
        level = [node for each in level for node in (each.left, each.right) if node]
    return stack[::-1]

# solution 2
def levelOrderBottom(self, root):
    if not root:
        return []
    levels = [[root]]
    result = []
    while levels:
        curlevel = levels.pop()
        newlevel, curvalues = [], []
        for each in curlevel:
            if each:
                curvalues += [each.val]
                newlevel += [each.left, each.right]
        if curvalues:
            result.append(curvalues)
        if newlevel:
            levels.append(newlevel)
    return result[::-1]


def levelOrderBottom(self, root):
    out, level = [], [root]
    if root:
        while level:
            out += [],
            add = out[-1].append
            level = [kid
                     for node in level if not add(node.val)
                     for kid in (node.left, node.right) if kid]
    return out[::-1]


>>> from timeit import timeit
>>> def test_append():
        x = []
        for i in xrange(100):
            x += [i]

>>> def test_list_comprehension():
        x = [i for i in xrange(100)]
        
>>> timeit(test_append, number=100000)
4.446563311239515
>>> timeit(test_list_comprehension, number=100000)
1.0300341831108426
>>> 


