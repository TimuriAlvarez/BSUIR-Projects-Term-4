package com.example.restservice;

import org.springframework.stereotype.Service;
import java.util.HashMap;

/**
 * Service class that provides application caching.
 */
@Service(value = "CalculatorCacheService")
public final class CalculatorCacheService {
	/**
	 * HashMap that contains cache.
	 */
	static final HashMap<Double, Double> hashMap = new HashMap<>();

	/**
	 * Cache checker for meters.
	 * Calls a conversion from CalculatorService class and puts the result as a record in HashMap.
	 * @param value Meters.
	 * @return Inches.
	 */
	public double meters2inches(String value) {
		LoggingRestController.debug("CalculatorCacheMap.meters2inches");
		double meters = CalculatorLogicService.String2double("/meters", value);
		if (!hashMap.containsKey(meters))
			hashMap.put(meters, CalculatorLogicService.meters2inches(meters));
		return hashMap.get(meters);
	}
	/**
	 * Getter for key from HashMap.
	 * @param value Actual HashMap value that must already be in the HashMap.
	 * @return Key value.
	 */
	private double getHashMapKey(double value) {
		LoggingRestController.warn("CalculatorCacheMap.getHashMapKey");
		for (double key:
			hashMap.keySet()) {
			if (hashMap.get(key).equals(value)) return key;
		}
		throw new HashMapKeyAbsenceException(value);
	}
	/**
	 * Cache checker for inches.
	 * Calls a conversion from CalculatorService class and puts the result as a record in HashMap.
	 * @param value Inches.
	 * @return Meters.
	 */
	public double inches2meters(String value) {
		LoggingRestController.debug("CalculatorCacheMap.inches2meters");
		double inches = CalculatorLogicService.String2double("/inches", value);
		if (!hashMap.containsValue(inches))
			hashMap.put(CalculatorLogicService.inches2meters(inches), inches);
		return getHashMapKey(inches);
	}
}
