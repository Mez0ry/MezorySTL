#ifndef MEZORY_STL_VECTOR_H
#define MEZORY_STL_VECTOR_H
 
namespace mezstd {
	template <typename vector>
	class RandomAccessIterator {
	public:
		using ValueType = typename vector::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;
	public:
		RandomAccessIterator(PointerType ptr) : ptr_(ptr){}
		RandomAccessIterator(const RandomAccessIterator& rhs) : ptr_(rhs.ptr_) { }
		~RandomAccessIterator() = default;

		inline ReferenceType operator*() const { return *ptr_; }
		inline PointerType operator->() const { return ptr_; }

		inline RandomAccessIterator& operator=(const RandomAccessIterator& rhs) {
			ptr_ = rhs.ptr_; 
			return *this; 
		}
		inline RandomAccessIterator& operator++()  {
			++ptr_;
			return *this;
		}

		inline const RandomAccessIterator& operator++() const {
			++ptr_;
			return *this;
		}
		
		inline RandomAccessIterator& operator--() {
			--ptr_;
			return *this;
		}

		 RandomAccessIterator operator++(int) const {
			RandomAccessIterator tmp(*this);
			++(*this);
			return tmp;
		}

		 RandomAccessIterator operator++(int) {
			 RandomAccessIterator tmp(*this);
			 ++(*this);
			 return tmp;
		 }

		inline RandomAccessIterator operator--(int) {
			RandomAccessIterator tmp(*this);
			--(*this);
			return tmp;
		}

		inline 	bool operator!=(const RandomAccessIterator& rhs) const {
			return(this->ptr_ != rhs.ptr_);
		}

		inline bool operator==(const RandomAccessIterator& rhs) const {
			return(this->ptr_ == rhs.ptr_);
		}

		inline 	bool operator>(const RandomAccessIterator& rhs) const {
			return(this->ptr_ > rhs.ptr_);
		}

		inline 	bool operator<(const RandomAccessIterator& rhs) const {
			return(this->ptr_ < rhs.ptr_);
		}

		inline 	bool operator>=(const RandomAccessIterator& rhs) const {
			return(this->ptr_ >= rhs.ptr_);
		}

		inline bool operator<=(const RandomAccessIterator& rhs) const {
			return(this->ptr_ <= rhs.ptr_);
		}

		friend inline RandomAccessIterator operator+(const RandomAccessIterator& rhs) { 
			return RandomAccessIterator(ptr_ + rhs.ptr_);
		}
		friend inline RandomAccessIterator operator-(const RandomAccessIterator& rhs) {
			return RandomAccessIterator(ptr_ - rhs.ptr_);
		}

	private:
		mutable PointerType ptr_;
	};

	template<typename _Type>
	class vector {
	public:
		using ValueType = _Type;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;
		using ConstReferenceType = const ValueType&;
		using SizeType = std::size_t;

		using Iterator = RandomAccessIterator<vector<ValueType>>;
	public:
		vector();
		~vector();
	public:

		/**
		* @brief access specified element with bounds checking
		* @return Reference to the requested element.
		*/
		ReferenceType at(const std::size_t pos) { return data_[pos]; }
		ConstReferenceType at(const std::size_t pos) const { return data_[pos]; }
		/**
		* @brief access the first element
		* @return reference to the first element
		*/
		ReferenceType front();
		ConstReferenceType front() const;
		/**
		* @brief access the last element
		* @return Reference to the last element.
		*/
		ReferenceType back();
		ConstReferenceType back() const;

		/**
		* @brief Checks if the container has no elements
		* @return true if the container is empty, false otherwise
		*/
		bool empty() const noexcept;
		/**
		* @brief Returns the number of elements in the container
		* @return The number of elements in the container.
		*/
		SizeType size() const noexcept { return size_; }
		/**
		* @brief reserves storage
		*/
		void reserve(SizeType new_capacity);
		/**
		* @brief Returns the number of elements that the container has currently allocated space for.
		* @return Capacity of the currently allocated storage.
		*/
		SizeType capacity() const noexcept;
		/**
		* @brief clears elements
		*/
		void clear() noexcept;
		/**
		* @brief adds element to the end
		*/
		void push_back(ConstReferenceType value);
		void push_back(_Type&& value);

		Iterator begin() {
			return Iterator(data_);
		}

		Iterator end() {
			return Iterator(data_ + size_);
		}

		Iterator cbegin() const {
			return Iterator(data_);
		}

		Iterator cend() const {
			return Iterator(data_ + size_);
		}

		ReferenceType operator[](const SizeType index)  {
			return data_[index];
		}

	private:
		PointerType data_;
		SizeType size_;
		SizeType capacity_ = 2;
	private:
		void reallocate(std::size_t capacity) {
			std::size_t bytes = size_ + capacity;
			capacity_ = bytes;

			_Type* tmp = new _Type[size_];
			for (int i = 0; i < size_; i++) {
				tmp[i] = data_[i];
			}
	 
			delete[] data_;

			data_ = new _Type[bytes];
			for (int i = 0; i < size_; i++) {
				data_[i] = tmp[i];
			}
			 
		}
	};
	template<typename _Type>
	inline vector<_Type>::vector() : capacity_(0)
	{
		data_ = new ValueType[capacity_];
	}

	template<typename _Type>
	inline vector<_Type>::~vector()
	{
		delete[] data_;
	}

	template<typename _Type>
	inline void mezstd::vector<_Type>::push_back(ConstReferenceType value)
	{
		if (size_ >= capacity_) {
			 
			if (!capacity_)
				capacity_++;

			reallocate(capacity_);
		}
		data_[size_++] = value;
	}

	template<typename _Type>
	inline void mezstd::vector<_Type>::push_back(_Type&& value)
	{
		if (size_ >= capacity_) {
	 
			if (!capacity_)
				capacity_++;

			reallocate(capacity_);
		}
		data_[size_++] = value;

	}

	template<typename _Type>
	inline std::size_t mezstd::vector<_Type>::capacity() const noexcept {
		return  capacity_;
	}
};
#endif // !MEZORY_STL_VECTOR_H
