# Giải thích về Code

## Tổng quan
Chương trình này triển khai thuật toán **Floyd-Warshall** để tìm đường đi ngắn nhất giữa tất cả các cặp nút trong đồ thị có hướng và có trọng số dựa vào input của người dùng. Nó cũng cung cấp chức năng tái tạo đường đi ngắn nhất giữa hai nút.

---

## Các thành phần chính

### 1. **Xử lý đầu vào (Hàm `inp`)**
- Đọc số lượng nút `n` và số lượng cạnh `m` từ đầu vào.
- Đọc `m` cạnh, mỗi cạnh được định nghĩa bởi hai nút (`x`, `y`) và một trọng số (`w`).
- Lưu các cạnh vào danh sách kề `adj`.

### 2. **Thuật toán Floyd-Warshall (Hàm `floyd_warshall`)**
- Khởi tạo hai ma trận 2D:
  - `dist[i][j]`: Lưu khoảng cách ngắn nhất từ nút `i` đến nút `j`.
  - `next[i][j]`: Lưu nút tiếp theo trên đường đi ngắn nhất từ `i` đến `j`.
- Lặp qua tất cả các cặp nút và cập nhật khoảng cách ngắn nhất bằng thuật toán Floyd-Warshall:
  - Nếu tìm thấy đường đi ngắn hơn qua một nút trung gian `k`, khoảng cách và nút tiếp theo sẽ được cập nhật.

### 3. **Tái tạo đường đi (Hàm `reconstruct_path`)**
- Tái tạo đường đi ngắn nhất giữa hai nút `u` và `v` bằng cách sử dụng ma trận `next`.
- Nếu không có đường đi, trả về một vector rỗng.

### 4. **Hàm chính**
- Đọc đầu vào đồ thị và khởi tạo các ma trận `dist` và `next`.
- Chạy thuật toán Floyd-Warshall để tính toán đường đi ngắn nhất.
- Xử lý nhiều truy vấn (`t` truy vấn) để:
  - In khoảng cách ngắn nhất giữa hai nút.
  - In đường đi được tái tạo nếu tồn tại.

---

## Quy trình ví dụ

### Đầu vào
```
5 6
1 2 3
1 3 8
2 3 2
2 4 5
3 4 1
4 5 4
2
1 4
3 5
```

### Thực thi
1. **Biểu diễn đồ thị**:
   - Các nút: 1 đến 5
   - Các cạnh: (1 → 2, 3), (1 → 3, 8), (2 → 3, 2), (2 → 4, 5), (3 → 4, 1), (4 → 5, 4)

2. **Truy vấn đường đi ngắn nhất**:
   - Truy vấn 1: Đường đi ngắn nhất từ 1 đến 4
     - Khoảng cách: 6
     - Đường đi: 1 → 2 → 3 → 4
   - Truy vấn 2: Đường đi ngắn nhất từ 3 đến 5
     - Khoảng cách: 5
     - Đường đi: 3 → 4 → 5

### Đầu ra
```
Shortest distance from 1 to 4: 6
Path: 1 2 3 4 
Shortest distance from 3 to 5: 5
Path: 3 4 5 
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
- Chương trình sử dụng `long long` (được định nghĩa là `int`) để xử lý các trọng số lớn.
- Hằng số `INF` đại diện cho trạng thái vô cực không thể đạt được.
- Macro `FOR` đơn giản hóa cú pháp vòng lặp để dễ đọc hơn.

