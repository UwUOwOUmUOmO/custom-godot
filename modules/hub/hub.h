// #ifndef HUB_H
// #define HUB_H

#pragma once

#include "core/object.h"
#include "core/ustring.h"
#include "core/array.h"
#include "core/dictionary.h"
#include "core/print_string.h"

class Hub : public Object {
	GDCLASS(Hub, Object);
private:
	bool trace_stack = true;
	bool allow_output = true;
	bool allow_debug = true;

	void push_stack(const Array& stack);
protected:
	static Hub* singleton;
	static void _bind_methods();
public:
	Hub();
	~Hub() = default;
	static Hub* get_singleton() { return singleton; }

	void error_check(int code, const Array& stack = Array());
	void print_fatal(const String& err, const Array& stack = Array());
	void print_warning(const String& err, const Array& stack = Array());
	void print_debug(const String& err, const Array& stack = Array());
	void print_custom(const String& flag, const String& err, const Array& stack = Array());
};

// #endif