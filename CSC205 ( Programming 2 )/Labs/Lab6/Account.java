public class Account {
  // Instance variables
  private double balance;

  // Constructors
  public Account(double initialBalance) {
    balance = initialBalance;
  }

  public Account() {
    balance = 0.0;
  }

  // Instance methods
  public void deposit(double amount) {
    balance += amount;
  }

  public void withdraw(double amount) {
    balance -= amount;
  }

  public double getBalance() {
    return balance;
  }

  public void close() {
    balance = 0.0;
  }
}
