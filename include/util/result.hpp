#pragma once

#include <optional>
#include <variant>
template <class OkT, class ErrorT>
class Result {
  private:
	std::variant<OkT, ErrorT> value;

  public:
    bool is_ok() {
		return std::holds_alternative<OkT>(this->value);
	}
    const OkT &get_value() {
		return std::get<OkT>(this->value);
	}
	const ErrorT &get_error() {
		return std::get<ErrorT>(this->value);
	}

    static Result<OkT, ErrorT> with_error(const ErrorT& error) {
		Result r;
		r.value = error;
      	return r;
    }

    static Result<OkT, ErrorT> with_ok(const OkT &value) {
		Result r;
		r.value = value;
    	return r;
	}
};

template <class ErrorT>
class Result<void, ErrorT> {
private:
  std::optional<ErrorT> err;

public:
  bool is_ok() { return !this->err.has_value(); }
  void get_value() { return; }
  const ErrorT &get_error() { return this->err.value(); }

  static Result<void, ErrorT> with_error(const ErrorT &error) {
    Result r;
    r.err = error;
    return r;
  }

  static Result<void, ErrorT> with_ok() {
    Result r;
    r.err = std::nullopt;
    return r;
  }
};