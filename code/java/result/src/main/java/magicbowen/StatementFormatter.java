package magicbowen;


public interface StatementFormatter {
    void onCustomer(String name);
    void onRental(String movieName, double charge);
    void onTotal(double charge, int points);
    String statement();
}
