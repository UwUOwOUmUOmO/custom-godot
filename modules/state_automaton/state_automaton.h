#ifndef STATE_AUTOMATON_H
#define STATE_AUTOMATON_H

// #include "modules/state/state.h"
#include <string>

#include "modules/hub/hub.h"
#include "core/dictionary.h"
#include "core/list.h"
#include "core/variant.h"
#include "core/reference.h"
#include "core/ustring.h"
#include "core/string_name.h"
#include "core/script_language.h"
#include "core/ordered_hash_map.h"
#include "core/hash_map.h"

class State;
class PushdownAutomaton;
class StateAutomaton;

typedef OrderedHashMap<StringName, Ref<State>> StateHashMap;
typedef HashMap<String, Variant> BlackboardHashMap;

class State : public Reference {
	GDCLASS(State, Reference);
private:
	// Ref<PushdownAutomaton> pda;
	StringName state_name;

protected:
	static void _bind_methods();
public:
	State();
	~State();

	void internal_start(const Ref<StateAutomaton>& machine);
	StringName internal_poll(const Ref<StateAutomaton>& machine);
	void internal_finalize(const Ref<StateAutomaton>& machine);

	void set_state_name(const StringName& new_state_name);
	inline StringName get_state_name() const { return state_name; }
};

class PushdownAutomaton : public Reference {
	GDCLASS(PushdownAutomaton, Reference);
private:
	StateHashMap state_pool;

	bool terminated = false;
protected:
	static void _bind_methods();

	inline StateHashMap* get_state_pool() { return &state_pool; }
public:
	PushdownAutomaton();
	~PushdownAutomaton();
	
	virtual Ref<State> get_entry_state();
	virtual Ref<State> get_state_by_name(const StringName& state_name) const;
	virtual Ref<State> get_next_state(const StringName& from_state) const;
	virtual Ref<State> get_prev_state(const StringName& from_state) const;

	friend class StateAutomaton;

	virtual bool add_state(const Ref<State>& new_state);
	virtual bool remove_state(const StringName& state_name);

	virtual void set_termination(const bool& status);
	virtual inline bool is_terminated() const { return terminated; }

	virtual inline void clean_pool() { state_pool.clear(); }
	virtual Dictionary get_all_states() const;
	virtual inline int get_pool_size() const { return state_pool.size(); }
};

class StateAutomaton : public Reference {
	GDCLASS(StateAutomaton, Reference);
private:
	BlackboardHashMap blackboard;
	float delta_time = 0.0;
	bool debug_status = false;
	bool terminated = false;

	Variant client;
	Ref<PushdownAutomaton> pda;
protected:
	static void _bind_methods();
public:
	StateAutomaton();
	~StateAutomaton();
	
	void boot();
	void poll(const float& delta = 0.0);
	void finalize();

	void set_termination(const bool& status);
	inline bool is_terminated() const { return terminated; }

	void set_pda(const Ref<PushdownAutomaton>& new_pda);
	inline Ref<PushdownAutomaton> get_pda() const { return pda; }

	inline void enable_debug(const bool& debugging) { debug_status = debugging; }
	inline bool is_debugging() const { return debug_status; }

	inline float get_delta() const { return delta_time; }
	Variant blackboard_get(const String& what);
	void blackboard_set(const String& what, const Variant& with);

	inline void set_client(const Variant& new_client) { client = new_client; }
	inline Variant get_client() const { return client; }
};
#endif