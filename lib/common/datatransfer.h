#ifndef COMMON_DATA_TRANSFER_H_
#define COMMON_DATA_TRANSFER_H_

namespace hdfs {

enum {
  kDataTransferVersion = 28,
};

enum Operation {
  kWriteBlock = 80,
  kReadBlock  = 81,
};

}

#endif
