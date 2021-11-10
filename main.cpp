    #include <bits/stdc++.h>

    #define ll      long long
    #define ld      long double
    #define sz(v)   (int)(v.size())
    #define inf     (ll)(1000000000000000000ll)

    using namespace std;

    vector< vector< int > > a;
    vector< vector< int > > a_saved;
    vector< set< int > > g;
    vector< int > used;
    vector< int > mt_left;
    vector< int > mt_right;

    set< int > x, y;

    bool kuhn(int v) {
        if (used[v]) return 0;
        used[v] = 1;
        for (int to : g[v]) {
            if (mt_right[to] == -1 || kuhn( mt_right[to] )) {
                mt_left[v] = to;
                mt_right[to] = v;
                return 1;
            }
        }

        return 0;
    }

    void find_mt() {
        mt_left.assign( sz(g) , -1);
        mt_right.assign( sz(g) , -1);
        for (int i = 0; i < mt_left.size(); i++) {
            if (mt_left[i] != -1) continue;

            used.assign( mt_left.size(), 0 );
            kuhn(i);

        }

    }

    void dfs(int v) {
        used[v] = 1;
        x.insert(v);

        for (int to : g[v]) {

            y.insert(to);

            if (mt_right[to] != -1 && !used[ mt_right[to] ]) {

                dfs( mt_right[to] );
            }
        }
    }
    
    int main() {

        ios_base::sync_with_stdio(0);
        cin.tie(0); cout.tie(0);

        int n;
        cin >> n;
        a.resize(n, vector< int > (n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
        }
        a_saved = a;

        g.resize(n);
        used.resize(n);
        

        for (int i = 0; i < n; i++) {
            int mn = 1000000000;
            for (int j = 0; j < n; j++) {
                mn = min(mn, a[i][j]);
            }
            for (int j = 0; j < n; j++) {
                a[i][j] -= mn;
            }
        }
        for (int j = 0; j < n; j++) {
            int mn = 1000000000;
            for (int i = 0; i < n; i++) {
                mn = min(mn, a[i][j]);
            }
            for (int i = 0; i < n; i++) {
                a[i][j] -= mn;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        while (true) {

            cout << "-----------------------------------------\n\n";

            for (int i = 0; i < n; i++) {
                g[i].clear();
                for (int j = 0; j < n; j++) {
                    if (!a[i][j]) {
                        g[i].insert(j);
                    }
                }
            }
            find_mt();            

            x.clear();
            y.clear();
            used.assign(n, 0);
            for (int i = 0; i < n; i++) {
                if (mt_left[i] == -1 && !used[i]) {
                    dfs( i );
                }
            }
            if (sz(x) == 0) break;

            cout << "x': ";
            for (int i : x) {
                cout << i + 1 << " ";
            }
            cout << endl;
            cout << "y': ";
            for (int i : y) {
                cout << i + 1 << " ";
            }
            cout << endl;

            
            int delta = 1000000000;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (x.count(i) && !y.count(j)) {
                        delta = min(delta, a[i][j]);
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (x.count(i) && !y.count(j)) {
                        a[i][j] -= delta;
                    }
                    else if (!x.count(i) && y.count(j)) {
                        a[i][j] += delta;
                    }
                }
            }

            cout << "delta: " << delta << "\n\n";

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << setw(2) << a[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;



        }


        int res = 0;
        cout << "res:\n\n";

        for (int i = 0; i < n; i++) {
            cout << i + 1 << " " << mt_left[i] + 1 << endl;
            res += a_saved[i][ mt_left[i] ];
        }
        cout << endl;

        cout << res;




        


           
        return 0;
    }
