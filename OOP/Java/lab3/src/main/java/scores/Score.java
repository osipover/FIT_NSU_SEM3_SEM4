package scores;

public class Score {
    private String name;
    private int totalTime;

    public Score(String name, int totalTime) {
        this.name = name;
        this.totalTime = totalTime;
    }

    public String getName() {
        return this.name;
    }

    public int getTotalTime() {
        return this.totalTime;
    }
}
