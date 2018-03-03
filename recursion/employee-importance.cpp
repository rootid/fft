//Employee Importance
//You are given a data structure of employee information, which includes the
//employee's unique id, his importance value and his direct subordinates' id.
//For example, employee 1 is the leader of employee 2, and employee 2 is the
//leader of employee 3. They have importance value 15, 10 and 5, respectively.
//Then employee 1 has a data structure like [1, 15, [2]], and employee 2 has
//[2, 10, [3]], and employee 3 has [3, 5, []]. Note that although employee 3 is
//also a subordinate of employee 1, the relationship is not direct.
//Now given the employee information of a company, and an employee id, you need
//to return the total importance value of this employee and all his
//subordinates.
//Example 1:
//Input: [[1, 5, [2, 3]], [2, 3, []], [3, 3, []]], 1
//Output: 11
//Explanation:
//Employee 1 has importance value 5, and he has two direct subordinates:
//employee 2 and employee 3. They both have importance value 3. So the total
//importance value of employee 1 is 5 + 3 + 3 = 11.
//Note:
//One employee has at most one direct leader and may have several subordinates.
//The maximum number of employees won't exceed 2000.
/*
// Employee info
class Employee {
    // It's the unique id of each node;
    // unique id of this employee
    public int id;
    // the importance value of this employee
    public int importance;
    // the id of direct subordinates
    public List<Integer> subordinates;
};
*/

//############################### Recursion ###############################
class Solution {
    public int getImportance(List<Employee> employees, int id) {
        int sum = 0;
        for (Employee e : employees) {
            if (e.id == id) {
                sum += e.importance;
                for (int sub : e.subordinates) {
                    sum += getImportance(employees, sub);
                }
            }
        }
        return sum;
    }
}

//#### Traversal ####
int result = 0;
public int getImportance(List<Employee> employees, int id) {
        List<Integer> subordinates = new LinkedList<>();
        int result = 0;
        for (Employee e : employees) {
            if (e.id == id) {
                subordinates = e.subordinates;
                result += e.importance;
                break;
            }
        }
        if (subordinates.size() == 0) return result;
        for (int i : subordinates) result += getImportance(employees, i);
        return result;
}

//#### Traversal ####
  int total = 0;
  public int getImportance(List<Employee> employees, int id) {
      Employee manager = employees.stream().filter(e -> e.id == id).collect(Collectors.toList()).get(0);
      total += manager.importance;
      manager.subordinates.forEach(subId -> getImportance(employees, subId));
      return total;
  }

//##################### BFS  #####################
//Given data structure into a map of Id to importance and subordinates, which
//helps with look up during the BFS with LinkedList as queue.
class Solution {
    class EmpData {
        public int importance;
        public List<Integer> subordinates;
        public EmpData(int imp, List<Integer> subs){
            this.importance = imp;
            this.subordinates = subs;
        }
    }
    public int getImportance(List<Employee> employees, int id) {
        int ret = 0;
        //Build employee to <importance, subordinates> table (HashMap) for quick lookup.
        Map<Integer, EmpData> employeeIdToData = new HashMap<Integer, EmpData>();
        for (Employee emp : employees){
            EmpData empData = new EmpData(emp.importance, emp.subordinates);
            employeeIdToData.put(emp.id, empData);
        }
        //The good old BFS.
        Queue<Integer> toProcess = new LinkedList<>();
        toProcess.add(id);
        while(toProcess.size() != 0){
            int i = toProcess.poll();
            if (!employeeIdToData.containsKey(i)){
                break;
            }else{
                EmpData data = (EmpData) employeeIdToData.get(i);
                ret += data.importance;
                toProcess.addAll(data.subordinates);
            }
        }
        return ret;
    }
}

//##################### traversal  #####################
class Solution(object):
    def getImportance(self, employees, id):
        """
        :type employees: Employee
        :type id: int
        :rtype: int
        """
        index={e.id:(e.importance,e.subordinates) for e in employees}
        def calc(id):
            imp,sub=index[id]
            return imp+sum(map(calc,sub))
        return calc(id)
