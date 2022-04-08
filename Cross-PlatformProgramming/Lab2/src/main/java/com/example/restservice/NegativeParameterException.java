package com.example.restservice;

public class NegativeParameterException extends RuntimeException {
	private String message;
	public NegativeParameterException(String source, double parameter) {
		this.message = "Negative input parameter '" + parameter + "' was caught in " + source;
	}
	public String getMessage() {
		return message;
	}
}
