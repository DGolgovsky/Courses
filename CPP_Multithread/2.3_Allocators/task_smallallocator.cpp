/*
 * Давайте напишем простой аллокатор.
 *
 * N.B. Для получения баллов дефрагментацию делать не требуется,
 * но очень рекомендуется сделать ее для самотренировки.
 * Для того, чтобы ее сделать, придется реализовывать умные указатели,
 * инвариантные относительно позиции блока памяти!
 *
 * N.B. ReAlloc должен сохранять данные в блоке.
 * То есть это не просто пара Free + Alloc.
 *
 * N.B. Следующий вариант и ему подобные считаются читерством:
 * class SmallAllocator {
 * public:
 *     void *Alloc(unsigned int Size) {
 *         return malloc(Size);
 *     };
 *     void *ReAlloc(void *Pointer, unsigned int Size) {
 *         return realloc(Pointer, Size);
 *     };
 *     void Free(void *Pointer) {
 *         return free(Pointer);
 *     };
 * };
 *
 * UPD: Так как возникло много вопросов, почему система не принимает
 * некоторые работы, выкладываю тест. Он всего один.
 * Программа не должна кориться и не должна выводить текст.
 *
 * SmallAllocator A1;
 * int * A1_P1 = (int *) A1.Alloc(sizeof(int));
 * A1_P1 = (int *) A1.ReAlloc(A1_P1, 2 * sizeof(int));
 * A1.Free(A1_P1);
 * SmallAllocator A2;
 * int * A2_P1 = (int *) A2.Alloc(10 * sizeof(int));
 * for(unsigned int i = 0; i < 10; i++) A2_P1[i] = i;
 * for(unsigned int i = 0; i < 10; i++)
 *     if(A2_P1[i] != i)
 *         std::cout << "ERROR 1" << std::endl;
 * int * A2_P2 = (int *) A2.Alloc(10 * sizeof(int));
 * for(unsigned int i = 0; i < 10; i++) A2_P2[i] = -1;
 * for(unsigned int i = 0; i < 10; i++)
 *     if(A2_P1[i] != i)
 *         std::cout << "ERROR 2" << std::endl;
 * for(unsigned int i = 0; i < 10; i++)
 *     if(A2_P2[i] != -1)
 *         std::cout << "ERROR 3" << std::endl;
 * A2_P1 = (int *) A2.ReAlloc(A2_P1, 20 * sizeof(int));
 * for(unsigned int i = 10; i < 20; i++) A2_P1[i] = i;
 * for(unsigned int i = 0; i < 20; i++)
 *     if(A2_P1[i] != i)
 *         std::cout << "ERROR 4" << std::endl;
 * for(unsigned int i = 0; i < 10; i++)
 *     if(A2_P2[i] != -1)
 *         std::cout << "ERROR 5" << std::endl;
 * A2_P1 = (int *) A2.ReAlloc(A2_P1, 5 * sizeof(int));
 * for(unsigned int i = 0; i < 5; i++)
 *     if(A2_P1[i] != i)
 *         std::cout << "ERROR 6" << std::endl;
 * for(unsigned int i = 0; i < 10; i++)
 *     if(A2_P2[i] != -1)
 *         std::cout << "ERROR 7" << std::endl;
 * A2.Free(A2_P1);
 * A2.Free(A2_P2);
 */

class SmallAllocator
{
public:
	SmallAllocator() {
		_str* start_str = (_str*)&Memory[0];
		start_str->size = sizeof(Memory) - sizeof(_str);
		start_str->isFree = 1;
		start_str->prev = 0;
		start_str->next = sizeof(_str);

		start_str = (_str*)&Memory[start_str->next];
		start_str->size = sizeof(Memory)-((sizeof(_str)*2)+sizeof(end_str));
		start_str->isFree = 1;
		start_str->prev = 0;
		start_str->next = 0;
		end_str* end_str = (end_str*)&start_str->data[start_str->size];
		end_str->size = start_str->size;
		end_str->isFree = start_str->isFree;
	}

