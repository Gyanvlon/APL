import java.util.*;

public class EmployeeScheduler {

    public enum Shift {
        MORNING("Morning"),
        AFTERNOON("Afternoon"),
        EVENING("Evening");

        private final String displayName;

        Shift(String displayName) {
            this.displayName = displayName;
        }

        public String getDisplayName() {
            return displayName;
        }
    }

    public enum Day {
        MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
    }

    static class Employee {
        private String name;
        private Map<Day, Shift> preferences;
        private Map<Day, Shift> assignedShifts;
        private int daysWorked;
        public Employee(String name) {
            this.name = name;
            this.preferences = new HashMap<>();
            this.assignedShifts = new HashMap<>();
            this.daysWorked = 0;
        }
        public String getName() { return name; }
        public Map<Day, Shift> getPreferences() { return preferences; }
        public Map<Day, Shift> getAssignedShifts() { return assignedShifts; }
        public int getDaysWorked() { return daysWorked; }

        public void addPreference(Day day, Shift shift) {
            preferences.put(day, shift);
        }

        public void assignShift(Day day, Shift shift) {
            if (!assignedShifts.containsKey(day)) {
                assignedShifts.put(day, shift);
                daysWorked++;
            }
        }

        public boolean isAvailable(Day day) {
            return !assignedShifts.containsKey(day) && daysWorked < 5;
        }

        public boolean hasPreference(Day day, Shift shift) {
            return preferences.containsKey(day) && preferences.get(day) == shift;
        }
    }

    private Map<Day, Map<Shift, List<Employee>>> schedule;
    private List<Employee> employees;
    private Random random;
    private static final int MIN_EMPLOYEES_PER_SHIFT = 2;
    private Scanner scanner;

    public EmployeeScheduler() {
        this.schedule = new HashMap<>();
        this.employees = new ArrayList<>();
        this.random = new Random();
        this.scanner = new Scanner(System.in);
        for (Day day : Day.values()) {
            schedule.put(day, new HashMap<>());
            for (Shift shift : Shift.values()) {
                schedule.get(day).put(shift, new ArrayList<>());
            }
        }
    }

    public static void main(String[] args) {
        EmployeeScheduler manager = new EmployeeScheduler();
        try {
            manager.inputEmployeeData();
            if (!manager.employees.isEmpty()) {
                System.out.println("\n--- Generating Schedule ---");
                manager.generateSchedule();
                manager.displaySchedule();
            } else {
                System.out.println("No employees entered. Exiting...");
            }

        } catch (Exception e) {
            System.err.println("An error occurred: " + e.getMessage());
            e.printStackTrace();
        } finally {
            manager.scanner.close();
        }
    }

    private void inputEmployeeData() {
        System.out.println("Enter employee information. Type 'done' as employee name to finish early.");
        int employeeCount = 1;
        while (true) {
            System.out.printf("Enter name for employee %d: ", employeeCount);
            String name = scanner.nextLine().trim();
            if (name.equalsIgnoreCase("done") || name.isEmpty()) {
                break;
            }
            boolean nameExists = false;
            for (Employee emp : employees) {
                if (emp.getName().equalsIgnoreCase(name)) {
                    nameExists = true;
                    break;
                }
            }

            if (nameExists) {
                System.out.println("Employee with this name already exists. Please enter a different name.");
                continue;
            }
            Employee employee = new Employee(name);
            System.out.println("Enter shift preferences for " + name + ".");
            System.out.println("Valid shifts: MORNING, AFTERNOON, EVENING. Enter 'skip' to skip a day, or 'cancel' to skip this employee.");
            System.out.println("Note: Only one shift preference is allowed per day.");
            boolean skipEmployee = false;
            for (Day day : Day.values()) {
                System.out.println("\nPreference for " + day + ":");
                System.out.print("Enter shift (MORNING, AFTERNOON, EVENING), 'skip', or 'cancel': ");
                String input = scanner.nextLine().trim().toUpperCase();

                if (input.equals("CANCEL")) {
                    skipEmployee = true;
                    break;
                } else if (input.equals("SKIP")) {
                    continue;
                } else {
                    try {
                        Shift shift = Shift.valueOf(input);
                        employee.addPreference(day, shift);
                    } catch (IllegalArgumentException e) {
                        System.out.println("Invalid shift: " + input + ". Skipping this day.");
                    }
                }
            }

            if (!skipEmployee) {
                employees.add(employee);
                System.out.println("Employee " + name + " added successfully!");
                employeeCount++;
            }
            System.out.print("\nAdd another employee? (y/n/done): ");
            String response = scanner.nextLine().trim().toLowerCase();
            if (response.equals("n") || response.equals("no") || response.equals("done")) {
                break;
            }
        }

        System.out.println("\nTotal employees added: " + employees.size());
    }

