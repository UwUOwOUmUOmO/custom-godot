#ifndef RTSCOM_META_H
#define RTSCOM_META_H


#include "servers/physics_server.h"
#include "core/reference.h"
#include "core/string_name.h"
#include "core/script_language.h"
#include "core/print_string.h"

// #define USE_STL_WRAPPER
// #ifdef USE_STL_WRAPPER

#include <vector>
#include <stdexcept>
#include <memory>
#include <iterator>
template <class T> class WrappedVector {
private:
	std::shared_ptr<std::vector<T>> vec_ref;
public:
	_FORCE_INLINE_ WrappedVector() {
		vec_ref = std::make_shared<std::vector<T>>();
	}
	_FORCE_INLINE_ WrappedVector(const WrappedVector& vec) {
		vec_ref = vec.vec_ref;
	}
	_FORCE_INLINE_ WrappedVector(WrappedVector* vec) {
		vec_ref = vec->vec_ref;
	}
	_FORCE_INLINE_ WrappedVector(const std::vector<T>& real_vec) {
		vec_ref = std::make_shared<std::vector<T>>(real_vec);
	}
	_FORCE_INLINE_ WrappedVector(const std::initializer_list<T>& init_list) {
		vec_ref = std::make_shared<std::vector<T>>(init_list);
	}
	_FORCE_INLINE_ bool is_valid() const {
		return vec_ref.operator bool();
	}
	_FORCE_INLINE_ bool is_null() const { return !is_valid(); }
	_FORCE_INLINE_ bool operator==(const std::vector<T>& real_vec) const {
		ERR_FAIL_COND_V(is_null(), false);
		if (size() != real_vec.size()) return false;
		return std::equal(real_vec.begin(), real_vec.end(), vec_ref->begin());
	}
	_FORCE_INLINE_ bool operator==(const WrappedVector& vec) const {
		ERR_FAIL_COND_V(is_null(), false);
		if (size() != vec.size()) return false;
		return *this == (vec.vec_ref);
	}
	_FORCE_INLINE_ bool operator==(const std::initializer_list<T>& init_list) const {
		ERR_FAIL_COND_V(is_null(), false);
		if (size() != init_list.size()) return false;
		return *this == WrappedVector(init_list);
	}
	_FORCE_INLINE_ WrappedVector& operator=(const std::vector<T>& real_vec) {
		ERR_FAIL_COND_V(is_null(), *this);
		vec_ref->operator=(real_vec); return *this;
	}
	_FORCE_INLINE_ WrappedVector& operator=(const WrappedVector& vec) {
		ERR_FAIL_COND_V(is_null(), *this);
		vec_ref->operator=(vec->vec_ref); return *this;
	}
	_FORCE_INLINE_ WrappedVector& operator=(const std::initializer_list<T>& init_list) {
		ERR_FAIL_COND_V(is_null(), *this);
		vec_ref->operator=(std::vector<T>(init_list)); return *this;
	}
	_FORCE_INLINE_ size_t size() const {
		ERR_FAIL_COND_V(is_null(), 0);
		return vec_ref->size();
	}
	_FORCE_INLINE_ void push_back(const T& value) {
		ERR_FAIL_COND(is_null());
		vec_ref->push_back(value);
	}
	_FORCE_INLINE_ T& pop_back() {
		ERR_FAIL_COND_V(is_null(), *(new T()));
		T& re = vec_ref->operator[](size() - 1);
		vec_ref->pop_back();
		return re;
	}
	_FORCE_INLINE_ void insert(const int64_t& at, const T& value) {
		ERR_FAIL_COND(is_null());
		auto index = at;
		auto s = size();
		if (at < 0) index = s + at;
		ERR_FAIL_COND(index < 0);
		ERR_FAIL_COND(index >= s);
		vec_ref->insert(vec_ref->begin() + index, value);
	}
	_FORCE_INLINE_ T& operator[](int idx) {
		ERR_FAIL_COND_V(is_null(), *(new T()));
		auto index = idx;
		auto s = size();
		if (idx < 0) index = s + idx;
		ERR_FAIL_COND_V((index < 0), *(new T()));
		ERR_FAIL_COND_V(index >= s, *(new T()));
		return vec_ref->operator[](index);
	}
	_FORCE_INLINE_ operator bool() const {
		ERR_FAIL_COND_V(is_null(), false);
		return !empty();
	}
	_FORCE_INLINE_ const T& operator[](int idx) const {
		ERR_FAIL_COND_V(is_null(), *(new T()));
		auto index = idx;
		auto s = size();
		if (idx < 0) index = s + idx;
		ERR_FAIL_COND_V((index < 0), *(new T()));
		ERR_FAIL_COND_V(index >= s, *(new T()));
		return vec_ref->operator[](index);
	}
	// _FORCE_INLINE_ T& operator[](int64_t idx) {
	// 	auto index = idx;
	// 	auto s = size();
	// 	ERR_FAIL_COND_V((index < 0), *(new T()));
	// 	ERR_FAIL_COND(index >= s);
	// 	return vec_ref->operator[](index);
	// }
	_FORCE_INLINE_ int64_t find(const T& what, const int64_t& from = 0) const {
		ERR_FAIL_COND_V(is_null(), -1);
		if (empty()) return -1;
		int64_t iter = from;
		auto s = size();
		ERR_FAIL_COND_V_MSG(s < 0, -1, "Broken vector detected");
		// print_verbose(String("Finding item from index: ") + itos(from));
		// print_verbose(String("Finding item with whole size: ") + itos(s));
		for (; iter < s; iter += 1) {
			if (vec_ref->operator[](iter) == what) return iter;
		}
		return -1;
	}
	_FORCE_INLINE_ void remove(const int64_t& at) {
		ERR_FAIL_COND(is_null());
		if (empty()) return;
		auto index = at;
		auto s = size();
		if (at < 0) index = s + at;
		ERR_FAIL_COND(index < 0);
		ERR_FAIL_COND(index >= s);
		// print_verbose(String("Removing item at raw index: ") + itos(at));
		// print_verbose(String("Removing item at index: ") + itos(index));
		// print_verbose(String("Removing item with whole size: ") + itos(s));
		vec_ref->erase(vec_ref->begin() + index);
	}
	_FORCE_INLINE_ void erase(const T& what) {
		ERR_FAIL_COND(is_null());
		if (empty()) return;
		// print_verbose(String("Erasing..."));
		auto index = find(what);
		if (index == -1) return;
		// print_verbose(String("Erasing item at index: ") + itos(index));
		remove(index);
	}
	_FORCE_INLINE_ void change_pointer(const WrappedVector& vec){
		vec_ref = vec.vec_ref;
	}
	_FORCE_INLINE_ void change_pointer(const std::shared_ptr<std::vector<T>>& ptr){
		vec_ref = ptr;
	}
	_FORCE_INLINE_ void make_unique() {
		change_pointer(std::make_shared<std::vector<T>>());
	}
	_FORCE_INLINE_ void clear() {
		ERR_FAIL_COND(is_null());
		vec_ref->clear();
	}
	_FORCE_INLINE_ bool empty() const {
		ERR_FAIL_COND_V(is_null(), true);
		return vec_ref->empty();
	}
	_FORCE_INLINE_ void copy(const WrappedVector& vec){
		ERR_FAIL_COND(is_null());
		clear();
		auto other = vec.vec_ref;
		for (auto iter : *other){
			push_back(iter);
		}
	}
	_FORCE_INLINE_ void copy(const std::vector<T>& vec){
		ERR_FAIL_COND(is_null());
		clear();
		for (auto iter : vec){
			push_back(iter);
		}
	}
	_FORCE_INLINE_ void duplicate(const WrappedVector& vec){
		make_unique();
		copy(vec);
	}
	_FORCE_INLINE_ void duplicate(const std::vector<T>& vec){
		make_unique();
		copy(vec);
	}
	_FORCE_INLINE_ WrappedVector<T> make_duplicate() const{
		WrappedVector<T> new_dup();
		new_dup.duplicate(*this);
		return new_dup;
	}
	_FORCE_INLINE_ std::weak_ptr<std::vector<T>> get_weakptr() const {
		std::weak_ptr<std::vector<T>> ptr = vec_ref;
		return ptr;
	}
};

