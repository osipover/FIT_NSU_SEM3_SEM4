import java.io.IOException;
import java.io.Reader;
import java.util.Comparator;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Map;

public class WordTable {
    public WordTable(Reader reader) throws IOException{
        wordTable = new HashMap<String, Integer>();
        FileParser parser = new FileParser(reader);
        while(reader.ready()) {
            String word = parser.getNextWord();
            if (wordTable.containsKey(word))
                wordTable.replace(word, wordTable.get(word) + 1);
            else
                wordTable.put(word, 1);
        }
    }

    public ArrayList<WordStatistic> sort(){
        var sortedTable = new ArrayList<WordStatistic>();
        for (Map.Entry<String, Integer> pair : wordTable.entrySet()){
            WordStatistic cell = new WordStatistic(pair.getKey(), pair.getValue());
            WordStatistic.totalCount++;
            sortedTable.add(cell);
        }
        sortedTable.sort(new CompareCells());
        return sortedTable;
    }

    HashMap<String, Integer> wordTable;
}

class CompareCells implements Comparator<WordStatistic> {
    @Override
    public int compare(WordStatistic cell1, WordStatistic cell2){
        return cell2.getNumInclusion() - cell1.getNumInclusion();
    }
}

