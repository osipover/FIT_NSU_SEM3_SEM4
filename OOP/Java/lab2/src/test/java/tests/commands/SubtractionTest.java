package tests.commands;

import com.commands.Subtraction;
import com.commands.exceptions.ArgumentsNumberException;
import com.context.Context;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class SubtractionTest {
    Context context = new Context();
    Subtraction sub = new Subtraction();

    @ParameterizedTest
    @CsvSource(value = {
            "10.0, -10.0",
            "12.5, 12.5",
            "-25, -25",
            "0.0, 0.0"
    })
    void testAddition(Double value1, Double value2) {
        context.push(value2);
        context.push(value1);
        assertDoesNotThrow(() -> {
            sub.execute(new ArrayList<>(), context);
        });
        assertEquals(value1 - value2, context.pop());
    }

    @Test
    void testArgumentNumberException(){
        assertThrows(ArgumentsNumberException.class, () -> {
            sub.execute(new ArrayList<>(), context);
        });

        context.push(10.0);
        assertThrows(ArgumentsNumberException.class, () -> {
            sub.execute(new ArrayList<>(), context);
        });
    }

}