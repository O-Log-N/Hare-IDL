/*******************************************************************************
Copyright (C) 2016 OLogN Technologies AG

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*******************************************************************************/

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED "include guard"

#include <memory>
#include <vector>
#include <string>
#include <ostream>
#include <cassert>

/*
TODO maybe throw an exception, by now is better to assert and let the debugger kickin.
*/
#define ASSERT(condition) assert(condition)

namespace hare
{
	class Node;

	const bool NotImplementedYet = false;
//	inline void HARESERT(bool condition) { assert(condition); }

	struct Location {
		const char* fileName;
		int lineNumber;
		Location() : fileName(0), lineNumber(0) {}

		bool isValid() const {
			return fileName != 0;
		}
		std::string toString() const;
		std::ostream& write(std::ostream& os) const;
	};


	template <class T>
	class Child
	{
	private:
		Node* const parent;
		std::unique_ptr<T> child;
	public:
		Child(Node* parent) :parent(parent) {}
		Child(Child &&) = default;
		Child(const Child& other) :parent(other.parent), child() { set(other->clone()); }
//		~Child() { ASSERT(!child); }

		void release() {
			assert(child);
			return child.release();
		}

		void set(T* new_child) {
			assert(new_child);
			assert(!child);
			new_child->parent = parent;
			child.reset(new_child);
		}

		T* operator->() const {
			return get();
		}

		T* get() const {
			return child.get();
		}

		explicit operator bool() const {
			return static_cast<bool>(child);
		}
	};

	template <class T>
	class ChildList
	{
	private:
		Node* const parent;
		std::vector<Child<T> > child_list;

		Child<T> make_child(T* new_child) const {
			ASSERT(new_child != 0);
			Child<T> ch(parent);
			ch.set(new_child);
			return ch;
		}

	public:
		ChildList(Node* parent) :parent(parent) {}
//		~ChildList() { ASSERT(child_list.empty()); }

		typedef typename std::vector<Child<T> >::iterator iterator;
		typedef typename std::vector<Child<T> >::const_iterator const_iterator;

		iterator begin() { return child_list.begin(); }
		const_iterator begin() const { return child_list.begin(); }
		const_iterator cbegin() const { return child_list.cbegin(); }

		iterator end() { return child_list.end(); }
		const_iterator end() const { return child_list.end(); }
		const_iterator cend() const { return child_list.cend(); }

		bool empty() const {
			return child_list.empty();
		}

		Child<T>& at(size_t index) {
			return child_list.at(index);
		}

		const Child<T>& at(size_t index) const {
			return child_list.at(index);
		}

		void push_back(T* new_child) {
			child_list.push_back(make_child(new_child));
		}

		void insert_at(size_t index, T* new_child) {
			child_list.insert(child_list.begin() + index, make_child(new_child));
		}

		T* release_at(size_t index) {
			ch = child_list.at(index).release();
			child_list.erase(child_list.begin() + index);
			return ch;
		}

	};

}
#endif // COMMON_H_INCLUDED
