//Integer to English Words
//Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.
//For example,
//123 -> "One Hundred Twenty Three"
//12345 -> "Twelve Thousand Three Hundred Forty Five"
//1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
//Hint:
//Did you see a pattern in dividing the number into chunk of words? For example, 123 and 123000.
//Group the number by thousands (3 digits). You can write a helper function that takes a number less than pow(10,3) and convert just that chunk to words.
//There are many edge cases. What are some good test cases? Does your code work with input such as 0? Or pow(10,3)010? (middle chunk is zero and should not be printed out)


//######################################## Recursive ########################################
final String[] digits = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"}; //0, 1-19
final String[] tens = {"Zero", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"}; //0,10-90
final int[] powers = { (int) Math.pow(10,9), (int) Math.pow(10,6), (int) Math.pow(10,3), (int)Math.pow(10,2), (int)Math.pow(10, 1)};
private String int2string(int n) {
    if (n >= powers[0]) {
        return int2string(n / powers[0] ) + " Billion" + int2string(n % powers[0] );
    } else if (n >= powers[1]) {
        return int2string(n / powers[1] ) + " Million" + int2string(n % powers[1]);
    } else if (n >= powers[2]) {
        return int2string(n / powers[2]) + " Thousand" + int2string(n % powers[2]);
    } else if (n >= powers[3]) {
        return int2string(n / powers[3]) + " Hundred" + int2string(n % powers[3]);
    } else if (n >= 20) { //21 : Twenty(idxing) one(mod)
        return  " " + tens[n / powers[4]] + int2string(n % powers[4]);
    } else if (n >= 1) {
        return " " + digits[n];
    }
    return "";
}

public String numberToWords(int num) {
    if(num <= 0) return digits[0];
    return int2string(num).trim();
}

//######################################## Recursive ########################################
class Solution {

     final String[] lessThan20Words = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
     final String[] tyWords = {"","","Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
     final String[] THOUSANDS = {"Billion", "Million", "Thousand", "Hundred"};
     final int[] radix = { (int) Math.pow(10,9), (int) Math.pow(10,6), (int) Math.pow(10,3), (int)Math.pow(10,2)};

    public String numberToWords(int num) {
        if (num == 0) return "Zero";
        StringBuffer sb = new StringBuffer();
        int count = 0;
        for (int i = 0; i < radix.length; ++i) {
            if (num/radix[i] == 0) continue;
            sb.append(numberToWords(num / radix[i]) + " "); //get the next number
            sb.append(dexWords[i] + " ");
            num %= radix[i]; //update the number
        }
        if (num < 20) {
            sb.append(lessThan20Words[num]);
        }else {
            sb.append(THOUSANDS[num/10] + " ");
            sb.append(lessThan20Words[num % 10]);
        }
        return sb.toString().trim();
    }
}
//######################################## Recursive ########################################
string digits[20] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
string tens[10] = {"Zero", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
int powers[5] = {10,10*10,10*10*10,100*100*100,100*100*100*100*10};

int[] radix = {10*Math.pow(10,9),10*Math.pow(10,5), 1000, 100};


string int2string(int n) {
    if (n >= pow(10,9)) {
        return int2string(n / powers[4] ) + " Billion" + int2string(n % powers[4] );
    } else if (n >= pow(10,6)) {
        return int2string(n / powers[3] ) + " Million" + int2string(n % powers[3]);
    } else if (n >= pow(10,3)) {
        return int2string(n / powers[2]) + " Thousand" + int2string(n % powers[2]);
    } else if (n >= pow(10,2)) {
        return int2string(n / powers[1]) + " Hundred" + int2string(n % powers[1]);
    } else if (n >= 20) { //21 : Twenty(idxing) one(mod)
        return  " " + tens[n / powers[0]] + int2string(n % powers[0]);
    } else if (n >= 1) {
        return " " + digits[n];
    } else {
        return "";
    }
}
string numberToWords(int num) {
    if (num == 0) {
        return "Zero";
    }
    string ret = int2string(num);
    return ret.substr(1, ret.length() - 1);
}

//##################### Use of MOVE sematics rather than substring #####################
string numberToWords(int num) {
    if(num == 0) {
        return "Zero";
    } else {
       string ret = int2string(num), result = "";
       move(ret.begin()+1, ret.end(), std::back_inserter(result));
       return result;
   }
}

/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
