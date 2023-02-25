package tests;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import com.stream.Stream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

class StreamTest {
    @Test
    void testStreamConstructorSystemIn(){
        String[] args = {};
        Stream stream = new Stream(args);
        assertEquals(System.in, stream.getIn());
    }

    @Test
    void testStreamConstructorFile(){
        String[] args = {"src/main/resources/test_files/simple_example.txt"};
        Stream stream = new Stream(args);
        BufferedReader reader = new BufferedReader(new InputStreamReader(stream.getIn()));
        try {
            assertEquals("# Calculator", reader.readLine());
        } catch (IOException ex){
            System.err.println(ex.getMessage());
        }
    }

    @Test
    void testStreamConstructorInvalidInput(){
        String[] args = {"i_do_not_exist.txt"};
        Stream stream = new Stream(args);
        assertEquals(System.in, stream.getIn());
    }
}