    private void generateSchedule() {
        clearSchedule();
        assignBasedOnPreferences();
        ensureMinimumStaffing();
        System.out.println("Schedule generated successfully!");
    }

    private void clearSchedule() {
        for (Day day : Day.values()) {
            for (Shift shift : Shift.values()) {
                schedule.get(day).get(shift).clear();
            }
        }

        for (Employee employee : employees) {
            employee.getAssignedShifts().clear();
            employee.daysWorked = 0;
        }
    }

    private void assignBasedOnPreferences() {
        for (Day day : Day.values()) {
            for (Shift shift : Shift.values()) {
                List<Employee> eligibleEmployees = new ArrayList<>();

                for (Employee employee : employees) {
                    if (employee.isAvailable(day) && employee.hasPreference(day, shift)) {
                        eligibleEmployees.add(employee);
                    }
                }

                int maxPerShift = Math.min(eligibleEmployees.size(), 4);
                for (int i = 0; i < maxPerShift; i++) {
                    Employee employee = eligibleEmployees.get(i);
                    if (employee.isAvailable(day)) {
                        assignEmployeeToShift(employee, day, shift);
                    }
                }
            }
        }
    }

    private void ensureMinimumStaffing() {
        for (Day day : Day.values()) {
            for (Shift shift : Shift.values()) {
                List<Employee> currentShiftEmployees = schedule.get(day).get(shift);

                while (currentShiftEmployees.size() < MIN_EMPLOYEES_PER_SHIFT) {
                    Employee availableEmployee = findAvailableEmployee(day);

                    if (availableEmployee == null) {
                        System.out.println("Warning: Cannot meet minimum staffing for " +
                                day + " " + shift.getDisplayName() + " shift");
                        break;
                    }

                    assignEmployeeToShift(availableEmployee, day, shift);
                }
            }
        }
    }

    private Employee findAvailableEmployee(Day day) {
        List<Employee> availableEmployees = new ArrayList<>();

        for (Employee employee : employees) {
            if (employee.isAvailable(day)) {
                availableEmployees.add(employee);
            }
        }

        if (availableEmployees.isEmpty()) {
            return null;
        }

        return availableEmployees.get(random.nextInt(availableEmployees.size()));
    }

    private void assignEmployeeToShift(Employee employee, Day day, Shift shift) {
        if (employee.isAvailable(day)) {
            schedule.get(day).get(shift).add(employee);
            employee.assignShift(day, shift);
        }
    }

    private void displaySchedule() {
        System.out.println("\n" + "=".repeat(80));
        System.out.println("                    WEEKLY EMPLOYEE SCHEDULE");
        System.out.println("=".repeat(80));

        if (employees.isEmpty()) {
            System.out.println("No schedule available. No employees were added.");
            return;
        }

        System.out.printf("%-12s", "Day");
        for (Shift shift : Shift.values()) {
            System.out.printf("%-25s", shift.getDisplayName());
        }
        System.out.println();
        System.out.println("-".repeat(80));
        for (Day day : Day.values()) {
            System.out.printf("%-12s", day.toString());

            for (Shift shift : Shift.values()) {
                List<Employee> shiftEmployees = schedule.get(day).get(shift);
                StringBuilder shiftInfo = new StringBuilder();

                if (shiftEmployees.isEmpty()) {
                    shiftInfo.append("No staff");
                } else {
                    for (int i = 0; i < shiftEmployees.size(); i++) {
                        if (i > 0) shiftInfo.append(", ");
                        shiftInfo.append(shiftEmployees.get(i).getName());
                    }
                }

                String displayText = shiftInfo.length() > 22 ?
                        shiftInfo.substring(0, 22) + "..." :
                        shiftInfo.toString();

                System.out.printf("%-25s", displayText);
            }
            System.out.println();
        }

        System.out.println("-".repeat(80));
        displayEmployeeSummary();
    }

    private void displayEmployeeSummary() {
        System.out.println("\nEMPLOYEE SUMMARY:");
        for (Employee employee : employees) {
            System.out.printf("%-15s: %d days worked", employee.getName(), employee.getDaysWorked());

            if (employee.getDaysWorked() > 5) {
                System.out.print(" (OVERWORKED!)");
            } else if (employee.getDaysWorked() < 2) {
                System.out.print(" (Underutilized)");
            }
            System.out.println();
        }
    }
}