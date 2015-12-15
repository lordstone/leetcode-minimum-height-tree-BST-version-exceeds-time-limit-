class Solution {
public:

    typedef struct node{
        vector<node*> arr;
        int val;
        node(int myval){val = myval;}
    }node;
    
    
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        vector<int> ans;
        if(n == 0 || edges.size() == 0) return ans;
        
        vector<node> arr;
        for(int i = 0; i < n; i ++){
            arr.push_back(node(i));
        }
         
        
        vector<int> minMax (n, -1);
        int curmin = -1;
        
        for(int i = 0; i < edges.size(); i ++){
            arr[edges[i].first].arr.push_back(&arr[edges[i].second]);
            arr[edges[i].second].arr.push_back(&arr[edges[i].first]);
        } 
        
        for(int i = 0; i < n ; i ++){
            stack<node*> mystk; stack<int> mystk_lvl;
            mystk.push(&arr[i]);
            mystk_lvl.push(0);
            
            bool nodemap[n] = {false};
            nodemap[i] = true;
            
            int imax = 0;
            
            while(mystk.size() > 0 ){
                
                node * cur = mystk.top();
                int mycurstep = mystk_lvl.top();
                
                nodemap[cur->val] = true;
                
                if(imax < mycurstep) imax = mycurstep;
                if(mycurstep > curmin && curmin != -1) break; //not a candidate
                
                mystk.pop();
                mystk_lvl.pop();
                
                for(int j = 0; j < cur->arr.size(); j ++){
                    if(!nodemap[cur->arr[j]->val]){
                        mystk.push(cur->arr[j]);
                        mystk_lvl.push(mycurstep + 1);
                    }
                }//end for j
                
            }//end while
            
            if(imax < curmin || curmin == -1) curmin = imax;
            minMax[i] = imax;
            
        }//end for i
        
        for(int i = 0; i < n ; i++){
            if(minMax[i] == curmin) ans.push_back(i);
        }
        
        return ans;
    }
    
    
};
