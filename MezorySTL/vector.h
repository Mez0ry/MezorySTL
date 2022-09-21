#ifndef MEZORY_STL_VECTOR_H
#define MEZORY_STL_VECTOR_H
 
namespace mezstd {
	template<typename _Type>
	class vector {
	private:
		using ValueType = _Type;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;
		using ConstReferenceType = const ValueType&;
		using SizeType = std::size_t;
	public:
	/**
	* @brief access specified element with bounds checking
	* @return Reference to the requested element.
	*/
		ReferenceType at();
		ConstReferenceType at() const;
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
		SizeType size() const noexcept;
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

	private:
		PointerType data_;
		SizeType size_;
	};
}
#endif // !MEZORY_STL_VECTOR_H
