package com.example.restservice;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import static com.example.restservice.LoggingController.*;

/**
 * Controller that gets user's url-request and sends appropriate response.
 */
@RestController
public class CalculatorController {
	/**
	 * Greetings page. Implemented just for fun.
	 * @return Greetings message.
	 */
	@GetMapping("/")
	public String calculatorGreetings() {
		start("Greeting");
		end("Greeting");
		return "Greetings, traveller. Here you can convert meters to inches and vice versa: all you, need is a right page and the value. Available pages: /, /meters, /inches. Good luck there.";
	}
	/**
	 * From meter to inch converter page.
	 * @param value real, not negative value of meters.
	 * @return String that contains meters and their value in inches.
	 */
	@GetMapping("/meters")
	public String meters2inches(@RequestParam(value = "value", required = false) String value) {
		start("/meters");
		double inches = CalculatorCache.meters2inches(value);
		end("/meters");
		return value + " meter(s) is " + inches + " inch(es).";
	}
	/**
	 * From inch to meter converter page.
	 * @param value real, not negative value of inches.
	 * @return String that contains inches and their value in meters.
	 */
	@GetMapping("/inches")
	public String inches2meters(@RequestParam(value = "value", required = false) String value) {
		start("/inches");
		double meters = CalculatorCache.inches2meters(value);
		end("/inches");
		return value + " inch(s) is " + meters + " meter(s).";
	}
}