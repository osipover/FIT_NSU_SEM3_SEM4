package tests.commands;

import com.commands.Division;
import com.commands.exceptions.ArgumentsNumberException;
import com.commands.exceptions.DivisionByZeroException;
import com.context.Context;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;
import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class DivisionTest {
    Context context = new Context();
    Division division = new Division();

    @ParameterizedTest
    @CsvSource(value = {
            "10.0, 10.0",
            "12.0, -4.0",
            "25.25, 1",
            "-123.25, -321.5"
    })
    void testAddition(Double value1, Double value2) {
        context.push(value2);
        context.push(value1);
        assertDoesNotThrow(() -> {
            division.execute(new ArrayList<>(), context);
        });
        assertEquals(value1 / value2, context.pop());
    }

   @Test
    void testDivisionByZero(){
       context.push(0.0);
       context.push(1.0);
       assertThrows(DivisionByZeroException.class, () -> {
           division.execute(new ArrayList<>(), context);
       });
   }

    @Test
    void testArgumentNumberException(){
        assertThrows(ArgumentsNumberException.class, () -> {
            division.execute(new ArrayList<>(), context);
        });

        context.push(10.0);
        assertThrows(ArgumentsNumberException.class, () -> {
            division.execute(new ArrayList<>(), context);
        });
    }

}