#include <array>
#include <optional>
#include <utility>

template <typename T, size_t N>
class CircularArray {
public:
	CircularArray() = default;

	// TODO(anirudh): Should I use std::expected here ?
	void Push(T&& elem) {
		if (Full()) return;
		++size_;
		elements_[increment(back_)] = std::forward<T>(elem);
	}

	// TOOD(anirudh): Is std::expected a more performant choice ? Atleast its more readable.
	std::optional<T> Pop() {
		if (Empty()) return std::nullopt;
		--size_;
		return std::move(elements_[increment(front_)]);
	}

	bool Full() const { return size_ == N; }
	bool Empty() const { return size_ == 0; }
private:
	size_t increment(size_t& index) { return std::exchange(index, (index + 1) % N); }

private:
	std::array<T, N> elements_;
	size_t size_ = 0;
	size_t front_ = 0;
	size_t back_ = 0;
};
