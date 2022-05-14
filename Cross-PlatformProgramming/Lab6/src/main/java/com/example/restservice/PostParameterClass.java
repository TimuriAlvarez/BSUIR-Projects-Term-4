package com.example.restservice;

/**
 * Record used for parsing JSON as a sequence of POST-request parameters.
 * @param units POST-request parameter field "units".
 * @param value POST-request parameter field "value".
 */
public record PostParameterClass(String units, double value) {
    /**
     * POST-request parameter getters.
     */
    public String units() {
        if (units == null) throw new UnitsAbsenceException();
        return units;
    }

}
