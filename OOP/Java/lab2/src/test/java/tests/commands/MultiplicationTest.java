package tests.commands;

import com.commands.Multiplication;
import com.commands.exceptions.ArgumentsNumberException;
import com.context.Context;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class MultiplicationTest {
    Context context = new Context();
    Multiplication mult = new Multiplication();

    @ParameterizedTest
    @CsvSource(value = {
            "1.0, 0.0",
            "2.5, 2.0",
            "-25, -2",
            "0.0, 0.0"
    })
    void testAddition(Double value1, Double value2) {
        context.push(value1);
        context.push(value2);
        assertDoesNotThrow(() -> {
            mult.execute(new ArrayList<>(), context);
        });
        assertEquals(value1 * value2, context.pop());
    }

    @Test
    void testArgumentNumberException(){
        assertThrows(ArgumentsNumberException.class, () -> {
            mult.execute(new ArrayList<>(), context);
        });

        context.push(10.0);
        assertThrows(ArgumentsNumberException.class, () -> {
            mult.execute(new ArrayList<>(), context);
        });
    }

}