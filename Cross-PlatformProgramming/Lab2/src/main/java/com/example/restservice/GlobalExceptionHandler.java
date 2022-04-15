package com.example.restservice;

import org.jetbrains.annotations.NotNull;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;

@ControllerAdvice
public class GlobalExceptionHandler {
	@ExceptionHandler(value = AbsentParameterException.class)
	public ResponseEntity<String> AbsentParameterExceptionHandler(@NotNull AbsentParameterException exception) {
		LoggingController.errorLog("Absent Parameter Exception");
		return new ResponseEntity<>(exception.getMessage(), HttpStatus.BAD_REQUEST);
	}
	@ExceptionHandler(value = EmptyParameterException.class)
	public ResponseEntity<String> EmptyParameterExceptionHandler(EmptyParameterException exception) {
		LoggingController.errorLog("Empty Parameter Exception");
		return new ResponseEntity<>(exception.getMessage(), HttpStatus.BAD_REQUEST);
	}
	@ExceptionHandler(value = InappropriateParameterException.class)
	public ResponseEntity<String> InappropriateParameterExceptionHandler(InappropriateParameterException exception) {
		LoggingController.errorLog("Inappropriate Parameter Exception");
		return new ResponseEntity<>(exception.getMessage(), HttpStatus.BAD_REQUEST);
	}
	@ExceptionHandler(value = NegativeParameterException.class)
	public ResponseEntity<String> NegativeParameterExceptionHandler(NegativeParameterException exception) {
		LoggingController.errorLog("Negative Parameter Exception");
		return new ResponseEntity<>(exception.getMessage(), HttpStatus.BAD_REQUEST);
	}
	@ExceptionHandler(value = Exception.class)
	public ResponseEntity<String> DefaultExceptionHandler(Exception exception) {
		LoggingController.errorLog("Unknown Exception");
		LoggingController.warnLog("Exception may be left unhandled!");
		return new ResponseEntity<>(exception.getMessage(), HttpStatus.INTERNAL_SERVER_ERROR);
	}
}
