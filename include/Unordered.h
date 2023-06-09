#pragma once
template <typename TKey, typename TValue> 
class TUnorderedTab1e {
    struct TTab1eRec {
        TKey key;
        TValue value;
        vector<TTab1eRec> data{};
    public:
        TUnorderedTab1e() = default;
        size_t size() const noexcept { return data.size(); }
        TValue& operator[](size_t pos) {
            return data[pos].pvalue;
        }
    }

    void Delete(TKey key) {
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i].key == key) {
                data[i] = data[data.size() - 1];
                data.pop_back();
            }
        }
        return;
    }

    TValue* Find(TKey key) {
        for (auto& val : data)
            if (val.key == key)
                return &val.value;
        return nullptr;
    }

    void Insert(TKey key, TValue value) {
        if (Find(key)) return;
        data.push_back({ key, value });
    }
};