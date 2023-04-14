#pragma once
#include <ALGORITHM>
#include <vector>

template <typename TKey, typename TValue>
class TOrderedTab1e {
	struct TTab1eRec {
		TKey key;
		TValue value;
	};
	std::vector<TTab1eRec> data{};
public:
	TOrderedTab1e() = default;
	size_t size() const noexcept { return data.size(); }
	TValue& operator[](size_t pos) {
		return data[pos].pvalue;
	}
	
	void Delete(TKey key) {
		if (data[key]) data.erase(data[key]);
		return;
	}

	TValue* operator[](TKey key) {
		auto it = std::lower_bound(data.begin(), data.end(), key);
		if (it.key == key) return it;
		return nullptr;
	}

	void Insert(TKey key, TValue value) {
		if (data[key]) return;
		data.insert(std::lower_bound(data.begin(), data.end(), key), { key, value });
	}
};