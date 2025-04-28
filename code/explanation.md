# Giải thích về Code

## Tổng quan
Chương trình này triển khai thuật toán **Floyd-Warshall** để tìm đường đi ngắn nhất giữa tất cả các cặp nút trong đồ thị có hướng hoặc vô hướng với trọng số. Ngoài ra, chương trình hỗ trợ:
- Tái tạo đường đi ngắn nhất.
- Xử lý các truy vấn từ người dùng.
- Phát hiện và xử lý chu trình âm.

---

## Các thành phần chính

### 1. **Xử lý đầu vào (`inp`)**
- Đọc số lượng nút (`n`), số lượng cạnh (`m`), và chế độ đồ thị (`mode`):
  - `mode = 0`: Đồ thị vô hướng.
  - `mode = 1`: Đồ thị có hướng.
- Đọc `m` cạnh, mỗi cạnh được định nghĩa bởi hai nút (`x`, `y`) và trọng số (`w`).
- Lưu các cạnh vào danh sách kề `adj`. Nếu đồ thị vô hướng (`mode == 0`), thêm cả cạnh ngược.

### 2. **Thuật toán Floyd-Warshall (`floyd_warshall`)**
- Khởi tạo hai ma trận 2D:
  - `dist[i][j]`: Lưu khoảng cách ngắn nhất từ nút `i` đến nút `j`. Giá trị ban đầu là:
    - `0` nếu `i == j`.
    - `INF` nếu không có cạnh trực tiếp giữa `i` và `j`.
  - `next[i][j]`: Lưu nút tiếp theo trên đường đi ngắn nhất từ `i` đến `j`.
- Cập nhật khoảng cách ban đầu dựa trên danh sách kề `adj`.
- Lặp qua tất cả các cặp nút và cập nhật khoảng cách ngắn nhất qua nút trung gian `k`:
  - Nếu tìm thấy đường đi ngắn hơn qua `k`, cập nhật `dist[i][j]` và `next[i][j]`.

### 3. **Tái tạo đường đi (`reconstruct_path`)**
- Tái tạo một đường đi ngắn nhất giữa hai nút `u` và `v` bằng cách sử dụng ma trận `next`.
- Nếu không có đường đi, trả về danh sách rỗng.
- Nếu `u == v`, trả về chính nút `u`.

### 4. **Hàm chính**
- Đọc đầu vào và khởi tạo các ma trận `dist` và `next`.
- Chạy thuật toán Floyd-Warshall để tính toán đường đi ngắn nhất.
- Phát hiện chu trình âm bằng cách kiểm tra `dist[i][i] < 0` cho từng nút `i`.
- Xử lý các truy vấn từ người dùng:
  - In khoảng cách ngắn nhất giữa hai nút.
  - In đường đi được tái tạo nếu tồn tại.
  - Nếu phát hiện chu trình âm, in thông báo và giá trị chu trình âm.

---

## Giải thích các dòng chính trong `run.cpp`

### 1. **Dòng 7-11: Định nghĩa macro**
```cpp
#define TEST_CASE 
#define pb push_back
#define int long long
#define FOR(i, a, b) for(auto i = a; i < b; i++)
#define io(a) if (a) freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)
```
- `TEST_CASE`: Macro để định nghĩa các trường hợp kiểm thử.
- `pb`: Macro để thêm phần tử vào vector. (push_back)
- `#define int long long`: Định nghĩa kiểu `int` là `long long` để xử lý số lớn.
- `FOR`: Macro để viết gọn vòng lặp `for`.
- `io(a)`: Macro để chuyển hướng đầu vào/đầu ra từ file nếu `a = true`.

### 2. **Dòng 13-15: Khai báo biến toàn cục**
```cpp
const int maxn = 1e5 + 1, INF = 1e18;
int n, m, mode;
vector<pair<int, int>> adj[maxn];
```
- `maxn`: Giới hạn số lượng cạnh tối đa.
- `INF`: Hằng số đại diện cho trạng thái không thể đạt được (vô cực).
- `n, m, mode`: Số lượng nút, cạnh, và chế độ đồ thị (có hướng/vô hướng).
- `adj`: Danh sách kề để lưu các cạnh của đồ thị.

