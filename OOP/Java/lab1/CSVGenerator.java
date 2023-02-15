import java.io.FileOutputStream;
import java.io.IOException;
import java.io.Writer;
import java.io.OutputStreamWriter;

public class CSVGenerator {
    private String fileName;
    private FileOutputStream outputStream;

    public CSVGenerator(String fileName) throws IOException{
        try {
            this.fileName = fileName;
            this.outputStream = new FileOutputStream(fileName);
        }
        catch (IOException ex){
            throw new IOException("[ERROR] I can't open " + this.fileName);
        }
    }
    public void write(WordTable wordTable) throws IOException{
        Writer writer = null;
        writer = new OutputStreamWriter(outputStream);
        try{
            var sortedTable = wordTable.sort();
            for (WordStatistic cell : sortedTable){
                writer.write(cell.toString() + "\n");
            }
        }
        catch(IOException ex){
            throw new IOException("[ERROR] I can't write in " + this.fileName);
        }
    }
}
