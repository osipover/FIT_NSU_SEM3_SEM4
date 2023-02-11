import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;

public class Main {
    public static void main(String[] args) {
        Reader reader = null;
        try {
            reader = new InputStreamReader(new FileInputStream("test.txt"));
            WordTable wordTable = new WordTable(reader);
            CSVGenerator csvGenerator = new CSVGenerator("output.csv");
            csvGenerator.write(wordTable);
        }
        catch(IOException ex){
            System.out.println(ex.getMessage());
        }
    }
}
