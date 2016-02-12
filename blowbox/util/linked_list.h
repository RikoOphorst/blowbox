#pragma once

#include "../../blowbox/core/memory/allocator.h"
#include "../../blowbox/core/memory/memory_manager.h"

#include <iterator>

namespace blowbox
{
	namespace util
	{
		template<typename T>
		class LinkedList
		{
		private:
			struct Node
			{
				Node(T& data, Node* next) : data(data), next(next) {}

				// Quick note: The node keeps references to the memory, instead of making copies.
				// This is done because it reduces the memory footprint immensely. If not for this,
				// the memory footprint of any linked list is effectively doubled, which is not
				// ideal.
				T& data;
				Node* next;
			};

		public:
			class Iterator : public std::iterator<std::forward_iterator_tag, T>
			{
			public:
				friend class ConstIterator;
				friend class LinkedList;

				inline Iterator(Node* node = nullptr) :
					represents_(node)
				{

				}

				inline Iterator(const Iterator& other) :
					represents_(other.represents_)
				{

				}

				inline Iterator& operator=(const Iterator& other)
				{
					represents_ = other.represents_;
					return *this;
				}

				inline Iterator& operator++()
				{
					represents_ = represents_->next;
					return *this;
				}

				inline Iterator operator++(int)
				{
					Iterator temp(*this);
					represents_ = represents_->next;
					return temp;
				}

				inline reference operator*() const
				{
					return represents_->data;
				}

				inline pointer operator->() const
				{
					return &represents_->data;
				}

				inline bool operator==(const Iterator& other)
				{
					return represents_ == other.represents_;
				}

				inline bool operator!=(const Iterator& other)
				{
					return represents_ != other.represents_;
				}

			private:
				Node* represents_;
			};

			class ConstIterator : public std::iterator<std::forward_iterator_tag, const T>
			{
			public:
				friend class Iterator;
				friend class List;

				inline ConstIterator(const Node* other = nullptr) :
					represents_(other)
				{
				
				}

				inline ConstIterator(const ConstIterator& other) :
					represents_(other.represents_) 
				{
				
				}

				inline ConstIterator(const iterator& other) :
					represents_(other.represents_)
				{
				
				}

				inline ConstIterator& operator=(const ConstIterator& other)
				{
					represents_ = other.represents_; 
					return *this;
				}

				inline ConstIterator& operator=(const Iterator& other)
				{
					represents_ = other.represents_; 
					return *this;
				}

				inline ConstIterator& operator++()
				{
					represents_ = represents_->m_next; 
					return *this;
				}

				inline ConstIterator operator++(int)
				{
					ConstIterator tmp(*this); represents_ = represents_->m_next; return tmp;
				}

				inline reference operator*() const 
				{ 
					return represents_->m_data; 
				}

				inline pointer operator->() const 
				{ 
					return represents_; 
				}

				inline bool operator==(const ConstIterator& other) const
				{
					return represents_ == other.represents_;
				}

				inline bool operator!=(const ConstIterator& other) const
				{
					return represents_ != other.represents_;
				}

			private:
				const Node* represents_;
			};

		public:
			LinkedList(memory::Allocator* allocator) :
				head_(nullptr),
				allocator_(allocator)
			{

			}

			LinkedList(const LinkedList& other) :
				head_(nullptr)
			{
				for (ConstIterator i = other.Begin(); i != other.End(); i++)
				{
					PushFront(*i);
				}

				Reverse();
			}

			~LinkedList()
			{
				Clear();
			}

			void Clear()
			{
				while (!IsEmpty())
				{
					PopFront();
				}
			}

			void Reverse()
			{
				Node* p = nullptr;
				Node* i = head_;
				Node* n;

				while (i)
				{
					n		= i->next;
					i->next = p;
					p		= i;
					i		= n;
				}

				head_ = p;
			}

			void Swap(LinkedList& other)
			{
				Node* temp = head_;
				head_ = other.head_;
				other.head_ = temp;
			}

			void PushFront(T& data)
			{
				Node* temp = memory::MemoryManager::Allocate<Node, T&, Node*>(allocator_, data, head_);
				head_ = temp;
			}

			void InsertAfter(Iterator& iterator, const T& data)
			{
				if (IsEmpty())
				{
					PushFront(data);
					return;
				}

				Node* new_node = memory::MemoryManager::Allocate<Node, T&, Node*>(allocator_, data, iterator.represents_->next);
				iterator.represents_->next = new_node;
			}

			void PopFront()
			{
				if (head_ != nullptr)
				{
					Node* new_head = head_->next;
					memory::MemoryManager::Deallocate<Node>(allocator_, head_);
					head_ = new_head;
				}
			}

			void EraseAfter(Iterator& iterator)
			{
				Node* remove = iterator->represents_->next;

				if (remove != nullptr)
				{
					iterator.represents_->next = remove->next;
					memory::MemoryManager::Deallocate<Node>(allocator_, remove);
				}
			}

			bool IsEmpty()
			{
				return head_ == nullptr;
			}

			inline T& Front() 
			{ 
				return *begin(); 
			}
			
			inline const T& Front() const 
			{ 
				return *begin(); 
			}

			inline Iterator Begin()
			{
				return Iterator(head_);
			}

			inline Iterator End()
			{
				return Iterator();
			}

			inline ConstIterator Begin() const
			{
				return head_;
			}

			inline ConstIterator End() const
			{
				return ConstIterator();
			}
		private:
			

			Node* head_;
			memory::Allocator* allocator_;
		};
	}
}