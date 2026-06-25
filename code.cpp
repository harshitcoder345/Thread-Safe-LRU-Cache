#include <iostream>
#include <unordered_map>
#include <list>
#include <mutex>

using namespace std;

class ThreadSafeLRUCache {
private:
    int capacity;
    
    // List stores pairs of {Key, Value}
    // Most recently used elements stay at the front, least recently used at the back
    list<pair<int, int>> cacheList;
    
    // Map stores: Key -> Iterator pointing to the node in cacheList
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;
    
    // Mutex to ensure mutual exclusion across multiple threads
    mutex mtx;

public:
    // Constructor to initialize the cache capacity
    ThreadSafeLRUCache(int cap) {
        capacity = cap;
    }

    // Fetches the value for a given key. Returns -1 if not found.
    int get(int key) {
        // Automatically locks the mutex on entry and unlocks on exit
        lock_guard<mutex> lock(mtx); 
        
        // If the key does not exist in the cache
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }

        // If the key exists, move it to the front of the list (Most Recently Used)
        auto it = cacheMap[key];
        int value = it->second;

        cacheList.erase(it);
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin(); // Update map with the new node position

        return value;
    }

    // Inserts or updates a key-value pair in the cache
    void put(int key, int value) {
        lock_guard<mutex> lock(mtx); 

        // Case 1: Key already exists, remove the old entry from the list
        if (cacheMap.find(key) != cacheMap.end()) {
            auto it = cacheMap[key];
            cacheList.erase(it);
        } 
        // Case 2: Cache is full, evict the Least Recently Used (back element)
        else if (cacheList.size() == capacity) {
            auto lruItem = cacheList.back();
            cacheMap.erase(lruItem.first);   // Remove from map
            cacheList.pop_back();            // Remove from list
            cout << "[Evicted] Cache full! Removed Key: " << lruItem.first << endl;
        }

        // Insert the new element at the front of the list
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin(); // Map tracking the new position
    }

    // Helper function to print the current state of the cache
    void display() {
        lock_guard<mutex> lock(mtx); 
        cout << "Cache State (MRU -> LRU): ";
        for (auto const& item : cacheList) {
            cout << "[" << item.first << ":" << item.second << "] ";
        }
        cout << "\n----------------------------------------" << endl;
    }
};

int main() {
    int cap;
    cout << "Enter Cache Capacity: ";
    cin >> cap;

    ThreadSafeLRUCache cache(cap);
    int choice, key, value;

    while (true) {
        cout << "\n1. Put (Insert/Update)\n2. Get (Fetch)\n3. Exit\nChoose option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Key and Value: ";
            cin >> key >> value;
            cache.put(key, value);
            cache.display();
        } else if (choice == 2) {
            cout << "Enter Key: ";
            cin >> key;
            int res = cache.get(key);
            if (res == -1) cout << "Key not found!" << endl;
            else cout << "Fetched Value: " << res << endl;
            cache.display();
        } else {
            cout << "Exiting Simulator..." << endl;
            break;
        }
    }
    return 0;
}