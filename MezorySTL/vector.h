#ifndef MEZORY_STL_VECTOR_H
#define MEZORY_STL_VECTOR_H
#include <iterator>
namespace mezstd {
	template <typename vector>
	class RandomAccessIterator : public std::iterator<std::random_access_iterator_tag, vector> {
	public:
		using ValueType		   = typename vector::ValueType;
		using PointerType      = ValueType*;
		using ReferenceType    = ValueType&;
		using difference_type  = typename std::iterator<std::random_access_iterator_tag, vector>::difference_type;
		using IteratorCategory = std::random_access_iterator_tag;
	public:
		RandomAccessIterator() : ptr_(nullptr){}
		RandomAccessIterator(PointerType ptr) : ptr_(ptr){}
		RandomAccessIterator(const RandomAccessIterator& rhs) : ptr_(rhs.ptr_) { }
		~RandomAccessIterator() = default;

		inline RandomAccessIterator& operator+=(difference_type rhs) {
			ptr_ += rhs; 
			return *this;
		}

		inline RandomAccessIterator& operator-=(difference_type rhs) {
			ptr_ -= rhs;
			return *this;
		}

		inline ReferenceType operator*() const { return *ptr_; }
		inline PointerType operator->() const { return ptr_; }
		inline ReferenceType operator[](difference_type rhs) const {
			return ptr_[rhs];
		}


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

		inline difference_type operator-(const RandomAccessIterator& rhs) const { return ptr_ - rhs.ptr_; }
		inline RandomAccessIterator operator+(difference_type rhs) const { return RandomAccessIterator(ptr_ + rhs); }
		inline RandomAccessIterator operator-(difference_type rhs) const { return RandomAccessIterator(ptr_ - rhs); }

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
		using size_type = unsigned int;

		using Iterator = RandomAccessIterator<vector<ValueType>>;
	public:
		vector();
		~vector();
	public:

		/**
		* @brief access specified element with bounds checking
		* @return Reference to the requested element.
		*/
		ReferenceType at(const size_type pos) { return data_[pos]; }
		ConstReferenceType at(const size_type pos) const { return data_[pos]; }

		/**
		* @brief access the first element
		* @return reference to the first element
		*/
		ReferenceType front() {
			return *data_;
		}
		ConstReferenceType front() const {
			return *data_;
		}

		/**
		* @brief access the last element
		* @return Reference to the last element.
		*/
		ReferenceType back() {
			return *(data_ + size_ - 1);
		}

		ConstReferenceType back() const {
			return *(data_ + size_ - 1);
		}

		/**
		* @brief Checks if the container has no elements
		* @return true if the container is empty, false otherwise
		*/
		bool empty() const noexcept {
			return (data_ == (data_ + size_));
		}

		/**
		* @brief Returns the number of elements in the container
		* @return The number of elements in the container.
		*/
		size_type size() const noexcept { 
			return size_; 
		}

		/**
		* @brief reserves storage
		*/
		void reserve(size_type new_capacity) {
			reallocate(new_capacity);
		}

		/**
		* @brief Returns the number of elements that the container has currently allocated space for.
		* @return Capacity of the currently allocated storage.
		*/
		size_type capacity() const noexcept;

		/**
		* @brief clears elements
		*/
		void clear() noexcept {
			for (PointerType it = data_; it != data_ + size_; ++it)
				it->~ValueType();
			
			size_ = 0;
		}

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

		ReferenceType operator[](const size_type index)  {
			return data_[index];
		}
		/**
		* @brief Two vectors are equal if they have the same number of elements and their respective elements have the same values. Otherwise, they are unequal.
		*/
		friend inline bool operator ==(const vector<ValueType>& left, const vector<ValueType>& right)
		{
			if (left.size() != right.size()) 
				return false;

			return (std::equal(left.cbegin(), left.cend(), right.cbegin()));
		}

	private:
		PointerType data_;
		size_type size_;
		size_type capacity_ = 2;
	private:
		void reallocate(size_type capacity) {
			size_type bytes = size_ + capacity;
			capacity_ = bytes;

			PointerType tmp = new ValueType[size_];
			for (size_type i = 0; i < size_; i++) {
				tmp[i] = data_[i];
			}
	 
			delete[] data_;

			data_ = new ValueType[bytes];
			for (size_type i = 0; i < size_; i++) {
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
		size_ = 0;
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
