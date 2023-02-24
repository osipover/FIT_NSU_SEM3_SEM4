package com.context;

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
        public Map<String, Double> getDefines(){
                return this.defines;
        }
        public Stack<Double> getStack(){
                return this.stack;
        }
}
