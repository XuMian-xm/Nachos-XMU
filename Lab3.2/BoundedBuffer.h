#ifndef BOUNDEDBUFFER_H_INCLUDED
#define BOUNDEDBUFFER_H_INCLUDED
#include "list.h"
#include "synch.h"

class BoundedBuffer {
   public:
     // create a bounded buffer with a limit of 'maxsize' bytes
     BoundedBuffer(int maxsize);
     ~BoundedBuffer();
     // read 'size' bytes from the bounded buffer, storing into 'data'.
     // ('size' may be greater than 'maxsize')
     void Read(void *data, int size);

     // write 'size' bytes from 'data' into the bounded buffer.
     // ('size' may be greater than 'maxsize')
     void Write(void *data, int size);
     int UsedSize;					//buffer�ѱ�ʹ�õĴ�С

   private:
	void *buffer;
    int maxsize;
	int FrontPlace,BackPlace;		//��־��������������ǰ��λ��

	Lock *lock;
	Condition *NotFull, *NotEmpty;
};
#endif // BOUNDEDBUFFER_H_INCLUDED
