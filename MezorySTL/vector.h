#ifndef MEZORY_STL_VECTOR_H
#define MEZORY_STL_VECTOR_H
 
namespace mezstd {
	template<typename _Type>
	class vector {
	public:
		using ValueType = _Type;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;
		using ConstReferenceType = const ValueType&;
		using SizeType = std::size_t;
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
