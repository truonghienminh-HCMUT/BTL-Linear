# Giải thích về Code

## Tổng quan
Chương trình này triển khai thuật toán **Floyd-Warshall** để tìm đường đi ngắn nhất giữa tất cả các cặp nút trong đồ thị có hướng hoặc vô hướng với trọng số. Ngoài ra, chương trình còn hỗ trợ tái tạo đường đi ngắn nhất và xử lý các truy vấn từ người dùng.

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
- Tái tạo đường đi ngắn nhất giữa hai nút `u` và `v` bằng cách sử dụng ma trận `next`.
- Nếu không có đường đi, trả về danh sách rỗng.
- Nếu `u == v`, trả về chính nút `u`.

### 4. **Hàm chính**
- Đọc đầu vào và khởi tạo các ma trận `dist` và `next`.
- Chạy thuật toán Floyd-Warshall để tính toán đường đi ngắn nhất.
- Xử lý các truy vấn từ người dùng:
  - In khoảng cách ngắn nhất giữa hai nút.
  - In đường đi được tái tạo nếu tồn tại.
  - Nếu phát hiện chu trình âm, in thông báo và giá trị chu trình âm.

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
2
5 5
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
     - (9 → 10, -6), (10 → 8, 3), (9 → 3, 11), (5 → 8, 6)

2. **Ma trận khoảng cách ban đầu**:
   - Các cạnh trực tiếp được khởi tạo với trọng số tương ứng.
   - Các nút không kết nối trực tiếp được gán giá trị `INF`.
   - Đường đi từ một nút đến chính nó được gán giá trị `0`.

3. **Truy vấn**:
   - Truy vấn 1: Tìm đường đi ngắn nhất từ nút `5` đến nút `5`.
     - Khoảng cách: `0`.
     - Đường đi: `5`.
   - Truy vấn 2: Tìm đường đi ngắn nhất từ nút `2` đến nút `6`.
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

5
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
