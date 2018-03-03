//Gas Station
//There are N gas stations along a circular route, where the amount of gas at
//station i is gas[i].
//You have a car with an unlimited gas tank and it costs cost[i] of gas to
//travel from station i to its next station (i+1). You begin the journey with
//an empty tank at one of the gas stations.
//Return the starting gas station's index if you can travel around the circuit
//once, otherwise return -1.
//Note:
//The solution is guaranteed to be unique.
//####################### Please NOTE : solution is guaranteed to be unique. #######################
// if the sum of gas is greater than the sum of cost, then there's a solution
// the start station of the solution exists after the greatest net deficit(GND) station
// 0-------k--n  given net[0-n] > 0,  station k is GND
// (1) for any station i between k and n, net[k-i] > 0, cause if not, k would not be the GND
// (2) for any station j between 0 and k, net[k-n-j] > 0,
//     cause net[k-n] + net[0-k] > 0, net[0-j] > net[0-k] (k is GND)
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int len = gas.size();
    int total_gas = 0;
    int total_cost = 0;
    int tank = 0;
    int start = 0;
    for(int i=0;i<len;i++) {
        total_gas += gas[i];
        total_cost += cost[i];
        tank += (gas[i] - cost[i]);
        if(tank < 0) {
            start = i + 1;
            tank = 0; //start fueling the tank once again
        }
    }
    if (total_cost > total_gas) {
        return -1;
    }
    return start;
}
