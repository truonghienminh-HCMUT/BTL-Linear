# Giải thích về Code

## Tổng quan
Chương trình này triển khai thuật toán **Floyd-Warshall** để tìm đường đi ngắn nhất giữa tất cả các cặp nút trong đồ thị có hướng và có trọng số. Nó cũng cung cấp chức năng tái tạo đường đi ngắn nhất giữa hai nút dựa trên input của người dùng.

---

## Các thành phần chính

### 1. **Xử lý đầu vào (Hàm `inp`)**
- Đọc số lượng nút `n` và số lượng cạnh `m` từ đầu vào.
- Đọc `m` cạnh, mỗi cạnh được định nghĩa bởi hai nút (`u`, `v`) và một trọng số (`w`).
- Lưu các cạnh vào ma trận trọng số `graph`.

### 2. **Thuật toán Floyd-Warshall (Hàm `floyd_warshall`)**
- Khởi tạo hai ma trận 2D:
  - `dist[i][j]`: Lưu khoảng cách ngắn nhất từ nút `i` đến nút `j`.
  - `next[i][j]`: Lưu nút tiếp theo trên đường đi ngắn nhất từ `i` đến `j`.
- Lặp qua tất cả các cặp nút và cập nhật khoảng cách ngắn nhất bằng thuật toán Floyd-Warshall:
  - Nếu tìm thấy đường đi ngắn hơn qua một nút trung gian `k`, cập nhật khoảng cách và nút tiếp theo.
  - Xử lý chu trình âm nếu tồn tại.

### 3. **Tái tạo đường đi (Hàm `get_path`)**
- Tái tạo đường đi ngắn nhất giữa hai nút `u` và `v` bằng cách sử dụng ma trận `next`.
- Nếu không có đường đi, trả về một danh sách rỗng.

### 4. **Hàm chính**
- Đọc đầu vào đồ thị và khởi tạo các ma trận `dist` và `next`.
- Chạy thuật toán Floyd-Warshall để tính toán đường đi ngắn nhất.
- Xử lý các truy vấn để:
  - In khoảng cách ngắn nhất giữa hai nút.
  - In đường đi được tái tạo nếu tồn tại.

---

## Quy trình ví dụ

### Đầu vào
```
4 4
1 2 5
2 3 3
3 4 1
4 1 8
2
1 3
4 2
```

### Thực thi
1. **Biểu diễn đồ thị**:
   - Các nút: 1 đến 4
   - Các cạnh: (1 → 2, 5), (2 → 3, 3), (3 → 4, 1), (4 → 1, 8)

2. **Truy vấn đường đi ngắn nhất**:
   - Truy vấn 1: Đường đi ngắn nhất từ 1 đến 3
     - Khoảng cách: 8
     - Đường đi: 1 → 2 → 3
   - Truy vấn 2: Đường đi ngắn nhất từ 4 đến 2
     - Khoảng cách: 13
     - Đường đi: 4 → 1 → 2

### Đầu ra
```
Shortest distance from 1 to 3: 8
Path: 1 2 3
Shortest distance from 4 to 2: 13
Path: 4 1 2
```

---

## Độ phức tạp

### Độ phức tạp thời gian
- **Khởi tạo**: \(O(n^2)\)
- **Thuật toán Floyd-Warshall**: \(O(n^3)\)
- **Tái tạo đường đi**: \(O(n)\) cho mỗi truy vấn

### Độ phức tạp không gian
- Ma trận trọng số: \(O(n^2)\)
- Ma trận khoảng cách và ma trận `next`: \(O(n^2)\)

---

## Ghi chú
- Chương trình sử dụng `int` để xử lý các trọng số.
- Hằng số `INF` đại diện cho trạng thái vô cực không thể đạt được.
- Các truy vấn được xử lý tuần tự để in kết quả.
- Đảm bảo rằng đồ thị không chứa chu trình âm trước khi thực hiện truy vấn.
