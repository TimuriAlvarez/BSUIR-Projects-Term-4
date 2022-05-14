package com.example.restservice;

import org.jetbrains.annotations.NotNull;
import org.springframework.http.*;
import org.springframework.web.bind.annotation.*;

/**
 * Controller class that handles all application exceptions.
 */
@ControllerAdvice
public class ExceptionHandlerAdvice {
	/**
	 * The handler for all exceptions from Calculator Exception class.
	 * @param exception Any of Calculator Exception class children.
	 * @return Response Entity which contains exception message and Http Status: BAD_REQUEST.
	 */
	@ExceptionHandler(value = CalculatorException.class)
	public ResponseEntity<String> CalculatorExceptionHandler(@NotNull CalculatorException exception) {
		LoggingRestController.logError(exception.getType());
		return new ResponseEntity<>(exception.getMessage(), HttpStatus.BAD_REQUEST);
	}
	/**
	 * The handler for all exceptions except of Calculator Exception class.
	 * @param exception Any exception.
	 * @return Response Entity which contains exception message and Http Status: INTERNAL_SERVER_ERROR.
	 */
	@ExceptionHandler(value = Exception.class)
	public ResponseEntity<String> DefaultExceptionHandler(@NotNull Exception exception) {
		LoggingRestController.logError("Unknown Exception");
		LoggingRestController.logError("Exception may be left unhandled!");
		return new ResponseEntity<>(exception.getMessage(), HttpStatus.INTERNAL_SERVER_ERROR);
	}
}
