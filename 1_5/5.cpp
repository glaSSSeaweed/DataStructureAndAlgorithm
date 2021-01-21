class Solution {
public:
    int m;
    int n;
    vector<vector<char>>* b_;
    string* w_;
    vector<vector<bool>> mark;
    bool foo(int pos, int i, int j){
        mark[i][j] =true;
        if(pos >= w_->length())
            return false;
        if((*w_)[pos] == (*b_)[i][j] && pos == w_->length()-1)
            return true;
        if((*w_)[pos] != (*b_)[i][j]){
            mark[i][j] =false;
            return false;
        }
            
        if(i+1 <m){
            if(!mark[i+1][j] && i+1<m && foo(pos+1, i+1, j)) return true;
        }
            
        if(j+1 <n){
             if(!mark[i][j+1] &&j+1<n && foo(pos+1, i, j+1)) return true;
        }
           
        if(j-1>=0){
            if(!mark[i][j-1] &&j-1>=0 && foo(pos+1, i, j-1)) return true;
        }
         
        if(i-1>=0){
            if(!mark[i-1][j] &&i-1>=0 && foo(pos+1, i-1, j)) return true;
        }
        mark[i][j] =false;
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        n = board[0].size();
        b_ = &board;
        w_ = &word;
        mark = vector<vector<bool>>(m, vector<bool>(n,false));
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(foo(0, i, j))
                    return true;
            }
        }
        return false;
    }
};