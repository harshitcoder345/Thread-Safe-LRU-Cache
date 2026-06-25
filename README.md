# Thread-Safe LRU Cache Simulator

A high-performance, industry-grade implementation of a **Least Recently Used (LRU) Cache** in C++. This project upgrades the standard LeetCode algorithm into a multi-threaded system capable of handling concurrent operations safely without data corruption.

---

##  Key Features

* **$O(1)$ Time Complexity:** Achieves constant time efficiency for both `PUT` (insertion/update) and `GET` (retrieval) operations.
* **Thread-Safety (Concurrency):** Integrated `std::mutex` and `std::lock_guard` to prevent race conditions during multi-threaded access.
* **Smart Eviction Policy:** Automatically identifies and evicts the least recently used elements when the cache reaches its maximum capacity.
* **Interactive CLI Simulator:** Includes a user-friendly command-line interface to test live operations and witness cache evictions in real-time.

---

##  Tech Stack & Concepts Used

* **Language:** C++ (C++11 standard or higher)
* **Data Structures:** Doubly Linked List (`std::list`), Hash Map (`std::unordered_map`)
* **Concurrency:** Multi-threading, Mutex Locking (`<mutex>`)

---

##  How to Run Locally

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git](https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git)
   cd thread-safe-LRU
