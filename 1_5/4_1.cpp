class Solution {
public:
    string p_;
    string s_;
bool regexp(size_t sPos, size_t pPos)
{
	if (sPos >= s_.size()){
        //aa
        //aa*
		if (p_[pPos] == '*')
			return true;
        //aa
        //aaa*
		if(pPos+1<p_.size())
		{
			if (p_[pPos + 1] == '*')
			{
                //aa
                //aaa*a*
				if (pPos + 2 < p_.size())
					return regexp(sPos, pPos + 2);
				return true;
			}
		}
		return  pPos >= p_.size();
	}
	if (p_[pPos] == '.' || p_[pPos] == s_[sPos])
	{
		if (pPos + 1 < p_.size() && p_[pPos + 1] == '*')
		{
			//尝试匹配0个
			if (regexp(sPos, pPos + 2))
				return true;
			//尝试匹配1个
			if (regexp(sPos + 1, pPos))
				return true;
			return false;
		}
		return regexp(sPos + 1, pPos + 1);

	}
	if (p_[pPos] != s_[sPos])
	{
		if (pPos + 1 < p_.size() && p_[pPos + 1] == '*')
			return regexp(sPos, pPos + 2);	
		return false;
	}
	return false;
}

	bool isMatch(string s, string p) {
        p_ = p;
        s_ = s;
        return regexp(0, 0);
	}
};