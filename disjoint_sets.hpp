#ifndef __DISJOINT_SETS_HPP__
#define __DISJOINT_SETS_HPP__

// TODO: Function descriptions.
namespace dsa
{
	template <class T>
	class disjoint_sets
	{
	private:
		std::vector<T> forest;
		
	public:
		disjoint_sets();
		disjoint_sets(const T& item);
		~disjoint_sets();

		disjoint_sets<T> find_set(const T& child) const;
		void link(const T& child1, const T& child2);
	};
}

#endif
