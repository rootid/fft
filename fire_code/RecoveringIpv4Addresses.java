import java.util.*;
// Recovering IPv4 Addresses
// You are given a String containing at least 4 numbers that represented an IPv4
// Address, but the separator data - i.e. the dots that separate each Byte in a
// 4 Byte Ipv4 address, has been lost. Write a method - generateIPAddrs that
// takes in this String and returns an ArrayList of Strings containing all
// possible IPv4 Addresses that can be generated from the given sequence of
// decimal integers.
// Note:
//- The IP Addresses for this problem are written in the decimal dot notation.
// - You must use all the digits in the input String
// - The order in which the IP Addresses are returned does not matter
// - 0.0.0.1 and 0.0.0.01 may be considered 2 distinct possibilities. i.e. do
// not ignore leading or trailing 0s.
// Examples:
// generateIPAddrs("1001") ==> {"1.0.0.1"}
// generateIPAddrs("1010") ==> {"1.0.1.0"}
// generateIPAddrs("25525511135") ==> {"255.255.11.135", "255.255.111.35"}
public class RecoveringIpv4Addresses {
  //############### Iterative solution #########################
  public static ArrayList<String> generateIPAddrs(String s) {
    ArrayList<String> result = new ArrayList<>();
    if (s == null || s.length() <= 3) return result;
    StringBuilder sb = new StringBuilder(s);
    generateIPAddrsHelper(sb, result);
    return result;
  }

  private static void generateIPAddrsHelper(StringBuilder sb,
                                            ArrayList<String> result) {
    // 12.345.34.456

    for (int a = 1; a <= 3; a++)        // ends at a Each interval of length = 3
      for (int b = 1; b <= 3; b++)      // ends at b
        for (int c = 1; c <= 3; c++)    // ends at c
          for (int d = 1; d <= 3; d++)  // ends at d
            if (a + b + c + d == sb.length()) {
              int A = Integer.valueOf(sb.substring(0, a));
              int B = Integer.valueOf(sb.substring(a, a + b));
              int C = Integer.valueOf(sb.substring(a + b, a + b + c));
              int D = Integer.valueOf(sb.substring(a + b + c, a + b + c + d));
              String ans = "";
              // In case of ip excluding zeros use only A,B,C,D to construct ip
              // addresses
              if (A <= 255 && B <= 255 && C <= 255 && D <= 255)
                if ((ans = sb.substring(0, a) + "." + sb.substring(a, a + b) +
                           "." + sb.substring(a + b, a + b + c) + "." +
                           sb.substring(a + b + c, a + b + c + d))
                        .length() == sb.length() + 3)
                  result.add(ans);
            }
  }

  //################### Recursion ######################
  public ArrayList<String> restoreIpAddresses(String s) {
    ArrayList<String> result = new ArrayList<>();
    if (s == null || s.length() <= 3 || s.length() > 12) return result;
    helper(s, 0, 0, "", result);
    return result;
  }

  void helper(String s, int k, int group, String localStr,
              ArrayList<String> result) {
    if (group == 4 && k == s.length()) {
      result.add(localStr);
      return;
    }
    // pick all the strings of length 3
    for (int i = 1; i <= 3; i++) {
      if (k + i > s.length()) break;
      String section = s.substring(k, k + i);
      // if(section.length() > 1 && section.startsWith("0") ||
      // Integer.parseInt(section) >= 256)  break;
      if (Integer.parseInt(section) >= 256) break;
      helper(s, k + i, group + 1,
             group == 0 ? section : localStr + "." + section, result);
    }
  }
}
