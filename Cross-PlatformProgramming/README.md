# Cross-platform Programming ```LAB```

| Information |                            |
|-------------|----------------------------|
| Year        | 2nd                        |
| Term        | 4th                        |
| Discipline  | Cross-platform Programming |
| Labs        | 1 - 4                      |
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

# Lab 2

## Error logging/handling

### Terms of reference

1. Add validation for the input parameters returning 400 HTTP error in case of empty or incorrect params provided
2. Add internal errors handling returning 500 HTTP error code in case of internal service exception/error
3. Add logging of all process steps and errors (use different log levels for errors and debug messages)
4. Add unit test for your service checking happy path and exceptional cases

# Lab 3

## Collections intro, project structure

### Terms of reference

1. Add simple cache for your service as in-memory Map where key is an input parameter and value is calculation results. This Map (cache) should be stored as a separate class (bean). Use dependencies injection mechanism of Spring Framework (autowiring) for adding cache to your service.
2. Web service should check cache to get calculation results from it first, if there are no calculation results for input parameter yet, do the calculation and put it into the cache before returning results in response.

# Lab 4

## Concurrency

### Terms of reference

1. Add a new service (Counter) which calculates number of your main service calls and returns the number when requested. Counter should be implemented as a separate thread safe bean with synchronized access.
2. Create high load test for your main service using JMeter, Postman or any other tool. The load test should make thousands of calls in short period of time. Then make sure that Counter correctly calculates number of service calls done by the load test.

# Lab 5
## Functional programming with Java 8
### Terms of reference
# Lab 6
## Functional filtering and mapping
### Terms of reference
# Lab 7
## Data persistence
### Terms of reference
# Lab 8
## Asynchronous calls
### Terms of reference

# Tests

All labs can be tested by running ```TESTS```.

# Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

# Copyright

This repository is under exclusive copyright.

I do grant each User of GitHub a nonexclusive, worldwide license to use, display, and perform My Content through the GitHub Service and to reproduce My Content solely on GitHub as permitted through GitHub's functionality but that is all. No other licences are provided for Users of GitHub.

© All rights reserved, 2022
