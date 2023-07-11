/**************************************************************************************************************************************************************************
There are several cards arranged in a row, and each card has an associated number of points. The points are given in the integer array cardPoints.

In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.

Your score is the sum of the points of the cards you have taken.

Given the integer array cardPoints and the integer k, return the maximum score you can obtain.

 

Example 1:

Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12
Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score.
The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.
Example 2:

Input: cardPoints = [2,2,2], k = 2
Output: 4
Explanation: Regardless of which two cards you take, your score will always be 4.
Example 3:

Input: cardPoints = [9,7,7,9,7,7,9], k = 7
Output: 55
Explanation: You have to take all the cards. Your score is the sum of points of all cards.
 

Constraints:

1 <= cardPoints.length <= 105
1 <= cardPoints[i] <= 104
1 <= k <= cardPoints.length
**************************************************************************************************************************************************************************/

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        
        //v1 is prefissum vector from start v2 is from end 

      // we can also do this in same array no need of v1 and v2 but this is okk 
        int n=cardPoints.size();
        vector<int>v1(k),v2(k);

        v1[0]=cardPoints[0];  
        for(int i=1;i<k;i++)
        v1[i]=v1[i-1]+cardPoints[i];

        v2[0]=cardPoints[n-1];
          int j=1;
        for(int i=n-2;i>=(n-k);i--)
        {
            v2[j]=v2[j-1]+cardPoints[i];
            j++;
        }

        int maxs=max(v1[k-1],v2[k-1]);
          int i;
          int sum=0;
        for( i=0,j=k-2;i<k-1;i++,j--)
        {
              sum+=v2[i]+v1[j];
              if(maxs<sum)
              maxs=sum;

              sum=0;
        }
        for( i=0,j=k-2;i<k-1;i++,j--)
        {
              sum+=v1[i]+v2[j];
              if(maxs<sum)
              maxs=sum;

              sum=0;
        }

        return maxs;

             
        
    }
};

/*********************************************************************************************************************************************************************/
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int res = 0;
		
		//First k elements in our window
        for(int i=0;i<k;i++) res+=cardPoints[i];
        
        int curr=res;
        for(int i=k-1;i>=0;i--) {
			//We remove the last visited element and add the non-visited element from the last
            curr-=cardPoints[i];
            curr+=cardPoints[cardPoints.size()-k+i];
			
            //We check the maximum value any possible combination can give
			res = max(res, curr);
        }
        
        return res;
    }
};

/************************************************************************************************************************************************************************/
// Approach: 2: DP. 
// Key here is realizing that only 1st K and last K elements are relevant so calculating the sums from them.
// TC: O(n), SC: O(n)
int maxScore(vector<int>& cardPoints, int k) {
    int n=cardPoints.size();
    int maxScore = 0;
    vector<int> front(k+1), rear(k+1);
    front[0] = rear[0] = 0;

    // calculate prefix sum of the 1st k elements in front and last k elements in rear
    // arr: [1,2,3,4,5,6,1], k=3
    // front: [0,1,3,6], rear: [0,1,7,12]
    for(int i=0;i<k;i++){
        front[i+1] = front[i]+cardPoints[i];
        rear[i+1] = rear[i] + cardPoints[n-1-i];
    }

    // just add relevant prefix sums from front and rear to get the currentScore
    for(int i=0;i<=k; i++){
        int currentScore = front[i] + rear[k-i];
        maxScore = max(maxScore, currentScore);
    }
    return maxScore;
}


// Approach: 3 (Space Optimized DP)
// TC: O(k), SC: O(1)
    int maxScore(vector<int>& cardPoints, int k) {
        int n=cardPoints.size();
        int front = 0, rear = 0;
        
        // frontScore is initialized to the sum of the first k cards in the array, and rearScore is initialized to 0.
        for(int i=0;i<k; i++)
            front += cardPoints[i];
        
        int maxScore = front, currentScore;
        
        // Iterate backwards from i = k - 1 -> 0. At each iteration, we calculate the score by selecting i cards from the beginning
        // of the array and k - i cards from the end (currentScore). If this score is greater than maxScore, we update it.
        for(int i=k-1; i>=0; i--){
            front -= cardPoints[i];
            rear += cardPoints[n-(k-i)];
            currentScore = front+rear;
            maxScore = max(currentScore, maxScore);
        }
        return maxScore;
    }
