package magicbowen;


public class Movie {
    private String title;
    private MovieType type;

    public Movie(String title, MovieType type) {
        this.title = title;
        this.type = type;
    }

    public String getTitle() {
        return title;
    }

    public double getCharge(int daysRented) {
        return type.getCharge(daysRented);
    }

    public int getPoints(int daysRented) {
        return type.getPoints(daysRented);
    }
}
