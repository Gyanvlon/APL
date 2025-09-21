#include <iostream>
#include <vector>
#include <memory>
#include <string>

/**
 * C++ Memory Management Analysis
 * Demonstrates manual memory management, RAII, and smart pointers
 */

// Example 1: Manual memory management (traditional C++ approach)
void manualMemoryManagement() {
    std::cout << "=== Manual Memory Management Example ===" << std::endl;
    
    // Heap allocation - programmer responsible for deallocation
    std::vector<int>* vec = new std::vector<int>();
    vec->push_back(1);
    vec->push_back(2);
    vec->push_back(3);
    
    std::cout << "Vector contents: ";
    for (int i : *vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Must explicitly delete to avoid memory leak
    delete vec;
    // vec is now a dangling pointer - using it would be undefined behavior
}

// Example 2: RAII (Resource Acquisition Is Initialization)
void raiiExample() {
    std::cout << "=== RAII Example ===" << std::endl;
    
    {
        // Stack allocation - automatic cleanup
        std::vector<int> vec = {1, 2, 3, 4, 5};
        std::cout << "Stack vector size: " << vec.size() << std::endl;
        
        // vec is automatically destroyed when going out of scope
    } // <-- vec destructor called here automatically
    
    std::cout << "Stack vector automatically cleaned up" << std::endl;
}

// Example 3: Smart pointers (Modern C++)
void smartPointerExample() {
    std::cout << "=== Smart Pointer Example ===" << std::endl;
    
    // unique_ptr - exclusive ownership
    {
        std::unique_ptr<std::vector<int>> unique_vec = 
            std::make_unique<std::vector<int>>();
        unique_vec->push_back(10);
        unique_vec->push_back(20);
        
        std::cout << "Unique ptr vector size: " << unique_vec->size() << std::endl;
        // Automatically cleaned up when unique_ptr goes out of scope
    }
    
    // shared_ptr - shared ownership with reference counting
    std::shared_ptr<std::string> shared_str = 
        std::make_shared<std::string>("Shared string");
    
    {
        std::shared_ptr<std::string> another_ref = shared_str;
        std::cout << "Reference count: " << shared_str.use_count() << std::endl;
        std::cout << "Shared string: " << *another_ref << std::endl;
    } // another_ref goes out of scope, reference count decreases
    
    std::cout << "Reference count after scope: " << shared_str.use_count() << std::endl;
}

// Example 4: Memory leak demonstration
void memoryLeakExample() {
    std::cout << "=== Memory Leak Example (Don't do this!) ===" << std::endl;
    
    for (int i = 0; i < 5; i++) {
        int* leaked_memory = new int(i);
        std::cout << "Allocated int with value: " << *leaked_memory << std::endl;
        // Missing delete - this creates a memory leak!
        // delete leaked_memory; // <-- This line should be here
    }
    
    std::cout << "Created memory leaks (5 integers not freed)" << std::endl;
}

// Example 5: Exception safety and RAII
class Resource {
public:
    Resource(const std::string& name) : name_(name) {
        std::cout << "Resource '" << name_ << "' acquired" << std::endl;
    }
    
    ~Resource() {
        std::cout << "Resource '" << name_ << "' released" << std::endl;
    }
    
private:
    std::string name_;
};

void exceptionSafetyExample() {
    std::cout << "=== Exception Safety Example ===" << std::endl;
    
    try {
        Resource res1("Database Connection");
        Resource res2("File Handle");
        
        // Even if an exception is thrown here, destructors will be called
        // throw std::runtime_error("Something went wrong!");
        
        std::cout << "Operations completed successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    // res1 and res2 destructors called automatically
}

int main() {
    std::cout << "C++ Memory Management Demonstration" << std::endl;
    std::cout << "===================================" << std::endl;
    
    manualMemoryManagement();
    std::cout << std::endl;
    
    raiiExample();
    std::cout << std::endl;
    
    smartPointerExample();
    std::cout << std::endl;
    
    memoryLeakExample();
    std::cout << std::endl;
    
    exceptionSafetyExample();
    
    std::cout << "\nKey Features:" << std::endl;
    std::cout << "- Manual memory management (new/delete)" << std::endl;
    std::cout << "- RAII for automatic resource management" << std::endl;
    std::cout << "- Smart pointers for safer memory handling" << std::endl;
    std::cout << "- Deterministic destruction" << std::endl;
    std::cout << "- Potential for memory leaks and dangling pointers" << std::endl;
    std::cout << "- Zero-overhead principle" << std::endl;
    
    return 0;
}