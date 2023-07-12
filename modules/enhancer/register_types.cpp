#include "register_types.h"
#include "vfile_access.h"
#include "basic_scheduler.h"
#include "core/print_string.h"
#include "core/io/file_access_encrypted.h"
#include "core/io/file_access_memory.h"
#include "core/os/os.h"



static BasicScheduler* BasicSchedulerPtr = nullptr;
static SynchronizationPoint* SynchronizationPointPtr = nullptr;

void register_enhancer_types() {
	ClassDB::register_class<BasicScheduler>();
	BasicSchedulerPtr = memnew(BasicScheduler);
	SynchronizationPointPtr = new SynchronizationPoint();
	Engine::get_singleton()->add_singleton(Engine::Singleton("BasicScheduler", BasicScheduler::get_singleton()));
}
void unregister_enhancer_types() {
	memdelete(BasicSchedulerPtr);
	delete SynchronizationPointPtr;
}