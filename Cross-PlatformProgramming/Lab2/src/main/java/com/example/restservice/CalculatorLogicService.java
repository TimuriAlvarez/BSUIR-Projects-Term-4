package com.example.restservice;

import org.springframework.stereotype.Service;

/**
 * Service class that contains mathematical and logical rules of "meter-to-inch" and "inch-to-meter" conversions.
 */
@Service(value = "CalculatorLogicService")
public final class CalculatorLogicService {
	/**
	 * Service constant: conversion coefficient.
	 */
	private static final double coefficient = 39.37007874;
	/**
	 * Service method for conversion from String to double.
	 * Also validates parameter value, provided by parameter sender.
	 * @param location Location for exceptions.
	 * @param value Value that should be converted.
	 * @return The value converted to double.
	 */
	public static double String2double(String location, String value) {
		LoggingRestController.logDebug("CalculatorLogicService.String2double");
		if (value == null) throw new ParameterAbsenceException(location);
		if (value.isEmpty()) throw new EmptyParameterException(location);

		double result;
		try { result = Double.parseDouble(value); }
		catch (Exception exception) { throw new InappropriateParameterException(location, value); }
		if (result < 0) throw new NegativeParameterException(location, value);

		return result;
	}
	/**
	 * From meter to inch converter.
	 * @param meters Value of meters.
	 * @return Value of inches.
	 */
	public static double meters2inches(double meters) {
		LoggingRestController.logMethod("CalculatorLogicService.meters2inches");
		return meters * coefficient;
	}
	/**
	 * From inch to meter converter.
	 * @param inches Value of inches.
	 * @return Value of meters.
	 */
	public static double inches2meters(double inches) {
		LoggingRestController.logMethod("CalculatorLogicService.inches2meters");
		return inches / coefficient;
	}
}
