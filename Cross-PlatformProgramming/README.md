# Cross-platform Programming Labs

## General information

| Information |                            |
|-------------|----------------------------|
| Year        | 2nd                        |
| Term        | 4th                        |
| Discipline  | Cross-platform Programming |
| Quantity    | 8                          |
| OS          | Any (Web-application)      |

# Lab 1

## Intro

### Common terms of reference

1. Create and run locally simple web/REST service using any open-source example on Java stack: Spring/maven/gradle/Jersey/Spring MVC.
2. Create GET endpoint with input parameters as URL query params, performing calculation based on your Option, and returning results in JSON format.

## Meters Convertor

### Personal terms of reference

Flow:

* When: User inputs value to "Meters" input field
* Then: Presses "Meters to inches" button
* And: Value appears in "Inches" input field
* When: User inputs value to "Inches" input field
* Then: Presses "Inches to meters" button
* And: Value appears in "Meters" input field

Update: using JSON files is explicitly excluded from the terms, replaced by String class.

### Tests

The lab can be tested using Spring Boot Tests that are located [here](https://github.com/TimuriAlvarez/BSUIR-Projects-Term-4/blob/main/Cross-PlatformProgramming/Lab1/src/test/java/com/example/restservice/RestServiceApplicationTests.java "Lab 1 Tests").

# Lab 2

## Error logging/handling

### Terms of reference

1. Add validation for the input parameters returning 400 HTTP error in case of empty or incorrect params provided
2. Add internal errors handling returning 500 HTTP error code in case of internal service exception/error
3. Add logging of all process steps and errors (use different log levels for errors and debug messages)
4. Add unit test for your service checking happy path and exceptional cases

### Tests

The lab can be tested using Spring Boot Tests that are located [here](https://github.com/TimuriAlvarez/BSUIR-Projects-Term-4/blob/main/Cross-PlatformProgramming/Lab2/src/test/java/com/example/restservice/RestServiceApplicationTests.java "Lab 2 Tests").

# Lab 3

## Collections intro, project structure

### Terms of reference

1. Add simple cache for your service as in-memory Map where key is an input parameter and value is calculation results. This Map (cache) should be stored as a separate class (bean). Use dependencies injection mechanism of Spring Framework (autowiring) for adding cache to your service.
2. Web service should check cache to get calculation results from it first, if there are no calculation results for input parameter yet, do the calculation and put it into the cache before returning results in response.

### Tests

The lab can be tested using Spring Boot Tests that are located [here](https://github.com/TimuriAlvarez/BSUIR-Projects-Term-4/blob/main/Cross-PlatformProgramming/Lab3/src/test/java/com/example/restservice/RestServiceApplicationTests.java "Lab 3 Tests").

# Lab 4

## Concurrency

### Terms of reference

1. Add a new service (Counter) which calculates number of your main service calls and returns the number when requested. Counter should be implemented as a separate thread safe bean with synchronized access.
2. Create high load test for your main service using JMeter, Postman or any other tool. The load test should make thousands of calls in short period of time. Then make sure that Counter correctly calculates number of service calls done by the load test.

### Tests

The lab can be tested using Spring Boot Tests that are located [here](https://github.com/TimuriAlvarez/BSUIR-Projects-Term-4/blob/main/Cross-PlatformProgramming/Lab4/src/test/java/com/example/restservice/RestServiceApplicationTests.java "Lab 4 Tests").

# Lab 5

## Functional programming with Java 8

### Terms of reference

In scope of this practical task we need to try functional programming approach using Java 8 new features:

* Update initial service created in first practical task to have ability to process sequence (stream) of input parameters. Stream API and lambdas should be used for this.
* Add new POST method which should get sequence of input parameters (they can be passed as JSON data in request body, or as simple CSV file), validate them and call new service for processing bulk data. Result can be returned as JSON or CSV file.

### Tests

The lab can be tested using Spring Boot Tests that are located [here](https://github.com/TimuriAlvarez/BSUIR-Projects-Term-4/blob/main/Cross-PlatformProgramming/Lab5/src/test/java/com/example/restservice/RestServiceApplicationTests.java "Lab 5 Tests").

# Lab 6

## Functional filtering and mapping

### Terms of reference

In previous task we did bulk operation for a stream of input data. In this task we need to apply some statistics calculation using aggregation/reduction. Calculated statistic should be added into POST response data (either JSON or CSV file). Statistics should include:
 
* Total amount of input parameters (or pairs/triples of parameters) provided
* Total amount of input parameters (or pairs/triples of parameters) which produced incorrect result (were not valid)
* Maximum and minimum values from results calculated
* Result which was returned most times (most popular)

### Tests

The lab can be tested using Spring Boot Tests that are located [here](https://github.com/TimuriAlvarez/BSUIR-Projects-Term-4/blob/main/Cross-PlatformProgramming/Lab6/src/test/java/com/example/restservice/RestServiceApplicationTests.java "Lab 6 Tests").

# Lab 7

## Data persistence

### Terms of reference

* We are going to wire persistence layer for storage of inbound request data and outbound response. Feel free to pick whatever database that will satisfy your needs but be ready to explain your choice.
* Adjust your web service with ability to store all calculation results of the service in database or file using one of standard persistence framework (Spring Data/Hibernate/MyBatis).

### Tests

The lab can be tested using Spring Boot Tests that are located [here](https://github.com/TimuriAlvarez/BSUIR-Projects-Term-4/blob/main/Cross-PlatformProgramming/Lab7/src/test/java/com/example/restservice/RestServiceApplicationTests.java "Lab 7 Tests").

# Lab 8

## Asynchronous calls

### Terms of reference

* Improve your web-service by adding asynchronous call for main calculation service and providing REST call response containing auto-generated processID (random number, which should be used as a key to store calculation results in database) without waiting for the calculation results.
* All calculation results should be written into database (storage) within asynchronously called service. Add a rest endpoint to get calculation results from database by processID provided.

### Tests

The lab can be tested using Spring Boot Tests that are located [here](https://github.com/TimuriAlvarez/BSUIR-Projects-Term-4/blob/main/Cross-PlatformProgramming/Lab8/src/test/java/com/example/restservice/RestServiceApplicationTests.java "Lab 8 Tests").

# Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

# Copyright

This repository is under exclusive copyright.

I do grant each User of GitHub a nonexclusive, worldwide license to use, display, and perform My Content through the GitHub Service and to reproduce My Content solely on GitHub as permitted through GitHub's functionality but that is all. No other licences are provided for Users of GitHub.

© All rights reserved, 2022
