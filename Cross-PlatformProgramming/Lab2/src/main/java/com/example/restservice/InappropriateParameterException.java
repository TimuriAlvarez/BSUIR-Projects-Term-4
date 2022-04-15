package com.example.restservice;

public class InappropriateParameterException extends RuntimeException {
	final private String message;
	public InappropriateParameterException(String source, String parameter) {
		this.message = "EXCEPTION: Inappropriate input parameter '" + parameter + "' was caught in " + source;
	}
	public String getMessage() {
		return message;
	}
}
