import java.util.Objects;

public class WordStatistic implements Comparable<WordStatistic> {
    public WordStatistic(String word){
        this.word = word;
        numInclusion = 1;
    }

    @Override
    public boolean equals(Object o){
        if (this == o) return true;
        if ((o == null) || (this.getClass() != o.getClass())) return false;
        WordStatistic other = (WordStatistic) o;
        return this.word.equals(other.word);
    }

    @Override
    public int hashCode(){
        return this.numInclusion;
    }

    @Override
    public String toString() {
        return this.word + this.numInclusion;
    }

    @Override
    public int compareTo(WordStatistic cell){
        if (this.hashCode() > cell.hashCode()) return 1;
        if (Objects.equals(this.word, cell.word)) return 0;
        else return -1;
    }

    private String word;
    public int numInclusion;
}
