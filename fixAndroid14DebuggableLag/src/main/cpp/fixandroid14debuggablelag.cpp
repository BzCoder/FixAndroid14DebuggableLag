#include <jni.h>
#include <string>
#include <android/log.h>
#include "shadowhook.h"


template<typename T>
int findOffset(void *start, int regionStart, int regionEnd, T value) {

    if (NULL == start || regionEnd <= 0 || regionStart < 0) {
        return -1;
    }
    char *c_start = (char *) start;

    for (int i = regionStart; i < regionEnd; i += 4) {
        T *current_value = (T *) (c_start + i);
        if (value == *current_value) {

            return i;
        }
    }
    return -2;
}


extern "C"
JNIEXPORT void JNICALL
Java_me_github_fixandroid14debuggablelag_FixTools_fixAndroid14DebuggableLag(JNIEnv *env,
                                                                            jobject thiz) {
    void *handler = shadowhook_dlopen("libart.so");
    void **instance_ = static_cast<void **>(shadowhook_dlsym(handler,
                                                             "_ZN3art7Runtime9instance_E"));

    jobject
    (*getSystemThreadGroup)(void *runtime) =(jobject (*)(void *runtime)) shadowhook_dlsym(handler,
                                                                                          "_ZNK3art7Runtime20GetSystemThreadGroupEv");

    void
    (*UpdateEntrypointsForDebuggable)(void *instrumentation) = (void (*)(void *i)) shadowhook_dlsym(
            handler,
            "_ZN3art15instrumentation15Instrumentation30UpdateEntrypointsForDebuggableEv");

    if (getSystemThreadGroup == nullptr || UpdateEntrypointsForDebuggable == nullptr) {
        __android_log_print(ANDROID_LOG_DEBUG, "bzbz1111", "getSystemThreadGroup  faile");
        shadowhook_dlclose(handler);
        return;
    }
    jobject thread_group = getSystemThreadGroup(*instance_);
    int vm_offset = findOffset(*instance_, 0, 4000, thread_group);
    if (vm_offset < 0) {
        __android_log_print(ANDROID_LOG_DEBUG, "bzbz1111", "vm_offset not found");
        shadowhook_dlclose(handler);
        return;
    }

    void (*setRuntimeDebugState)(void *instance_, int r) =(void (*)(void *runtime,
                                                                    int r)) shadowhook_dlsym(
            handler, "_ZN3art7Runtime20SetRuntimeDebugStateENS0_17RuntimeDebugStateE");

    if (setRuntimeDebugState != nullptr) {
        setRuntimeDebugState(*instance_,
                             0);
    }
    void *instrumentation = reinterpret_cast<void *>(reinterpret_cast<char *>(*instance_) +
                                                     vm_offset - 368 );

    UpdateEntrypointsForDebuggable(instrumentation);
    setRuntimeDebugState(*instance_,
                         2);
    shadowhook_dlclose(handler);
    __android_log_print(ANDROID_LOG_DEBUG, "bzbz1111", "bootImageNterp success");
}