// #endif


#define USE_STL_VECTOR
// #define STL_WRAPPER_SAME_API

#if defined(STL_WRAPPER_SAME_API) && defined(USE_STL_WRAPPER)
#define VECTOR WrappedVector
#define VEC_FIND(vec, elem, i)                                             \
	auto iter = std::find(vec.begin(), vec.end(), elem);                   \
	i = (iter == vec.end() ? -1 : iter - vec.begin());
#define VEC_HAS(vec, elem){                                                \
	int i = 0;                                                             \
	VEC_FIND(vec, elem, i);                                                \
	return i != -1;                                                        \
}
#define VEC_ERASE(vec, elem)                                               \
{                                                                          \
	auto __size = vec.size();                                              \
	for (unsigned int __i = 0; __i < __size; __i++){                       \
		if (vec[__i] == elem){                                             \
			auto iter = vec.begin() + __i;                                 \
			vec.erase(iter);                                               \
			break;                                                         \
		}                                                                  \
	}                                                                      \
}
#elif defined(USE_STL_WRAPPER) && !defined(STL_WRAPPER_SAME_API)
#define VECTOR WrappedVector
#define VEC_FIND(vec, elem, i) i = vec.find(elem)
#define VEC_HAS(vec, elem) { return (vec.find(elem) != -1); }
#define VEC_ERASE(vec, elem) { vec.erase(elem); }
#define VEC_REMOVE(vec, idx) vec.remove(idx);
#elif defined(USE_STL_VECTOR)

