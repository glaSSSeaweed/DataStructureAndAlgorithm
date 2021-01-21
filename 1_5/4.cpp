class Solution {
public:
    bool isMatch(string s, string p) {
       	int m = s.size();
		int n = p.size();
		vector<vector<bool> > dynamicProg(m+1, vector<bool>(n+1, false););
		dynamicProg[0][0] = true;	
		// "" "x*y*z..."
		for (int j = 1; j <= n; j++)
			if (p[j - 1] == '*')
				dynamicProg[0][j] = dynamicProg[0][j - 2];

		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (p[j - 1] == '*')
				{
					//IS '*'
					//aaa
					//aaa b*
					//匹配0个
					//s[0:i-1],p[0:j-1] 取决于 s[0:i-1],p[0:j-3]
					bool repeatZero = dynamicProg[i][j - 2];
					bool repeatOver = false;

					//aaa
					//a*a
					//匹配一个
					//s[0:i-1],p[0:j-1] 取决于 s[0:i-2],p[0:j-1] /a /a* 注意(/ab /a*)
					if (s[i - 1] == p[j - 2] || p[j - 2] == '.')
						repeatOver = dynamicProg[i - 1][j];
					
					dynamicProg[i][j] = repeatZero || repeatOver;
				}
				else
				{
					//NOT '*'
					//s[0:i-1],p[0:j-1] 取决于 s[0:i-2],p[0:j-2]
					if (s[i - 1] == p[j - 1] || p[j - 1] == '.')
						dynamicProg[i][j] = dynamicProg[i - 1][j - 1];
				}
			}
		}
		return dynamicProg[m][n];
    }
};