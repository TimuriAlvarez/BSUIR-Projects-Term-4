package com.example.restservice;

public class AbsentParameterException extends RuntimeException {
	final private String message;
	public AbsentParameterException(String source) {
		this.message = "EXCEPTION: The absence of input parameter was caught in " + source;
	}
	public String getMessage() {
		return message;
	}
}
