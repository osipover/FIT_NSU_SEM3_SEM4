package com.context;

import java.util.EmptyStackException;
import java.util.HashMap;
import java.util.Stack;
import java.util.Map;

public class Context {
        private Stack<Double> stack;
        private Map<String, Double> defines;

        public Context() {
                this.defines = new HashMap<String, Double>();
                this.stack = new Stack<Double>();
        }

        public Double getValue(String definition) {
                return this.defines.get(definition);
        }

        public void define(String definition, Double value){
                this.defines.put(definition, value);
        }

        public Double pop() throws EmptyStackException {
                return this.stack.pop();
        }

        public void push(Double value){
                this.stack.push(value);
        }

        public Double getLastArgument() throws EmptyStackException{
                return this.stack.peek();
        }
}
