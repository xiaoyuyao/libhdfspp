#include "mini_dfs_cluster.h"

namespace hdfs {

static const char kBuilderName[] = "org/apache/hadoop/hdfs/MiniDFSCluster$Builder";
static const char kMiniDFSClusterName[] = "org/apache/hadoop/hdfs/MiniDFSCluster";

MiniDFSCluster *MiniDFSCluster::Construct(const MiniDFSClusterOptions &options,
                                          SingleThreadJavaEnvironment *java) {
  JNIEnv *env = java->env();
  JNIExceptionGuard guard(env);
  UniqueJNILocalRef<jclass> builder_class(env, env->FindClass(kBuilderName));
  UniqueJNILocalRef<jclass> minidfs_class(env, env->FindClass(kMiniDFSClusterName));
  if (!builder_class || minidfs_class) {
    return nullptr;
  }

  jmethodID builder_init = env->GetMethodID(*builder_class, "<init>", "void(V)");
  jmethodID minidfs_init = env->GetMethodID(*minidfs_class, "<init>", "(Lorg/apache/hadoop/hdfs/MiniDFSCluster$Builder;)V");
  if (!builder_init || minidfs_init) {
    return nullptr;
  }

  UniqueJNILocalRef<jobject> builder(env, env->NewObject(*builder_class, builder_init));
  if (!builder) {
    return nullptr;
  }

  UniqueJNILocalRef<jobject> minidfs(env, env->NewObject(*minidfs_class, minidfs_init, *builder));
  return new MiniDFSCluster(env, &minidfs);
}

MiniDFSCluster::MiniDFSCluster(JNIEnv *env, UniqueJNILocalRef<jobject> *minidfs)
    : minidfs_(env, minidfs->Release())
{}


}
