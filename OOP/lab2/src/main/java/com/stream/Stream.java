package com.stream;

import java.io.*;

public class Stream {
    private InputStream in;

    public Stream(String[] args)   {
        try {
            if (args.length != 0) this.in = new FileInputStream(args[0]);
            else this.in = System.in;
        } catch (FileNotFoundException ex){
            System.err.println("I can't open " + args[0] + ". I will use stdin");
            this.in = System.in;
        }
    }

    public InputStream getIn(){
        return this.in;
    }

}
