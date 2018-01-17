#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
private:
  

public:
  void enqueue(int ele);
  int dequeue() throw(QueueEmpty);
  int size() const;
  int front() const throw(QueueEmpty);
  bool empty();
  Queue();
  virtual ~Queue();
};

#endif /* QUEUE_H */
