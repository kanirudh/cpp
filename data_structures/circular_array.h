#pragma once

#include <array>
#include <optional>
#include <utility>

template <typename T, size_t N>
class CircularArray {
public:
	CircularArray() = default;

	void Push(T elem) {
		if (Full()) return;
		++size_;
		elements_[increment(back_)] = std::move(elem);
	}

	std::optional<T> Pop() {
		if (Empty()) return std::nullopt;
		--size_;
		return std::move(elements_[increment(front_)]);
	}

	bool Full() const noexcept { return size_ == N; }

	bool Empty() const noexcept { return size_ == 0; }

private:
	static constexpr size_t increment(size_t& index) { return std::exchange(index, (index + 1) % N); }

	std::array<T, N> elements_ = {};
	size_t size_ = 0;
	size_t front_ = 0;
	size_t back_ = 0;
};
