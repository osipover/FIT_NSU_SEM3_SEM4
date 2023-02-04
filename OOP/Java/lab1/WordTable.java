import java.util.TreeSet;

public class WordTable {
    public WordTable(){
        this.table = new TreeSet<WordStatistic>();
    }
  
    public void add(WordStatistic cell){
        WordStatistic curCell = table.ceiling(cell);
        if ((curCell == null) || (!curCell.equals(cell))) {
            table.add(cell);
        }
        else{
            cell.numInclusion = curCell.numInclusion + 1;
            table.remove(curCell);
            table.add(cell);
        }
    }
  
    @Override
    public String toString(){
        return table.toString();
    }
  
    private TreeSet<WordStatistic> table;
}
