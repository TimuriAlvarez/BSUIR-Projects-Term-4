package com.example.restservice;

public class EmptyParameterException extends RuntimeException {
	final private String message;
	public EmptyParameterException(String source) {
		this.message = "EXCEPTION: Empty input parameter was caught in " + source;
	}
	public String getMessage() {
		return message;
	}
}
