#!/usr/bin/env python

lst_ = ['5.35' 
        ,'a'
        ,'false'
        ,'100'
        ,'I am a code monk'
        ,'true'
        ,'17.3'
        ,'c'
        ,'derp']



def is_float(input):
  try:
    num = float(input)
  except ValueError:
    return False
  return True

int main() :
    for i in lst_ :
        #print "%s = %d " %(i,len(i))
        if(i.isdigit()) :
            print "Primitive : int"
        elif( len(i) == 1 and ( (i >= 'a' and i <= 'z') or (i >= 'A' and i <= 'Z'))  ) :
            print "Primitive : char"
        elif (i == 'true' or i == 'false') :
            print "Primitive : boolean"
        elif(is_float(i) == True):
            print "Primitive : double"
        else :
            print "Referenced : String"
    
    