#include <vector>
#define VECTOR std::vector
#define VEC_FIND(vec, elem, i)                                             \
	auto iter = std::find(vec.begin(), vec.end(), elem);                   \
	i = (iter == vec.end() ? -1 : iter - vec.begin());
#define VEC_HAS(vec, elem){                                                \
	int i = 0;                                                             \
	VEC_FIND(vec, elem, i);                                                \
	return i != -1;                                                        \
}
#define VEC_ERASE(vec, elem)                                               \
{                                                                          \
	auto __size = vec.size();                                              \
	for (unsigned int __i = 0; __i < __size; __i++){                       \
		if (vec[__i] == elem){                                             \
			auto iter = vec.begin() + __i;                                 \
			vec.erase(iter);                                               \
			break;                                                         \
		}                                                                  \
	}                                                                      \
}
#define VEC_REMOVE(vec, idx) vec.erase(vec.begin() + idx)
#else
#include "core/vector.h"
#define VECTOR Vector
#define VEC_FIND(vec, elem, i)                                             \
	i = vec.find(elem);
#define VEC_HAS(vec, elem)                                                 \
	{ return vec.find(elem) != -1; }
#define VEC_ERASE(vec, elem)                                               \
	{ vec.erase(elem); }
#define VEC_REMOVE(vec, idx) vec.remove(idx)
#endif

#define VEC2GDARRAY(vec, arr) {                                            \
	for (uint32_t __i = 0, __size = vec.size(); __i < __size; __i++){      \
		arr.push_back(vec[__i]);                                           \
	}                                                                      \
}

#define rcsnew(classptr) new classptr
#define rcsdel(ptr) { delete ptr; ptr = nullptr; }
// #define rcsnew(ptr) memnew(ptr)
// #define rcsdel(ptr) memdelete(ptr);

enum CombatantStatus {
	UNINITIALIZED,
	STANDBY,
	ACTIVE,
	DESTROYED,
};

class RID_RCS;

class RCSChip : public Reference{
	GDCLASS(RCSChip, Reference);
private:
	RID host;

	void callback(const float& delta);
protected:
	virtual void internal_callback(const float& delta) {};
	virtual void internal_init() {};
	static void _bind_methods();
public:
	RCSChip();
	~RCSChip();

	friend class RID_RCS;

	void set_host(const RID& r_host);
	_FORCE_INLINE_ RID get_host() const { return host; }
};

#endif
