package com.example.restservice;

public class NegativeParameterException extends RuntimeException {
	final private String message;
	public NegativeParameterException(String source, double parameter) {
		this.message = "EXCEPTION: Negative input parameter '" + parameter + "' was caught in " + source;
	}
	public String getMessage() {
		return message;
	}
}
