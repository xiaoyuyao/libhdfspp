#include "jni_helper.h"

namespace hdfs {

SingleThreadJavaEnvironment::SingleThreadJavaEnvironment(JavaVM *jvm, JNIEnv *env)
    : jvm_(jvm)
    , env_(env)
{}

SingleThreadJavaEnvironment::~SingleThreadJavaEnvironment() {
  jvm_->DestroyJavaVM();
}

SingleThreadJavaEnvironment *SingleThreadJavaEnvironment::Construct(const std::string &class_path) {
  JNIEnv *env;
  JavaVM *jvm;
  JavaVMOption option;
  option.optionString = const_cast<char*>(class_path.c_str());
  JavaVMInitArgs args;
  memset(&args, 0, sizeof(args));
  args.version = JNI_VERSION_1_6;
  args.nOptions = 1;
  args.options = &option;

  long status = JNI_CreateJavaVM(&jvm, reinterpret_cast<void**>(&env), &args);
  return status == JNI_ERR ? nullptr : new SingleThreadJavaEnvironment(jvm, env);
}

}
