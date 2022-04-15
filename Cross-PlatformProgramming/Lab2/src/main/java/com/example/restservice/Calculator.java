package com.example.restservice;

/**
 * Service class that contains mathematical and logical rules of "meter-to-inch" and "inch-to-meter" conversions.
 */
public final class Calculator {
	/**
	 * Service constant: conversion coefficient.
	 */
	private static final double coefficient = 39.370_078_74;
	/**
	 * Service method for conversion from String to double.
	 * Also validates parameter value, provided by parameter sender.
	 * @param sender Page which has requested conversion.
	 * @param value Value that should be converted.
	 * @return The value converted to double.
	 */
	private static double String2double(String sender, String value) {
		if (value == null) throw new ParameterAbsenceException(sender);
		if (value.isEmpty()) throw new EmptyParameterException(sender);

		double result;
		try { result = Double.parseDouble(value); }
		catch (Exception exception) { throw new InappropriateParameterException(sender, value); }
		if (result < 0) throw new NegativeParameterException(sender, value);

		LoggingController.infoLog(LoggingController.DefaultLogs.String2doubleConversion);

		return result;
	}
	/**
	 * From meter to inch converter
	 * @param meters Value of meters
	 * @return Value of inches
	 */
	public static double meters2inches(String sender, String meters) {
		return String2double(sender, meters) * coefficient;
	}
	/**
	 * From inch to meter converter
	 * @param inches Value of inches
	 * @return Value of meters
	 */
	public static double inches2meters(String sender, String inches) {
		return String2double(sender, inches) / coefficient;
	}
}
