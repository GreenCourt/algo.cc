template<typename A,size_t N,typename T> void FILL(A (&array)[N],const T &val){fill((T*)array,(T*)(array+N),val);}
template<typename T> void FILL(vector<T> &v, const T &x) {fill(v.begin(), v.end(), x);}
template<typename T> void FILL(vector<vector<T>> &v, const T &x) {for(auto &i:v)fill(i.begin(), i.end(), x);}
template<typename T> void FILL(vector<vector<vector<T>>> &v, const T &x) {for(auto &i:v) for(auto &j:i)fill(j.begin(), j.end(), x);}
