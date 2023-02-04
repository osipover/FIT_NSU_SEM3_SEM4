import java.io.IOException;
import java.io.Reader;

public class Parser {
    Parser(Reader reader){
        this.reader = reader;
    }
    
    public String getNextWord() throws IOException {
        StringBuilder newWord = new StringBuilder("");
        try{
            while(newWord.toString().equals("")){
                //System.out.println("!");
                int data = reader.read();
                while((data != -1) && Character.isLetterOrDigit(data)){
                    newWord.append((char)data);
                    data = reader.read();
                }
            }
        }
        catch(IOException ex){
            throw ex;
        }
        return newWord.toString();
    }

    private Reader reader;
}
