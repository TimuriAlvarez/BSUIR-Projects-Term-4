package com.example.restservice;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

/**
 * Controller that gets user's url-request and sends appropriate response.
 */
@RestController(value = "CalculatorRestController")
public class CalculatorRestController {
	/**
	 * Message that stores the output result before returning it  as  a  response.
	 */
	private String message;
	/**
	 * Greetings page. Implemented just for fun.
	 * @return Greetings message.
	 */
	@GetMapping("/")
	public String calculatorGreetings() {
		message = "Greetings, traveller. Here you can convert meters to inches and vice versa: all you, need is a right page and the value. Available pages: /, /meters, /inches. Good luck there.";
		return message;
	}
	/**
	 * From meter to inch converter page.
	 * @param value real, not negative value of meters.
	 * @return String that contains meters and their value in inches.
	 */
	@GetMapping("/meters")
	public String calculator2inches(@RequestParam(value = "value", required = false) String value) {
		message = value + " meter(s) is " + CalculatorLogicService.meters2inches(CalculatorLogicService.String2double("/meters", value)) + " inch(es).";
		return message;
	}
	/**
	 * From inch to meter converter page.
	 * @param value real, not negative value of inches.
	 * @return String that contains inches and their value in meters.
	 */
	@GetMapping("/inches")
	public String calculator2meters(@RequestParam(value = "value", required = false) String value) {
		message = value + " inch(s) is " + CalculatorLogicService.inches2meters(CalculatorLogicService.String2double("/inches", value)) + " meter(s).";
		return message;
	}
}