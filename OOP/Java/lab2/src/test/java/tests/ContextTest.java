package tests;

import com.context.Context;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import static org.junit.jupiter.api.Assertions.*;

class ContextTest {
    Context context;

    @BeforeEach
    void prepareContext(){
        context = new Context();
        context.define("val1", 1.0);
        context.define("val2", 1.5);
        context.define("val3", 2.0);
        context.push(1.0);
        context.push(1.5);
        context.push(2.0);
    }


    @ParameterizedTest
    @CsvSource(value = {
            "'val1', 1.0",
            "'val2', 1.5",
            "'val3', 2.0",
            "'val4', ,"
    })
    void testGetValue(String definition, Double value) {
        assertEquals(value, context.getValue(definition));
    }

    @Test
    void testPop() {
        assertEquals(2.0, context.pop());
        assertNotEquals(2.0, context.pop());
    }

    @Test
    void getLastArgument() {
        assertEquals(2.0, context.getLastArgument());
        assertEquals(2.0, context.getLastArgument());
    }
}
