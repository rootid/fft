/**

Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.

For example:
Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it.

*/

//38 % 10 = 8
//8 % 10 = 3
//
//38/10 = 3
//num = 8
//
//99999

int getSum(int num) {

    int sum = 0;
    int rem = num/10;    //rem = 9999;
    while (rem >= 1) {  //rem = 3
        sum += (num%10);  // sum = 9+9+9+9+9 = 4+5
        num = num/10;     //num = 0
        if (num == 0 && sum/10 >= 1) {
            rem = sum;   //rem = 45
            num = rem;   //num = 45
            sum = 0;     //sum = 0
        } else if (num == 0 && sum/10 <= 9) {
            break;
        }      
    }
    return sum;
}


int addDigits(int number){
    if(number<10){
        return number;
    }

    int sum = 0;
    while(number>0){
        sum += number%10;
        number = number/10;
    }

    return addDigits(sum);
}
