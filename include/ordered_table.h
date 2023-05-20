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
		return this[pos].value;
	}
	
	void Delete(TKey key) {
		auto it = std::lower_bound(data.begin(), data.end(), key, [](const TTab1eRec& r, const TKey& k) { return r.key < k; });
		if (it != data.end() && it->key == key) data.erase(it);
	}

	TValue* operator[](TKey key) {
		auto comp = [](const TTab1eRec& r, const TKey& k) { return r.key < k; };
		auto it = std::lower_bound(data.begin(), data.end(), key, comp);
		if (it != data.end() && it->key == key) {
			return &it->value;
		}
		return nullptr;
	}

	void Insert(TKey key, TValue value) {
		auto comp = [](const TTab1eRec& r, const TKey& k) { return r.key < k; };
		auto it = std::lower_bound(data.begin(), data.end(), key, comp);
		if (it != data.end() && it->key == key) {
			it->value = value;  // Update value of existing element
		}
		else {
			data.insert(it, { key, value });  // Insert new element
		}
	}
};