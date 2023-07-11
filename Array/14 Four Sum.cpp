/**************************************************************************************************************************************************************************
Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:

0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.

 

Example 1:

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
Example 2:

Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]
 

Constraints:

1 <= nums.length <= 200
-109 <= nums[i] <= 109
-109 <= target <= 109
*************************************************************************************************************************************************************************/
The key idea is to downgrade the problem to a 2Sum problem eventually. And the same algorithm can be expand to NSum problem.


class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& num, int target) {
        
         vector<vector<int> > res;
    
        if (num.empty())
            return res;
    
        std::sort(num.begin(),num.end());
        if(target<0 && num[0]>=0)
        return res;
    
        for (int i = 0; i < num.size(); i++) {
        
            long long target_3 = (long long)target - (long long)num[i];
        
            for (int j = i + 1; j < num.size(); j++) {
            
                long long target_2 = (long long)target_3 - (long long)num[j];
            
                int front = j + 1;
                int back = num.size() - 1;
            
                while(front < back) {
                
                    int two_sum = num[front] + num[back];
                
                    if (two_sum < target_2) front++;
                
                    else if (two_sum > target_2) back--;
                
                    else {
                    
                        vector<int> quadruplet(4, 0);
                        quadruplet[0] = num[i];
                        quadruplet[1] = num[j];
                        quadruplet[2] = num[front];
                        quadruplet[3] = num[back];
                        res.push_back(quadruplet);
                    
                        // Processing the duplicates of number 3
                        while (front < back && num[front] == quadruplet[2])
                         ++front;
                    
                        // Processing the duplicates of number 4
                        while (front < back && num[back] == quadruplet[3])
                          --back;
                
                    }
                }
                
                // Processing the duplicates of number 2
                while(j + 1 < num.size() && num[j + 1] == num[j]) ++j;
            }
        
            // Processing the duplicates of number 1
            while (i + 1 < num.size() && num[i + 1] == num[i]) ++i;
        
        }
    
        return res;
    
    }
};
