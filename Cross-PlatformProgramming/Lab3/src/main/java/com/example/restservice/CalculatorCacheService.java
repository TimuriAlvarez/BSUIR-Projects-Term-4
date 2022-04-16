package com.example.restservice;

import org.springframework.stereotype.Component;
import org.springframework.stereotype.Service;
import java.util.HashMap;

/**
 * Service class that provides application caching.
 */
@Component
@Service(value = "CalculatorCacheService")
public final class CalculatorCacheService {
	/**
	 * HashMap that contains cache.
	 */
	HashMap<Double, Double> hashMap;
	/**
	 * Calculator Cache Service constructor.
	 * Initializes HashMap with a new HashMap() value.
	 */
	CalculatorCacheService() {
		this.hashMap = new HashMap<>();
	}
	/**
	 * Cache checker for meters.
	 * Calls a conversion from CalculatorService class and puts the result as a record in HashMap.
	 * @param value Meters.
	 * @return Inches.
	 */
	public double meters2inches(String value) {
		LoggingRestController.logDebug("CalculatorCacheMap.meters2inches");
		double meters = CalculatorLogicService.String2double("/meters", value);
		if (!hashMap.containsKey(meters))
			hashMap.put(meters, CalculatorLogicService.meters2inches(meters));
		return hashMap.get(meters);
	}
	/**
	 * Cache checker for inches.
	 * Calls a conversion from CalculatorService class and puts the result as a record in HashMap.
	 * @param value Inches.
	 * @return Meters.
	 */
	public double inches2meters(String value) {
		LoggingRestController.logDebug("CalculatorCacheMap.inches2meters");
		double inches = CalculatorLogicService.String2double("/inches", value);
		if (!hashMap.containsValue(inches))
			hashMap.put(CalculatorLogicService.inches2meters(inches), inches);
		return getHashMapKey(inches);
	}
	/**
	 * Getter for key from HashMap.
	 * @param value Actual HashMap value that must already be in the HashMap.
	 * @return Key value.
	 */
	private double getHashMapKey(double value) {
		LoggingRestController.logMethod("CalculatorCacheMap.getHashMapKey");
		for (double key:
			hashMap.keySet()) {
			if (hashMap.get(key).equals(value)) return key;
		}
		throw new HashMapKeyAbsenceException(value);
	}
}
