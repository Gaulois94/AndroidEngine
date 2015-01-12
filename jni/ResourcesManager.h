#ifndef DEF_RESSOURCESMANAGER
#define DEF_RESSOURCESMANAGER

#include <iostream>
#include <map>

template <typename T>
struct clean
{
	static void release(T const& v)
	{

	}
};

template <typename T>
struct clean<T*>
{
	static void release(T * v)
	{
		if(v)
			delete v;
		v = NULL;
	}
};

template <typename T>
struct clean_array
{
	static void release(T * v)
	{
		delete[] v;
	}
};

template <typename T, typename CT = clean<T> >
class ResourcesManager
{
	typedef std::string keyType;
	typedef CT cleanning_traits;
public:
	ResourcesManager();
	~ResourcesManager();

	void add(const std::string &name, const T &type);
	bool remove(const std::string &name);
	bool remove(const T &resource);
	T &get(const std::string &name);
	const std::string &get(const T &resource) const;
	bool exist(const std::string &name) const;
	bool exist(const T &resource) const;
	
	void clean();

	int getSize() const;
protected:
	std::map <std::string, T> m_resources;
};

template <typename T, typename CT>
 ResourcesManager<T, CT>::ResourcesManager()
{

}

template <typename T, typename CT>
 ResourcesManager<T, CT>::~ResourcesManager()
{
	for(auto & p : m_resources)
		CT::release(p.second);
}

template <typename T, typename CT>
 void ResourcesManager<T, CT>::add(const std::string &name, const T &type)
{
	if(m_resources.find(name) == m_resources.end())
		m_resources.insert(std::make_pair(name, type));
}

template <typename T, typename CT>
 bool ResourcesManager<T, CT>::remove(const std::string &name)
{
	if(exist(name))
	{
		CT::release(m_resources[name]);
		m_resources.erase(name);
		return true;
	}
	return false;
}

template <typename T, typename CT>
 bool ResourcesManager<T, CT>::remove(const T& resource)
{
	for(typename std::map<std::string, T>::iterator it = m_resources.begin(); it != m_resources.end(); ++it)
		if(it->second == resource)
		{
			cleanning_traits::release(it->second);
			m_resources.erase(it);
			return true;
		}

	return false;
}

template <typename T, typename CT>
 T &ResourcesManager<T, CT>::get(const std::string &name)
{
	return m_resources.find(name)->second;
}

template <typename T, typename CT>
 void ResourcesManager<T, CT>::clean()
{
	for(auto & p : m_resources)
		CT::release(p.second);
	m_resources.clear();
}

template <typename T, typename CT>
 const std::string  &ResourcesManager<T, CT>::get(const T &resource) const
{
	for(typename std::map<std::string, T>::const_iterator it=m_resources.begin(); it != m_resources.end(); ++it)
		if(it->second == resource)
			return it->first;
	
	std::cout << "The resource isn't in this ResourceManager. This function return the first key std::string" << std::endl;
	return m_resources.begin()->first;
}

template <typename T, typename CT>
 bool ResourcesManager<T, CT>::exist(const std::string &name) const
{
	if(m_resources.find(name) == m_resources.end())
		return false;
	return true;
}

template <typename T, typename CT>
 bool ResourcesManager<T, CT>::exist(const T &resource) const
{
	for(typename std::map<std::string, T>::iterator it = m_resources.begin(); it != m_resources.end(); ++it)
		if(it == &resource)
			return true;
	return false;
}

template <typename T, typename CT>
 int ResourcesManager<T, CT>::getSize() const
{
	return m_resources.size();
}

#endif
