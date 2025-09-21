// Rust Memory Management Analysis
// Demonstrates ownership, borrowing, and RAII principles

use std::rc::Rc;
use std::cell::RefCell;

// Example 1: Stack allocation and ownership
fn ownership_example() {
    println!("=== Ownership Example ===");
    let mut vec = Vec::new();  // Vec allocated on heap, but ownership is clear
    vec.push(1);
    vec.push(2);
    
    let vec_ref = &vec;  // Borrowing - no ownership transfer
    println!("Vector: {:?}", vec_ref);
    
    // vec goes out of scope and is automatically dropped (RAII)
}

// Example 2: Memory safety through borrowing rules
fn borrowing_example() {
    println!("=== Borrowing Example ===");
    let mut data = vec![1, 2, 3, 4, 5];
    
    // Multiple immutable borrows are allowed
    let slice1 = &data[0..2];
    let slice2 = &data[2..4];
    println!("Slice1: {:?}, Slice2: {:?}", slice1, slice2);
    
    // But mutable and immutable borrows cannot coexist
    // let slice3 = &data[1..3];  // This would be fine
    // data.push(6);  // This would cause a compile error if slice3 existed
    
    data.push(6);  // Safe now that immutable borrows are done
    println!("Modified data: {:?}", data);
}

// Example 3: Reference counting for shared ownership
fn shared_ownership_example() {
    println!("=== Shared Ownership Example ===");
    let shared_data = Rc::new(RefCell::new(vec![1, 2, 3]));
    
    let clone1 = Rc::clone(&shared_data);
    let clone2 = Rc::clone(&shared_data);
    
    // Modify through RefCell for interior mutability
    shared_data.borrow_mut().push(4);
    clone1.borrow_mut().push(5);
    
    println!("Shared data: {:?}", clone2.borrow());
    println!("Reference count: {}", Rc::strong_count(&shared_data));
}

// Example 4: Zero-cost abstractions
fn zero_cost_abstractions() {
    println!("=== Zero-Cost Abstractions ===");
    let numbers = vec![1, 2, 3, 4, 5];
    
    // This iterator chain compiles to very efficient code
    let sum: i32 = numbers
        .iter()
        .filter(|&&x| x % 2 == 0)
        .map(|&x| x * x)
        .sum();
    
    println!("Sum of squares of even numbers: {}", sum);
}

fn main() {
    println!("Rust Memory Management Demonstration");
    println!("====================================");
    
    ownership_example();
    borrowing_example();
    shared_ownership_example();
    zero_cost_abstractions();
    
    println!("\nKey Features:");
    println!("- Compile-time memory safety");
    println!("- Zero-cost abstractions");
    println!("- No garbage collector");
    println!("- Ownership system prevents data races");
}