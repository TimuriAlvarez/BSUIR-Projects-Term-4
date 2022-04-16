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
	 * @param value Value that should be converted.
	 * @return The value converted to double.
	 */
	public static double String2double(String value) {
		if (value == null) throw new RuntimeException();
		if (value.isEmpty()) throw new RuntimeException();

		double result = Double.parseDouble(value);
		if (result < 0) throw new RuntimeException();

		return result;
	}
	/**
	 * From meter to inch converter.
	 * @param meters Value of meters.
	 * @return Value of inches.
	 */
	public static double meters2inches(double meters) {
		return meters * coefficient;
	}
	/**
	 * From inch to meter converter.
	 * @param inches Value of inches.
	 * @return Value of meters.
	 */
	public static double inches2meters(double inches) {
		return inches / coefficient;
	}
}
