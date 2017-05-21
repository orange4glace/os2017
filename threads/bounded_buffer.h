// bounded_buffer.h

#ifndef BOUNDED_BUFFER_H_
#define BOUNDED_BUFFER_H_

#include "copyright.h"
#include "thread.h"
#include "list.h"
#include "synch.h"
#include "main.h"

class BoundedBuffer {

  public:

    BoundedBuffer(unsigned int max_size);
    ~BoundedBuffer();

    int Read(void* data, unsigned int size);
    int Write(void* data, unsigned int size);

    void Close();

    void SelfTest();
    
  private:
    
    unsigned int max_size_;
    unsigned int size_;
    Semaphore producer_;
    Semaphore consumer_;
    Lock mutex_;

    char* buffer_;
    unsigned int buffer_index_;

    bool closed_;

};

#endif