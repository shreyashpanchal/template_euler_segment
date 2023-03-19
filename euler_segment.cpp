ll timer = 0;
vector<ll> tin;
vector<ll> tout;
vector<ll> segmentTree;
void euler(int node, int parent, vector<vector<ll>> &graph)
{
    tin[node] = timer++;
    for (auto &child : graph[node])
    {
        if (child == parent)
            continue;
        euler(child, node, graph);
    }
    tout[node] = timer++;
}
void buildEuler(ll s, ll e, ll node, vector<ll> &euler)
{
    if (s == e)
    {
        bug(s, e, node, euler[s]);
        segmentTree[node] = euler[s];
        return;
    }
    ll mid = s + (e - s) / 2;
    buildEuler(s, mid, (node * 2) + 1, euler);
    buildEuler(mid + 1, e, (node * 2) + 2, euler);
    segmentTree[node] = segmentTree[(node * 2) + 1] + segmentTree[(node * 2) + 2];
}
ll queryEuler(ll start, ll end, ll l, ll r, ll node)
{
    // no  overlap
    if (end < l or r < start)
        return 0;
    // complete overlap
    bug(start, end, l, r);
    if (start <= l && end >= r)
        return segmentTree[node];
    // partial overlap

    ll mid = l + (r - l) / 2;

    ll leftQuery = queryEuler(start, end, l, mid, (node * 2) + 1);

    ll rightQuery = queryEuler(start, end, mid + 1, r, (node * 2) + 2);

    return leftQuery + rightQuery;
}
ll query(ll node, vector<ll> &tin, vector<ll> &tout, ll m)
{
    ll start = tin[node];
    ll end = tout[node];
    bug(start, end, m);
    return queryEuler(start, end, 0, m - 1, 0);
}
void solve(ll cnt)
{
    ll n;
    cin >> n;
    ll edges = n - 1;
    vector<vector<ll>> graph(n + 1);
    while (edges--)
    {
        ll x, y;
        cin >> x >> y;
        graph[x].pb(y);
        graph[y].pb(x);
    }
    tin.resize(n + 1, 0);
    tout.resize(n + 1, 0);
    euler(1, -1, graph);
    vector<ll> euler((n * 2), 0);
    for (ll i = 1; i <= n; i++)
    {
        euler[tin[i]] = i;
        euler[tout[i]] = i;
    }
    ll m = euler.size();
    segmentTree.resize(m * 4, 0);
    buildEuler(0, m - 1, 0, euler);
    cout << query(2, tin, tout, m) / 2;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    clock_t z = clock();
    ll cnt = 0;
    ll t;

    cin >> t;
    while (t--)
        solve(cnt++);

    cerr << "Run Time : " << ((double)(clock() - z) / CLOCKS_PER_SEC);

    return 0;
}
