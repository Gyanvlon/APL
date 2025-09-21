import java.util.*;
import java.lang.ref.WeakReference;

/**
 * Java Memory Management Analysis
 * Demonstrates garbage collection, reference types, and memory patterns
 */
public class MemoryAnalysis {
    
    // Example 1: Automatic garbage collection
    public static void garbageCollectionExample() {
        System.out.println("=== Garbage Collection Example ===");
        
        List<Integer> list = new ArrayList<>();
        for (int i = 0; i < 1000000; i++) {
            list.add(i);
        }
        System.out.println("Created large list with " + list.size() + " elements");
        
        // Suggest garbage collection (not guaranteed to run immediately)
        System.gc();
        
        // List will be automatically cleaned up when it goes out of scope
        // No explicit memory management required
    }
    
    // Example 2: Memory leaks through static references
    private static List<Object> memoryLeakExample = new ArrayList<>();
    
    public static void potentialMemoryLeak() {
        System.out.println("=== Potential Memory Leak Example ===");
        
        // Objects added to static collections won't be garbage collected
        for (int i = 0; i < 1000; i++) {
            memoryLeakExample.add(new Object());
        }
        System.out.println("Added " + memoryLeakExample.size() + " objects to static list");
        
        // These objects will persist for the lifetime of the application
        // unless explicitly removed
    }
    
    // Example 3: Weak references for cache-like behavior
    public static void weakReferenceExample() {
        System.out.println("=== Weak Reference Example ===");
        
        Object strongRef = new Object();
        WeakReference<Object> weakRef = new WeakReference<>(strongRef);
        
        System.out.println("Strong reference exists: " + (weakRef.get() != null));
        
        strongRef = null; // Remove strong reference
        System.gc(); // Suggest garbage collection
        
        // Weak reference may now return null
        System.out.println("After GC, weak reference exists: " + (weakRef.get() != null));
    }
    
    // Example 4: String interning and memory efficiency
    public static void stringInternExample() {
        System.out.println("=== String Interning Example ===");
        
        String str1 = "Hello World";
        String str2 = "Hello World";
        String str3 = new String("Hello World");
        String str4 = str3.intern();
        
        System.out.println("str1 == str2 (literal): " + (str1 == str2));
        System.out.println("str1 == str3 (new): " + (str1 == str3));
        System.out.println("str1 == str4 (interned): " + (str1 == str4));
        
        // Demonstrates JVM's string pool optimization
    }
    
    // Example 5: Try-with-resources for automatic resource management
    public static void resourceManagementExample() {
        System.out.println("=== Resource Management Example ===");
        
        // Automatic resource management with try-with-resources
        try (Scanner scanner = new Scanner("Hello World")) {
            while (scanner.hasNext()) {
                System.out.println("Token: " + scanner.next());
            }
            // Scanner is automatically closed here
        }
        
        System.out.println("Resources automatically cleaned up");
    }
    
    public static void main(String[] args) {
        System.out.println("Java Memory Management Demonstration");
        System.out.println("===================================");
        
        garbageCollectionExample();
        potentialMemoryLeak();
        weakReferenceExample();
        stringInternExample();
        resourceManagementExample();
        
        System.out.println("\nKey Features:");
        System.out.println("- Automatic garbage collection");
        System.out.println("- Simplified memory management");
        System.out.println("- Reference-based object handling");
        System.out.println("- Potential for memory leaks with static references");
        System.out.println("- JVM optimizations (string interning, etc.)");
    }
}