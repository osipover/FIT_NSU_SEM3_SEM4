 import java.io.IOException;
import java.io.Reader;
import java.util.Comparator;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Map;

public class WordTable {
    private HashMap<String, Integer> wordTable;

    public WordTable(Reader reader) throws IOException{
        wordTable = new HashMap<String, Integer>();
        FileParser parser = new FileParser(reader);
        while(reader.ready()) {
            String word = parser.getNextWord();
            wordTable.merge(word, 1, (prev, next) -> prev + 1);
        }
    }
    public ArrayList<WordStatistic> sort(){
        var sortedTable = new ArrayList<WordStatistic>();
        for (Map.Entry<String, Integer> pair : wordTable.entrySet()){
            WordStatistic cell = new WordStatistic(pair.getKey(), pair.getValue());
            sortedTable.add(cell);
            WordStatistic.totalCount++;
        }
        sortedTable.sort(new CompareCells());
        return sortedTable;
    }
}

class CompareCells implements Comparator<WordStatistic> {
    @Override
    public int compare(WordStatistic cell1, WordStatistic cell2){
        return cell2.getNumInclusion() - cell1.getNumInclusion();
    }
}

