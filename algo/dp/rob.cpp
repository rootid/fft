
public static int rob(int[] value){
        int tmp = 0;
        int[] max = new int[value.length];
        for(int i=0;i<value.length;i++){
            if(i<2){
                max[i] = value[i];
            }else{
                tmp = max[i-2] + value[i];
                if(tmp>max[i-1]){
                    max[i] = tmp;
                }else{
                    max[i] = max[i-1];
                }
            }
        }
        
        System.out.println(Arrays.toString(max));
        
        return max[value.length];
    }
}
