package tests;

import com.parser.CommandParser;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.CsvSource;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class CommandParserTest {
    CommandParser commandParser = new CommandParser();;

    @ParameterizedTest
    @CsvSource(value = {
            "'DEFINE a 5', 'DEFINE'",
            "'PUSH', 'PUSH'",
            "'PUSH a b c', 'PUSH'",
            "'# Some comment', '#'",
            "'*', '*'",
            "'/', '/'",
            "'+', '+'",
            "'-', '-'",
    })
    void testGetCmdName(String line, String cmdName) {
        commandParser.parse(line);
        assertEquals(cmdName, commandParser.getCmdName());
    }

    @ParameterizedTest
    @MethodSource("provideArgumentsForCmdArgsTest")
    void testGetCmdArgs(String line, ArrayList<String> args) {
        commandParser.parse(line);
        assertEquals(args, commandParser.getCmdArgs());
    }

    static Stream<Arguments> provideArgumentsForCmdArgsTest(){
        return Stream.of(
                Arguments.of("DEFINE a 5", new ArrayList<String>(Arrays.asList("a", "5"))),
                Arguments.of("PUSH", new ArrayList<>()),
                Arguments.of("PUSH a b c", new ArrayList<String>(Arrays.asList("a", "b", "c"))),
                Arguments.of("*", new ArrayList<>()),
                Arguments.of("/", new ArrayList<>()),
                Arguments.of("+", new ArrayList<>()),
                Arguments.of("-", new ArrayList<>())
        );
    }
}