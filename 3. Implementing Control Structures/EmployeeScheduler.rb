require 'set'

class EmployeeScheduler
  class Shift
    MORNING = 'Morning'
    AFTERNOON = 'Afternoon'
    EVENING = 'Evening'
    
    ALL = [MORNING, AFTERNOON, EVENING].freeze
    
    def self.valid?(shift)
      ALL.include?(shift)
    end
    
    def self.from_string(str)
      case str.upcase
      when 'MORNING'
        MORNING
      when 'AFTERNOON'
        AFTERNOON
      when 'EVENING'
        EVENING
      else
        nil
      end
    end
  end
  
  class Day
    MONDAY = 'Monday'
    TUESDAY = 'Tuesday'
    WEDNESDAY = 'Wednesday'
    THURSDAY = 'Thursday'
    FRIDAY = 'Friday'
    SATURDAY = 'Saturday'
    SUNDAY = 'Sunday'
    
    ALL = [MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY].freeze
    
    def self.valid?(day)
      ALL.include?(day)
    end
  end

  class Employee
    attr_reader :name, :preferences, :assigned_shifts, :days_worked
    
    def initialize(name)
      @name = name
      @preferences = {}
      @assigned_shifts = {}
      @days_worked = 0
    end
    
    def add_preference(day, shift)
      @preferences[day] = shift
    end
    
    def assign_shift(day, shift)
      unless @assigned_shifts.key?(day)
        @assigned_shifts[day] = shift
        @days_worked += 1
      end
    end
    
    def available?(day)
      !@assigned_shifts.key?(day) && @days_worked < 5
    end
    
    def has_preference?(day, shift)
      @preferences.key?(day) && @preferences[day] == shift
    end
    
    def clear_assignments
      @assigned_shifts.clear
      @days_worked = 0
    end
  end
  
  MIN_EMPLOYEES_PER_SHIFT = 2
  
  def initialize
    @schedule = {}
    @employees = []
    Day::ALL.each do |day|
      @schedule[day] = {}
      Shift::ALL.each do |shift|
        @schedule[day][shift] = []
      end
    end
  end
  
  def self.main
    manager = new
    
    begin
      manager.input_employee_data
      if !manager.employees.empty?
        puts "\n--- Generating Schedule ---"
        manager.generate_schedule
        manager.display_schedule
      else
        puts "No employees entered. Exiting..."
      end
      
    rescue => e
      puts "An error occurred: #{e.message}"
      puts e.backtrace
    end
  end
  
  def input_employee_data
    puts "Enter employee information. Type 'done' as employee name to finish early."
    
    employee_count = 1
    loop do
      print "Enter name for employee #{employee_count}: "
      name = gets.chomp.strip
      break if name.downcase == 'done' || name.empty?
      name_exists = false
      @employees.each do |emp|
        if emp.name.downcase == name.downcase
          name_exists = true
          break
        end
      end
      
      if name_exists
        puts "Employee with this name already exists. Please enter a different name."
        next
      end
      
      employee = Employee.new(name)
      
      puts "Enter shift preferences for #{name}."
      puts "Valid shifts: MORNING, AFTERNOON, EVENING. Enter 'skip' to skip a day, or 'cancel' to skip this employee."
      puts "Note: Only one shift preference is allowed per day."
      
      skip_employee = false
      Day::ALL.each do |day|
        puts "\nPreference for #{day}:"
        print "Enter shift (MORNING, AFTERNOON, EVENING), 'skip', or 'cancel': "
        input = gets.chomp.strip.upcase
        
        case input
        when 'CANCEL'
          skip_employee = true
          break
        when 'SKIP'
          next
        else
          shift = Shift.from_string(input)
          if shift
            employee.add_preference(day, shift)
          else
            puts "Invalid shift: #{input}. Skipping this day."
          end
        end
      end
      
      unless skip_employee
        @employees << employee
        puts "Employee #{name} added successfully!"
        employee_count += 1
      end
      print "\nAdd another employee? (y/n/done): "
      response = gets.chomp.strip.downcase
      break if ['n', 'no', 'done'].include?(response)
    end
    
    puts "\nTotal employees added: #{@employees.size}"
  end
  
  def employees
    @employees
  end
  
  def generate_schedule
    clear_schedule
    assign_based_on_preferences
    ensure_minimum_staffing
    
    puts "Schedule generated successfully!"
  end
  
  def display_schedule
    puts "\n" + "=" * 80
    puts "                    WEEKLY EMPLOYEE SCHEDULE"
    puts "=" * 80
    
    if @employees.empty?
      puts "No schedule available. No employees were added."
      return
    end
    
    printf "%-12s", "Day"
    Shift::ALL.each do |shift|
      printf "%-25s", shift
    end
    puts
    puts "-" * 80
    Day::ALL.each do |day|
      printf "%-12s", day
      
      Shift::ALL.each do |shift|
        shift_employees = @schedule[day][shift]
        shift_info = ""
        
        if shift_employees.empty?
          shift_info = "No staff"
        else
          names = shift_employees.map(&:name)
          shift_info = names.join(", ")
        end
        
        display_text = shift_info.length > 22 ? 
                      "#{shift_info[0, 22]}..." : 
                      shift_info
        
        printf "%-25s", display_text
      end
      puts
    end
    
    puts "-" * 80
    display_employee_summary
  end
  
  def display_employee_summary
    puts "\nEMPLOYEE SUMMARY:"
    @employees.each do |employee|
      status = ""
      if employee.days_worked > 5
        status = " (OVERWORKED!)"
      elsif employee.days_worked < 2
        status = " (Underutilized)"
      end
      
      printf "%-15s: %d days worked%s\n", employee.name, employee.days_worked, status
    end
  end
  
  private
  
  def clear_schedule
    Day::ALL.each do |day|
      Shift::ALL.each do |shift|
        @schedule[day][shift].clear
      end
    end
    
    @employees.each(&:clear_assignments)
  end
  
  def assign_based_on_preferences
    Day::ALL.each do |day|
      Shift::ALL.each do |shift|
        eligible_employees = []
        
        @employees.each do |employee|
          if employee.available?(day) && employee.has_preference?(day, shift)
            eligible_employees << employee
          end
        end
    
        max_per_shift = [eligible_employees.size, 4].min
        (0...max_per_shift).each do |i|
          employee = eligible_employees[i]
          if employee.available?(day)
            assign_employee_to_shift(employee, day, shift)
          end
        end
      end
    end
  end
  
  def ensure_minimum_staffing
    Day::ALL.each do |day|
      Shift::ALL.each do |shift|
        current_shift_employees = @schedule[day][shift]
        
        while current_shift_employees.size < MIN_EMPLOYEES_PER_SHIFT
          available_employee = find_available_employee(day)
          
          if available_employee.nil?
            puts "Warning: Cannot meet minimum staffing for #{day} #{shift} shift"
            break
          end
          
          assign_employee_to_shift(available_employee, day, shift)
        end
      end
    end
  end
  
  def find_available_employee(day)
    available_employees = []
    
    @employees.each do |employee|
      available_employees << employee if employee.available?(day)
    end
    
    return nil if available_employees.empty?
    
    available_employees.sample 
  end
  
  def assign_employee_to_shift(employee, day, shift)
    if employee.available?(day)
      @schedule[day][shift] << employee
      employee.assign_shift(day, shift)
    end
  end
end

if __FILE__ == $0
  EmployeeScheduler.main
end