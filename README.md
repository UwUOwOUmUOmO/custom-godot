
# Godot Engine

<p align="center">
  <a href="https://godotengine.org">
    <img src="logo_outlined.svg" width="400" alt="Godot Engine logo">
  </a>
</p>

Original repository: https://github.com/godotengine/godot/tree/3.5

## Description
This is a custom build of the Godot Engine (v3.5.0) by me, cycastic (also known by my accursed handle UwUOwOUmUOmO). This repository is originally created dedicated to my unnamed RTS game, but due to various reasons, I decided to make it available publicly.
The following is a list of feature that was added to the engine, most are situated inside `modules/`, others are modified classes from `core/`:

- Advanced curve: A derived class from `Curve`, used for approximation of definite integral using Trapezoidal rule
- Daemon manager: A singleton class that is used to manage daemon processes (deprecated)
- Basic scheduler: A test class used to study the functionalities of a task scheduler (deprecated)
- File Access EPK: A planned `FileAccess` derived class, used to load encrypted `.epk` resource file
- Virtual File Access (VFA): A `FileAccess` derived class, used to load file contents from other `FileAccess` to heap allocated memory. These loaded files are now called virtual files
- Virtual File Access (Project Settings): `ProjectSettings` singleton class was modified to be able to load `.pck` files to the memory using VFA before actually reading the resource files. Through various tests, it is concluded that this provide no performance advantages whatsoever despite taking up a lot of memory
- GodotSteam: A module that contains the steam library for Godot, the original repository can be found [here](https://gramps.github.io/GodotSteam/)
- Hub: A simple singleton class used for logging
- Future: A simple asynchronous execution module. This appear to work for the time being, but various tests must be carried out before it can become stable
- Layerable Control: A `Control` (Godot term for UI component) derived class that can be used to open and close UI other layerable controls in a LIFO manner
- Node Dispatcher: A singleton used to invoke node's iteration events in parallel instead of being in sequential manner like `SceneTree`
- Scene Tree hook (Scene Tree): `SceneTree` singleton class was modified to invoke `NodeDispatcher` events each frame before any of its own iteration events can be fired off.
- Paralex: an improved asynchronous execution module that use the Godot provided `CommandQueueMT` model, but provide methods that can be called by GDscript
- Record: A simple dataclass that trivialize the serialization and deserialization of resource objects (deprecated)
- Settings Server: A singleton class that contains everything related to application settings, along with the means to apply it
- State automaton: A simple module that provide GDscript class objects with a performance way to interact with finite state machine. While being faster than most GDscript implementation (thanks to it being implemented in C++), this module in itself is not very efficient
- RTS Com: A module that provide the game that I was making with a way to manage and interact a massive game match. The match could contains dozens of squadrons, and each squadron could have up to 40 units with their own states and animation, that's why a unique and efficient way is required to handle it, and `Sentrience` (the main singleton class of this module) does just that

 ## Mô tả
Đây là một bản fork của Godot Engine bởi tôi, cycastic (aka. UwUOwOUmUOmO). Repo này ban đầu được tạo ra để sử dụng cho dự án game indie của tôi nhưng do nhiều lý do, tôi đã quyết định công khai nó.
Sau đây là các tính năng tôi đã thêm vào engine, không theo thứ tự nào cả:

- Advanced curve: lớp con của `Curve`, dùng để tính tích phân của hình cung bằng phương pháp hình thang
- Daemon manager: một lớp singleton dùng để quản lý các tiến trình nền (ngừng hỗ trợ)
- Basic scheduler: một lớp singleton tạo ra để nghiên cứu cách thức hoạt động của bộ quản lý tiến trình (ngừng hỗ trợ)
- File Access EPK: Một lớp con của `FileAccess`, dùng để đọc file tài nguyên được mã hóa `.epk`
- Virtual File Access (VFA): Một lớp con của `FileAccess`, dùng để đọc các tập tin từ các `FileAccess` khác và lưu vào trong một vùng bộ nhớ cấp phát bởi heap. Các tập tin mới này dược gọi là tập tin ảo.
- Virtual File Access (Project Settings): `ProjectSettings` đã được sửa đổi để có khả năng đọc các file tài nguyên `.pck` vào bộ nhớ làm file ảo. Theo các thử nghiệm sơ bộ, việc làm này không những không cải thiện thời gian tải tài nguyên mà còn chiếm nhiều bộ nhớ
- GodotSteam: Module giúp Godot sử dụng các tính năng của Steam. Repo gốc có thể được tìm thấy tại [đây](https://gramps.github.io/GodotSteam/)
- Hub: Một lớp singleton đơn giản dùng để log thông tin
- Future: một module đơn giản giúp Godot xử lý bất đồng bộ. Module này chưa được kiểm nghiệm kỹ càng, và đã bị thay thế bổi Paralex
- Layerable Control: Một lớp con của `Control` (thành phần giao diện trong Godot) được dùng để mở và đóng các layerable controls khác theo kiểu vào trước ra sau.
- Node Dispatcher: Một lớp singleton dùng để gọi các sự kiện lặp của Godot (`_process` và `_physics_process`) một cách song song thay vì tuần tự như `SceneTree`.
- Scene Tree hook (Scene Tree): `SceneTree` đã được sửa đổi để gọi các sự kiện lặp của `NodeDispatcher` trước khi gọi các sự kiện của chính nó mỗi frame
- Paralex: Một module thực thi bất đồng bộ được cải tiến, dựa vào `CommandQueueMT` của Godot và cung cấp các phương thức để người lập trình có thể gọi từ GDscript.
- Record: Một lớp chứa dữ liệu đơn giản để tối ưu hóa quá trình mã hóa và giải mã file tài nguyên (ngừng hỗ trợ)
- Settings Server: Một lớp singleton dùng để lưu trữ các cài đặt của ứng dụng, và các phương thức dùng để áp đặt nó
- State automaton: Một module đơn giản dùng để cung cấp cho các đối tượng GDscript cách để tương tác với máy trạng thái hữu hạn
- RTS Com: Một module dùng để quản lý trận đấu trong game của tôi làm. Một trận đấu có thể có hàng tá tiểu đội, và mỗi tiểu đội có thể có tới 40 đơn vị với các trạng thái và animation riêng của chúng, nên cần một cách nào đó để quản lý và xử lý nó một cách tối ưu và hiệu quả nhất, và `Sentrience` (một lớp singleton chính của module này) được tạo ra để giải quyết điều đó.
