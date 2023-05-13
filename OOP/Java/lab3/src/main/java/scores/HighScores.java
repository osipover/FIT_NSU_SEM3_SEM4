package scores;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;

public class HighScores implements Serializable {
    private final int MAX_NUM_SCORES = 10;
    private ArrayList<Score> table;

    public HighScores() {
        table = new ArrayList<Score>();
    }


    public void add(Score score) {
        table.add(score);
        Collections.sort(table);
        if (table.size() > MAX_NUM_SCORES) {
            table.remove(MAX_NUM_SCORES - 1);
        }
    }

    public ArrayList<Score> getTable(){
        return this.table;
    }
}
