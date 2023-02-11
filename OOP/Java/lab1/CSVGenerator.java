import java.io.FileOutputStream;
import java.io.IOException;
import java.io.Writer;
import java.io.OutputStreamWriter;

public class CSVGenerator {
    public CSVGenerator(String fileName) throws IOException{
        try {
            this.fileOut = new FileOutputStream(fileName);
        }
        catch (IOException ex){
            throw new IOException("[ERROR] I can't open output file");
        }
    }

    public void write(WordTable wordTable) {
        Writer writer = null;
        writer = new OutputStreamWriter(this.fileOut);
        try{
            for (WordStatistic cell : wordTable.sort()){
                writer.write(cell.toString() + "\n");
            }
        }
        catch(IOException ex){
            System.err.println("[ERROR] I can't write in output file");
        }
    }

    private final FileOutputStream fileOut;
}
