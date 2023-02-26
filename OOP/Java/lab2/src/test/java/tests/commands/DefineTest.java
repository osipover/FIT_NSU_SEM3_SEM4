package tests.commands;

import com.commands.Define;
import com.commands.exceptions.ArgumentsNumberException;
import com.commands.exceptions.DefineException;
import com.context.Context;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.CsvSource;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class DefineTest {
    Context context = new Context();
    Define define = new Define();

    @ParameterizedTest
    @CsvSource(value = {
            "a, 5",
            "arg, -1.0"
    })
    void testDefine(String definition, Double value){
        ArrayList<String> args = new ArrayList<>(Arrays.asList(definition, value.toString()));
        assertDoesNotThrow(() -> define.execute(args, context));
        assertEquals(value, context.getValue(definition));
    }

    static Stream<Arguments> prepareArgNumException(){
        return Stream.of(
                Arguments.of(new ArrayList<String>()),
                Arguments.of(new ArrayList<String>(Arrays.asList("a"))),
                Arguments.of(new ArrayList<String>(Arrays.asList("a", "5", "b")))
        );
    }
    @ParameterizedTest
    @MethodSource("prepareArgNumException")
    void testArgumentsNumberException(ArrayList<String> args) {
        assertThrows(ArgumentsNumberException.class, () -> define.execute(args, context));
    }

    static Stream<Arguments> prepareDefineException(){
        return Stream.of(
                Arguments.of(new ArrayList<String>(Arrays.asList("123", "123"))),
                Arguments.of(new ArrayList<String>(Arrays.asList("a", "b"))),
                Arguments.of(new ArrayList<String>(Arrays.asList("a", "12b33")))
        );
    }
    @ParameterizedTest
    @MethodSource("prepareDefineException")
    void testDefineException(ArrayList<String> args){
        assertThrows(DefineException.class, () -> define.execute(args, context));
    }
}