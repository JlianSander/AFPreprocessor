#ifndef ENUMS_H
#define ENUMS_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdexcept>

#include <iostream>

/// <summary>
/// Abbreviations of the different types of tasks, which the solver can solve
/// </summary>
enum task { DC, DS, SE, UNKNOWN_TASK };

/// <summary>
/// Return values of the preprocessor, indicating if the preprocessor solved the problem, and if so to what conclusion
/// </summary>
enum acceptance_result { accepted, rejected, unknown };

/// <summary>
/// Abbreviations of the different file formats, that the solver can handle
/// </summary>
enum format {I23, TGF, UNKNOWN_FORMAT};

using namespace std;

/// <summary>
/// This class is responsible for converting to and from Enum-Data-Types.
/// </summary>
class Enums {
public:

	/// <summary>
	/// This method converts the specified string into a file format.
	/// </summary>
	/// <param name="format_abbreviation">String containing the abbreviation of the file format as used in the enum.</param>
	/// <returns>File format corresponding to the specified string.</returns>
	static format string_to_format(string format_abbreviation);
};

#endif