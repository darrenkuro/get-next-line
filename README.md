<h1 align="center">Get Next Line</h1>

<p align="center">
    <img src="https://img.shields.io/badge/license-MIT-blue?style=flat-square&logo=opensourceinitiative&logoColor=white" alt="License"/>
    <img src="https://img.shields.io/badge/status-stable-brightgreen?style=flat-square&logo=git&logoColor=white" alt="Status">
    <img src="https://img.shields.io/badge/score-125%2F100-3CB371?style=flat-square&logo=42&logoColor=white" alt="Score"/>
    <img src="https://img.shields.io/badge/date-May%2014th,%202023-ff6984?style=flat-square&logo=Cachet&logoColor=white" alt="Date"/>
</p>

> A simple function that reads and returns the next line from a file descriptor.

---

## 🚀 Overview

**Get Next Line** is one of the early projects in 42’s curriculum. It focuses on implementing a function that reads and returns a line from a file descriptor—handling partial reads, dynamic buffers, and persistent state between function calls. The project emphasizes efficient memory management, careful handling of edge cases, and a solid understanding of how low-level file I/O and buffering work in C.

## 🧰 Tech Stack: ![C](https://img.shields.io/badge/-C-A8B9CC?style=flat-square&logo=C&logoColor=black)

## 📦 Features

- **Line-by-line reading**: returns a full line, including the newline, on each call.
- **Persistent buffer**: maintains unread data between calls for each file descriptor.
- **Multiple FDs supported**: handles multiple open files simultaneously without interference.
- **Configurable buffer size**: behavior changes dynamically with `BUFFER_SIZE` defined at compile time.
- **Optimized memory management**: no leaks, no redundant allocations.

---

## 🛠️ Configuration

### Prerequisites
- Compiler: gcc or clang
- Build tool: make

### Installation & Usage
```bash
git clone https://github.com/darrenkuro/get-next-line.git && cd get-next-line
```

### Examples & Demo
```bash
clang src/get_next_line.c src/get_next_line_utils.c test/main.c -o gnl -Iinclude
```
```bash
clang src/get_next_line_bonus.c src/get_next_line_utils_bonus.c test/main_bonus.c -o gnl -Iinclude
```

---

## 📝 Notes & Lessons

- Stack might overflow for large BUFFER_SIZE, putting it on the heap would solve the problem, at cost of performance. Since timeout is likely an issue for moulinette, it would probably be the best solution.

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

## 📫 Contact

Darren Kuro – [darren0xa@gmail.com](mailto:darren0xa@gmail.com)
GitHub: [@darrenkuro](https://github.com/darrenkuro)
