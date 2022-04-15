package com.example.restservice;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

/**
 * Controller that gets user's url-request and sends appropriate response.
 */
@RestController
public class CalculatorController {
	/**
	 * From meter to inch converter.
	 * @param meters real, not negative value of meters.
	 * @return String that contains meters and their value in inches.
	 */
	@GetMapping("/meters")
	public String calculatorMeters(@RequestParam("value") double meters) {
		// The length can't be negative
		if (meters < 0) throw new RuntimeException();
		return "" + meters + " meter(s) is " + Calculator.meter2inch(meters) + " inch(es).";
	}
	/**
	 * From inch to meter converter.
	 * @param inches real, not negative value of inches.
	 * @return String that contains inches and their value in meters.
	 */
	@GetMapping("/inches")
	public String calculatorInches(@RequestParam("value") double inches) {
		// The length can't be negative
		if (inches < 0) throw new RuntimeException();
		return "" + inches + " inch(s) is " + Calculator.inch2meter(inches) + " meter(s).";
	}
}