### 3. **Dòng 32-41: Hàm `inp`**
```cpp
void inp(){
    cin >> n >> m >> mode;
    FOR(i, 0, m){
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].pb({y, w});
        if (mode == 0)
            adj[y].pb({x, w});
    }
}
```
- Đọc dữ liệu đầu vào từ người dùng hoặc file.
- Lưu các cạnh vào danh sách kề `adj`.
- Nếu đồ thị vô hướng (`mode == 0`), thêm cả cạnh ngược.
- Nếu có hướng, chỉ thêm cạnh từ `x` đến `y`.

### 4. **Dòng 43-73: Hàm `floyd_warshall`**
```cpp
void floyd_warshall(int n, vector<vector<int>>& dist, vector<vector<int>>& next){
    FOR(i, 1, n + 1){
        FOR(j, 1, n + 1){
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
            next[i][j] = 0;
        }
    }

    FOR(u, 1, n + 1){
        for (auto& edge : adj[u]){
            int v = edge.first, w = edge.second;
            dist[u][v] = min(dist[u][v], w);
            next[u][v] = v;
        }
    }

    FOR(k, 1, n + 1){
        FOR(i, 1, n + 1){
            FOR(j, 1, n + 1){
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }   
    
}
```
- Khởi tạo ma trận `dist` và `next`.
- Cập nhật khoảng cách ban đầu dựa trên danh sách kề.
- Sử dụng vòng lặp ba lớp để cập nhật khoảng cách ngắn nhất qua nút trung gian `k`.

### 5. **Dòng 75-87: Hàm `reconstruct_path`**
```cpp
vector<int> reconstruct_path(int u, int v, const vector<vector<int>>& next){
    vector<int> path;
    if (next[u][v] == 0){
        if (u == v) path.push_back(u);
        return path;
    }
    path.push_back(u);
    while (u != v){
        u = next[u][v];
        path.push_back(u);
    }
    return path;
}
```
- Tái tạo đường đi ngắn nhất từ `u` đến `v` bằng cách sử dụng ma trận `next`.
- Trả về danh sách các nút trên đường đi.

### 6. **Dòng 89-169: Hàm `main`**
```cpp
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    io(true);
    inp();

    vector<vector<int>> dist(n + 1, vector<int>(n + 1));
    vector<vector<int>> next(n + 1, vector<int>(n + 1));

    floyd_warshall(n, dist, next);

    vector<bool> neg_cycle(n + 1, false);
    FOR(i, 1, n + 1) {
        if (dist[i][i] < 0) {
            neg_cycle[i] = true;
        }
    }

    int t, u, v;
    // cout << "Floyd-Warshall Algorithm for " << (mode == 0 ? "undirected" : "directed") << " graph.\n";
    // cout << "Matrix of shortest distances:\n";
    // cout << setw(5) << "i\\j";
    // FOR(i, 1, n + 1)
    //     cout << setw(5) << i;
    
    FOR(i, 1, n + 1){
        // cout << endl << setw(5) << i;
        FOR(j, 1, n + 1){
            if (dist[i][j] == INF)
                cout << setw(5) <<  "INF";
            else {
                bool flag = false;
                FOR(k, 1, n + 1) {
                    if (neg_cycle[k] && dist[i][k] != INF && dist[k][j] != INF) {
                        flag = true;
                        break;
                    }
                }
                if (flag)
                    cout << setw(5) << "-INF";
                else
                    cout << setw(5) << dist[i][j];
            }
        }
        cout << endl;
    }
    cout << '\n';
    #ifdef TEST_CASE
    // cin >> t;
    t = 1;
    while (t--){
        cin >> u >> v;
        bool neg = false;
        FOR(k, 1, n + 1) {
            if (neg_cycle[k] && dist[u][k] != INF && dist[k][v] != INF) {
                neg = true;
                break;
            }
        }
        if (neg)
            // cout << "- Path from " << u << " to " << v << " is affected by a negative cycle.\n";
            cout << "-INF\n";
        else if (dist[u][v] == INF)
            // cout << "- No path from " << u << " to " << v << ".\n";
            cout << "INF\n";
        else{
            if (u == v){
                cout << u << endl;
                continue;
            }
            vector<int> path = reconstruct_path(u, v, next);
            FOR(i, 0, path.size()){
                cout << path[i] << " ";
            }
            cout << endl;
        }
    }
    #endif

    return 0;
}
```
- Đọc dữ liệu đầu vào và khởi tạo các ma trận `dist` và `next`.
- Chạy thuật toán Floyd-Warshall.
- Phát hiện chu trình âm bằng cách kiểm tra `dist[i][i] < 0`.
- In ma trận khoảng cách ngắn nhất.
- Xử lý các truy vấn:
  - Nếu có chu trình âm, in `-INF`.
  - Nếu không có đường đi, in `INF`.
  - Nếu có đường đi, in khoảng cách và đường đi ngắn nhất.

