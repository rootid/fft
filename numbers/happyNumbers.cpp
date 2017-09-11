//Happy Number
int isHappyNumberHelper(int number){
    if(number<3){
        return number;
    }
    int nextSum = 0;
    while(number>0) {
        int rem = number%10;
        nextSum += pow(rem,2) ;
        number = number/10;
    }
    return isHappyNumberHelper(nextSum);
}

bool isHappyNumber(int no) {
  if ( isHappyNumberHelper (no) == 1) {
    return true;
  }
  return false;
}
