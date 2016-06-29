

#include <fas/type_list.hpp>
#include <fas/integral/int_.hpp>
#include <fas/typemanip/empty_type.hpp>

#include <vector>
#include <array>
#include <string>
#include <deque>
#include <list>
#include <set>
#include <memory>

#if __cplusplus >= 201103L
#include <unordered_set>
#endif


namespace iow{ namespace json{

/// /////////////////////////////////////////////////////

template< typename T, char L, char R >
class serializerA;

template<typename C, typename R>
struct array_base;

template<typename C, typename R>
struct array_reserve
{
  template<typename T>
  inline void reserve(T& t)
  {
    t.reserve(R::value);
  }
};

template<typename C>
struct array_reserve<C, fas::empty_type>
{
  template<typename T>
  inline void reserve(T&)
  {
  }
};

template<typename J, typename R>
struct array_base< std::vector<J>, R>
{
  typedef std::vector<J> json_container;
  typedef J json_value;
  typedef typename json_value::target target;
  typedef std::vector<target> target_container;
  typedef serializerT< array_r< json_container, R> > serializer;
  typedef std::back_insert_iterator<target_container> inserter_iterator;
  static inserter_iterator inserter(target_container& t) { return std::back_inserter(t); }
};

template<typename J, typename R>
struct array_base< std::deque<J>, R>
{
  typedef std::deque<J> json_container;
  typedef J json_value;
  typedef typename json_value::target target;
  typedef std::deque<target> target_container;
  typedef serializerT< array_r< json_container, R> > serializer;
  typedef std::back_insert_iterator<target_container> inserter_iterator;
  static inserter_iterator inserter(target_container& t) { return std::back_inserter(t); }
};

template<typename J, typename R>
struct array_base< std::list<J>, R>
{
  typedef std::list<J> json_container;
  typedef J json_value;
  typedef typename json_value::target target;
  typedef std::list<target> target_container;
  typedef serializerT< array_r< json_container, R> > serializer;
  typedef std::back_insert_iterator<target_container> inserter_iterator;
  static inserter_iterator inserter(target_container& t) { return std::back_inserter(t); }
};

template<typename K, typename V, typename R>
struct array_base< std::vector< pair<K, V> >, R>
{
  typedef pair<K, V> json_value;
  typedef std::vector< json_value > json_container;
  typedef typename json_value::target target;
  typedef std::vector<target> target_container;
  typedef serializerA< array_r< json_container, R>, '{', '}' > serializer;
  typedef std::back_insert_iterator<target_container> inserter_iterator;
  static inserter_iterator inserter(target_container& t) { return std::back_inserter(t); }
};

template<typename J, int N, typename R>
struct array_base< J[N], R>
{
  typedef J json_container[N];
  typedef J json_value;
  typedef typename json_value::target target;
  typedef target target_container[N];
  typedef serializerT< array_r< json_container, R > > serializer;
};

template<typename J, typename R>
struct array_base< std::set<J>, R>
{
  typedef std::set<J> json_container;
  typedef J json_value;
  typedef typename json_value::target target;
  typedef std::set<target> target_container;
  typedef serializerT< array_r< json_container, R > > serializer;
  typedef std::insert_iterator<target_container> inserter_iterator;
  static inserter_iterator inserter(target_container& t) { return std::inserter(t, t.begin()); }
};

template<typename J, typename R>
struct array_base< std::multiset<J>, R>
{
  typedef std::multiset<J> json_container;
  typedef J json_value;
  typedef typename json_value::target target;
  typedef std::multiset<target> target_container;
  typedef serializerT< array_r< json_container, R > > serializer;
  typedef std::insert_iterator<target_container> inserter_iterator;
  static inserter_iterator inserter(target_container& t) { return std::inserter(t, t.begin()); }
};


#if __cplusplus >= 201103L

template<typename J, typename R>
struct array_base< std::unordered_set<J>, R>
{
  typedef std::unordered_set<J> json_container;
  typedef J json_value;
  typedef typename json_value::target target;
  typedef std::unordered_set<target> target_container;
  typedef serializerT< array_r< json_container, R > > serializer;
  typedef std::insert_iterator<target_container> inserter_iterator;
  static inserter_iterator inserter(target_container& t) { return std::inserter(t, t.begin()); }
};

template<typename J, typename R>
struct array_base< std::unordered_multiset<J>, R>
{
  typedef std::unordered_multiset<J> json_container;
  typedef J json_value;
  typedef typename json_value::target target;
  typedef std::unordered_multiset<target> target_container;
  typedef serializerT< array_r< json_container, R > > serializer;
  typedef std::insert_iterator<target_container> inserter_iterator;
  static inserter_iterator inserter(target_container& t) { return std::inserter(t, t.begin()); }
};

template<typename J, size_t N, typename R>
struct array_base< std::array<J, N>, R>
{
  typedef std::array<J, N> json_container;
  typedef J json_value;
  typedef typename json_value::target target;
  typedef std::array<target, N> target_container;
  typedef serializerT< array_r< json_container, R> > serializer;
};

#endif

template<typename C, typename R>
struct array_r
  : public array_base<C, R>
  , public array_reserve<C, R>
{
  typedef array_base<C, R> base;
  typedef typename base::target_container target;
  typedef typename base::serializer serializer;

};

template< typename T, typename L, typename R>
struct array_r< object<T, L>, R>
  : array_r< std::vector< object<T, L> >, R>
{
};

template< typename K, typename V, typename R>
struct array_r< pair<K, V>, R>
  : array_r< std::vector< pair<K, V> >, R>
{
};

template<typename C, int R>
struct array: array_r<C, fas::int_<R> > {};

template<typename C>
struct array<C, -1>: array_r<C, fas::empty_type> {};

template<int Reserve>
struct vector_of_strings: array< std::vector< value< std::string > >,  Reserve> {};

template<int Reserve>
struct deque_of_strings: array< std::deque< value< std::string > >,  Reserve> {};

template<int Reserve>
struct list_of_strings: array< std::list< value< std::string > >,  Reserve> {};

}}
