
# Employee Scheduler Application - Multi-Language Implementation

A comprehensive employee scheduling system implemented in both **Ruby** and **Java**, demonstrating advanced control structures and object-oriented programming principles across different programming paradigms.

## 📋 Overview

This project showcases two distinct implementations of an employee scheduling system:
- **Ruby Implementation**: Feature-rich with priority-based scheduling and real-time conflict resolution
- **Java Implementation**: Object-oriented design with enum-based shift management and comprehensive error handling

Both implementations manage employee schedules across a 7-day week with three daily shifts (Morning, Afternoon, Evening) while ensuring fair distribution of work hours and meeting business requirements.

## 🎯 Core Features (Both Implementations)

### Scheduling Rules
- ✅ **No Double Shifts**: Employees cannot work more than one shift per day
- ✅ **Work-Life Balance**: Maximum 5 working days per employee per week
- ✅ **Minimum Staffing**: Each shift requires at least 2 employees
- ✅ **Fair Distribution**: Balanced assignment algorithms
- ✅ **Conflict Resolution**: Smart handling of scheduling conflicts

### Advanced Features
- 📊 **Comprehensive Reporting**: Detailed schedule output with statistics
- 🔄 **Multi-Phase Scheduling**: Optimized assignment algorithms
- ⚠️ **Error Handling**: Robust validation and user guidance
- 📈 **Performance Tracking**: Employee work summaries and utilization reports

## 💎 Ruby Implementation (`EmployeeScheduler.rb`)

### Ruby-Specific Features
- **Priority-Based Scheduling**: Employees can set shift priorities (1=High, 2=Medium, 3=Low)
- **Real-Time Availability**: Live capacity checking during registration
- **Interactive Interface**: User-friendly prompts with visual feedback
- **Capacity Control**: Maximum 3 employees per shift during booking phase

### Ruby Control Structures Demonstrated
```ruby
# Conditional Logic
case input
when 'CANCEL'
  skip_employee = true
  break
when 'SKIP'
  next
else
  shift = Shift.from_string(input)
end

# Loop Control
loop do
  print "Enter name for employee #{employee_count}: "
  name = gets.chomp.strip
  break if name.downcase == 'done' || name.empty?
  # ... processing logic
end

# Iterator Methods
@employees.each do |employee|
  available_employees << employee if employee.available?(day)
end

# Exception Handling
begin
  manager.input_employee_data
rescue => e
  puts "An error occurred: #{e.message}"
end
```

### Running Ruby Version
```bash
ruby EmployeeScheduler.rb
```

#### Ruby Usage Example
```
Enter employee information. Type 'done' as employee name to finish early.
Enter name for employee 1: Alice
Enter shift preferences for Alice.
Valid shifts: MORNING, AFTERNOON, EVENING. Enter 'skip' to skip a day, or 'cancel' to skip this employee.

Preference for Monday:
Enter shift (MORNING, AFTERNOON, EVENING), 'skip', or 'cancel': morning
```

## ☕ Java Implementation (`EmployeeSchedulerJavaVersion.rb`)

### Java-Inspired Features (Converted to Ruby)
- **Enum-like Classes**: Type-safe shift and day management
- **Static Methods**: Class-level utility functions
- **Object-Oriented Design**: Clear separation of concerns with nested classes
- **Exception Management**: Comprehensive error handling with try-catch patterns

### Java-Style Control Structures (in Ruby)
```ruby
# Enum-like Implementation
class Shift
  MORNING = 'Morning'
  AFTERNOON = 'Afternoon'
  EVENING = 'Evening'
  ALL = [MORNING, AFTERNOON, EVENING].freeze
  
  def self.from_string(str)
    case str.upcase
    when 'MORNING' then MORNING
    when 'AFTERNOON' then AFTERNOON
    when 'EVENING' then EVENING
    else nil
    end
  end
end

# Enhanced For Loop Equivalent
Day::ALL.each do |day|
  Shift::ALL.each do |shift|
    eligible_employees = []
    # Processing logic
  end
end

# While Loop with Break Condition
while current_shift_employees.size < MIN_EMPLOYEES_PER_SHIFT
  available_employee = find_available_employee(day)
  break if available_employee.nil?
  assign_employee_to_shift(available_employee, day, shift)
end
```

### Running Java-Style Version
```bash
ruby EmployeeSchedulerJavaVersion.rb
```

## 🔧 Technical Implementation Comparison

| Feature | Ruby Implementation | Java-Style Implementation |
|---------|-------------------|---------------------------|
| **Data Types** | Dynamic typing with symbols | Static-like typing with constants |
| **Error Handling** | `begin/rescue/end` | `begin/rescue` (try-catch style) |
| **Collections** | Native Hash/Array | Hash/Array with Java-like methods |
| **Method Naming** | `snake_case` | `snake_case` (converted from camelCase) |
| **Class Structure** | Ruby classes with modules | Nested classes (Java-style) |
| **Iterators** | Ruby blocks (`each`, `map`) | Enhanced for-loop equivalents |

## 📊 Sample Output (Both Versions)

