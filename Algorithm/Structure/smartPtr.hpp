class RC
	{
    private:
		int count; // Reference count

    public:
		void ref() {count++;}
		int unref() {return --count;}
	};

template <class T>
class SP
	{
	private:
		T* ptr;
		RC* reference;
	public:
		SP() : ptr(NULL) 
			{
			reference = new RC();
			reference->ref();
			}
		SP(T* pValue) : ptr(pValue) 
			{
			reference = new RC();
			reference->ref();
			}
		SP(const SP<T>& sptr) : ptr(sptr.ptr), reference(sptr.reference)
			{
			reference->ref();
			}
		~SP()
			{
			if (0 == reference->unref())
				{
				delete ptr;
				delete reference;
				}
			}
		SP<T>& operator = (const SP<T>& sptr)
			{
			if (this != &sptr)
				{
				if(reference->unref() == 0)
					{
					delete pData;
					delete reference;
					}

				ptr = sptr.ptr;
				reference = sptr.reference;
				reference->ref();
				}
			return *this;
			}
		T& operator * () {return *ptr}
		T* operator -> () {return ptr;}
	};