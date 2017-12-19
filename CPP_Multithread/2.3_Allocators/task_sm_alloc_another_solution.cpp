#include <cstring>
#include <map>


class SmallAllocator {
private:
	static const size_t memory_size = 1048576;
	char memory[memory_size];

	using MemoryMap = std::map<char *, size_t>;
	MemoryMap free_blocks, allocated_blocks;

	MemoryMap::iterator try_merge_free_blocks(MemoryMap::iterator &a, MemoryMap::iterator &b) 
	{
		if (a->first + a->second == b->first || a->first == b->first + b->second) {
			auto res_block = MemoryMap::value_type{ a->first < b->first ? a->first : b->first, a->second + b->second };
			free_blocks.erase(a); free_blocks.erase(b);

			return free_blocks.insert(res_block).first;
		}

		return free_blocks.end();
	}

	void put_block(char *block, size_t size) 
	{
		auto pos = free_blocks.insert({ block, size }).first;
		if (pos != free_blocks.begin()) {
			auto prev_it = std::prev(pos);
			auto res = try_merge_free_blocks(prev_it, pos);
			if (res != free_blocks.end())
				pos = res;
		}

		auto next_it = std::next(pos);
		if (next_it != free_blocks.end())
			try_merge_free_blocks(pos, next_it);
	}
public:
	SmallAllocator() {
		free_blocks[memory] = memory_size;
	}

	void *Alloc(unsigned int Size) {
		for (auto it = free_blocks.begin(); it != free_blocks.end(); ++it) {
			if (it->second >= Size) {
				char *ptr = it->first;
				if (it->second > Size)
					free_blocks[it->first + Size] = it->second - Size;
				free_blocks.erase(it);
				allocated_blocks.insert({ptr, Size});

				return ptr;
			}
		}

		throw std::bad_alloc();
	}

	void *ReAlloc(void *Pointer, size_t Size) {
		auto it = allocated_blocks.find(reinterpret_cast<char *>(Pointer));
		if (it == allocated_blocks.end())
			throw std::bad_alloc();

		void *NewPointer = Alloc(Size);
		memcpy(NewPointer, Pointer, std::min(Size, it->second));
		Free(Pointer);

		return NewPointer;
	}
	void Free(void *Pointer) {
		auto it = allocated_blocks.find(reinterpret_cast<char *>(Pointer));
		if (it == allocated_blocks.end())
			throw std::bad_alloc();

		put_block(it->first, it->second);
		allocated_blocks.erase(it);
	}
};
