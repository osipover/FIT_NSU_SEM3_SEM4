package scores;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Comparator;

public class HighScores implements Serializable {
    private final int MAX_NUM_SCORES = 10;
    private ArrayList<Score> table;

    public HighScores() {
        table = new ArrayList<Score>();
    }

    private void sort(){
        table.sort(new Comparator<Score>() {
            @Override
            public int compare(Score o1, Score o2) {
                Integer timeO1 = o1.getTotalTime();
                Integer timeO2 = o2.getTotalTime();
                return timeO1.compareTo(timeO2);
            }
        });
    }

    public void add(Score score) {
        table.add(score);
        sort();
        if (table.size() > MAX_NUM_SCORES) {
            table.remove(MAX_NUM_SCORES - 1);
        }
    }

    public ArrayList<Score> getTable(){
        return this.table;
    }


}
