/***************************************************************************************************************************************************************************
Given an m x n matrix, return all elements of the matrix in spiral order.

 

Example 1:


Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:


Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100
***************************************************************************************************************************************************************************/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int nrow = matrix.size();
        int ncol = matrix[0].size();
        int l_wall = -1, r_wall = ncol, u_wall = 0, d_wall = nrow;
        char direction = 'r';
        vector<int> result;
        int i = 0, j = 0;
        while(result.size() < nrow * ncol) {
            result.push_back(matrix[i][j]);
            if(direction == 'r') {
                j++;
                if(j == r_wall) {
                    r_wall--;
                    j = r_wall;
                    direction = 'd';
                    i++;
                }
            }
            else if(direction == 'd') {
                i++;
                if(i == d_wall) {
                    d_wall--;
                    i = d_wall;
                    direction = 'l';
                    j--;
                }
            }
            else if(direction == 'l') {
                j--;
                if(j == l_wall) {
                    l_wall++;
                    j = l_wall;
                    direction = 'u';
                    i--;
                }
            }
            else if(direction == 'u') {
                i--;
                if(i == u_wall) {
                    u_wall++;
                    i = u_wall;
                    direction = 'r';
                    j++;
                }
            }
        }
        return result;
    }
};
