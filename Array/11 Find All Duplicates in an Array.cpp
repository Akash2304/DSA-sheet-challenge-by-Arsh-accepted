/***************************************************************************************************************************************************************************
Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears once or twice,
return an array of all the integers that appears twice.

You must write an algorithm that runs in O(n) time and uses only constant extra space.

 

Example 1:

Input: nums = [4,3,2,7,8,2,3,1]
Output: [2,3]
Example 2:

Input: nums = [1,1,2]
Output: [1]
Example 3:

Input: nums = [1]
Output: []
 

Constraints:

n == nums.length
1 <= n <= 105
1 <= nums[i] <= n
Each element in nums appears once or twice.
**************************************************************************************************************************************************************************/

Before explaining the algo, we should always keep in mind that every element will be in range of (1,n) where n is the size of input array.

Algorithm:

Scan every element in array.
Negate the value at index of ((absolute value of scanned element) - 1)).
Now check if the value a the index is +ve or not. If positive its a duplicate element .
Sample array :
[4,2,4,3,1]

1st Pass:
Element Scanned = 4
Index to negate = 3
Array => [4,2,4,-3,1]
n[3] = -3 which is -ve so this is distinct till now

2nd Pass:
Element Scanned = 2
Index to negate = 1
Array => [4,-2,4,-3,1]
n[1] = -2 which is -ve so this is distinct till now

3rd Pass:
Element Scanned = 4
Index to negate = 3
Array => [4,-2,4,3,1]
n[3] = 3 which is +ve , means its duplicate. Add to duplicates vector.

4th Pass:
Element Scanned = 3
Index to negate = 2
Array => [4,-2,-4,3,1]
n[2] = -4 which is -ve so this is distinct till now.

5th Pass:
Element Scanned = 1
Index to negate = 0
Array = [-4,-2,-4,3,1]
n[0] = -4 which is -ve so this is distinct till now

[-4] was the duplicate element found .

Time Complexity: O(n) where n is size of input array
Space Complexity: O(1)

**************************
class Solution {
public:
    vector<int> findDuplicates(vector<int>& n) {
        vector<int> duplicates;
        
        
        for(int i=0;i<n.size();i++)
        { 
            // evaluate index of selected element if array would have been sorted..
            int indexOfElem = abs(n[i]) - 1;
            
            // negate the element
            n[indexOfElem] = - n[indexOfElem];
            
            // if this element is positive means double negation had happened which 
            // means we editied this element twice.
            if(n[indexOfElem]>0)
                duplicates.push_back(indexOfElem+1);
            
        }
        return duplicates;
    }
};
