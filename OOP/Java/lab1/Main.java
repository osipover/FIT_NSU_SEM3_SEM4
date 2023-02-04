import java.io.IOException;
import java.io.Reader;
import java.io.InputStreamReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;

public class Main {
    public static void main(String args[]) {
        Reader reader = null;
        try {
            reader = new InputStreamReader(new FileInputStream("test.txt"));
            Parser parser = new Parser(reader);
            WordTable wordTable = new WordTable();
            while (reader.ready()) {
                WordStatistic cell = new WordStatistic(parser.getNextWord());
                wordTable.add(cell);
            }
            System.out.println(wordTable);
        }
        catch(IOException ex){
            System.out.println(ex.getMessage());
        }
    }
}
