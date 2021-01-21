class Solution {
public:
	Solution() :counter(0),tmparr() {}
	void ms(vector<int>& arr, int L, int R);
	vector<int> tmparr;
	int counter;
    int reversePairs(vector<int>& nums) {
        int len = nums.size();
        if (len < 2)
            return  0;
        tmparr = vector<int>(len);
        ms(nums, 0, len - 1);
        return counter;
	}
};

void Solution::ms(vector<int>& arr, int L, int R) {
	if (L == R)
		return;
	int mid = (R + L) / 2;
	ms(arr, L, mid);
	ms(arr, mid + 1, R);
    int tmpIndex = 0;
	int L_index = L;
	int R_index = mid + 1;
	int tmp = 0;
	//34 12
	while (L_index <= mid && R_index <= R) {
		if (arr[L_index] > arr[R_index])
            counter += (R-R_index+1);
		tmparr[tmpIndex++] = arr[L_index] > arr[R_index] ? arr[L_index++] : arr[R_index++];

	}
	while (L_index <= mid) {
		tmparr[tmpIndex++] = arr[L_index++];
	}
	while (R_index <= R) {
		tmparr[tmpIndex++] = arr[R_index++];
	}
	for (int i = 0; i < tmpIndex; i++) {
		arr[L + i] = tmparr[i];
	}
}