	void* Alloc(unsigned int Size) {
		void* Result = NULL;
		_str* strt_free_str = (_str*)&Memory[0];
		while(strt_free_str->next != 0) {
			strt_free_str = (_str*)&Memory[strt_free_str->next];
			if(strt_free_str->size >= Size) {
				_str* strt_alloc_str = NULL;
				if((strt_free_str->size >= (Size + sizeof(_str) +sizeof(end_str) + 1))) {
					//сможем оставить хотя бы минимальный свободный блок
					std::size_t off_alloc = strt_free_str->size - (Size + sizeof(_str));
					std::size_t NewFreeSize = off_alloc - sizeof(end_str);
					strt_alloc_str = (_str*)&strt_free_str->data[off_alloc];
					strt_alloc_str->isFree = 0;
					strt_alloc_str->size = Size;
					end_str* end_alloc_str = (end_str*)&strt_free_str->data[strt_free_str->size];
					end_alloc_str->isFree = 0;
					end_alloc_str->size = Size;

					end_str* end_free_str = (end_str*)&strt_free_str->data[NewFreeSize];
					end_free_str->isFree = 1;
					end_free_str->size = NewFreeSize;
					strt_free_str->size = NewFreeSize;
				} else {
					//придется отдавать весь блок
					end_str* end_alloc_str = (end_str*)&strt_free_str->data[strt_free_str->size];
					end_alloc_str->isFree = 0;
					_str* prv_free_str = (_str*)&Memory[strt_free_str->prev];
					prv_free_str->next = strt_free_str->next;
					if (strt_free_str->next != 0) {
						_str* next_free_str = (_str*)&Memory[strt_free_str->next];
						next_free_str->prev = strt_free_str->prev;
					}
					strt_alloc_str = (_str*)&strt_free_str[0];
					strt_free_str->isFree = 0;
				}
				Result = (void*)&strt_alloc_str->data[0];
			}
		}
		return Result;
	}

	void* ReAlloc(void* Pointer, unsigned int Size) {
		if ((Size > 0) && (Pointer != NULL)) {
			char* new_ptr = (char*)Alloc(Size);
			if (new_ptr != NULL) {
				_str* strt_alloc_str = (_str*)((std::size_t)Pointer - sizeof(_str));
				unsigned int CopySize = std::min(Size, (unsigned int)strt_alloc_str->size);
				char* CharPointer = (char*)Pointer;
				for (unsigned int i = 0; i < CopySize; ++ i) {
					new_ptr[i] = CharPointer[i];
				}
				Free(Pointer);
				return (void*)&new_ptr[0];
			} else {
				return NULL;
			}
		} else {
			Free(Pointer);
			return NULL;
		}
	}

	void Free(void* Pointer) {
		if (Pointer != NULL) {
			_str* strt_free_str = (_str*)&Memory[0];
			_str* strt_alloc_str = (_str*)((std::size_t)Pointer - sizeof(_str));
			end_str* end_alloc_str = (end_str*)&strt_alloc_str->data[strt_alloc_str->size];
			_str* prv_free_str = NULL;
			_str* next_free_str = NULL;
			strt_alloc_str->isFree = 1;
			end_alloc_str->isFree = 1;

			if (strt_alloc_str != (_str*)&strt_free_str->data[0]) {
				end_str* end_prv_str = (end_str*)((std::size_t)strt_alloc_str - sizeof(end_str));
				if (end_prv_str->isFree) {
					prv_free_str = (_str*)((std::size_t)end_prv_str - end_prv_str->size - sizeof(_str));
					prv_free_str->size += strt_alloc_str->size + sizeof(end_str) + sizeof(_str);
					end_alloc_str->size = prv_free_str->size;
				}
			}
			if (prv_free_str == NULL) {
				while(strt_free_str->next != 0) {
					strt_free_str = (_str*)&Memory[strt_free_str->next];
				}
				strt_free_str->next = (std::size_t)strt_alloc_str - (std::size_t)Memory;
				strt_alloc_str->prev = (std::size_t)strt_free_str - (std::size_t)Memory;
				strt_alloc_str->next = 0;
				prv_free_str = strt_alloc_str;
			}
			if ((((std::size_t)Memory + sizeof(Memory)) - (std::size_t)end_alloc_str) >= (sizeof(end_str) + sizeof(_str))) {
				next_free_str = (_str*)((std::size_t)end_alloc_str + sizeof(end_str));
				if (next_free_str->isFree) {
					_str* prv_free_4_next_ = (_str*)&Memory[next_free_str->prev];
					prv_free_4_next_->next = next_free_str->next;
					if (next_free_str->next != 0) {
						_str* next_free_4_next_ = (_str*)&Memory[next_free_str->next];
						next_free_4_next_->prev = next_free_str->prev;
					}
					end_str* end_next_free_ = (end_str*)&next_free_str->data[next_free_str->size];
					prv_free_str->size += (sizeof(end_str) + sizeof(_str) + next_free_str->size);
					end_next_free_->size = prv_free_str->size;
				}
			}
		}
	}

private:
	struct _str {
		unsigned long long isFree : 1;
		unsigned long long size : 20;
		unsigned long long prev : 20;
		unsigned long long next : 20;
		char data[];
	};

	struct end_str {
		unsigned long padding : 11;
		unsigned long size : 20;
		unsigned long isFree : 1;
	};

	char Memory[1048576];
};
