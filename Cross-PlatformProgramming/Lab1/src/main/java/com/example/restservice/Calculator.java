package com.example.restservice;

/**
 * Service class that contains mathematical rules of meter-inch and inch-meter conversions.
 */
public final class Calculator {
	private static final double coefficient = 39.370_078_74;
	/**
	 * From meter to inch converter
	 * @param meters Value of meters
	 * @return Value of inches
	 */
	public static double meter2inch(double meters) {
		return meters * coefficient;
	}
	/**
	 * From inch to meter converter
	 * @param inches Value of inches
	 * @return Value of meters
	 */
	public static double inch2meter(double inches) {
		return inches / coefficient;
	}
}
