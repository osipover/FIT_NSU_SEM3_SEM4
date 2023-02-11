public class WordStatistic {
    public WordStatistic (String word, int numInclusion){
        this.word = word;
        this.numInclusion = numInclusion;
    }

    public String getWord(){
        return this.word;
    }

    public int getNumInclusion(){
        return this.numInclusion;
    }

    @Override
    public String toString(){
        return word + ";" + numInclusion + ";" + percentOfAllWords() + "%";
    }

    private double percentOfAllWords(){
        double percent = ((double)numInclusion/totalCount) * 100;
        return (double)((int)(percent * 100))/100;
    }

    public static int totalCount = 0;
    private String word;
    private int numInclusion;
}
