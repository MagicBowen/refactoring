package magicbowen;

import org.junit.Test;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.*;


public class CustomerTest {
    @Test
    public void statement() throws Exception {
        Customer customer = new Customer("Robert");
        customer.addRental(new Rental(new Movie("The Beautiful Life", Movie.NEW_RELEASE), 5));
        customer.addRental(new Rental(new Movie("Tom and Jerry", Movie.CHILDREN), 4));
        customer.addRental(new Rental(new Movie("Animal World", Movie.REGULAR), 2));
        String statement = new StringBuilder()
                .append("Rental record for Robert\n")
                .append("\tThe Beautiful Life\t15.0\n")
                .append("\tTom and Jerry\t3.0\n")
                .append("\tAnimal World\t2.0\n")
                .append("Amount owed is 20.0\n")
                .append("You earned 4 frequent renter points\n")
                .toString();
        assertThat(statement, equalTo(customer.statement()));
    }

}