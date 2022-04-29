package com.example.restservice;

/**
 * Exception class for all application exceptions.
 */
class CalculatorException extends RuntimeException {
	/**
	 * Exception label.
	 */
	static final private String exception = "Run-time exception: ";
	/**
	 * Exception type field.
	 */
	final private String type;
	/**
	 * Exception location field.
	 */
	final private String location;
	/**
	 * Exception constructor.
	 * @param type Exception type.
	 * @param location Exception location.
	 */
	public CalculatorException(String type, String location) {
		LoggingRestController.logDebug("CalculatorException.CalculatorException");
		this.type = type;
		this.location = location;
	}
	/**
	 * Method for getting exception message.
	 * @return Exception message.
	 */
	@Override
	public String getMessage() {
		LoggingRestController.logDebug("CalculatorException.getMessage");
		return getType() + " was caught in " + location + ".";
	}
	/**
	 * Method for getting exception type.
	 * @return Exception type.
	 */
	public String getType() {
		LoggingRestController.logDebug("CalculatorException.getType");
		return exception + type;
	}
}

/**
 * Exception class for input parameter absence.
 */
class ParameterAbsenceException extends CalculatorException {
	public ParameterAbsenceException(String location) {
		super("The absence of input parameter", location);
		LoggingRestController.logDebug("ParameterAbsenceException.ParameterAbsenceException");
	}
}

/**
 * Exception class for empty input parameter.
 */
class EmptyParameterException extends CalculatorException {
	EmptyParameterException(String location) {
		super("Empty input parameter", location);
		LoggingRestController.logDebug("EmptyParameterException.EmptyParameterException");
	}
}

/**
 * Exception class for inappropriate input parameter.
 */
class InappropriateParameterException extends CalculatorException  {
	public InappropriateParameterException(String location, String parameter) {
		super("Inappropriate input parameter '" + parameter + "'", location);
		LoggingRestController.logDebug("InappropriateParameterException.InappropriateParameterException");
	}
}

/**
 * Exception class for negative input parameter.
 */
class NegativeParameterException extends CalculatorException {
	public NegativeParameterException(String location, String parameter) {
		super("Negative input parameter '" + parameter + "'", location);
		LoggingRestController.logDebug("NegativeParameterException.NegativeParameterException");
	}
}

/**
 * Exception class for HashMap key absence.
 */
class HashMapKeyAbsenceException extends CalculatorException {
	public HashMapKeyAbsenceException(double value) {
		super("The absence of HashMap key for value '" + value + "'", "application cache");
		LoggingRestController.logDebug("HashMapKeyAbsenceException.HashMapKeyAbsenceException");
	}
}

/**
 * Exception class for Units recognition exception.
 */
class UnitsRecognitionException extends CalculatorException {
	public UnitsRecognitionException(String units) {
		super("Units '" + units + "' recognition failure", "/calculator");
		LoggingRestController.logDebug("PostParameterException.PostParameterException");
	}
}
