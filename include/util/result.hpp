#pragma once

#include <optional>
#include <variant>

/**
* Holds either an OK value (if no errors) or an error value
* if there's an error. Alternative to using exceptions.
*/
template <class OkT, class ErrorT>
class Result {
private:
	/**
	* Holds either the OK or Error value.
	*/
	std::variant<OkT, ErrorT> value;

public:
	/**
	* Returns true if holding an OK value (no error), false otherwise.
	*/
	bool is_ok() { return std::holds_alternative<OkT>(this->value); }

	/**
	* Returns true if holding an error value, false otherwise
	*/
	bool is_err() { return !is_ok(); }

	/**
	* Gets the OK value from the variant. Throws if error. Check `is_ok()`
	* first if you're not sure.
	*/
	OkT &get_value() { return std::get<OkT>(this->value); }

	/**
	* Gets the ERROR value from the variant. Throws if error. Check `is_err()`
	* first if you're not sure.
	*/
	ErrorT &get_error() { return std::get<ErrorT>(this->value); }

	/**
	 * Creates a new Result with ok value.
	 */
	static Result<OkT, ErrorT> with_ok(const OkT &value) {
		Result r;
		r.value = value;
		return r;
	}

	/**
	* Creates a new Result with error value.
	*/
    static Result<OkT, ErrorT> with_error(const ErrorT& error) {
		Result r;
		r.value = error;
      	return r;
    }
};

// The below is made to allow for void to be added to the OK value
// of results. Like std::variant, we don't do the same for the error value.

/**
 * Holds either an OK value (if no errors) or an error value
 * if there's an error. Alternative to using exceptions.
 */
template <class ErrorT>
class Result<void, ErrorT> {
private:
	/**
	* Holds the error value if we have an error. 
	*/
	std::optional<ErrorT> err;

public:
	/**
	 * Returns true if holding an OK value (no error), false otherwise.
	 */
	bool is_ok() { return !this->err.has_value(); }

	/**
	 * Returns true if holding an error value, false otherwise
	 */
	bool is_err() { return this->err.has_value(); }

	/**
	 * Gets the OK value from the variant. Check `is_ok()`
	 * first if you're not sure.
	 */
	void get_value() { return; }

	/**
	 * Gets the ERROR value from the variant. Throws if error. Check `is_err()`
	 * first if you're not sure.
	 */
	ErrorT &get_error() { return this->err.value(); }

	/**
	 * Creates a new Result with ok value.
	 */
	static Result<void, ErrorT> with_ok() {
		Result r;
		r.err = std::nullopt;
		return r;
	}

	/**
	 * Creates a new Result with error value.
	 */
	static Result<void, ErrorT> with_error(const ErrorT &error) {
		Result r;
		r.err = error;
		return r;
	}
};