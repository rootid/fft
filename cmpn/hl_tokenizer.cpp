Given a string, parse it and return a string array. It's like a tokenizer, but the rules are too...
For exmple, string="abc(edf)hij{klmn}opq[rst]uvw"
The delimiter are (), {}, []. They are in pair. So output array:
["abc", "edf", "hij", "klmn", "opq", "rst", "uvw"]
That's the rule 1. The rule 2 is, if any two consecutive "(" means escaping, that is "((" is actually output char "(". It's not part of the delimitor. Similar to ")", "{", "}", "[", "]".
abc(e))df) => ["abc", "e)df"], since the "))" outpus ")".
Rule 3: if "{" is inside a delimiter pair (), then "{" isn't part of the delimitor. Output it as is.
abc(e{df}}g) =>  ["abc", "e{df}}g"]

//scan , stack (lt)
public List<String> tokenize(String s) {

  Set<Character> ltSet = new Hash<>();
  ltSet.add("(");
  ltSet.add("{");
  ltSet.add("[");

  Set<Character> rtSet = new Hash<>();
  rtSet.add(")");
  rtSet.add("}");
  rtSet.add("]");
  Stack<Integer> cStk = new Deque<>();
  char[] charArr = s.toCharArray();
  List<String> result = new ArrayList<>();
  int startIdx = 0;
  for(int i=0;i<charArr.length;i++) {
    if(cStack.isEmpty() && ltSet.contains(charArr[i])) {
      cStack.push(i);
      result.add(s.substring(startIdx, i));
      startIdx = i;
    }
    if(!cStack.isEmpty() && rtSet.contains(charArr[i])) {
      if(charArr[cStack.top()] == '(' && charArr[i] != ')') continue;
      else if(charArr[cStack.top()] == '{' && charArr[i] != '}') continue;
      else if(charArr[cStack.top()] == '[' && charArr[i] != ']') continue;
      char lastMatch = c;
      while(i > charArr.length && chrArr[i] == lastMatch) i++;
      result.add(s.substring(startIdx, i));
      cStack.pop();
      startIdx = i;
    }
  }
  if(startIdx != charArr.length())
      result.add(s.substring(startIdx, charArr.length()));
  return result;
}