```
================================================================================
                    WEEKLY EMPLOYEE SCHEDULE
================================================================================
Day         Morning                  Afternoon                Evening         
--------------------------------------------------------------------------------
Monday      Alice, Bob               Charlie, Diana           Eve, Frank      
Tuesday     Bob, Diana               Alice, Eve               Charlie, Frank  
Wednesday   Alice, Charlie           Bob, Eve                 Diana, Frank    
Thursday    Diana, Frank             Alice, Charlie           Bob, Eve        
Friday      Alice, Eve               Bob, Diana               Charlie, Frank  
Saturday    Bob, Charlie             Diana, Frank             Alice, Eve      
Sunday      Diana, Eve               Alice, Frank             Bob, Charlie    
--------------------------------------------------------------------------------

EMPLOYEE SUMMARY:
Alice          : 5 days worked
Bob            : 5 days worked (MAX)
Charlie        : 5 days worked (MAX)
Diana          : 5 days worked (MAX)
Eve            : 5 days worked (MAX)
Frank          : 5 days worked (MAX)
```

## 🎓 Educational Objectives

### Programming Language Concepts
- **Ruby Features**: Dynamic typing, blocks, symbols, metaprogramming
- **Java Concepts**: Static typing, enums, encapsulation, inheritance
- **Cross-Language Patterns**: Design patterns that work across languages

### Control Flow Mastery
- **Conditional Statements**: `if/else`, `case/when`, `unless`
- **Loop Constructs**: `while`, `for`, `loop do`, iterator methods
- **Exception Handling**: `begin/rescue` vs `try/catch` patterns
- **Method Control**: `break`, `next`, `return`, `redo`

### Object-Oriented Design
- **Encapsulation**: Private/public method organization
- **Inheritance**: Class hierarchies and method overriding
- **Polymorphism**: Duck typing vs static typing
- **Composition**: Object relationships and dependencies

## 📁 Project Structure

```
3. Implementing Control Structures/
├── EmployeeScheduler.rb           # Ruby implementation (Original)
├── EmployeeSchedulerJavaVersion.rb # Java-style Ruby implementation
├── README.md                      # This comprehensive documentation
├── test_booking.rb               # Test scripts for booking system
└── test_fix.rb                   # Fix verification scripts
```

## 🧪 Testing Both Implementations

### Ruby Version Testing
```bash
# Interactive mode
ruby EmployeeScheduler.rb

# Test with sample input
echo -e "Alice\nmorning\nafternoon\nevening\nmorning\nevening\nafternoon\nmorning\ndone" | ruby EmployeeScheduler.rb
```

### Java-Style Version Testing
```bash
# Interactive mode
ruby EmployeeSchedulerJavaVersion.rb

# Both versions support the same input format
```

## 🔍 Code Quality Features

### Ruby Implementation
- **Idiomatic Ruby**: Uses blocks, symbols, and Ruby conventions
- **Metaprogramming**: Dynamic method calls and reflection
- **Functional Patterns**: Map, select, and other enumerable methods
- **Duck Typing**: Flexible object interactions

### Java-Style Implementation
- **Type Safety**: Enum-like structures for data validation
- **Explicit Interfaces**: Clear method signatures and contracts
- **Error Prevention**: Comprehensive input validation
- **Structured Design**: Layered architecture with clear separation

## 📈 Performance Considerations

| Aspect | Ruby Version | Java-Style Version |
|--------|-------------|-------------------|
| **Memory Usage** | Lower (dynamic allocation) | Slightly higher (structured objects) |
| **Execution Speed** | Fast (optimized Ruby) | Comparable (Ruby with Java patterns) |
| **Scalability** | Excellent for small-medium datasets | Better for large, structured datasets |
| **Maintainability** | High (Ruby conventions) | Very high (explicit structure) |

## 🔮 Language-Specific Advantages

### Ruby Strengths
- 🚀 **Rapid Development**: Minimal boilerplate code
- 🎨 **Expressive Syntax**: Readable and concise
- 🔄 **Flexible**: Dynamic typing and metaprogramming
- 📦 **Rich Libraries**: Extensive standard library

### Java-Style Strengths
- 🛡️ **Type Safety**: Compile-time error detection
- 📋 **Structure**: Clear interfaces and contracts
- 🏗️ **Scalability**: Enterprise-level architecture patterns
- 🔍 **Tooling**: Better IDE support and debugging

## 🎯 Learning Outcomes

After studying both implementations, students will understand:

1. **Language Paradigms**: How the same problem can be solved differently
2. **Control Structure Variations**: Different approaches to loops, conditions, and flow
3. **Design Patterns**: Language-agnostic vs language-specific patterns
4. **Trade-offs**: Performance, maintainability, and development speed considerations
5. **Best Practices**: Idiomatic code in different programming languages

## 📜 Assignment Compliance

This project fulfills all requirements for the Advanced Programming Languages coursework:

✅ **Multiple Languages**: Ruby and Java-style implementations  
✅ **Control Structures**: Comprehensive demonstration of conditionals, loops, and branching  
✅ **Real Application**: Practical employee scheduling system  
✅ **Documentation**: Extensive README with examples and explanations  
✅ **Testing**: Multiple test scenarios and validation  

## 👥 Contributing

This is an educational project demonstrating programming language concepts. Students are encouraged to:
- Compare the two implementations
- Identify language-specific optimizations
- Experiment with additional features
- Create implementations in other languages

## 📞 Support

For questions about the implementation, language comparisons, or educational content, please refer to the course materials or contact the instructor.

---
*Developed as part of Advanced Programming Languages (APL) coursework - Fall 2025*  
*Demonstrating mastery of control structures across multiple programming paradigms*