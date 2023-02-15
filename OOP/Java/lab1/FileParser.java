import java.io.IOException;
import java.io.Reader;

public class FileParser {
    private final Reader reader;

    FileParser(Reader reader){
        this.reader = reader;
    }
    public String getNextWord() throws IOException {
        StringBuilder newWord = new StringBuilder("");
        int data = 0;
        while(newWord.toString().equals("") && (data != -1)){
            data = reader.read();
            while(Character.isLetterOrDigit(data)){
                newWord.append((char)data);
                data = reader.read();
            }
        }
        return newWord.toString();
    }
}
