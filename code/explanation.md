# Giải thích về Code

## Tổng quan
Chương trình này triển khai thuật toán **Floyd-Warshall** để tìm đường đi ngắn nhất giữa tất cả các cặp nút trong đồ thị có hướng hoặc vô hướng với trọng số. Ngoài ra, chương trình hỗ trợ:
- Tái tạo đường đi ngắn nhất.
- Xử lý các truy vấn từ người dùng.
- In tất cả các đường đi ngắn nhất nếu có nhiều đường đi.

---

## Các thành phần chính

### 1. **Xử lý đầu vào (`inp`)**
- Đọc số lượng nút (`n`), số lượng cạnh (`m`), và chế độ đồ thị (`mode`):
  - `mode = 0`: Đồ thị vô hướng.
  - `mode = 1`: Đồ thị có hướng.
- Đọc `m` cạnh, mỗi cạnh được định nghĩa bởi hai nút (`x`, `y`) và trọng số (`w`).
- Lưu các cạnh vào danh sách kề `adj`. Nếu đồ thị vô hướng (`mode == 0`), thêm cả cạnh ngược.

### 2. **Thuật toán Floyd-Warshall (`floyd_warshall`)**
- Khởi tạo ba cấu trúc dữ liệu:
  - `dist[i][j]`: Lưu khoảng cách ngắn nhất từ nút `i` đến nút `j`. Giá trị ban đầu là:
    - `0` nếu `i == j`.
    - `INF` nếu không có cạnh trực tiếp giữa `i` và `j`.
  - `next[i][j]`: Lưu nút tiếp theo trên đường đi ngắn nhất từ `i` đến `j`.
  - `all_paths[i][j]`: Lưu tất cả các đường đi ngắn nhất từ `i` đến `j`.
- Cập nhật khoảng cách ban đầu dựa trên danh sách kề `adj`.
- Lặp qua tất cả các cặp nút và cập nhật khoảng cách ngắn nhất qua nút trung gian `k`:
  - Nếu tìm thấy đường đi ngắn hơn qua `k`, cập nhật `dist[i][j]`, `next[i][j]`, và `all_paths[i][j]`.
  - Nếu có nhiều đường đi ngắn nhất, thêm tất cả các đường đi vào `all_paths[i][j]`.

### 3. **Tái tạo đường đi (`reconstruct_path`)**
- Tái tạo một đường đi ngắn nhất giữa hai nút `u` và `v` bằng cách sử dụng ma trận `next`.
- Nếu không có đường đi, trả về danh sách rỗng.
- Nếu `u == v`, trả về chính nút `u`.

### 4. **In tất cả các đường đi ngắn nhất (`print_all_paths`)**
- Sử dụng cấu trúc `all_paths[i][j]` để in tất cả các đường đi ngắn nhất từ `i` đến `j`.

### 5. **Hàm chính**
- Đọc đầu vào và khởi tạo các ma trận `dist`, `next`, và `all_paths`.
- Chạy thuật toán Floyd-Warshall để tính toán đường đi ngắn nhất.
- Xử lý các truy vấn từ người dùng:
  - Nếu có nhiều đường đi ngắn nhất, in tất cả các đường đi bằng `print_all_paths`.
  - Nếu chỉ có một đường đi, in đường đi đó bằng `reconstruct_path`.
  - Nếu phát hiện chu trình âm, in thông báo và giá trị chu trình âm.

---

## Quy trình ví dụ

### Đầu vào
Dữ liệu đầu vào từ file `input_alt.txt`:
```
8 10 1
1 2 1
1 3 1
2 4 1
2 7 1
3 4 1
4 5 1
6 5 1
6 7 1
7 5 1
7 8 1
1 5
```

### Phân tích
1. **Biểu diễn đồ thị**:
   - Số nút: 8
   - Số cạnh: 10
   - Đồ thị có hướng (`mode = 1`).
   - Các cạnh:
     - (1 → 2, 1), (1 → 3, 1), (2 → 4, 1), (2 → 7, 1), (3 → 4, 1)
     - (4 → 5, 1), (6 → 5, 1), (6 → 7, 1), (7 → 5, 1), (7 → 8, 1).

2. **Ma trận khoảng cách ban đầu**:
   - Các cạnh trực tiếp được khởi tạo với trọng số tương ứng.
   - Các nút không kết nối trực tiếp được gán giá trị `INF`.
   - Đường đi từ một nút đến chính nó được gán giá trị `0`.

3. **Truy vấn**:
   - Truy vấn: Tìm đường đi ngắn nhất từ nút `1` đến nút `5`.
     - Khoảng cách: `3`.
     - Các đường đi:
       - `1 → 2 → 4 → 5`
       - `1 → 2 → 7 → 5`
       - `1 → 3 → 4 → 5`.

### Đầu ra
Dữ liệu đầu ra từ file `output_alt.txt`:
```
0    1    1    2    3  INF    2    3
  INF    0  INF    1    2  INF    1    2
  INF  INF    0    1    2  INF  INF  INF
  INF  INF  INF    0    1  INF  INF  INF
  INF  INF  INF  INF    0  INF  INF  INF
  INF  INF  INF  INF    1    0    1    2
  INF  INF  INF  INF    1  INF    0    1
  INF  INF  INF  INF  INF  INF  INF    0

1 2 4 5 
1 2 7 5 
1 3 4 5
```

---

## Độ phức tạp

### Độ phức tạp thời gian
- **Khởi tạo**: \(O(n^2)\)
- **Thuật toán Floyd-Warshall**: \(O(n^3)\)
- **Tái tạo đường đi**: \(O(n)\) cho mỗi truy vấn
- **In tất cả các đường đi**: \(O(k)\), với \(k\) là số lượng đường đi ngắn nhất.

### Độ phức tạp không gian
- Danh sách kề: \(O(m)\)
- Ma trận khoảng cách, ma trận `next`, và ma trận `all_paths`: \(O(n^2)\)

---

## Ghi chú
- Chương trình hỗ trợ cả đồ thị có hướng và vô hướng.
- Chu trình âm được phát hiện và xử lý để đảm bảo kết quả chính xác.
- Hằng số `INF` đại diện cho trạng thái không thể đạt được.
- Ký hiệu `-INF` đại diện cho đường đi bị ảnh hưởng bởi ít nhất một chu trình âm.
- Các truy vấn được xử lý tuần tự để in kết quả.
