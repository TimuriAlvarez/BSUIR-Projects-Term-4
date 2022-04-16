package com.example.restservice;

import org.springframework.beans.factory.annotation.Autowired;
import java.util.HashMap;

public final class CalculatorCache {
	@Autowired
	static HashMap<Double, Double> hashMap = new HashMap<>();
	public static double meters2inches(String value) {
		LoggingController.debug("CalculatorCacheMap.meters2inches");
		double meters = CalculatorService.String2double("/meters", value);
		if (!hashMap.containsKey(meters))
			hashMap.put(meters, CalculatorService.meters2inches(meters));
		return hashMap.get(meters);
	}
	private static double getHashMapKey(double value) {
		LoggingController.warn("CalculatorCacheMap.getHashMapKey");
		for (double key:
			hashMap.keySet()) {
			if (hashMap.get(key).equals(value)) return key;
		}
		throw new HashMapKeyAbsenceException(value);
	}
	public static double inches2meters(String value) {
		LoggingController.debug("CalculatorCacheMap.inches2meters");
		double inches = CalculatorService.String2double("/inches", value);
		if (!hashMap.containsValue(inches))
			hashMap.put(CalculatorService.inches2meters(inches), inches);
		return getHashMapKey(inches);
	}
}
