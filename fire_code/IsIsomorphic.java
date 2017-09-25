// 1. Map only accept reference type as Key.
// 2. t.charAt(i) will be autoboxing to Character as Key. t.charAt(i)+"" return
// String as Key. Main idea is using single HashMap as two HashMaps with
// different keys.

public class IsIsomorphic {
  public boolean isIsomorphic(String s, String t) {
    Map m = new HashMap();
    for (Integer i = 0; i < s.length(); ++i)
      if (m.put(s.charAt(i), i) != m.put(t.charAt(i) + "", i)) return false;
    return true;
  }
}
