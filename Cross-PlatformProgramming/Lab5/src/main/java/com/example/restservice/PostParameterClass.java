package com.example.restservice;

/**
 * Class used for parsing JSON as a sequence of POST-request parameters.
 */
public class PostParameterClass {
	/**
	 * POST-request parameter fields.
	 */
	final private String units;
	final private double value;
	/**
	 * POST-request parameter constructor.
	 */
	public PostParameterClass(String units, double value) {
		this.units = units;
		this.value = value;
	}
	/**
	 * POST-request parameter getters.
	 */
	public String getUnits() {
		return units;
	}
	public double getValue() {
		return value;
	}
}
