#include <string>

namespace iow{ namespace json{

template<>
struct value<char, -1>
{
  typedef char target;
  typedef serializerT< value<char, -1> > serializer;
};

template<>
struct value<unsigned char, -1>
{
  typedef unsigned char target;
  typedef serializerT< value<unsigned char, -1> > serializer;
};

template<>
struct value<short, -1>
{
  typedef short target;
  typedef serializerT< value<short, -1> > serializer;
};

template<>
struct value<unsigned short, -1>
{
  typedef unsigned short target;
  typedef serializerT< value<unsigned short, -1> > serializer;
};


template<>
struct value<int, -1>
{
  typedef int target;
  typedef serializerT< value<int, -1> > serializer;
};

template<>
struct value<unsigned int, -1>
{
  typedef unsigned int target;
  typedef serializerT< value<unsigned int, -1> > serializer;
};

template<>
struct value<long int>
{
  typedef long int target;
  typedef serializerT< value<long int, -1> > serializer;
};

template<>
struct value<unsigned long, -1>
{
  typedef unsigned long target;
  typedef serializerT< value<unsigned long, -1> > serializer;
};


template<>
struct value<long long, -1>
{
  typedef long long target;
  typedef serializerT< value<long long, -1> > serializer;
};

template<>
struct value<unsigned long long, -1>
{
  typedef unsigned long long target;
  typedef serializerT< value<unsigned long long, -1> > serializer;
};

template<>
struct value<bool, -1>
{
  typedef bool target;
  typedef serializerT< value<bool, -1> > serializer;
};

template<int R>
struct value<std::string, R>
{
  enum {reserve=-1};
  typedef std::string target;
  typedef serializerT< value<std::string, R> > serializer;
};

template<int R>
struct value< std::vector<char>, R >
{
  enum {reserve=-1};
  typedef std::vector<char> target;
  typedef serializerT< value< target, R > > serializer;
};

template<int N>
struct value< char[N], -1 >
{
  typedef char target[N];
  typedef serializerT< value<char[N], -1>  > serializer;
};

template<typename T>
struct value_quoted {
  typedef T target;
  typedef serializerQuoted< T > serializer;
};

}}