---

## Quy trình ví dụ

### Đầu vào
Dữ liệu đầu vào từ file `input.txt`:
```
10 14 1
5 1 4
5 2 2
1 3 5
2 1 -1
2 3 4
3 6 2
4 6 -3
6 7 1
7 2 5
8 9 -5
9 10 -6
10 8 3
9 3 11
5 8 6
2 6
```

### Phân tích
1. **Biểu diễn đồ thị**:
   - Số nút: 10
   - Số cạnh: 14
   - Đồ thị có hướng (`mode = 1`).
   - Các cạnh:
     - (5 → 1, 4), (5 → 2, 2), (1 → 3, 5), (2 → 1, -1), (2 → 3, 4)
     - (3 → 6, 2), (4 → 6, -3), (6 → 7, 1), (7 → 2, 5), (8 → 9, -5)
     - (9 → 10, -6), (10 → 8, 3), (9 → 3, 11), (5 → 8, 6).

2. **Ma trận khoảng cách ban đầu**:
   - Các cạnh trực tiếp được khởi tạo với trọng số tương ứng.
   - Các nút không kết nối trực tiếp được gán giá trị `INF`.
   - Đường đi từ một nút đến chính nó được gán giá trị `0`.

3. **Truy vấn**:
   - Truy vấn: Tìm đường đi ngắn nhất từ nút `2` đến nút `6`.
     - Khoảng cách: `6`.
     - Đường đi: `2 → 3 → 6`.

### Đầu ra
Dữ liệu đầu ra từ file `output.txt`:
```
0   13    5  INF  INF    7    8  INF  INF  INF
   -1    0    4  INF  INF    6    7  INF  INF  INF
    7    8    0  INF  INF    2    3  INF  INF  INF
    2    3    7    0  INF   -3   -2  INF  INF  INF
 -INF -INF -INF  INF    0 -INF -INF -INF -INF -INF
    5    6   10  INF  INF    0    1  INF  INF  INF
    4    5    9  INF  INF   11    0  INF  INF  INF
 -INF -INF -INF  INF  INF -INF -INF -INF -INF -INF
 -INF -INF -INF  INF  INF -INF -INF -INF -INF -INF
 -INF -INF -INF  INF  INF -INF -INF -INF -INF -INF

2 3 6
```

---

## Độ phức tạp

### Độ phức tạp thời gian
- **Khởi tạo**: \(O(n^2)\)
- **Thuật toán Floyd-Warshall**: \(O(n^3)\)
- **Tái tạo đường đi**: \(O(n)\) cho mỗi truy vấn

### Độ phức tạp không gian
- Danh sách kề: \(O(m)\)
- Ma trận khoảng cách và ma trận `next`: \(O(n^2)\)

---

## Ghi chú
- Chương trình hỗ trợ cả đồ thị có hướng và vô hướng.
- Chu trình âm được phát hiện và xử lý để đảm bảo kết quả chính xác.
- Hằng số `INF` đại diện cho trạng thái không thể đạt được.
- Ký hiệu `-INF` đại diện cho đường đi bị ảnh hưởng bởi ít nhất một chu trình âm.
- Các truy vấn được xử lý tuần tự để in kết quả.
- Nếu có nhiều đường đi ngắn nhất, việc truy vết sẽ in ra kết quả có chỉ số nhỏ nhất. (Xem [run_alt.cpp](\alt\run_alt.cpp))
