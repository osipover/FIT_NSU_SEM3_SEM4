package tests.commands;

import com.commands.Addition;
import com.commands.exceptions.ArgumentsNumberException;
import com.context.Context;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class AdditionTest {
    Context context = new Context();
    Addition addition = new Addition();

    @ParameterizedTest
    @CsvSource(value = {
            "10.0, -10.0",
            "12.5, 12.5",
            "-25, -25",
            "0.0, 0.0"
    })
    void testAddition(Double value1, Double value2) {
        context.push(value1);
        context.push(value2);
        assertDoesNotThrow(() -> {
            addition.execute(new ArrayList<>(), context);
        });
        assertEquals(value1 + value2, context.pop());
    }

    @Test
    void testArgumentNumberException(){
        assertThrows(ArgumentsNumberException.class, () -> {
            addition.execute(new ArrayList<>(), context);
        });

        context.push(10.0);
        assertThrows(ArgumentsNumberException.class, () -> {
            addition.execute(new ArrayList<>(), context);
        });
    }
}