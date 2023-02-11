import java.io.IOException;
import java.io.Reader;

public class FileParser {
    FileParser(Reader reader){
        this.reader = reader;
    }

    public String getNextWord() throws IOException {
        StringBuilder newWord = new StringBuilder("");
        try{
            int data = 0;
            while(newWord.toString().equals("") && (data != -1)){
                data = reader.read();
                while((data != -1) && Character.isLetterOrDigit(data)){
                    newWord.append((char)data);
                    data = reader.read();
                }
            }
            return newWord.toString();
        }
        catch(IOException ex){
            throw ex;
        }
    }

    private Reader reader;
}
