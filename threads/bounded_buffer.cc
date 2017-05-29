// bounded_buffer.cpp
#include "bounded_buffer.h"

BoundedBuffer::BoundedBuffer(unsigned int max_size) :
	max_size_(max_size),
	consumer_("consumer", 0),
	producer_("producer", max_size),
	mutex_("prosumer_mutex"),
	closed_(false) {
	buffer_ = new char[max_size];
	buffer_index_ = 0;
}

BoundedBuffer::~BoundedBuffer() {
	delete buffer_;
}

int BoundedBuffer::Read(void* data, unsigned int size) {
	int ret = 0;
	for (uint i = 0; i < size; i ++) {
		if (closed_) break;
		consumer_.P();
		mutex_.Acquire();
		if (!closed_) {
			int index = buffer_index_ - size_ + max_size_;
			index %= max_size_;
			size_--;
			((char*)data)[i] = buffer_[index];
			ret ++;
			cout << "#### Read 1 byte" << endl;
		}
		mutex_.Release();
		producer_.V();
	}
	return ret;
}

int BoundedBuffer::Write(void* data, unsigned int size) {
	int ret = 0;
	for (uint i = 0; i < size; i ++) {
		if (closed_) break;
		producer_.P();
		mutex_.Acquire();
		if (!closed_) {
			buffer_[buffer_index_++] = ((char*)data)[i];
			size_++;
			buffer_index_ %= max_size_;
			ret ++;
			cout << "#### Wrote 1 byte" << endl;
		}
		mutex_.Release();
		consumer_.V();
	}
	return ret;
}

void BoundedBuffer::Close() {
	mutex_.Acquire();
	closed_ = true;
	mutex_.Release();
}

static Semaphore bounded_buffer_test_semaphore("bounded_buffer_test_semaphore", 0);
static int test_tmp = 65;

static void BoundedBufferSelfTest_Read(BoundedBuffer* bounded_buffer) {
	char* data = new char[3];
	int read_bytes = bounded_buffer->Read(data, 3);
	cout << "### Bytes read : " << read_bytes << endl;
	for (int j = 0; j < read_bytes; j ++)
		cout << data[j] << " ";
	cout << endl;

	bounded_buffer_test_semaphore.V();
}

static void BoundedBufferSelfTest_Write(BoundedBuffer* bounded_buffer) {
	char* data = new char[12];
	for (int i = 0; i < 12; i ++) data[i] = test_tmp++;
	int written_bytes = bounded_buffer->Write(data, 12);
	cout << "### Bytes written : " << written_bytes << endl;
	for (int j = 0; j < written_bytes; j ++)
		cout << data[j] << " ";
	cout << endl;

	bounded_buffer_test_semaphore.V();
}

void BoundedBuffer::SelfTest() {
    cout << "========= Bounded Buffer SelfTest Started" << endl;
    for (int i = 0; i < 2; i ++) {
    	Thread *consumer1 = new Thread("bounded_buffer_consumer_thread");
    	Thread *consumer2 = new Thread("bounded_buffer_consumer_thread");
    	Thread *consumer3 = new Thread("bounded_buffer_consumer_thread");
    	Thread *consumer4 = new Thread("bounded_buffer_consumer_thread");
    	Thread *producer = new Thread("bounded_buffer_producer_thread");
    	consumer1->Fork((VoidFunctionPtr) BoundedBufferSelfTest_Read, this);
    	consumer2->Fork((VoidFunctionPtr) BoundedBufferSelfTest_Read, this);
    	consumer3->Fork((VoidFunctionPtr) BoundedBufferSelfTest_Read, this);
    	consumer4->Fork((VoidFunctionPtr) BoundedBufferSelfTest_Read, this);
    	producer->Fork((VoidFunctionPtr) BoundedBufferSelfTest_Write, this);
    }

    for (int i = 0; i < 5 * 2; i ++) {
		bounded_buffer_test_semaphore.P();
		if (i == 4) Close();
		cout << "###################### Thread ended." << endl;
    }
}