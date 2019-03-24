package magicbowen.testdoubles;

import magicbowen.StatementFormatter;

import java.util.HashMap;


public class SpyStatementFormatter implements StatementFormatter {
    private String customerName;
    private HashMap<String, Double> rentals = new HashMap<>();
    private int totalPoints;
    private double totalCharge;

    @Override
    public void onCustomer(String name) {
        customerName = name;
    }

    @Override
    public void onRental(String movieName, double charge) {
        rentals.put(movieName, charge);
    }

    @Override
    public void onTotal(double charge, int points) {
        totalCharge = charge;
        totalPoints = points;
    }

    @Override
    public String statement() {
        return null;
    }

    public String getCustomerName() {
        return customerName;
    }

    public double getChargeOf(String movieName) {
        return rentals.get(movieName);
    }

    public int getTotalPoints() {
        return totalPoints;
    }

    public double getTotalCharge() {
        return totalCharge;
    }
}
