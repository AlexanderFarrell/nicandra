#pragma once

#include <optional>
template <class OkT, class ErrorT> class Result {
  private:
  	union {
        OkT ok;
        ErrorT err;
    } value;

    bool is_value_ok;

  public:
    bool is_ok() {
		return this->is_value_ok;
	}
    const OkT &get_value() {
		return this->value.ok;
	}
    const ErrorT &get_error() { return this->value.err; }

    static Result<OkT, ErrorT> with_error(const ErrorT& error) {
      Result r;
      r.value.err = error;
      r.is_value_ok = false;
      return r;
    }

    static Result<OkT, ErrorT> with_ok(const OkT &value) {
      Result r;
      r.value.ok = value;
      r.is_value_ok = true;
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