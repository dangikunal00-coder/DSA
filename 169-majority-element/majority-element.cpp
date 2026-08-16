class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cnt = 0 ;

        for(int i=0; i<nums.size(); i++)
        {
            cnt = 0;

            for(int j=i; j<nums.size(); j++)
            {
                if(nums[i] == nums[j])
                    cnt ++;
            }

        if (cnt > nums.size()/2)
            return nums[i];
        }

        return -1;
        
    }
};