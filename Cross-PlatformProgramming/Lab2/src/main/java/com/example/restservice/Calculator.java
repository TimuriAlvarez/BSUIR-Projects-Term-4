package com.example.restservice;

import org.jetbrains.annotations.NotNull;

/**
 * Service class that contains mathematical rules of meter-inch and inch-meter conversions.
 */
public final class Calculator {
	private static final double coefficient = 39.370_078_74;
	public static double String2double(@NotNull String sender, String value) {
		if (value == null) throw new AbsentParameterException(sender);
		if (value.isEmpty()) throw new EmptyParameterException(sender);

		double result;
		try { result = Double.parseDouble(value); }
		catch (Exception exception) { throw new InappropriateParameterException(sender, value); }
		if (result < 0) throw new NegativeParameterException(sender, result);

		LoggingController.infoLog(LoggingController.DefaultLogs.String2doubleConversion);

		return result;
	}
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
