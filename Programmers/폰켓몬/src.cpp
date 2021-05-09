#include <vector>
#include <unordered_set>
using namespace std;

int solution(vector<int> nums)
{
    unordered_set<int> mSet;
    for (int i = 0; i < nums.size(); i++) {
        mSet.insert(nums[i]);
    }
    if (mSet.size() > nums.size() / 2) {
        return nums.size() / 2;
    }
    return mSet.size();
}