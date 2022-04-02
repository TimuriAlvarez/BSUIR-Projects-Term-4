package com.example.restservice;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;

@ControllerAdvice
public class GlobalExceptionHandler {
	//private static final String empty_parameter = "Bad request was detected: Empty parameter was provided.";

	@ExceptionHandler(value = NegativeParameterException.class)
	public ResponseEntity NegativeParameterExceptionHandler(NegativeParameterException exception) {
		LoggingController.errorLog(exception.getMessage());
		return new ResponseEntity(exception.getMessage(), HttpStatus.BAD_REQUEST);
	}

	@ExceptionHandler(value = Exception.class)
	public ResponseEntity DefaultExceptionHandler(Exception exception) {
		LoggingController.errorLog(exception.getMessage());
		return new ResponseEntity(exception.getMessage(), HttpStatus.INTERNAL_SERVER_ERROR);
	}
}
