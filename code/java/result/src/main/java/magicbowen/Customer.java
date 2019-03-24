package magicbowen;


import java.util.ArrayList;
import java.util.List;
import java.util.function.BinaryOperator;
import java.util.function.Function;


public class Customer {
    public Customer(String name) {
        this.name = name;
    }

    public void addRental(Rental rental) {
        rentals.add(rental);
    }

    public String statement(StatementFormatter formatter) {
        formatter.onCustomer(getName());
        rentals.stream().forEach(rental -> formatter.onRental(rental.getMovie().getTitle(), rental.getCharge()));
        formatter.onTotal(getTotalCharge(), getTotalRenterPoints());
        return formatter.statement();
    }

    private double getTotalCharge() {
        return accumulate(0.0, rental -> rental.getCharge(), Double::sum);
    }

    private int getTotalRenterPoints() {
        return accumulate(0, rental -> rental.getPoints(), Integer::sum);
    }

    private <T> T accumulate(T initial, Function<Rental, T> mapper, BinaryOperator<T> accumulator) {
        return rentals.stream().map(mapper).reduce(initial, accumulator);
    }

    private String getName() {
        return name;
    }

    private String name;
    private List<Rental> rentals = new ArrayList<>();
}
