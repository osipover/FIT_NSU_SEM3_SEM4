package scores;

import java.io.Serializable;

public class Score implements Comparable<Score>, Serializable {
    private String name;
    private int hours;
    private int minutes;
    private int seconds;

    public Score(String name, int hours, int minutes, int seconds) {
        this.name = name;
        this.hours = hours;
        this.minutes = minutes;
        this.seconds = seconds;
    }

    public String getName() {
        return this.name;
    }

    @Override
    public String toString() {
        return String.format("%s     %02d:%02d:%02d", name, hours, minutes, seconds);
    }

    @Override
    public int compareTo(Score o) {
        if (this.hours < o.hours) return -1;
        if (this.hours == o.hours) {
            if (this.minutes < o.minutes) return -1;
            if (this.minutes == o.minutes) {
                if (this.seconds < o.seconds) return -1;
                if (this.seconds == o.seconds) return 0;
            }
        }
        return 1;
    }
}
