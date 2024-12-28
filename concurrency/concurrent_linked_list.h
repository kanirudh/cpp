/*
* Describes a concurrent linked list LIFO queue.
*/


template <typename T>
class ConcurrentQueue {
public:
	void emplace(T&& value);

	T& front();

	void pop_front();
private:
	//TODO(anirudh): Install these private variables.
};
