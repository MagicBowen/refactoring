package magicbowen;


public class TextStatementFormatter implements StatementFormatter {
    @Override
    public void onCustomer(String name) {
        statement.append(String.format("Rental record for %s%n", name));
    }

    @Override
    public void onRental(String movieName, double charge) {
        statement.append(String.format("\t%s\t%.1f\n", movieName, charge));
    }

    @Override
    public void onTotal(double charge, int points) {
        statement.append(String.format("Amount owed is %.1f%n", charge));
        statement.append(String.format("You earned %d frequent renter points%n", points));
    }

    @Override
    public String statement() {
        return statement.toString();
    }

    private StringBuilder statement = new StringBuilder();
}
