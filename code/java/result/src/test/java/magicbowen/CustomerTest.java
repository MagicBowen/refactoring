package magicbowen;

import magicbowen.testdoubles.SpyStatementFormatter;
import org.junit.Before;
import org.junit.Test;

import static magicbowen.MovieType.*;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.*;


public class CustomerTest {
    private static final String NAME = "Robert";

    private Customer customer;
    private SpyStatementFormatter formatter;

    @Before
    public void setup() {
        customer = new Customer(NAME);
        formatter = new SpyStatementFormatter();
    }

    @Test
    public void baseInfo() {
        customer.statement(formatter);
        assertThat(NAME, equalTo(formatter.getCustomerName()));
        assertThat(0.0, equalTo(formatter.getTotalCharge()));
        assertThat(0, equalTo(formatter.getTotalPoints()));
    }

    @Test
    public void newReleaseLessThan2Days() {
        customer.addRental(new Rental(new Movie("A", NEW_RELEASE_TYPE), 1));
        customer.statement(formatter);
        assertThat(3.0, equalTo(formatter.getChargeOf("A")));
        assertThat(3.0, equalTo(formatter.getTotalCharge()));
        assertThat(1, equalTo(formatter.getTotalPoints()));
    }

    @Test
    public void newReleaseMoreThan3Days() {
        customer.addRental(new Rental(new Movie("A", NEW_RELEASE_TYPE), 4));
        customer.statement(formatter);
        assertThat(12.0, equalTo(formatter.getTotalCharge()));
        assertThat(2, equalTo(formatter.getTotalPoints()));
    }

    // More tests for all algorithms of different movie types

    // Just one end-to-end test to verify the relation of all processes
    @Test
    public void statement() {
        customer.addRental(new Rental(new Movie("A", NEW_RELEASE_TYPE), 5));
        customer.addRental(new Rental(new Movie("B", CHILDREN_TYPE), 4));
        customer.addRental(new Rental(new Movie("C", REGULAR_TYPE), 2));

        customer.statement(formatter);

        assertThat(NAME, equalTo(formatter.getCustomerName()));
        assertThat(15.0, equalTo(formatter.getChargeOf("A")));
        assertThat(3.0, equalTo(formatter.getChargeOf("B")));
        assertThat(2.0, equalTo(formatter.getChargeOf("C")));
        assertThat(20.0, equalTo(formatter.getTotalCharge()));
        assertThat(4, equalTo(formatter.getTotalPoints()));
    }
}
