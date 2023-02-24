package com.main;
import com.calculator.Calculator;
import com.stream.Stream;

public class Main {
    public static void main(String[] args) {
        Stream stream = new Stream(args);
        Calculator calculator = new Calculator(stream.getIn());
        calculator.start();
    }
}