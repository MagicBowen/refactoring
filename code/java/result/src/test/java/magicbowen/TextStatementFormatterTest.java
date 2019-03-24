package magicbowen;

import org.junit.Test;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.equalTo;


public class TextStatementFormatterTest {
    @Test
    public void statement() throws Exception {

        StatementFormatter formatter = new TextStatementFormatter();
        formatter.onCustomer("Robert");
        formatter.onRental("The Beautiful Life", 15.0);
        formatter.onRental("Tom and Jerry", 3.0);
        formatter.onRental("Animal World", 2.0);
        formatter.onTotal(20.0, 4);

        String statement = new StringBuilder()
                .append("Rental record for Robert\n")
                .append("\tThe Beautiful Life\t15.0\n")
                .append("\tTom and Jerry\t3.0\n")
                .append("\tAnimal World\t2.0\n")
                .append("Amount owed is 20.0\n")
                .append("You earned 4 frequent renter points\n")
                .toString();

        assertThat(statement, equalTo(formatter.statement()));
    }

}