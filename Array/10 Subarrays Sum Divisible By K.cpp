/**************************************************************************************************************************************************************************
Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.

A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [4,5,0,-2,-3,1], k = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by k = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
Example 2:

Input: nums = [5], k = 9
Output: 0
 

Constraints:

1 <= nums.length <= 3 * 104
-104 <= nums[i] <= 104
2 <= k <= 104
*************************************************************************************************************************************************************************/

// FOR BETTER UNDERSTAND GO TO YOUTUBE THERE EXPLANATION IS QUITE GOOD

Let us consider the following example:
nums = [4,5,0,-2,-3,1], k = 5
If we consider the prefix sum of the above array and the remainders when they are divided by k (i.e prefixSum[i]%k), we get the following:

prefixSum = [4, 9, 9, 7, 4, 5]
   ..%k   = [4, 4, 4, 2, 4, 0]
For any subarray [i..j] whose sum is divisible by k, we can easily see that prefixSum[j] - prefixSum[i-1] = 0.
Thus if there are any repetitions in our prefixSum%k array, that represents a required subarray.

So if we have the count of every possible value of prefixSum%k, we can determine if there are any subarray that end at the current index and the sum is divisible by k.

Approach
We loop over the array, calculating the prefixSum on the way. We don't need to store this as they are never reused. We maintain the count of every sum%k we can get.
If we get a repitition, this index can be paired by any of the other indices that have the same sum%k, and hence contributes count[sum%k] to the total.

For considering the case of the prefixSums being themselves divisible by k and the case of the whole array being a subarray whose sum is divisible by k,
we need to initialize count[0] = 1.

Complexity
Time complexity: O(n+k)O(n + k)O(n+k)

Space complexity: O(k)O(k)O(k)
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
 int n = nums.size();
        vector<int> sums(k, 0);
        sums[0]++;
        int cnt = 0;
        int currSum = 0;
        for(int i = 0; i<n; i++) {
            // yaha k negative remainder ko handle karne ke liye use kiya gaya 
            currSum = (currSum + nums[i]%k + k)%k;
            cnt += sums[currSum];
            sums[currSum]++;
        }
        return cnt;
           
    }
};
/******************************************************************************************************************************************************************/

The solution makes use of a hashMap and works in a single pass.
The solution section gives something that is confusing for me so here is a more understandable solution:

curr_sum here is denoting the traditional cumulative sum at any point during the traversal of the arrray
Now curr_sum%k at any point gives the remainder,this can either be 0 or any other number.
Whatever the remainder is we are simply putting in the map thereby preparing a mapping of all the possible remainders from all
the possible sum and storing their frequency as the values.
The only thing and the most important this is to understand why this line of code works and why it gives the desired outputs.
if(mp.find(rem)!=mp.end())
count+=mp[rem];
We are increasing the count by the number of times the given remainder has been seen.
I am considering it a fact that :
If the remainders of array upto i and array upto j are equal (ri=rj),
then subarray from i to j has a remainder of 0,
which means It's the type of subarrays we're looking for!
Look here: https://leetcode.com/problems/subarray-sums-divisible-by-k/discuss/413234/DETAILED-WHITEBOARD!-BEATS-100-(Do-you-really-want-to-understand-It)
Now lets dry run the code with this concept to drill it in.

A = [4,5,0,-2,-3,1], K = 5
A = 4, curr_sum = 4, curr_sum%K = 4 map now is: 0-->1, 4-->1 RESULT: []

A = 5, curr_sum = 9, curr_sum%K = 4 map now is: 0-->1, 4-->2 So this means we found a remainder that was already there! count+=1 RESULT: ([5], ) (added one more)

A = 0, curr_sum = 9, curr_sum%K = 4 map now is: 0-->1, 4-->3 So this means we found a remainder that was already there! count+=2 RESULT: ([5,0], [5], [0]) (added two more)

A = -2, curr_sum = 7, curr_sum%K = 2 map now is: 0-->1, 4-->3, 2-->1
RESULT: ([5,0], [5], [0])

A = -3, curr_sum = 4, curr_sum%K = 4 map now is: 0-->1, 4-->4, 2-->1 So this means we found a remainder that was already there! count+=3
  RESULT: ([5,0], [5], [0], [5,0,-2,-3], [0,-2,-3], [-2,-3]) (added three more)

A = 1, curr_sum = 5, curr_sum%K = 0 map now is: 0-->2, 4-->4, 2-->1 So this means we found a remainder that was already there! count+=1 
  RESULT: ([5,0], [5], [0], [5,0,-2,-3], [0,-2,-3], [-2,-3], [4,5,0,-2,-3,1]) (added one more)

class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        int n = A.size();
        if(n==0) return 0;
        
        int i = 0, count = 0;
        int curr_sum = 0;
        unordered_map<int, int> mp;
        mp[0] = 1;// this is done because initial cumulative sum = 0 and that sum%k will be equal to 0 always
        
        while(i<n)
        {
            curr_sum+= A[i++];
            int rem = curr_sum % K;
            if(rem<0) rem += K;
            
            if(mp.find(rem)!=mp.end())
                count+=mp[rem];
            
            mp[rem]++;
            
        }
        return count;
    }
};
