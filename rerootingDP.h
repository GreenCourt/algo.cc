template <class S, class V, class E,
         S (*opS)(S, S), 
         S (*opV)(S, V), 
         S (*opE)(S, E), 
         S (*e)()>
struct RerootingDP {
  int n;
  vector<vector<int>> adj;
  vector<V> vertex_info;
  vector<vector<E>> edge_info;
  vector<vector<S>> dp;
  vector<S> ans;

  RerootingDP(int n) : n(n), adj(n), vertex_info(n), edge_info(n), dp(n), ans(n, e()) {}

  void add_edge(int from, int to, const E& info=E()) {
    adj[from].push_back(to);
    edge_info[from].emplace_back(info);
  };

  void solve() {
    /* O(N) */
    dfs(0);
    reroot(0);
  }

  S dfs(int v, int p=-1) {
    int deg = adj[v].size();
    dp[v] = vector<S>(deg, e());
    S x = e();
    for(int i=0; i<deg; i++) {
      int u = adj[v][i];
      if(u==p) continue;
      dp[v][i] = opE(dfs(u,v), edge_info[v][i]);
      x = opS(x, dp[v][i]);
    }
    return opV(x, vertex_info[v]);
  }

  void reroot(int v, int p=-1, const S& pval=e()) {
    int deg = adj[v].size();
    for(int i=0; i<deg; i++) if(adj[v][i] == p) {
      dp[v][i] = pval;
      break;
    }
    vector<S> sumL(deg+1, e()), sumR(deg+1, e());
    for(int i=0; i<deg; i++) sumL[i+1] = opS(sumL[i], dp[v][i]);
    for(int i=deg-1; i>=0; i--) sumR[i] = opS(sumR[i+1], dp[v][i]);
    ans[v] = sumL[deg];

    for(int i=0; i<deg; i++) {
      int u = adj[v][i];
      if (u == p) continue;
      reroot(u, v, opE(opV(opS(sumL[i], sumR[i+1]), vertex_info[v]), edge_info[v][i]));
    }
  }
};

#if 0
struct V { V() {}; };
struct E { E() {}; };
struct S { S() {}; };
S e() { return ; }
S opS(S a, S b) { return ; }
S opV(S s, V info) { return s; }
S opE(S s, E info) { return s; }
#endif
